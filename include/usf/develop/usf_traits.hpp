// ----------------------------------------------------------------------------
// @file    usf_traits.hpp
// @brief   Traits classes.
//          NB: usf::CharTraits class has the same purpose of the
//          std::char_traits class but is not compatible and cannot be
//          interchanged. Different interface and different implementation.
//          Intended for internal use only!
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_TRAITS_HPP
#define USF_TRAITS_HPP

namespace usf
{
namespace internal
{

// ----------------------------------------------------------------------------
// Custom char traits
// ----------------------------------------------------------------------------

class CharTraits
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC STATIC FUNCTIONS
        // --------------------------------------------------------------------

        template <typename CharDst, typename CharSrc,
                  typename std::enable_if<std::is_convertible<CharSrc, CharDst>::value, bool>::type = true>
        USF_ALWAYS_INLINE static USF_CPP14_CONSTEXPR
        void assign(CharDst*& dst, CharSrc ch, std::ptrdiff_t count) noexcept
        {
            while((count--) > 0) { *dst++ = static_cast<CharDst>(ch); }
        }

        template <typename CharDst, typename CharSrc,
                  typename std::enable_if<std::is_convertible<CharSrc, CharDst>::value, bool>::type = true>
        USF_ALWAYS_INLINE static USF_CPP14_CONSTEXPR
        void copy(CharDst*& dst, const CharSrc* src, std::ptrdiff_t count) noexcept
        {
            while((count--) > 0) { *dst++ = static_cast<CharDst>(*src++); }
        }

        template <typename CharT> USF_ALWAYS_INLINE static USF_CPP14_CONSTEXPR
        std::ptrdiff_t length(const CharT* str) noexcept
        {
            const CharT* str_begin = str;

            while(*str != CharT{}) { ++str; }

            return str - str_begin;
        }
};


// ----------------------------------------------------------------------------
// Custom type traits
// ----------------------------------------------------------------------------

template <typename T>
struct always_false : std::false_type {};

} // namespace internal
} // namespace usf

#endif // USF_TRAITS_HPP
