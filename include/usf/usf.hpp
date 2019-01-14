// ----------------------------------------------------------------------------
// DO NOT MANUALLY MODIFY THIS FILE, IT IS AUTO GENERATED USING A CMAKE SCRIPT!
// ----------------------------------------------------------------------------
// @file    usf.hpp
// @brief   usflib single header auto generated file.
// @date    14 January 2019
// ----------------------------------------------------------------------------
//
// μSF - Micro String Format v0.2.0 - https://github.com/hparracho/usflib
// Copyright (c) 2019 Helder Parracho (hparracho@gmail.com)
//
// See README.md file for additional credits and acknowledgments.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// ----------------------------------------------------------------------------

#ifndef USF_HPP
#define USF_HPP

// ----------------------------------------------------------------------------
// @file    usf_config.hpp
// @brief   usflib configuration header file.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_CONFIG_HPP
#define USF_CONFIG_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

// ----------------------------------------------------------------------------
// usflib configuration options
// ----------------------------------------------------------------------------

// Configuration of floating point support.
// USF_DISABLE_FLOAT_SUPPORT           : disables the support of floating point types (it will save considerable code size)

// Configuration of format output string termination option.
// USF_DISABLE_STRING_TERMINATION      : disables the null termination of the format output string

// Configuration of possible behavior when a condition is violated.
// USF_TERMINATE_ON_CONTRACT_VIOLATION : std::terminate() will be called (default)
// USF_ABORT_ON_CONTRACT_VIOLATION     : std::abort() will be called (more suitable for embedded platforms, maybe?)
// USF_THROW_ON_CONTRACT_VIOLATION     : an exception will be thrown


// ----------------------------------------------------------------------------
// Compiler version detection
// ----------------------------------------------------------------------------

// MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
// MSVC++ 14.1 _MSC_VER >= 1910 (Visual Studio 2017)
#if defined(_MSC_VER) && !defined(__clang__)
#  define USF_COMPILER_MSVC
#  define USF_MSVC_VERSION  (_MSC_VER / 10 - 10 * (5 + (_MSC_VER < 1900)))
#  if (USF_MSVC_VERSION < 140)
#    error usflib requires MSVC++ 14.0 or greater
#  endif
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.
#  define USF_CPLUSPLUS  (_MSC_VER <= 1900 ? 201103L : _MSVC_LANG)
#endif

#define USF_COMPILER_VERSION(major, minor, patch) (10 * (10 * (major) + (minor)) + (patch))

#if defined(__clang__)
#  define USF_COMPILER_CLANG
#  define USF_CLANG_VERSION  USF_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#  if (USF_CLANG_VERSION < 340)
#    error usflib requires Clang 3.4.0 or greater
#  endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
#  define USF_COMPILER_GCC
#  define USF_GCC_VERSION  USF_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#  if (USF_GCC_VERSION < 481)
#    error usflib requires GCC 4.8.1 or greater
#  endif
#endif


// ----------------------------------------------------------------------------
// C++ language version detection
// ----------------------------------------------------------------------------
#ifndef USF_CPLUSPLUS
#  define USF_CPLUSPLUS  __cplusplus
#endif

#define USF_CPP11_OR_GREATER  (USF_CPLUSPLUS >= 201103L)
#define USF_CPP14_OR_GREATER  (USF_CPLUSPLUS >= 201402L)
#define USF_CPP17_OR_GREATER  (USF_CPLUSPLUS >= 201703L)

#if !USF_CPP11_OR_GREATER
#error usflib requires compiler and library support \
for the ISO C++ 2011 standard. This support must be enabled \
with the -std=c++11 or -std=gnu++11 compiler options.
#endif

// C++14 features
#if USF_CPP14_OR_GREATER
#  define USF_CPP14_CONSTEXPR      constexpr
#  define USF_CPP14_CONSTEXPR_VAR  constexpr
#else
#  define USF_CPP14_CONSTEXPR
#  define USF_CPP14_CONSTEXPR_VAR  const
#endif

// C++17 features
#if USF_CPP17_OR_GREATER
#  define USF_CPP17_CONSTEXPR  constexpr
#else
#  define USF_CPP17_CONSTEXPR
#endif

// Fall through attribute
#if USF_CPP17_OR_GREATER
#  define USF_FALLTHROUGH  [[fallthrough]]
#else
#  if defined(USF_COMPILER_GCC) && (USF_GCC_VERSION >= 710)
#    define USF_FALLTHROUGH  [[gnu::fallthrough]]
#  elif defined(USF_COMPILER_CLANG)
#    define USF_FALLTHROUGH  [[clang::fallthrough]]
#  else
#    define USF_FALLTHROUGH  /*fall through*/
#  endif
#endif

// Always inline attribute
#if defined(USF_COMPILER_GCC) || defined(USF_COMPILER_CLANG)
#  define USF_ALWAYS_INLINE  [[gnu::always_inline]]
#elif defined(USF_COMPILER_MSVC)
#  define USF_ALWAYS_INLINE  __forceinline
#else
#  define USF_ALWAYS_INLINE  inline
#endif

// __has_include() support
#if defined(__has_include) && !defined(__INTELLISENSE__)
#  define USF_HAS_INCLUDE(x)  __has_include(x)
#else
#  define USF_HAS_INCLUDE(x)  0
#endif

// std::string_view support
#if USF_CPP17_OR_GREATER && USF_HAS_INCLUDE(<string_view>)
#  include <string_view>
#  define USF_STD_BASIC_STRING_VIEW  std::basic_string_view
#elif USF_CPP14_OR_GREATER && USF_HAS_INCLUDE(<experimental/string_view>)
#  include <experimental/string_view>
#  define USF_STD_BASIC_STRING_VIEW  std::experimental::basic_string_view
#endif

// char8_t support (C++20 only)
#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
#  define USF_CPP20_CHAR8_T_SUPPORT
#endif


// ----------------------------------------------------------------------------
// Target detection (maybe not the best way of doing it...)
// ----------------------------------------------------------------------------
#if (UINTPTR_MAX == UINT32_MAX)
#  define USF_TARGET_32_BITS  1
#elif (UINTPTR_MAX == UINT64_MAX)
#  define USF_TARGET_64_BITS  1
#else
#  error "usflib could not determine target architecture."
#endif


// ----------------------------------------------------------------------------
// Missing intrinsic functions definition for MSVC
// ----------------------------------------------------------------------------
#if defined(USF_COMPILER_MSVC)
#include <intrin.h>

#pragma intrinsic(_BitScanReverse, _BitScanReverse64)

int __builtin_clz(uint32_t value)
{
    unsigned long leading_zero = 0;
    return _BitScanReverse(&leading_zero, value) ? static_cast<int>(31 - leading_zero) : 32;
}

int __builtin_clzll(uint64_t value)
{
    unsigned long leading_zero = 0;
    return _BitScanReverse64(&leading_zero, value) ? static_cast<int>(63 - leading_zero) : 64;
}
#endif // defined(USF_COMPILER_MSVC)


// ----------------------------------------------------------------------------
// Error handling
// ----------------------------------------------------------------------------
// Two macros ensures any macro passed will
// be expanded before being stringified.
#define USF_STRINGIFY_DETAIL(x)  #x
#define USF_STRINGIFY(x)         USF_STRINGIFY_DETAIL(x)

#if defined(USF_THROW_ON_CONTRACT_VIOLATION)

namespace usf
{
namespace internal
{
template <typename Except>
[[noreturn]] USF_ALWAYS_INLINE constexpr
void throw_exception(const char* const msg)
{
    static_assert(std::is_convertible<Except, std::exception>::value,
                  "usf::throw_exception(): exception type should inherit from std::exception.");

    throw Except(msg);
}
} // namespace internal
} // namespace usf

#  define USF_CONTRACT_VIOLATION(except)  usf::internal::throw_exception<except>("Failure at " __FILE__ ", Line " USF_STRINGIFY(__LINE__))
#elif defined(USF_ABORT_ON_CONTRACT_VIOLATION)
#  define USF_CONTRACT_VIOLATION(except)  std::abort()
#else
#  define USF_CONTRACT_VIOLATION(except)  std::terminate()
#endif

