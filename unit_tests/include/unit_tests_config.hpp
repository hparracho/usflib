
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest.h"


#define USF_THROW_ON_CONTRACT_VIOLATION
//#define USF_DISABLE_FLOAT_SUPPORT
//#define USF_SINGLE_HEADER

#ifdef USF_SINGLE_HEADER
#include "usf/usf.hpp"
#else
#include "usf/develop/usf_config.hpp"
#include "usf/develop/usf_traits.hpp"
#include "usf/develop/usf_string_span.hpp"
#include "usf/develop/usf_string_view.hpp"
#include "usf/develop/usf_integer.hpp"
#include "usf/develop/usf_float.hpp"
#include "usf/develop/usf_arg_format.hpp"
#include "usf/develop/usf_arg_custom_type.hpp"
#include "usf/develop/usf_argument.hpp"
#include "usf/develop/usf_main.hpp"
#endif

#if USF_CPP14_OR_GREATER
#  define TEST_CONSTEXPR constexpr
#  define TEST_STATIC_ASSERT(cond) static_assert((cond), "")
#else
#  define TEST_CONSTEXPR
#  define TEST_STATIC_ASSERT(cond) assert(cond)
#endif

#define USF_TEST_BASIC_TYPES
#define USF_TEST_FORMAT_SPEC
#define USF_TEST_POSITIONAL_ARGS
#define USF_TEST_CUSTOM_TYPES
//#define USF_TEST_FLOATING_POINT
#define USF_TEST_BENCHMARKS
#define USF_TEST_BENCHMARK_PRINTF
//#define USF_TEST_BENCHMARK_FMT

#include <ctime>
#include <iostream>
