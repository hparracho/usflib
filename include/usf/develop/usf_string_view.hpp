// ----------------------------------------------------------------------------
// @file    usf_string_view.hpp
// @brief   String view class (minimal implementation).
//          Intended to replace basic functionality of std::string_view
//          throughout the library. It uses a begin / end iterator approach
//          instead of the standard data pointer and size implementations.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_STRING_VIEW_HPP
#define USF_STRING_VIEW_HPP

namespace usf
{

template <typename CharT>
class BasicStringView
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC TYPE ALIASES
        // --------------------------------------------------------------------

        using char_type       = CharT;
        using size_type       = std::ptrdiff_t; // Not std::size_t
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
                      "usf::BasicStringView: CharT must be a POD type (both trivial and standard-layout).");

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        // -------- CONSTRUCTORS ----------------------------------------------

        USF_CPP14_CONSTEXPR BasicStringView() noexcept = delete;

        USF_CPP14_CONSTEXPR BasicStringView(const BasicStringView&) noexcept = default;
        USF_CPP14_CONSTEXPR BasicStringView(BasicStringView&&) noexcept = default;
#if 0
        template <std::size_t N> // N includes the null terminator!
        USF_CPP14_CONSTEXPR BasicStringView(const char_type (&str)[N]) noexcept
            : m_begin{str}, m_end{str + N - 1}
        {}
#endif
        USF_CPP14_CONSTEXPR BasicStringView(const_pointer str) noexcept
            : m_begin{str}, m_end{str + internal::CharTraits::length(str)}
        {}

        USF_CPP14_CONSTEXPR BasicStringView(const_pointer str, const size_type str_count)
            : m_begin{str}, m_end{str + str_count}
        {
            USF_ENFORCE(str_count >= 0, std::runtime_error);
        }

        USF_CPP14_CONSTEXPR BasicStringView(const_iterator first, const_iterator last)
            : m_begin{first}, m_end{last}
        {
            USF_ENFORCE(first <= last, std::runtime_error);
        }

#if defined(USF_STD_BASIC_STRING_VIEW)
        template <typename Traits = std::char_traits<CharT>>
        USF_CPP14_CONSTEXPR BasicStringView(const USF_STD_BASIC_STRING_VIEW<CharT, Traits> view)
            : m_begin{view.cbegin()}, m_end{view.cend()}
        {}
#endif
        // -------- ASSIGNMENT ------------------------------------------------

        USF_CPP14_CONSTEXPR BasicStringView& operator = (const BasicStringView&) noexcept = default;
        USF_CPP14_CONSTEXPR BasicStringView& operator = (BasicStringView&&) noexcept = default;

        // -------- ELEMENT ACCESS --------------------------------------------

        // Returns a reference to the character at specified location `pos`.
        // Bounds checking is performed.
        inline USF_CPP14_CONSTEXPR const_reference at(const size_type pos) const
        {
            USF_ENFORCE(pos >= 0 && pos < size(), std::out_of_range);
            return m_begin[pos];
        }

        // Returns a reference to the character at specified location `pos`.
        // No bounds checking is performed.
        inline USF_CPP14_CONSTEXPR const_reference operator [] (const size_type pos) const noexcept { return m_begin[pos]; }

        // Returns reference to the first character of the sequence.
        inline USF_CPP14_CONSTEXPR const_reference front() const noexcept { assert(!empty()); return m_begin[0]; }

        // Returns reference to the last character of the sequence.
        inline USF_CPP14_CONSTEXPR const_reference back() const noexcept { assert(!empty()); return *(m_end - 1); }

        // Returns a pointer to the beginning of the sequence.
        inline USF_CPP14_CONSTEXPR const_pointer data() const noexcept { return m_begin; }

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
        inline USF_CPP14_CONSTEXPR  const_iterator cbegin() const noexcept { return m_begin; }
        inline USF_CPP14_CONSTEXPR  const_iterator  begin() const noexcept { return m_begin; }

        // Returns an iterator to the character following the last character of the sequence.
        // This character acts as a placeholder, attempting to access it results in undefined behavior.
        inline USF_CPP14_CONSTEXPR  const_iterator cend() const noexcept { return m_end; }
        inline USF_CPP14_CONSTEXPR  const_iterator  end() const noexcept { return m_end; }

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

        const_iterator m_begin{nullptr};
        const_iterator m_end  {nullptr};
};

using StringView = BasicStringView<char>;
using WStringView = BasicStringView<wchar_t>;

#if defined(USF_CPP20_CHAR8_T_SUPPORT)
using U8StringView = BasicStringView<char8_t>;
#endif
using U16StringView = BasicStringView<char16_t>;
using U32StringView = BasicStringView<char32_t>;

using ByteStringView = BasicStringView<uint8_t>;

} // namespace usf

#endif // USF_STRING_VIEW_HPP