#define USF_ENFORCE(cond, except)  ((!!(cond)) ? static_cast<void>(0) : USF_CONTRACT_VIOLATION(except))

#endif // USF_CONFIG_HPP


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


// ----------------------------------------------------------------------------
// @file    usf_string_span.hpp
// @brief   String span class (minimal implementation).
//          Intended to replace basic functionality of std::span throughout
//          the library. It uses a begin / end iterator approach instead of
//          the standard data pointer and size implementations.
// @date    14 January 2019
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
using WStringSpan = BasicStringSpan<wchar_t>;

#if defined(USF_CPP20_CHAR8_T_SUPPORT)
using U8StringSpan = BasicStringSpan<char8_t>;
#endif
using U16StringSpan = BasicStringSpan<char16_t>;
using U32StringSpan = BasicStringSpan<char32_t>;

using ByteStringSpan = BasicStringSpan<uint8_t>;

} // namespace usf

#endif // USF_STRING_SPAN_HPP


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


// ----------------------------------------------------------------------------
// @file    usf_integer.hpp
// @brief   Integer conversion and helper functions.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_INTEGER_HPP
#define USF_INTEGER_HPP

namespace usf
{
namespace internal
{

constexpr uint32_t pow10_uint32_lut[]
{
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000
};

constexpr uint64_t pow10_uint64_lut[]
{
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000,
    100000000000,
    1000000000000,
    10000000000000,
    100000000000000,
    1000000000000000,
    10000000000000000,
    100000000000000000,
    1000000000000000000,
    10000000000000000000U
};

constexpr char digits_hex_uppercase[]{"0123456789ABCDEF"};
constexpr char digits_hex_lowercase[]{"0123456789abcdef"};

class Integer
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC STATIC FUNCTIONS
        // --------------------------------------------------------------------

        // -------- POWERS OF 10 ----------------------------------------------
        static USF_CPP14_CONSTEXPR uint32_t pow10_uint32(const int index) noexcept
        {
            assert(index >= 0 && index < 10);

            return pow10_uint32_lut[index];
        }

        static USF_CPP14_CONSTEXPR uint64_t pow10_uint64(const int index) noexcept
        {
            assert(index >= 0 && index < 20);

            return pow10_uint64_lut[index];
        }

        // -------- COUNT DIGITS ----------------------------------------------
        // Based on the code from:
        // http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10
        // --------------------- ----------------------------------------------

        static USF_CPP14_CONSTEXPR int count_digits_dec(const uint32_t n) noexcept
        {
            if(n < 10) return 1;

            // The algorithm below doesn't work when `n` is 0 because:
            // 1. the result of __builtin_clz() is undefined if `n` is 0.
            // 2. the `pow10_uint32_lut` lookup table has the value 1 in
            //    the first element and not a 0 as the algorithm expects.
            // (both cases are covered by the previous if statement or
            //  by the slower commented OR operation below).

            // n = n | 1;

            const int t = (32 - __builtin_clz(n)) * 1233 >> 12;
            return t - (n < pow10_uint32_lut[t]) + 1;
        }

        static USF_CPP14_CONSTEXPR int count_digits_dec(const uint64_t n) noexcept
        {
            if(n <= std::numeric_limits<uint32_t>::max())
            {
                return count_digits_dec(static_cast<uint32_t>(n));
            }

            // The algorithm below doesn't work when `n` is 0 because:
            // 1. the result of __builtin_clzll() is undefined if `n` is 0.
            // 2. the `pow10_uint64_lut` lookup table has the value 1 in
            //    the first element and not a 0 as the algorithm expects.
            // (both cases are covered by the previous if statement or
            //  by the slower commented OR operation below).

            // n = n | 1;

            const int t = (64 - __builtin_clzll(n)) * 1233 >> 12;
            return t - (n < pow10_uint64_lut[t]) + 1;
        }

        static USF_CPP14_CONSTEXPR int count_digits_bin(const uint32_t n) noexcept
        {
            // The result of __builtin_clz() is undefined if `n` is 0.
            return (n < 2) ? 1 : (32 - __builtin_clz(n));
        }

        static USF_CPP14_CONSTEXPR int count_digits_bin(const uint64_t n) noexcept
        {
            // The result of __builtin_clzll() is undefined if `n` is 0.
            return (n < 2) ? 1 : (64 - __builtin_clzll(n));
        }

        template <typename T,
                  typename std::enable_if<std::numeric_limits<T>::is_integer && std::is_unsigned<T>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR int count_digits_oct(T n) noexcept
        {
            int digits = 1;
            while((n >>= 3U) != 0) { ++digits; }
            return digits;
        }

        template <typename T,
                  typename std::enable_if<std::numeric_limits<T>::is_integer && std::is_unsigned<T>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR int count_digits_hex(T n) noexcept
        {
            int digits = 1;
            while((n >>= 4U) != 0) { ++digits; }
            return digits;
        }

        // -------- FAST DIVIDE BY 10 -----------------------------------------
        // Based on the code from Hacker's Delight:
        // http://www.hackersdelight.org/divcMore.pdf
        // --------------------- ----------------------------------------------
        static USF_CPP14_CONSTEXPR uint32_t div10(const uint32_t n) noexcept
        {
#if defined(__arm__)
            uint32_t q = (n >> 1) + (n >> 2);
            q += (q >> 4);
            q += (q >> 8);
            q += (q >> 16);
            q >>= 3;

            const uint32_t r = n - (q << 3) - (q << 1);

            return q + ((r + 6) >> 4);
            // return q + (r > 9);
#else
            return n / 10;
#endif
        }

        static USF_CPP14_CONSTEXPR uint64_t div10(const uint64_t n) noexcept
        {
#if defined(__arm__)
            uint64_t q = (n >> 1) + (n >> 2);
            q += (q >> 4);
            q += (q >> 8);
            q += (q >> 16);
            q += (q >> 32);
            q >>= 3;

            const uint64_t r = n - (q << 3) - (q << 1);

            return q + ((r + 6) >> 4);
            // return q + (r > 9);
#else
            return n / 10;
#endif
        }

        // -------- CONVERTERS ------------------------------------------------
        // The following converters write the value from back to front.
        // It is assumed that the pointer `dst` is already placed at the
        // position after the last character. The pointer position is
        // calculated using the corresponding count_digits_xxx() functions.

        // Example:
        // value ->  1234
        // array -> [........]
        // dst   ->      ^

        // -------- DECIMAL CONVERSION ----------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_dec(CharT* dst, uint32_t value) noexcept
        {
            do
            {
                const uint32_t v = value;
                value = div10(value);
                *(--dst) = static_cast<CharT>('0' + (v - (value * 10)));
            }while(value);
        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_dec(CharT* dst, uint64_t value) noexcept
        {
            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value = div10(value);
                *(--dst) = static_cast<CharT>('0' + (v - (value * 10)));
            }

            convert_dec(dst, static_cast<uint32_t>(value));
        }

        // -------- BINARY CONVERSION -----------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_bin(CharT* dst, uint32_t value) noexcept
        {
            do
            {
                const uint32_t v = value;
                value >>= 1U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 1U)));
            }while(value);
        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_bin(CharT* dst, uint64_t value) noexcept
        {
            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value >>= 1U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 1U)));
            }

            convert_bin(dst, static_cast<uint32_t>(value));
        }

        // -------- OCTAL CONVERSION ------------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_oct(CharT* dst, uint32_t value) noexcept
        {
            do
            {
                const uint32_t v = value;
                value >>= 3U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 3U)));
            }while(value);
        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_oct(CharT* dst, uint64_t value) noexcept
        {
            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value >>= 3U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 3U)));
            }

            convert_oct(dst, static_cast<uint32_t>(value));
        }

        // -------- HEXADECIMAL CONVERSION ------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_hex(CharT* dst, uint32_t value, const bool uppercase) noexcept
        {
            const char* digits = uppercase ? digits_hex_uppercase : digits_hex_lowercase;

            do
            {
                const uint32_t v = value;
                value >>= 4U;
                *(--dst) = static_cast<CharT>(digits[v - (value << 4U)]);
            }while(value);

        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_hex(CharT* dst, uint64_t value, const bool uppercase) noexcept
        {
            const char* digits = uppercase ? digits_hex_uppercase : digits_hex_lowercase;

            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value >>= 4U;
                *(--dst) = static_cast<CharT>(digits[v - (value << 4U)]);
            }

            convert_hex(dst, static_cast<uint32_t>(value), uppercase);
        }
};

} // namespace internal
} // namespace usf

