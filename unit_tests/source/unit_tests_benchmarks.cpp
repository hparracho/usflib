
#include "unit_tests_config.hpp"

#if defined(USF_TEST_BENCHMARKS)

#include <chrono>

#if defined(USF_TEST_BENCHMARK_FMT)
#define FMT_HEADER_ONLY
#define FMT_STATIC_THOUSANDS_SEPARATOR '\''
#include "fmt/format.h"
#endif

// ----------------------------------------------------------------------------
// BENCHMARK
// ----------------------------------------------------------------------------
TEST_CASE("usf::format_to, benchmark")
{
    auto ms_min_usf1 = std::numeric_limits<int64_t>::max();
    auto ms_min_usf2 = std::numeric_limits<int64_t>::max();
    auto ms_min_usf3 = std::numeric_limits<int64_t>::max();

#if defined(USF_TEST_BENCHMARK_PRINTF)
    auto ms_min_std1 = std::numeric_limits<int64_t>::max();
    auto ms_min_std2 = std::numeric_limits<int64_t>::max();
    auto ms_min_std3 = std::numeric_limits<int64_t>::max();
#endif

#if defined(USF_TEST_BENCHMARK_FMT)
    auto ms_min_fmt1 = std::numeric_limits<int64_t>::max();
    auto ms_min_fmt2 = std::numeric_limits<int64_t>::max();
    auto ms_min_fmt3 = std::numeric_limits<int64_t>::max();
#endif

    const int max_runs = 10;
    const int max_iterations = 2000000;

    for(int r = 0; r < max_runs; ++r)
    {
        std::cout << "TESTRUN: " << r << '\n';

        // uSF usf::format_to
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                usf::format_to(str, 128, "{:f}|{:08x}|{:e}|{}|{:016x}|{:c}|%|{{|}}",
                               1.234, 56789, -0.00393333, "str", 1000, 'X');
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "usf:: " << str << " ->  " << ms << "ms\n";
            ms_min_usf1 = std::min(ms_min_usf1, ms);
        }
#if defined(USF_TEST_BENCHMARK_PRINTF)
        // Standard sprintf
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                sprintf(str, "%f|%08x|%e|%s|%016x|%c|%%|{|}",
                        1.234, 56789, -0.00393333, "str", 1000, 'X');
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "std:: " << str << " -> " << ms << "ms\n";
            ms_min_std1 = std::min(ms_min_std1, ms);
        }
#endif
#if defined(USF_TEST_BENCHMARK_FMT)
        // {fmt} fmt::format_to
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                auto res = fmt::format_to(str, "{:f}|{:08x}|{:e}|{}|{:016x}|{:c}|%|{{|}}",
                                          1.234, 56789, -0.00393333, "str", 1000, 'X');
                *res = '\0';
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "fmt:: " << str << " -> " << ms << "ms\n";
            ms_min_fmt1 = std::min(ms_min_fmt1, ms);
        }
#endif

        // uSF usf::format_to
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                usf::format_to(str, 128, "{:d}|{:x}|{:o}", __UINT32_MAX__, __UINT32_MAX__, __UINT32_MAX__);
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "usf:: " << str << " -> " << ms << "ms\n";
            ms_min_usf2 = std::min(ms_min_usf2, ms);
        }
#if defined(USF_TEST_BENCHMARK_PRINTF)
        // Standard sprintf
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                sprintf(str, "%u|%x|%o", __UINT32_MAX__, __UINT32_MAX__, __UINT32_MAX__);
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "std:: " << str << " -> " << ms << "ms\n";
            ms_min_std2 = std::min(ms_min_std2, ms);
        }
#endif
#if defined(USF_TEST_BENCHMARK_FMT)
        // {fmt} fmt::format_to
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                auto res = fmt::format_to(str, "{:d}|{:x}|{:o}", __UINT32_MAX__, __UINT32_MAX__, __UINT32_MAX__);
                *res = '\0';
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "fmt:: " << str << " -> " << ms << "ms\n";
            ms_min_fmt2 = std::min(ms_min_fmt2, ms);
        }
#endif

        // uSF usf::format_to
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                usf::format_to(str, 128, "{:d}|{:x}|{:o}", __UINT64_MAX__, __UINT64_MAX__, __UINT64_MAX__);
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "usf:: " << str << " -> " << ms << "ms\n";
            ms_min_usf3 = std::min(ms_min_usf3, ms);
        }
#if defined(USF_TEST_BENCHMARK_PRINTF)
        // Standard sprintf
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                sprintf(str, "%llu|%llx|%llo", __UINT64_MAX__, __UINT64_MAX__, __UINT64_MAX__);
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "std:: " << str << " -> " << ms << "ms\n";
            ms_min_std3 = std::min(ms_min_std3, ms);
        }
#endif
#if defined(USF_TEST_BENCHMARK_FMT)
        // {fmt} fmt::format_to
        {
            char str[128]{};
            auto start = std::chrono::steady_clock::now();
            for(int i = 0; i < max_iterations; ++i)
            {
                auto res = fmt::format_to(str, "{:d}|{:x}|{:o}", __UINT64_MAX__, __UINT64_MAX__, __UINT64_MAX__);
                *res = '\0';
            }
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "fmt:: " << str << " -> " << ms << "ms\n";
            ms_min_fmt3 = std::min(ms_min_fmt3, ms);
        }
#endif
    }

    std::cout << "BEST RESULTS:\n";
    std::cout << "USF:  " << ms_min_usf1 << "ms / " << ms_min_usf2 << "ms / " << ms_min_usf3 << "ms\n";
#if defined(USF_TEST_BENCHMARK_PRINTF)
    std::cout << "STD: " << ms_min_std1 << "ms / " << ms_min_std2 << "ms / " << ms_min_std3 << "ms\n";
#endif
#if defined(USF_TEST_BENCHMARK_FMT)
    std::cout << "FMT: " << ms_min_fmt1 << "ms / " << ms_min_fmt2 << "ms / " << ms_min_fmt3 << "ms\n";
#endif
}

#endif //defined(USF_TEST_BENCHMARKS)
