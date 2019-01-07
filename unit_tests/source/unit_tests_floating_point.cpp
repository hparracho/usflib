
#include "unit_tests_config.hpp"

#if defined(USF_TEST_FLOATING_POINT)

// ----------------------------------------------------------------------------
// FLOATING POINT CONVERSION
// ----------------------------------------------------------------------------
void test_float_convertion(const double value)
{
    const char types[]{'f', 'e', 'g'};

    for(int t = 0; t < 3; ++t) // Test fixed, scientific and general format
    {
        for(int p = 0; p <= 9; ++p) // Test precision from 0 to 9
        {
            char std_str[64]{};
            char usf_str[64]{};

            char std_fmt[8]{};
            char usf_fmt[8]{};

            sprintf(std_fmt, "%%.%d%c", p, types[t]);
            sprintf(std_str, std_fmt, value);

            usf::format_to(usf_fmt, 8, "{{:.{:d}{:c}}}", p, types[t]);
            usf::format_to(usf_str, 64, usf_fmt, value);

            const auto result_ok = strcmp(usf_str, std_str) == 0;

            WARN_UNARY(result_ok);
#if 0
            if(!result_ok)
            {
                printf("ERROR: %.20f, %s usf: %s || std %s\n", value, std_fmt, usf_str, std_str);
                usf::format_to(usf_str, 64, usf_fmt, value);
            }
#endif
        }
    }
}

TEST_CASE("usf::format_to, floating point conversion")
{
#if 0
    {
        for(int v = 0; v <= 10000; ++v)
        {
            test_float_convertion(static_cast<double>(v));
            test_float_convertion(static_cast<double>(v) * 1e-1);
            test_float_convertion(static_cast<double>(v) * 1e-2);
            test_float_convertion(static_cast<double>(v) * 1e-3);
            test_float_convertion(static_cast<double>(v) * 1e-4);
            test_float_convertion(static_cast<double>(v) * 1e-5);
            test_float_convertion(static_cast<double>(v) * 1e-6);
            test_float_convertion(static_cast<double>(v) * 1e-7);
            test_float_convertion(static_cast<double>(v) * 1e-8);
            test_float_convertion(static_cast<double>(v) * 1e-9);
        }
    }
#endif
    {
        // Some random floating point numbers to test...
        constexpr double test_values_fp[]
        {
            0.00085499999999999997,
            1.065,
            1.345499999999999918287585387588478624820709228515625,
            2.7144439999999949719722280860878527164459228515625,
            4.71333299999994981277495753602124750614166259765625,
            18.4755549999999999499777914024889469146728515625,
            4.82444399999994999461705447174608707427978515625,
            9.1811109999998503639062619186006486415863037109375,
            1e-12,
            -1e-12,
            9.1811109999998503639062619186006486415863037109375e-11,
            1.8446743E19,
            -1.8446743E-9,
            1e-12,
            1.8446743E-12,
            -1.8446743E-12,
            5.55555,
            5.0,
            4.9999,
            5.000111,
            5.005,
            5.5,
            5.50,
            5.501,
            0.000254,
            0.0005004,
            0.99e-13,
            0.9888,
            1.3455,
            0.9,
            -123.5,
            -123.51,
            -122.5,
            -122.51,
            -123.49,
            -122.49,
            0,
            0.0001,
            -9999.99,
            9.9e-13,
            9.9e-12,
            18446742974197923840.00001,
            1.84467429741979238400000,
            1844.67429741979238400000,
            1.8446743E19,
            1.8446743E18,
            -1.8446743E19,
            -1.8446743E18,
            4528212345678.946638528859811704183484516925,
            1e-14,
            0.9999e-14,
            2.98023223876953125E-8,
        };

        for(const auto value : test_values_fp)
        {
            test_float_convertion(value);
        }
    }
}

#endif // defined(USF_TEST_FLOATING_POINT)