#endif // USF_INTEGER_HPP


// ----------------------------------------------------------------------------
// @file    usf_float.hpp
// @brief   Floating point conversion and helper functions. Naive and limited
//          implementation with the usual precision/rounding errors (good for now).
// @date    07 January 2019
// ----------------------------------------------------------------------------

#if !defined(USF_DISABLE_FLOAT_SUPPORT)

#ifndef USF_FLOAT_HPP
#define USF_FLOAT_HPP

namespace usf
{
namespace internal
{

class Float
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC STATIC FUNCTIONS
        // --------------------------------------------------------------------

        template <typename CharT> static USF_CPP14_CONSTEXPR
        int convert(CharT* const significand, int& exponent,
                    double value, const bool format_fixed, const int precision) noexcept
        {
            uint64_t ipart = 0;
            uint64_t fpart = 0;

            int ipart_digits = 0;
            int fpart_digits = 0;

            int fpart_padding = 0;

            if(value < 1)
            {
                // Negative exponent

                value *= 1e19;

                fpart = static_cast<uint64_t>(value);
                fpart_digits = Integer::count_digits_dec(fpart);

                exponent = fpart_digits - 20;

                fpart_padding = -exponent - 1;

                //if(!format_fixed && precision > 19 - fpart_padding)
                if(fpart_padding > 14 - precision)
                {
                    fpart = static_cast<uint64_t>(value * static_cast<double>(Integer::pow10_uint64(fpart_padding)));
                    fpart_digits = Integer::count_digits_dec(fpart);
                }
            }
            else
            {
                // Positive exponent

                ipart = static_cast<uint64_t>(value);
                ipart_digits = Integer::count_digits_dec(ipart);

                fpart = static_cast<uint64_t>((value - static_cast<double>(ipart)) * 1e14);
                fpart_digits = Integer::count_digits_dec(fpart);

                exponent = ipart_digits - 1;

                fpart_padding = 14 - fpart_digits;
            }

            const auto round_index = 1 + precision + (format_fixed ? exponent : 0);

            if(round_index < 0)
            {
                // Specified precision higher than converted value.
                // Should print all zeros. Bail!
                significand[0] = '0';
                exponent = 0;
                return 1;
            }

            CharT* it = significand;

            if(ipart != 0)
            {
                it += ipart_digits;
                Integer::convert_dec(it, ipart);
            }

            if(fpart != 0)
            {
                if(ipart != 0)
                {
                    CharTraits::assign(it, '0', fpart_padding);
                }

                it += fpart_digits;
                Integer::convert_dec(it, fpart);
            }

            const auto significand_size = remove_trailing_zeros(significand, it);

            if(significand_size <= round_index)
            {
                // Rounding not needed. Bail!
                return significand_size;
            }

            //Round to the specified precision.
            return round(significand, significand_size, exponent, format_fixed, round_index);
        }

        private:

        // --------------------------------------------------------------------
        // PRIVATE STATIC FUNCTIONS
        // --------------------------------------------------------------------

        template <typename CharT> static USF_CPP14_CONSTEXPR
        int round(CharT* const significand, const int significand_size, int& exponent,
                  const bool format_fixed, const int round_index) noexcept
        {
            CharT* it = significand + round_index;

            bool round_up = false;

            if(round_index == significand_size - 1)
            {
                // Round the last digit of the significand buffer.
                // It can simultaneously be the first one if the
                // significant buffer has only one digit.

                const bool prev_digit_odd = (round_index > 0) ? (('0' - *(it - 1)) & 1) != 0 : false;

                if(*it > '5' || (*it == '5' && prev_digit_odd))
                {
                    // Round up if digit is:
                    // 1) greater than 5
                    //    e.g. 2.6 -> 3
                    // 2) exactly 5 and previous digit is odd
                    //    e.g. 2.5 -> 2
                    //    e.g. 3.5 -> 3
                    round_up = true;
                }
            }
            else if(*it >= '5')
            {
                // Round any digit except the last one. Since the trailing zeros were
                // removed, we only need to test if the digit is at least '5' because it
                // is granted that other non-zero digits are present after this position.
                round_up = true;
            }

            if(round_up)
            {
                bool carry = false;

                if(round_index > 0)
                {
                    --it;

                    do
                    {
                        if(*it < '9')
                        {
                            carry = false;
                            ++(*it);
                        }
                        else
                        {
                            carry = true;
                            *it = '0';
                        }
                    }while(--it >= significand && carry);
                }
                else
                {
                    carry = true;
                }

                // Buffer termination is not necessary since the caller functions
                // rely on the returned size and not on null terminator.

                if(carry)
                {
                    significand[0] = '1';
                    ++exponent;
                    return 1;
                }
            }
            else if(round_index == 0)
            {
                significand[0] = '0';
                exponent = 0;
                return 1;
            }

            // Do not remove the trailing zeros if format is fixed.
            if(format_fixed) { return round_index; }

            return remove_trailing_zeros(significand, significand + round_index);
        }

        // Evaluates the range [first, last), truncates all the trailing zeros and return the
        // new range size. Keeps always at least 1 element of the range (even if it is zero).
        template <typename CharT> static USF_CPP14_CONSTEXPR
        int remove_trailing_zeros(const CharT* const first, const CharT* last) noexcept
        {
            while((last - 1) > first && *(last - 1) == '0') { --last; }

            // Buffer termination is not really necessary since the caller
            // functions rely on the returned size and not on null terminator.

            return static_cast<int>(last - first);
        }
};

} // namespace internal
} // namespace usf

#endif // USF_FLOAT_HPP
#endif // !defined(USF_DISABLE_FLOAT_SUPPORT)


// ----------------------------------------------------------------------------
// @file    usf_arg_format.hpp
// @brief   Argument format parser class.
// @date    07 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARG_FORMAT_HPP
#define USF_ARG_FORMAT_HPP

namespace usf
{
namespace internal
{

template <typename CharT>
class ArgFormat
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC TYPE ALIASES
        // --------------------------------------------------------------------

        using iterator       = CharT*;
        using const_iterator = const CharT*;

        // --------------------------------------------------------------------
        // PUBLIC DEFINITIONS
        // --------------------------------------------------------------------

        enum class Align : uint8_t
        {
            kNone    = (0U << 1U),
            kLeft    = (1U << 1U),
            kRight   = (2U << 1U),
            kCenter  = (3U << 1U),
            kNumeric = (4U << 1U)
        };

        enum class Sign : uint8_t
        {
            kNone    = (0U << 4U),
            kMinus   = (1U << 4U),
            kPlus    = (2U << 4U),
            kSpace   = (3U << 4U)
        };

