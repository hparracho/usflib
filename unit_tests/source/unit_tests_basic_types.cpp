
#include "unit_tests_config.hpp"

#if defined(USF_TEST_BASIC_TYPES)

// ----------------------------------------------------------------------------
// BASIC TYPES
// ----------------------------------------------------------------------------
TEST_CASE("usf::format_to, basic types")
{
    char str[128]{};

    // Boolean type
    {
        usf::format_to(str, 128, "{}",   false); CHECK_EQ(str, "false");
        usf::format_to(str, 128, "{}",   true ); CHECK_EQ(str, "true");

        usf::format_to(str, 128, "{:d}", false); CHECK_EQ(str, "0");
        usf::format_to(str, 128, "{:d}", true ); CHECK_EQ(str, "1");

        usf::format_to(str, 128, "{:x}", false); CHECK_EQ(str, "0");
        usf::format_to(str, 128, "{:x}", true ); CHECK_EQ(str, "1");

        usf::format_to(str, 128, "{:X}", false); CHECK_EQ(str, "0");
        usf::format_to(str, 128, "{:X}", true ); CHECK_EQ(str, "1");

        usf::format_to(str, 128, "{:o}", false); CHECK_EQ(str, "0");
        usf::format_to(str, 128, "{:o}", true ); CHECK_EQ(str, "1");

        usf::format_to(str, 128, "{:b}", false); CHECK_EQ(str, "0");
        usf::format_to(str, 128, "{:b}", true ); CHECK_EQ(str, "1");

        usf::format_to(str, 128, "{:B}", false); CHECK_EQ(str, "0");
        usf::format_to(str, 128, "{:B}", true ); CHECK_EQ(str, "1");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", true), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", true), std::runtime_error);
    }

    // Character (char) type
    {
        usf::format_to(str, 128, "{}",   'N'); CHECK_EQ(str, "N");
        usf::format_to(str, 128, "{:c}", 'N'); CHECK_EQ(str, "N");
        usf::format_to(str, 128, "{:d}", 'N'); CHECK_EQ(str, "78");
        usf::format_to(str, 128, "{:x}", 'N'); CHECK_EQ(str, "4e");
        usf::format_to(str, 128, "{:X}", 'N'); CHECK_EQ(str, "4E");
        usf::format_to(str, 128, "{:o}", 'N'); CHECK_EQ(str, "116");
        usf::format_to(str, 128, "{:b}", 'N'); CHECK_EQ(str, "1001110");
        usf::format_to(str, 128, "{:B}", 'N'); CHECK_EQ(str, "1001110");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", 'N'), std::runtime_error);
    }

    // Integer (int) type
    {
        int value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = -123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "-7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "-7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "-173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "-1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "-1111011");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (unsigned int) type
    {
        unsigned int value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = static_cast<unsigned int>(-123);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "4294967173");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "4294967173");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "ffffff85");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "FFFFFF85");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "37777777605");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "11111111111111111111111110000101");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "11111111111111111111111110000101");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (int8_t) type
    {
        int8_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = -123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "-7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "-7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "-173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "-1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "-1111011");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (uint8_t) type
    {
        uint8_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = static_cast<uint8_t>(-123);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "133");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "133");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "85");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "85");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "205");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "10000101");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "10000101");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (int16_t) type
    {
        int16_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = -123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "-7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "-7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "-173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "-1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "-1111011");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (uint16_t) type
    {
        uint16_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = static_cast<uint16_t>(-123);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "65413");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "65413");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "ff85");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "FF85");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "177605");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111111110000101");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111111110000101");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (int32_t) type
    {
        int32_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = -123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "-7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "-7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "-173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "-1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "-1111011");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (uint32_t) type
    {
        uint32_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = static_cast<uint32_t>(-123);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "4294967173");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "4294967173");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "ffffff85");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "FFFFFF85");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "37777777605");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "11111111111111111111111110000101");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "11111111111111111111111110000101");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (int64_t) type
    {
        int64_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = -123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "-123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "-7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "-7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "-173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "-1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "-1111011");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Integer (uint64_t) type
    {
        uint64_t value = 123;

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "123");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "7b");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "7B");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "173");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111011");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111011");

        value = static_cast<uint64_t>(-123);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "18446744073709551493");
        usf::format_to(str, 128, "{:d}", value); CHECK_EQ(str, "18446744073709551493");
        usf::format_to(str, 128, "{:x}", value); CHECK_EQ(str, "ffffffffffffff85");
        usf::format_to(str, 128, "{:X}", value); CHECK_EQ(str, "FFFFFFFFFFFFFF85");
        usf::format_to(str, 128, "{:o}", value); CHECK_EQ(str, "1777777777777777777605");
        usf::format_to(str, 128, "{:b}", value); CHECK_EQ(str, "1111111111111111111111111111111111111111111111111111111110000101");
        usf::format_to(str, 128, "{:B}", value); CHECK_EQ(str, "1111111111111111111111111111111111111111111111111111111110000101");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Floating point (float) type
    {
        float value = 123.456789f;

        char std_str[32]{};

        usf::format_to(str, 128, "{}",   value); sprintf(std_str, "%g", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:f}", value); sprintf(std_str, "%f", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:F}", value); sprintf(std_str, "%F", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:e}", value); sprintf(std_str, "%e", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:E}", value); sprintf(std_str, "%E", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:g}", value); sprintf(std_str, "%g", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:G}", value); sprintf(std_str, "%G", static_cast<double>(value)); CHECK_EQ(str, std_str);

        value = -123.456789f;

        usf::format_to(str, 128, "{}",   value); sprintf(std_str, "%g", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:f}", value); sprintf(std_str, "%f", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:F}", value); sprintf(std_str, "%F", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:e}", value); sprintf(std_str, "%e", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:E}", value); sprintf(std_str, "%E", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:g}", value); sprintf(std_str, "%g", static_cast<double>(value)); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:G}", value); sprintf(std_str, "%G", static_cast<double>(value)); CHECK_EQ(str, std_str);

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:d}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:x}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:X}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:o}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:b}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:B}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Floating point (double) type
    {
        double value = 123.456789;

        char std_str[32]{};

        usf::format_to(str, 128, "{}",   value); sprintf(std_str, "%g", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:f}", value); sprintf(std_str, "%f", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:F}", value); sprintf(std_str, "%F", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:e}", value); sprintf(std_str, "%e", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:E}", value); sprintf(std_str, "%E", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:g}", value); sprintf(std_str, "%g", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:G}", value); sprintf(std_str, "%G", value); CHECK_EQ(str, std_str);

        value = -123.456789;

        usf::format_to(str, 128, "{}",   value); sprintf(std_str, "%g", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:f}", value); sprintf(std_str, "%f", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:F}", value); sprintf(std_str, "%F", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:e}", value); sprintf(std_str, "%e", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:E}", value); sprintf(std_str, "%E", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:g}", value); sprintf(std_str, "%g", value); CHECK_EQ(str, std_str);
        usf::format_to(str, 128, "{:G}", value); sprintf(std_str, "%G", value); CHECK_EQ(str, std_str);

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:d}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:x}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:X}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:o}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:b}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:B}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:p}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:P}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Pointer (void*) type
    {
        void* value = reinterpret_cast<void*>(1000);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "3e8");
        usf::format_to(str, 128, "{:p}", value); CHECK_EQ(str, "3e8");
        usf::format_to(str, 128, "{:P}", value); CHECK_EQ(str, "3E8");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:d}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:x}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:X}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:o}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:b}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:B}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // Constant pointer (const void*) type
    {
        const void* value = reinterpret_cast<void*>(1000);

        usf::format_to(str, 128, "{}",   value); CHECK_EQ(str, "3e8");
        usf::format_to(str, 128, "{:p}", value); CHECK_EQ(str, "3e8");
        usf::format_to(str, 128, "{:P}", value); CHECK_EQ(str, "3E8");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:d}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:x}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:X}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:o}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:b}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:B}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", value), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:s}", value), std::runtime_error);
    }

    // String (convertible to usf::StringView) type
    {
        char s1[]{"str"};
        usf::format_to(str, 128, "{}",   s1); CHECK_EQ(str, "str");
        usf::format_to(str, 128, "{:s}", s1); CHECK_EQ(str, "str");

        const char s2[]{"str"};
        usf::format_to(str, 128, "{}",   s2); CHECK_EQ(str, "str");
        usf::format_to(str, 128, "{:s}", s2); CHECK_EQ(str, "str");

        char* s3 = s1;
        usf::format_to(str, 128, "{}",   s3); CHECK_EQ(str, "str");
        usf::format_to(str, 128, "{:s}", s3); CHECK_EQ(str, "str");

        const char* s4 = s2;
        usf::format_to(str, 128, "{}",   s4); CHECK_EQ(str, "str");
        usf::format_to(str, 128, "{:s}", s4); CHECK_EQ(str, "str");

        usf::StringView sv(s1);
        usf::format_to(str, 128, "{}",   sv); CHECK_EQ(str, "str");
        usf::format_to(str, 128, "{:s}", sv); CHECK_EQ(str, "str");

        CHECK_THROWS_AS(usf::format_to(str, 128, "{:c}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:d}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:x}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:X}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:o}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:b}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:B}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:f}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:F}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:e}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:E}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:g}", sv), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:G}", sv), std::runtime_error);
    }
}

#endif // #if defined(USF_TEST_BASIC_TYPES)
