// ----------------------------------------------------------------------------
// @file    usf_config.hpp
// @brief   usflib configuration header file.
// @date    07 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_CONFIG_HPP
#define USF_CONFIG_HPP

#include <cassert>
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