        enum class Type : uint8_t
        {
            kNone,
            kChar,
            kIntegerDec,
            kIntegerHex,
            kIntegerOct,
            kIntegerBin,
            kPointer,
            kFloatFixed,
            kFloatScientific,
            kFloatGeneral,
            kString,
            kInvalid
        };

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        USF_CPP14_CONSTEXPR ArgFormat(usf::BasicStringView<CharT>& fmt, const int arg_count)
        {
            const_iterator it = fmt.cbegin();

            USF_ENFORCE(*it == '{', std::runtime_error);

            // Iterator is placed at "{" character, so advance it.
            ++it;

            // Parse argument index
            if(*it >= '0' && *it <= '9')
            {
                // Index limited to `arg_count` value.
                m_index = static_cast<int8_t>(parse_positive_small_int(it, arg_count));
            }

            if(*it == ':' && *(it + 1) != '}')
            {
                // A format spec is expected next...

                //Remove the empty format flag
                m_flags = Flags::kNone;

                // Advance ':' character
                ++it;

                // Try to parse alignment flag at second character of format spec.
                m_flags = parse_align_flag(*(it + 1));

                if(m_flags != Flags::kNone)
                {
                    // Alignment flag present at second character of format spec.
                    // Should also have a fill character at the first character.

                    // The fill character can be any character except '{' or '}'.
                    USF_ENFORCE(*it != '{' && *it != '}', std::runtime_error);

                    m_fill_char = *it;
                    it += 2;
                }
                else
                {
                    // Alignment flag not present at the second character of format spec.
                    // Try to parse the alignment flag at the first character instead...
                    m_flags = parse_align_flag(*it);

                    if(m_flags != Flags::kNone)
                    {
                        ++it;
                    }
                }

                // Parse sign flag
                switch(*it)
                {
                    case '-': m_flags |= Flags::kSignMinus; ++it; break;
                    case '+': m_flags |= Flags::kSignPlus;  ++it; break;
                    case ' ': m_flags |= Flags::kSignSpace; ++it; break;
                    default :                                     break;
                }

                // Parse hash flag
                if(*it == '#')
                {
                    m_flags |= Flags::kHash;
                    ++it;
                }

                bool fill_zero = false;

                // Parse fill zero flag
                if(*it == '0')
                {
                    fill_zero = true;
                    ++it;
                }

                // Parse width
                if(*it >= '0' && *it <= '9')
                {
                    // Limit width to 255 characters
                    m_width = parse_positive_small_int(it, 255);
                }

                // Parse precision
                if(*it == '.')
                {
                    ++it;

                    // Check for a missing/invalid precision specifier.
                    USF_ENFORCE(*it >= '0' && *it <= '9', std::runtime_error);

                    m_precision = static_cast<int8_t>(parse_positive_small_int(it, 127));
                }

                // Parse type
                if(*it != '}')
                {
                    switch(*it++)
                    {
                        case 'c': m_type = Type::kChar;            break;

                        case 'd': m_type = Type::kIntegerDec;      break;

                        case 'X': m_flags |= Flags::kUppercase;    USF_FALLTHROUGH;
                        case 'x': m_type = Type::kIntegerHex;      break;

                        case 'o': m_type = Type::kIntegerOct;      break;

                        case 'B': m_flags |= Flags::kUppercase;    USF_FALLTHROUGH;
                        case 'b': m_type = Type::kIntegerBin;      break;

                        case 'P': m_flags |= Flags::kUppercase;    USF_FALLTHROUGH;
                        case 'p': m_type = Type::kPointer;         break;

                        case 'F': m_flags |= Flags::kUppercase;    USF_FALLTHROUGH;
                        case 'f': m_type = Type::kFloatFixed;      break;

                        case 'E': m_flags |= Flags::kUppercase;    USF_FALLTHROUGH;
                        case 'e': m_type = Type::kFloatScientific; break;

                        case 'G': m_flags |= Flags::kUppercase;    USF_FALLTHROUGH;
                        case 'g': m_type = Type::kFloatGeneral;    break;

                        case 's': m_type = Type::kString;          break;

                        default : m_type = Type::kInvalid;         break;
                    }

                    USF_ENFORCE(m_type != Type::kInvalid, std::runtime_error);
                }

                // Validate the read format spec!

                if(fill_zero)
                {
                    // Fill zero flag has precedence over any other alignment and fill character.
                    m_flags = static_cast<uint8_t>((m_flags & (~Flags::kAlignBitmask)) | Flags::kAlignNumeric);
                    m_fill_char = '0';
                }

                if(align() == Align::kNumeric)
                {
                    // Numeric alignment are only valid for numeric and pointer types.
                    USF_ENFORCE(type_is_numeric() || type_is_pointer(), std::runtime_error);
                }

                if(sign() != Sign::kNone)
                {
                    // Sign is only valid for numeric types.
                    USF_ENFORCE(type_is_numeric(), std::runtime_error);
                }

                if(hash())
                {
                    // Alternative format is valid for hexadecimal (including
                    // pointers), octal, binary and all floating point types.
                    USF_ENFORCE(type_allow_hash(), std::runtime_error);
                }

                if(m_precision != -1)
                {
                    // Precision is only valid for floating point and string types.
                    USF_ENFORCE(type_is_float() || type_is_string(), std::runtime_error);
                }
            }

            // Test for unterminated argument format spec.
            USF_ENFORCE(it < fmt.cend() && *it++ == '}', std::runtime_error);

            fmt.remove_prefix(it - fmt.cbegin());
        }

        // Writes the alignment (sign, prefix and fill before) for any
        // argument type. Returns the fill counter to write after argument.
        USF_CPP14_CONSTEXPR int write_alignment(iterator& it, const_iterator end,
                                                int digits, const bool negative) const
        {
            digits += sign_width(negative) + prefix_width();

            int fill_after = 0;

            if(width() <= digits)
            {
                USF_ENFORCE(it + digits < end, std::runtime_error);
                write_sign(it, negative);
                write_prefix(it);
            }
            else
            {
                USF_ENFORCE(it + width() < end, std::runtime_error);

                int fill_count = width() - digits;

                const Align al = align();

                if(al == Align::kLeft)
                {
                    fill_after = fill_count;
                }
                else if(al == Align::kCenter)
                {
                    fill_after = fill_count - (fill_count / 2);
                    fill_count /= 2;
                }

                if(al != Align::kLeft && al != Align::kNumeric)
                {
                    // None (default right), Right or Center alignment
                    CharTraits::assign(it, fill_char(), fill_count);
                }

                write_sign(it, negative);
                write_prefix(it);

                if(al == Align::kNumeric)
                {
                    CharTraits::assign(it, fill_char(), fill_count);
                }
            }

            return fill_after;
        }

        inline constexpr CharT fill_char() const noexcept { return m_fill_char;                    }
        inline constexpr Type  type     () const noexcept { return m_type;                         }
        inline constexpr int   width    () const noexcept { return static_cast<int>(m_width    );  }
        inline constexpr int   precision() const noexcept { return static_cast<int>(m_precision);  }
        inline constexpr int   index    () const noexcept { return static_cast<int>(m_index    );  }

        inline constexpr Align align() const noexcept { return Align(m_flags & Flags::kAlignBitmask); }
        inline constexpr Sign  sign () const noexcept { return Sign (m_flags & Flags::kSignBitmask ); }

        inline constexpr bool  is_empty () const noexcept { return (m_flags & Flags::kEmpty    ) != 0; }
        inline constexpr bool  hash     () const noexcept { return (m_flags & Flags::kHash     ) != 0; }
        inline constexpr bool  uppercase() const noexcept { return (m_flags & Flags::kUppercase) != 0; }

        inline constexpr bool type_is_none   () const noexcept { return m_type == Type::kNone;    }
        inline constexpr bool type_is_char   () const noexcept { return m_type == Type::kChar;    }
        inline constexpr bool type_is_string () const noexcept { return m_type == Type::kString;  }
        inline constexpr bool type_is_pointer() const noexcept { return m_type == Type::kPointer; }

        inline constexpr bool type_is_integer() const noexcept { return m_type >= Type::kIntegerDec && m_type <= Type::kIntegerBin;   }
        inline constexpr bool type_is_float  () const noexcept { return m_type >= Type::kFloatFixed && m_type <= Type::kFloatGeneral; }
        inline constexpr bool type_is_numeric() const noexcept { return m_type >= Type::kIntegerDec && m_type <= Type::kFloatGeneral; }

        inline constexpr bool type_is_integer_dec() const noexcept { return m_type == Type::kIntegerDec; }
        inline constexpr bool type_is_integer_hex() const noexcept { return m_type == Type::kIntegerHex; }
        inline constexpr bool type_is_integer_oct() const noexcept { return m_type == Type::kIntegerOct; }
        inline constexpr bool type_is_integer_bin() const noexcept { return m_type == Type::kIntegerBin; }

        inline constexpr bool type_is_float_fixed     () const noexcept { return m_type == Type::kFloatFixed;      }
        inline constexpr bool type_is_float_scientific() const noexcept { return m_type == Type::kFloatScientific; }
        inline constexpr bool type_is_float_general   () const noexcept { return m_type == Type::kFloatGeneral;    }

        inline constexpr bool type_allow_hash() const noexcept
        {
            // Alternative format is valid for hexadecimal (including
            // pointers), octal, binary and all floating point types.
            return m_type >= Type::kIntegerHex && m_type <= Type::kFloatGeneral;
        }

