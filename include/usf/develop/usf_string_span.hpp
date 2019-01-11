// ----------------------------------------------------------------------------
// @file    usf_string_span.hpp
// @brief   String span class (minimal implementation).
//          Intended to replace basic functionality of std::span throughout
//          the library. It uses a begin / end iterator approach instead of
//          the standard data pointer and size implementations.
// @date    11 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_STRING_SPAN_HPP
#define USF_STRING_SPAN_HPP

namespace usf
{

template <typename CharT>
class BasicStringSpan
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC TYPE ALIASES
        // --------------------------------------------------------------------

        using char_type       = CharT;
        using size_type       = std::ptrdiff_t;
        using reference       = char_type&;
        using const_reference = const char_type&;
        using pointer         = char_type*;
        using const_pointer   = const char_type*;
        using iterator        = pointer;
        using const_iterator  = const_pointer;

        // --------------------------------------------------------------------
        // TEMPLATE PARAMETERS VALIDATION
        // --------------------------------------------------------------------

        static_assert(std::is_trivial<CharT>::value && std::is_standard_layout<CharT>::value,
                      "usf::BasicStringSpan: CharT must be a POD type (both trivial and standard-layout).");

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        // -------- CONSTRUCTORS ----------------------------------------------

        USF_CPP14_CONSTEXPR BasicStringSpan() noexcept = delete;

        USF_CPP14_CONSTEXPR BasicStringSpan(const BasicStringSpan&) noexcept = default;
        USF_CPP14_CONSTEXPR BasicStringSpan(BasicStringSpan&&) noexcept = default;
#if 0
        template <std::size_t N> // N includes the null terminator!
        USF_CPP14_CONSTEXPR BasicStringSpan(char_type (&str)[N]) noexcept
            : m_begin{str}, m_end{str + N - 1}
        {}
#endif
        USF_CPP14_CONSTEXPR BasicStringSpan(pointer str) noexcept
            : m_begin{str}, m_end{str + internal::CharTraits::length(str)}
        {}

        USF_CPP14_CONSTEXPR BasicStringSpan(pointer str, const size_type str_count)
            : m_begin{str}, m_end{str + str_count}
        {
            USF_ENFORCE(str_count >= 0, std::runtime_error);
        }

        USF_CPP14_CONSTEXPR BasicStringSpan(iterator first, iterator last)
            : m_begin{first}, m_end{last}
        {
            USF_ENFORCE(first <= last, std::runtime_error);
        }

        template <std::size_t N> USF_CPP14_CONSTEXPR
        BasicStringSpan(std::array<CharT, N>& array) noexcept
            : m_begin{array.begin()}, m_end{array.end()}
        {}

        // -------- ASSIGNMENT ------------------------------------------------

        USF_CPP14_CONSTEXPR BasicStringSpan& operator = (const BasicStringSpan&) noexcept = default;
        USF_CPP14_CONSTEXPR BasicStringSpan& operator = (BasicStringSpan&&) noexcept = default;

        // -------- ELEMENT ACCESS --------------------------------------------

        // Returns a reference to the character at specified location `pos`.
        // Bounds checking is performed.
        inline USF_CPP14_CONSTEXPR const_reference at(const size_type pos) const
        {
            USF_ENFORCE(pos >= 0 && pos < size(), std::out_of_range);
            return m_begin[pos];
        }

        inline USF_CPP14_CONSTEXPR reference at(const size_type pos)
        {
            USF_ENFORCE(pos >= 0 && pos < size(), std::out_of_range);
            return m_begin[pos];
        }

        // Returns a reference to the character at specified location `pos`.
        // No bounds checking is performed.
        inline USF_CPP14_CONSTEXPR const_reference operator [] (const size_type pos) const noexcept { return m_begin[pos]; }
        inline USF_CPP14_CONSTEXPR       reference operator [] (const size_type pos)       noexcept { return m_begin[pos]; }

        // Returns reference to the first character of the sequence.
        inline USF_CPP14_CONSTEXPR const_reference front() const noexcept { assert(!empty()); return m_begin[0]; }
        inline USF_CPP14_CONSTEXPR       reference front()       noexcept { assert(!empty()); return m_begin[0]; }

        // Returns reference to the last character of the sequence.
        inline USF_CPP14_CONSTEXPR const_reference back() const noexcept { assert(!empty()); return *(m_end - 1); }
        inline USF_CPP14_CONSTEXPR       reference back()       noexcept { assert(!empty()); return *(m_end - 1); }

        // Returns a pointer to the beginning of the sequence.
        inline USF_CPP14_CONSTEXPR const_pointer data() const noexcept { return m_begin; }
        inline USF_CPP14_CONSTEXPR       pointer data()       noexcept { return m_begin; }

#if defined(USF_STD_BASIC_STRING_VIEW)
        // Conversion to std::basic_string view.
        template <typename Traits = std::char_traits<CharT>>
        inline USF_CPP14_CONSTEXPR operator USF_STD_BASIC_STRING_VIEW<CharT, Traits>() const noexcept
        {
            return USF_STD_BASIC_STRING_VIEW<CharT, Traits>{data(), static_cast<std::size_t>(size())};
        }
#endif
        // -------- ITERATORS -------------------------------------------------

        // Returns an iterator to the first character of the sequence.
        inline USF_CPP14_CONSTEXPR const_iterator cbegin() const noexcept { return m_begin; }
        inline USF_CPP14_CONSTEXPR const_iterator  begin() const noexcept { return m_begin; }
        inline USF_CPP14_CONSTEXPR       iterator  begin()       noexcept { return m_begin; }

        // Returns an iterator to the character following the last character of the sequence.
        // This character acts as a placeholder, attempting to access it results in undefined behavior.
        inline USF_CPP14_CONSTEXPR const_iterator cend() const noexcept { return m_end; }
        inline USF_CPP14_CONSTEXPR const_iterator  end() const noexcept { return m_end; }
        inline USF_CPP14_CONSTEXPR       iterator  end()       noexcept { return m_end; }

        // -------- CAPACITY --------------------------------------------------

        // Checks if the sequence has no characters, i.e. whether begin() == end().
        inline USF_CPP14_CONSTEXPR bool empty() const noexcept { return (size() == 0); }

        // Returns the number of characters in the sequence, i.e. the distance between begin() and end().
        inline USF_CPP14_CONSTEXPR size_type size()   const noexcept { return static_cast<size_type>(m_end - m_begin); }
        inline USF_CPP14_CONSTEXPR size_type length() const noexcept { return static_cast<size_type>(m_end - m_begin); }

        // -------- MODIFIERS -------------------------------------------------

        // Moves the start of the sequence forward by `n` characters.
        // The behavior is undefined if n > size().
        inline USF_CPP14_CONSTEXPR void remove_prefix(const size_type n) noexcept
        {
            m_begin += n;
        }

        // Moves the end of the sequence back by `n` characters.
        // The behavior is undefined if n > size().
        inline USF_CPP14_CONSTEXPR void remove_suffix(const size_type n) noexcept
        {
            m_end -= n;
        }

    private:

        // --------------------------------------------------------------------
        // PRIVATE MEMBER VARIABLES
        // --------------------------------------------------------------------

        iterator m_begin{nullptr};
        iterator m_end  {nullptr};
};

using StringSpan = BasicStringSpan<char>;
using ByteStringSpan = BasicStringSpan<uint8_t>;

} // namespace usf

#endif // USF_STRING_SPAN_HPP