        inline USF_CPP14_CONSTEXPR void default_align_left() noexcept
        {
            if((m_flags & Flags::kAlignBitmask) == Flags::kAlignNone)
            {
                m_flags |= Flags::kAlignLeft;
            }
        }

    private:

        // --------------------------------------------------------------------
        // PRIVATE DEFINITIONS
        // --------------------------------------------------------------------

        enum Flags : uint8_t
        {
            kNone         = (0U << 0U),

            kEmpty        = (1U << 0U),

            kAlignNone    = (0U << 1U),
            kAlignLeft    = (1U << 1U),
            kAlignRight   = (2U << 1U),
            kAlignCenter  = (3U << 1U),
            kAlignNumeric = (4U << 1U),
            kAlignBitmask = (7U << 1U),

            kSignNone     = (0U << 4U),
            kSignMinus    = (1U << 4U),
            kSignPlus     = (2U << 4U),
            kSignSpace    = (3U << 4U),
            kSignBitmask  = (3U << 4U),

            kHash         = (1U << 6U),

            kUppercase    = (1U << 7U)
        };

        // --------------------------------------------------------------------
        // PRIVATE MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        inline constexpr int sign_width(const bool negative) const noexcept
        {
            return (!negative && sign() <= Sign::kMinus) ? 0 : 1;
        }

        inline constexpr int prefix_width() const noexcept
        {
            // Alternative format is valid for hexadecimal (including
            // pointers), octal, binary and all floating point types.
            return (!hash() || type_is_float()) ? 0 : type_is_integer_oct() ? 1 : 2;
        }

        USF_CPP14_CONSTEXPR void write_sign(iterator& it, const bool negative) const noexcept
        {
            if(negative)
            {
                *it++ = '-';
            }
            else
            {
                const Sign s = sign();

                if(s != Sign::kNone)
                {
                    if(s == Sign::kPlus )
                    {
                        *it++ = '+';
                    }
                    else if(s == Sign::kSpace)
                    {
                        *it++ = ' ';
                    }
                }
            }
        }

        USF_CPP14_CONSTEXPR void write_prefix(iterator& it) const noexcept
        {
            // Alternative format is valid for hexadecimal (including
            // pointers), octal, binary and all floating point types.
            if(hash() && !type_is_float())
            {
                *it++ = '0';

                if(type_is_integer_bin())
                {
                    *it++ = uppercase() ? 'B' : 'b';
                }
                else if(type_is_integer_hex() || type_is_pointer())
                {
                    *it++ = uppercase() ? 'X' : 'x';
                }
            }
        }

        // --------------------------------------------------------------------
        // PRIVATE STATIC FUNCTIONS
        // --------------------------------------------------------------------

        // Parses the input as a positive integer that fits into a `uint8_t` type. This
        // function assumes that the first character is a digit and terminates parsing
        // at the presence of the first non-digit character or when value overflows.
        static USF_CPP14_CONSTEXPR
        uint8_t parse_positive_small_int(const_iterator& it, const int max_value)
        {
            assert(max_value < 256);

            int value = 0;

            do
            {
                value = (value * 10) + static_cast<int>(*it++ - '0');

                // Check for overflow
                USF_ENFORCE(value <= max_value, std::runtime_error);
            }while(*it >= '0' && *it <= '9');

            return static_cast<uint8_t>(value);
        }

        static USF_CPP14_CONSTEXPR uint8_t parse_align_flag(const CharT ch) noexcept
        {
            switch(ch)
            {
                case '<': return Flags::kAlignLeft;    break;
                case '>': return Flags::kAlignRight;   break;
                case '^': return Flags::kAlignCenter;  break;
                case '=': return Flags::kAlignNumeric; break;
                default : return Flags::kNone;         break;
            }
        }

        // --------------------------------------------------------------------
        // PRIVATE MEMBER VARIABLES
        // --------------------------------------------------------------------

        CharT   m_fill_char = ' ';
        Type    m_type      = Type::kNone;
        uint8_t m_flags     = Flags::kEmpty;
        uint8_t m_width     =  0;
         int8_t m_precision = -1;
         int8_t m_index     = -1;
};

} // namespace internal
} // namespace usf

#endif // USF_ARG_FORMAT_HPP


// ----------------------------------------------------------------------------
// @file    usf_arg_custom_type.hpp
// @brief   User-defined custom type class (using the delegate idiom).
// @date    07 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARG_CUSTOM_TYPE_HPP
#define USF_ARG_CUSTOM_TYPE_HPP

namespace usf
{
namespace internal
{

template<typename CharT>
class ArgCustomType
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        USF_CPP14_CONSTEXPR ArgCustomType() = delete;

        template<typename T, BasicStringSpan<CharT>(*func)(BasicStringSpan<CharT>, const T&)>
        static USF_CPP14_CONSTEXPR ArgCustomType create(const T* obj)
        {
            return ArgCustomType(invoke_func<T, func>, obj);
        }

        USF_CPP14_CONSTEXPR BasicStringSpan<CharT> operator()(BasicStringSpan<CharT> dst) const
        {
            return m_function(dst, m_obj);
        }

    private:

        // --------------------------------------------------------------------
        // PRIVATE TYPE ALIASES
        // --------------------------------------------------------------------

        using FunctionType = BasicStringSpan<CharT>(*)(BasicStringSpan<CharT>, const void*);

        // --------------------------------------------------------------------
        // PRIVATE MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        USF_CPP14_CONSTEXPR ArgCustomType(const FunctionType func, const void* obj)
            : m_function{func}, m_obj{obj} {}

        template<typename T, BasicStringSpan<CharT>(*func)(BasicStringSpan<CharT>, const T&)>
        static USF_CPP14_CONSTEXPR BasicStringSpan<CharT> invoke_func(BasicStringSpan<CharT> dst, const void* obj)
        {
            return func(dst, *static_cast<const T*>(obj));
        }

        // --------------------------------------------------------------------
        // PRIVATE VARIABLES
        // --------------------------------------------------------------------

        const FunctionType m_function{nullptr};
        const void*        m_obj     {nullptr};
};

} // namespace internal
} // namespace usf

#endif // USF_ARG_CUSTOM_TYPE_HPP


// ----------------------------------------------------------------------------
// @file    usf_argument.hpp
// @brief   Argument format processor class.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_ARGUMENT_HPP
#define USF_ARGUMENT_HPP

namespace usf
{
namespace internal
{

template <typename CharT>
class Argument
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC TYPE ALIASES
        // --------------------------------------------------------------------

        using       iterator =       CharT*;
        using const_iterator = const CharT*;

        using Format = ArgFormat<CharT>;

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        constexpr Argument() = delete;

        constexpr Argument(const bool value) noexcept
            : m_bool(value), m_type_id(TypeId::kBool) {}

        constexpr Argument(const CharT value) noexcept
            : m_char(value), m_type_id(TypeId::kChar) {}

        constexpr Argument(const int32_t value) noexcept
            : m_int32(value), m_type_id(TypeId::kInt32) {}

        constexpr Argument(const uint32_t value) noexcept
            : m_uint32(value), m_type_id(TypeId::kUint32) {}

        constexpr Argument(const int64_t value) noexcept
            : m_int64(value), m_type_id(TypeId::kInt64) {}

        constexpr Argument(const uint64_t value) noexcept
            : m_uint64(value), m_type_id(TypeId::kUint64) {}

        constexpr Argument(const void* value) noexcept
            : m_pointer(reinterpret_cast<std::uintptr_t>(value)), m_type_id(TypeId::kPointer) {}

#if !defined(USF_DISABLE_FLOAT_SUPPORT)
        constexpr Argument(const double value) noexcept
            : m_float(value), m_type_id(TypeId::kFloat) {}
#endif
        constexpr Argument(const usf::BasicStringView<CharT> value) noexcept
            : m_string(value), m_type_id(TypeId::kString) {}

        constexpr Argument(const ArgCustomType<CharT> value) noexcept
            : m_custom(value), m_type_id(TypeId::kCustom) {}

        USF_CPP14_CONSTEXPR void format(usf::BasicStringSpan<CharT>& dst, Format& format) const
        {
            iterator it = dst.begin();

            switch(m_type_id)
            {
                case TypeId::kBool:    format_bool   (it, dst.end(), format, m_bool   ); break;
                case TypeId::kChar:    format_char   (it, dst.end(), format, m_char   ); break;
                case TypeId::kInt32:   format_integer(it, dst.end(), format, m_int32  ); break;
                case TypeId::kUint32:  format_integer(it, dst.end(), format, m_uint32 ); break;
                case TypeId::kInt64:   format_integer(it, dst.end(), format, m_int64  ); break;
                case TypeId::kUint64:  format_integer(it, dst.end(), format, m_uint64 ); break;
                case TypeId::kPointer: format_pointer(it, dst.end(), format, m_pointer); break;
#if !defined(USF_DISABLE_FLOAT_SUPPORT)
                case TypeId::kFloat:   format_float  (it, dst.end(), format, m_float  ); break;
#endif
                case TypeId::kString:  format_string (it, dst.end(), format, m_string ); break;
                case TypeId::kCustom:  USF_ENFORCE(format.is_empty(), std::runtime_error);
                                       it = m_custom(dst).end();                         break;
            }

            dst.remove_prefix(it - dst.begin());
        }

    private:

        // --------------------------------------------------------------------
        // PRIVATE STATIC FUNCTIONS
        // --------------------------------------------------------------------

        static USF_CPP14_CONSTEXPR void format_bool(iterator& it, const_iterator end,
                                                    const Format& format, const bool value)
        {
            if(format.type_is_none())
            {
                format_string(it, end, format, value ? "true" : "false", value ? 4 : 5);
            }
            else if(format.type_is_integer())
            {
                format_integer(it, end, format, static_cast<uint32_t>(value));
            }
            else
            {
                // Argument type / format mismatch
                USF_CONTRACT_VIOLATION(std::runtime_error);
            }
        }

        static USF_CPP14_CONSTEXPR void format_char(iterator& it, const_iterator end,
                                                    Format& format, const CharT value)
        {
            if(format.type_is_none() || format.type_is_char())
            {
                // Characters and strings align to left by default.
                format.default_align_left();

                const int fill_after = format.write_alignment(it, end, 1, false);
                *it++ = value;
                CharTraits::assign(it, format.fill_char(), fill_after);
            }
            else if(format.type_is_integer())
            {
                format_integer(it, end, format, static_cast<int32_t>(value));
            }
            else
            {
                // Argument type / format mismatch
                USF_CONTRACT_VIOLATION(std::runtime_error);
            }
        }

        template <typename T, typename std::enable_if<std::is_signed<T>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR void format_integer(iterator& it, const_iterator end,
                                                       const Format& format, const T value)
        {
            using unsigned_type = typename std::make_unsigned<T>::type;

            const bool negative = (value < 0);
            const auto uvalue = static_cast<unsigned_type>(negative ? -value : value);

            format_integer(it, end, format, uvalue, negative);
        }

        template <typename T, typename std::enable_if<std::is_unsigned<T>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR void format_integer(iterator& it, const_iterator end, const Format& format,
                                                       const T value, const bool negative = false)
        {
            int fill_after = 0;

            if(format.type_is_none() || format.type_is_integer_dec())
            {
                const auto digits = Integer::count_digits_dec(value);
                fill_after = format.write_alignment(it, end, digits, negative);
                it += digits;
                Integer::convert_dec(it, value);
            }
            else if(format.type_is_integer_hex())
            {
                const auto digits = Integer::count_digits_hex(value);
                fill_after = format.write_alignment(it, end, digits, negative);
                it += digits;
                Integer::convert_hex(it, value, format.uppercase());
            }
            else if(format.type_is_integer_oct())
            {
                const auto digits = Integer::count_digits_oct(value);
                fill_after = format.write_alignment(it, end, digits, negative);
                it += digits;
                Integer::convert_oct(it, value);
            }
            else if(format.type_is_integer_bin())
            {
                const auto digits = Integer::count_digits_bin(value);
                fill_after = format.write_alignment(it, end, digits, negative);
                it += digits;
                Integer::convert_bin(it, value);
            }
            else
            {
                // Argument type / format mismatch
                USF_CONTRACT_VIOLATION(std::runtime_error);
            }

            CharTraits::assign(it, format.fill_char(), fill_after);
        }

        static USF_CPP14_CONSTEXPR void format_pointer(iterator& it, const_iterator end,
                                                       const Format& format, const std::uintptr_t value)
        {
            if(format.type_is_none() || format.type_is_pointer())
            {
#if defined(USF_TARGET_64_BITS)
                const auto ivalue = static_cast<uint64_t>(value);
#else
                const auto ivalue = static_cast<uint32_t>(value);
#endif
                const auto digits = Integer::count_digits_hex(ivalue);
                const auto fill_after = format.write_alignment(it, end, digits, false);
                it += digits;
                Integer::convert_hex(it, ivalue, format.uppercase());
                CharTraits::assign(it, format.fill_char(), fill_after);
            }
            else
            {
                // Argument type / format mismatch
                USF_CONTRACT_VIOLATION(std::runtime_error);
            }
        }

#if !defined(USF_DISABLE_FLOAT_SUPPORT)
        static USF_CPP14_CONSTEXPR
        void format_float(iterator& it, const_iterator end, const Format& format, double value)
        {
            // Test for argument type / format match
            USF_ENFORCE(format.type_is_none() || format.type_is_float(), std::runtime_error);

            if(std::isnan(value))
            {
                format_string(it, end, format, format.uppercase() ? "NAN" : "nan", 3);
            }
            else
            {
                const bool negative = std::signbit(value);

                if(std::isinf(value))
                {
                    format_string(it, end, format, format.uppercase() ? "INF" : "inf", 3, negative);
                }
                else
                {
                    if(negative) { value = -value; }

                    struct fp_t
                    {
                        union
                        {
                            double   d;
                            uint64_t i;
                        };
                    };

                    const fp_t fp_value{{value}};

                    if(fp_value.i == 0)
                    {
                        format_float_zero(it, end, format, negative);
                    }
                    else if(value >= 1E-19 && value <= 1.8446744E19)
                    {
                        int precision = format.precision();

                        if(precision < 0) { precision = 6; }

                        bool format_fixed = format.type_is_float_fixed();
                        bool significant_figures = false;

                        if(format.type_is_none() || format.type_is_float_general())
                        {
                            // General format
                            significant_figures = true;

                            if(precision > 0) { --precision; }
                        }

                        CharT significand[36]{}; // 34 characters should be the maximum size needed
                        int exponent = 0;

                        const auto significand_size = Float::convert(significand, exponent, value, format_fixed, precision);

                        if(significant_figures)
                        {
                            if(exponent >= -4 && exponent <= precision)
                            {
                                format_fixed = true;
                            }

                            if(!format.hash()) { precision = significand_size - 1; }

                            if(format_fixed)
                            {
                                precision -= exponent;
                            }
                        }

                        int fill_after = 0;

                        if(format_fixed)
                        {
                            // Fixed point format
                            if(exponent < 0)
                            {
                                // 0.<0>SIGNIFICAND[0:N]<0>

                                const int full_digits = precision + 2;
                                fill_after = format.write_alignment(it, end, full_digits, negative);

                                *it++ = '0';
                                *it++ = '.';

                                int zero_digits = -exponent - 1;
                                CharTraits::assign(it, '0', zero_digits);
                                CharTraits::copy(it, significand, significand_size);

                                // Padding is needed if conversion function removes trailing zeros.
                                zero_digits = precision - zero_digits - significand_size;
                                CharTraits::assign(it, '0', zero_digits);
                            }
                            else
                            {
                                const int full_digits = exponent + 1 + precision + static_cast<int>(precision > 0 || format.hash());
                                fill_after = format.write_alignment(it, end, full_digits, negative);

                                const int ipart_digits = exponent + 1;

                                if(ipart_digits >= significand_size)
                                {
                                    // [SIGNIFICAND]<0><.><0>

                                    CharTraits::copy(it, significand, significand_size);
                                    CharTraits::assign(it, '0', ipart_digits - significand_size);

                                    if(precision > 0 || format.hash())
                                    {
                                        *it++ = '.';
                                    }

                                    if(precision > 0)
                                    {
                                        CharTraits::assign(it, '0', precision);
                                    }
                                }
                                else
                                {
                                    // SIGNIFICAND[0:x].SIGNIFICAND[x:N]<0>

                                    CharTraits::copy(it, significand, ipart_digits);
                                    *it++ = '.';

                                    const int copy_size = significand_size - ipart_digits;
                                    CharTraits::copy(it, significand + ipart_digits, copy_size);

                                    // Padding is needed if conversion function removes trailing zeros.
                                    CharTraits::assign(it, '0', precision - copy_size);
                                }
                            }
                        }
                        else
                        {
                            // Exponent format
                            // SIGNIFICAND[0:N]<.>eEXP
                            // OR
                            // SIGNIFICAND[0].SIGNIFICAND[1:N]<0>eEXP

                            const int full_digits = 5 + precision + static_cast<int>(precision > 0 || format.hash());
                            fill_after = format.write_alignment(it, end, full_digits, negative);

                            *it++ = *significand;

                            if(precision > 0 || format.hash())
                            {
                                *it++ = '.';

                                const int copy_size = significand_size - 1;
                                CharTraits::copy(it, significand + 1, copy_size);
                                CharTraits::assign(it, '0', precision - copy_size);
                            }

                            write_float_exponent(it, exponent, format.uppercase());
                        }

                        CharTraits::assign(it, format.fill_char(), fill_after);

                        //it += sprintf(it, "[%s] Size:%d Exponent:%d Precision:%d Fixed:%d->", significand, significand_size, exponent, precision, int(format_fixed));
                    }
                    else
                    {
                        format_string(it, end, format, format.uppercase() ? "OVF" : "ovf", 3, negative);
                    }
                }
            }
        }

        static USF_CPP14_CONSTEXPR
        void write_float_exponent(iterator& it, int exponent, const bool uppercase) noexcept
        {
            *it++ = uppercase ? 'E' : 'e';

            if(exponent < 0)
            {
                exponent = -exponent;
                *it++ = '-';
            }
            else
            {
                *it++ = '+';
            }

            // No point in making a proper integer to string
            // conversion for exponent since we only support [e-19; e19].
            assert(exponent <= 19);

            if(exponent < 10)
            {
                *it++ = '0';
                *it++ = static_cast<CharT>('0' + exponent);
            }
            else
            {
                *it++ = '1';
                *it++ = static_cast<CharT>('0' + (exponent - 10));
            }
        }

        static USF_CPP14_CONSTEXPR
        void format_float_zero(iterator& it, const_iterator end, const Format& format, const bool negative)
        {
            int precision = 0;

            if(format.type_is_float_fixed() || format.type_is_float_scientific())
            {
                precision = format.precision();
            }

            int digits = 1;

            if(precision > 0) { digits += precision + 1; }

            if(format.type_is_float_scientific()) { digits += 4; }

            const int fill_after = format.write_alignment(it, end, digits, negative);

            *it++ = '0';

            if(precision > 0)
            {
                *it++ = '.';
                CharTraits::assign(it, '0', precision);
            }

            if(format.type_is_float_scientific())
            {
                *it++ = format.uppercase() ? 'E' : 'e';
                *it++ = '+';
                *it++ = '0';
                *it++ = '0';
            }

            CharTraits::assign(it, format.fill_char(), fill_after);
        }
#endif // !defined(USF_DISABLE_FLOAT_SUPPORT)

        static USF_CPP14_CONSTEXPR void format_string(iterator& it, const_iterator end,
                                                      Format& format, const usf::BasicStringView<CharT>& str)
        {
            // Test for argument type / format match
            USF_ENFORCE(format.type_is_none() || format.type_is_string(), std::runtime_error);

            // Characters and strings align to left by default.
            format.default_align_left();

            // If precision is specified use it up to string size.
            const int str_length = (format.precision() == -1)
                                 ? static_cast<int>(str.size())
                                 : std::min(static_cast<int>(format.precision()), static_cast<int>(str.size()));

            format_string(it, end, format, str.data(), str_length);
        }

        template <typename CharSrc,
                  typename std::enable_if<std::is_convertible<CharSrc, CharT>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR void format_string(iterator& it, const_iterator end,
                                                      const Format& format, const CharSrc* str,
                                                      const int str_length, const bool negative = false)
        {
            const int fill_after = format.write_alignment(it, end, str_length, negative);

            CharTraits::copy(it, str, str_length);
            CharTraits::assign(it, format.fill_char(), fill_after);
        }

        // --------------------------------------------------------------------
        // PRIVATE MEMBER VARIABLES
        // --------------------------------------------------------------------

        enum class TypeId
        {
            kBool = 0,
            kChar,
            kInt32,
            kUint32,
            kInt64,
            kUint64,
            kPointer,
#if !defined(USF_DISABLE_FLOAT_SUPPORT)
            kFloat,
#endif
            kString,
            kCustom
        };

        union
        {
            bool                            m_bool;
            CharT                           m_char;
            int32_t                         m_int32;
            uint32_t                        m_uint32;
            int64_t                         m_int64;
            uint64_t                        m_uint64;
            std::uintptr_t                  m_pointer;
#if !defined(USF_DISABLE_FLOAT_SUPPORT)
            double                          m_float;
#endif
            usf::BasicStringView<CharT>     m_string;
            ArgCustomType<CharT>            m_custom;
        };

        TypeId                              m_type_id;
};




// Boolean
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const bool arg)
{
    return arg;
}

// Character (char)
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const char arg)
{
    return static_cast<CharT>(arg);
}

// Character (CharT != char)
template <typename CharT, typename std::enable_if<!std::is_same<CharT, char>::value, bool>::type = true>
inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const CharT arg)
{
    return arg;
}

// 8 bit signed integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const int8_t arg)
{
    return static_cast<int32_t>(arg);
}

// 8 bit unsigned integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const uint8_t arg)
{
    return static_cast<uint32_t>(arg);
}

// 16 bit signed integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const int16_t arg)
{
    return static_cast<int32_t>(arg);
}

// 16 bit unsigned integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const uint16_t arg)
{
    return static_cast<uint32_t>(arg);
}

// 32 bit signed integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const int arg)
{
    return static_cast<int32_t>(arg);
}

// 32 bit unsigned integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const unsigned int arg)
{
    return static_cast<uint32_t>(arg);
}

#if (__LONG_MAX__ != __LONG_LONG_MAX__)

// 32 bit signed integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const long int arg)
{
    return static_cast<int32_t>(arg);
}

// 32 bit unsigned integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const unsigned long int arg)
{
    return static_cast<uint32_t>(arg);
}

#endif // (__LONG_MAX__ != __LONG_LONG_MAX__)

// 64 bit signed integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const int64_t arg)
{
    if(arg >= std::numeric_limits<int32_t>::min()
    && arg <= std::numeric_limits<int32_t>::max())
    {
        return static_cast<int32_t>(arg);
    }

    return arg;
}

// 64 bit unsigned integer
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const uint64_t arg)
{
    if(arg <= std::numeric_limits<uint32_t>::max())
    {
        return static_cast<uint32_t>(arg);
    }

    return arg;
}

// Pointer (void*)
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(void* arg)
{
    return arg;
}

// Pointer (const void*)
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const void* arg)
{
    return arg;
}

#if !defined(USF_DISABLE_FLOAT_SUPPORT)
// Floating point (float)
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(float arg)
{
    return static_cast<double>(arg);
}

// Floating point (double)
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(double arg)
{
    return arg;
}
#endif // !defined(USF_DISABLE_FLOAT_SUPPORT)

// String (convertible to string view)
template <typename CharT, typename T,
          typename std::enable_if<std::is_convertible<T, usf::BasicStringView<CharT>>::value, bool>::type = true>
inline USF_CPP14_CONSTEXPR Argument<CharT> make_argument(const T& arg)
{
    return usf::BasicStringView<CharT>(arg);
}

} // namespace internal

// User-defined custom type formatter forward declaration
template <typename CharT, typename T>
struct Formatter
{
    static BasicStringSpan<CharT> format_to(BasicStringSpan<CharT>, const T&);
};

namespace internal
{

// User-defined custom type
template <typename CharT, typename T,
          typename std::enable_if<!std::is_convertible<T, usf::BasicStringView<CharT>>::value, bool>::type = true>
inline USF_CPP14_CONSTEXPR Argument<CharT> make_argument(const T& arg)
{
    using _T = typename std::decay<decltype(arg)>::type;

    return ArgCustomType<CharT>::template create<_T, &usf::Formatter<CharT, _T>::format_to>(&arg);
}

} // namespace internal
} // namespace usf

#endif // USF_ARGUMENT_HPP


// ----------------------------------------------------------------------------
// @file    usf_main.hpp
// @brief   Main process functions and public interface.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_MAIN_HPP
#define USF_MAIN_HPP

namespace usf
{
namespace internal
{

template <typename CharT> USF_CPP14_CONSTEXPR
void parse_format_string(usf::BasicStringSpan<CharT>& str, usf::BasicStringView<CharT>& fmt)
{
          CharT* str_it = str.begin();
    const CharT* fmt_it = fmt.cbegin();

    while(fmt_it < fmt.cend() && str_it < str.end())
    {
        if(*fmt_it == '{' )
        {
            if(*(fmt_it + 1) == '{')
            {
                // Found '{{' escape character, skip the first and copy the second '{'.
                ++fmt_it;
                *str_it++ = *fmt_it++;
            }
            else
            {
                // A type format should follow...
                break;
            }
        }
        else if(*fmt_it == '}')
        {
            USF_ENFORCE(*(fmt_it + 1) == '}', std::runtime_error);

            // Found '}}' escape character, skip the first and copy the second '}'.
            ++fmt_it;
            *str_it++ = *fmt_it++;
        }
        else
        {
            // Copy literal text
            *str_it++ = *fmt_it++;
        }
    }

    //USF_ENFORCE(str_it < str.end(), std::runtime_error);

    str.remove_prefix(str_it - str.begin());
    fmt.remove_prefix(fmt_it - fmt.cbegin());
}




template <typename CharT> USF_CPP14_CONSTEXPR
void process(usf::BasicStringSpan<CharT>& str, usf::BasicStringView<CharT>& fmt,
             const Argument<CharT>* const args, const int arg_count)
{
    // Argument's sequential index
    int arg_seq_index = 0;

    parse_format_string(str, fmt);

    while(!fmt.empty())
    {
        ArgFormat<CharT> format(fmt, arg_count);

        // Determine which argument index to use, sequential or positional.
        int arg_index = format.index();

        if(arg_index < 0)
        {
            USF_ENFORCE(arg_seq_index < arg_count, std::runtime_error);
            arg_index = arg_seq_index++;
        }

        args[arg_index].format(str, format);

        parse_format_string(str, fmt);
    }
}

} // namespace internal




template <typename CharT, typename... Args> USF_CPP14_CONSTEXPR
BasicStringSpan<CharT> basic_format_to(BasicStringSpan<CharT> str, BasicStringView<CharT> fmt)
{
    auto str_begin = str.begin();

    internal::parse_format_string(str, fmt);

    USF_ENFORCE(fmt.empty(), std::runtime_error);

#if !defined(USF_DISABLE_STRING_TERMINATION)
    // If not disabled in configuration, null terminate the resulting string.
    str[0] = CharT{};
#endif

    // Return a string span to the resulting string
    return BasicStringSpan<CharT>(str_begin, str.begin());
}

template <typename CharT, typename... Args> USF_CPP14_CONSTEXPR
BasicStringSpan<CharT> basic_format_to(BasicStringSpan<CharT> str, BasicStringView<CharT> fmt, Args&&... args)
{
    // Nobody should be that crazy, still... it costs nothing to be sure!
    static_assert(sizeof...(Args) < 128, "usf::basic_format_to(): crazy number of arguments supplied!");

    auto str_begin = str.begin();

    const internal::Argument<CharT> arguments[sizeof...(Args)]{internal::make_argument<CharT>(args)...};

    internal::process(str, fmt, arguments, static_cast<int>(sizeof...(Args)));

#if !defined(USF_DISABLE_STRING_TERMINATION)
    // If not disabled in configuration, null terminate the resulting string.
    str[0] = CharT{};
#endif

    // Return a string span to the resulting string
    return BasicStringSpan<CharT>(str_begin, str.begin());
}

template <typename CharT, typename... Args> USF_CPP14_CONSTEXPR
CharT* basic_format_to(CharT* str, const std::ptrdiff_t str_count, BasicStringView<CharT> fmt, Args&&... args)
{
    return basic_format_to(BasicStringSpan<CharT>(str, str_count), fmt, args...).end();
}




// ----------------------------------------------------------------------------
// Formats a char string 
// ---------------------------------------------------------------------------
template <typename... Args> USF_CPP14_CONSTEXPR
StringSpan format_to(StringSpan str, StringView fmt, Args&&... args)
{
    return basic_format_to(str, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
char* format_to(char* str, const std::ptrdiff_t str_count, StringView fmt, Args&&... args)
{
    return basic_format_to(str, str_count, fmt, args...);
}

// ----------------------------------------------------------------------------
// Formats a wchar_t string 
// ---------------------------------------------------------------------------
template <typename... Args> USF_CPP14_CONSTEXPR
WStringSpan format_to(WStringSpan str, WStringView fmt, Args&&... args)
{
    return basic_format_to(str, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
wchar_t* format_to(wchar_t* str, const std::ptrdiff_t str_count, WStringView fmt, Args&&... args)
{
    return basic_format_to(str, str_count, fmt, args...);
}

// ----------------------------------------------------------------------------
// Formats a char8_t string 
// ---------------------------------------------------------------------------
#if defined(USF_CPP20_CHAR8_T_SUPPORT)
template <typename... Args> USF_CPP14_CONSTEXPR
U8StringSpan format_to(U8StringSpan str, U8StringView fmt, Args&&... args)
{
    return basic_format_to(str, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
char8_t* format_to(char8_t* str, const std::ptrdiff_t str_count, U8StringView fmt, Args&&... args)
{
    return basic_format_to(str, str_count, fmt, args...);
}
#endif // defined(USF_CPP20_CHAR8_T_SUPPORT)

// ----------------------------------------------------------------------------
// Formats a char16_t string 
// ---------------------------------------------------------------------------
template <typename... Args> USF_CPP14_CONSTEXPR
U16StringSpan format_to(U16StringSpan str, U16StringView fmt, Args&&... args)
{
    return basic_format_to(str, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
char16_t* format_to(char16_t* str, const std::ptrdiff_t str_count, U16StringView fmt, Args&&... args)
{
    return basic_format_to(str, str_count, fmt, args...);
}

// ----------------------------------------------------------------------------
// Formats a char32_t string 
// ---------------------------------------------------------------------------
template <typename... Args> USF_CPP14_CONSTEXPR
U32StringSpan format_to(U32StringSpan str, U32StringView fmt, Args&&... args)
{
    return basic_format_to(str, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
char32_t* format_to(char32_t* str, const std::ptrdiff_t str_count, U32StringView fmt, Args&&... args)
{
    return basic_format_to(str, str_count, fmt, args...);
}

// ----------------------------------------------------------------------------
// Formats a byte string as char string 
// ----------------------------------------------------------------------------
template <typename... Args> USF_CPP14_CONSTEXPR
ByteStringSpan format_to(ByteStringSpan str, StringView fmt, Args&&... args)
{
    static_assert(CHAR_BIT == 8, "usf::format_to(): invalid char size.");
    char *end = basic_format_to(reinterpret_cast<char*>(str.data()), str.size(), fmt, args...);

    return ByteStringSpan(str.begin(), reinterpret_cast<uint8_t*>(end));
}

template <typename... Args> USF_CPP14_CONSTEXPR
uint8_t* format_to(uint8_t* str, const std::ptrdiff_t str_count, StringView fmt, Args&&... args)
{
    static_assert(CHAR_BIT == 8, "usf::format_to(): invalid char size.");
    return reinterpret_cast<uint8_t*>(basic_format_to(reinterpret_cast<char*>(str), str_count, fmt, args...));
}

} // namespace usf

#endif // USF_MAIN_HPP

#endif // USF_HPP
