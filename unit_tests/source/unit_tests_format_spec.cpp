
#include "unit_tests_config.hpp"

#if defined(USF_TEST_FORMAT_SPEC)

// ----------------------------------------------------------------------------
// FORMAT SPEC
// ----------------------------------------------------------------------------
TEST_CASE("usf::format_to, format spec")
{
    char str[128]{};

    const void* ptr = reinterpret_cast<void*>(1000);

    {
        // WIDTH WITHOUT TYPE
        usf::format_to(str, 128, "{:14}", false); CHECK_EQ(str, "         false");
        usf::format_to(str, 128, "{:14}", 'N'  ); CHECK_EQ(str, "N             ");
        usf::format_to(str, 128, "{:14}", 123  ); CHECK_EQ(str, "           123");
        usf::format_to(str, 128, "{:14}", 1.234); CHECK_EQ(str, "         1.234");
        usf::format_to(str, 128, "{:14}", ptr  ); CHECK_EQ(str, "           3e8");
        usf::format_to(str, 128, "{:14}", "str"); CHECK_EQ(str, "str           ");
    }
    {
        // WIDTH + TYPE
        usf::format_to(str, 128, "{:14c}", 'N'  ); CHECK_EQ(str, "N             ");
        usf::format_to(str, 128, "{:14d}", 123  ); CHECK_EQ(str, "           123");
        usf::format_to(str, 128, "{:14x}", 123  ); CHECK_EQ(str, "            7b");
        usf::format_to(str, 128, "{:14o}", 123  ); CHECK_EQ(str, "           173");
        usf::format_to(str, 128, "{:14b}", 123  ); CHECK_EQ(str, "       1111011");
        usf::format_to(str, 128, "{:14f}", 1.234); CHECK_EQ(str, "      1.234000");
        usf::format_to(str, 128, "{:14e}", 1.234); CHECK_EQ(str, "  1.234000e+00");
        usf::format_to(str, 128, "{:14g}", 1.234); CHECK_EQ(str, "         1.234");
        usf::format_to(str, 128, "{:14p}", ptr  ); CHECK_EQ(str, "           3e8");
        usf::format_to(str, 128, "{:14s}", "str"); CHECK_EQ(str, "str           ");
    }
    {
        // PRECISION + TYPE
        usf::format_to(str, 128, "{:.1f}", 1.234); CHECK_EQ(str, "1.2");
        usf::format_to(str, 128, "{:.1e}", 1.234); CHECK_EQ(str, "1.2e+00");
        usf::format_to(str, 128, "{:.1g}", 1.234); CHECK_EQ(str, "1");
        usf::format_to(str, 128, "{:.1s}", "str"); CHECK_EQ(str, "s");

        // PRECISION + INVALID TYPE
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1c}", 'N'), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1d}", 123), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1x}", 123), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1o}", 123), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1b}", 123), std::runtime_error);

        // PRECISION WITHOUT TYPE
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", false), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 'N'  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 123  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 123  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 123  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 123  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 1.234), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 1.234), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", 1.234), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", ptr  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:.1}", "str"), std::runtime_error);
    }
    {
        // LEFT ALIGNMENT + WIDTH
        usf::format_to(str, 128, "{:<14c}", 'N'  ); CHECK_EQ(str, "N             ");
        usf::format_to(str, 128, "{:<14d}", 123  ); CHECK_EQ(str, "123           ");
        usf::format_to(str, 128, "{:<14x}", 123  ); CHECK_EQ(str, "7b            ");
        usf::format_to(str, 128, "{:<14o}", 123  ); CHECK_EQ(str, "173           ");
        usf::format_to(str, 128, "{:<14b}", 123  ); CHECK_EQ(str, "1111011       ");
        usf::format_to(str, 128, "{:<14f}", 1.234); CHECK_EQ(str, "1.234000      ");
        usf::format_to(str, 128, "{:<14e}", 1.234); CHECK_EQ(str, "1.234000e+00  ");
        usf::format_to(str, 128, "{:<14g}", 1.234); CHECK_EQ(str, "1.234         ");
        usf::format_to(str, 128, "{:<14p}", ptr  ); CHECK_EQ(str, "3e8           ");
        usf::format_to(str, 128, "{:<14s}", "str"); CHECK_EQ(str, "str           ");
    }
    {
        // RIGHT ALIGNMENT + WIDTH
        usf::format_to(str, 128, "{:>14c}", 'N'  ); CHECK_EQ(str, "             N");
        usf::format_to(str, 128, "{:>14d}", 123  ); CHECK_EQ(str, "           123");
        usf::format_to(str, 128, "{:>14x}", 123  ); CHECK_EQ(str, "            7b");
        usf::format_to(str, 128, "{:>14o}", 123  ); CHECK_EQ(str, "           173");
        usf::format_to(str, 128, "{:>14b}", 123  ); CHECK_EQ(str, "       1111011");
        usf::format_to(str, 128, "{:>14f}", 1.234); CHECK_EQ(str, "      1.234000");
        usf::format_to(str, 128, "{:>14e}", 1.234); CHECK_EQ(str, "  1.234000e+00");
        usf::format_to(str, 128, "{:>14g}", 1.234); CHECK_EQ(str, "         1.234");
        usf::format_to(str, 128, "{:>14p}", ptr  ); CHECK_EQ(str, "           3e8");
        usf::format_to(str, 128, "{:>14s}", "str"); CHECK_EQ(str, "           str");
    }
    {
        // CENTER ALIGNMENT + WIDTH
        usf::format_to(str, 128, "{:^14c}", 'N'  ); CHECK_EQ(str, "      N       ");
        usf::format_to(str, 128, "{:^14d}", 123  ); CHECK_EQ(str, "     123      ");
        usf::format_to(str, 128, "{:^14x}", 123  ); CHECK_EQ(str, "      7b      ");
        usf::format_to(str, 128, "{:^14o}", 123  ); CHECK_EQ(str, "     173      ");
        usf::format_to(str, 128, "{:^14b}", 123  ); CHECK_EQ(str, "   1111011    ");
        usf::format_to(str, 128, "{:^14f}", 1.234); CHECK_EQ(str, "   1.234000   ");
        usf::format_to(str, 128, "{:^14e}", 1.234); CHECK_EQ(str, " 1.234000e+00 ");
        usf::format_to(str, 128, "{:^14g}", 1.234); CHECK_EQ(str, "    1.234     ");
        usf::format_to(str, 128, "{:^14p}", ptr  ); CHECK_EQ(str, "     3e8      ");
        usf::format_to(str, 128, "{:^14s}", "str"); CHECK_EQ(str, "     str      ");
    }
    {
        // NUMERIC ALIGNMENT + WIDTH
        usf::format_to(str, 128, "{:=14d}", 123  ); CHECK_EQ(str, "           123");
        usf::format_to(str, 128, "{:=14x}", 123  ); CHECK_EQ(str, "            7b");
        usf::format_to(str, 128, "{:=14o}", 123  ); CHECK_EQ(str, "           173");
        usf::format_to(str, 128, "{:=14b}", 123  ); CHECK_EQ(str, "       1111011");
        usf::format_to(str, 128, "{:=14f}", 1.234); CHECK_EQ(str, "      1.234000");
        usf::format_to(str, 128, "{:=14e}", 1.234); CHECK_EQ(str, "  1.234000e+00");
        usf::format_to(str, 128, "{:=14g}", 1.234); CHECK_EQ(str, "         1.234");
        usf::format_to(str, 128, "{:=14p}", ptr  ); CHECK_EQ(str, "           3e8");

        // NUMERIC ALIGNMENT + WIDTH + INVALID TYPE
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:=14c}", 'N'  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:=14s}", "str"), std::runtime_error);
    }
    {
        // FILL CHAR + NUMERIC ALIGNMENT + WIDTH
        usf::format_to(str, 128, "{:0=14d}", 123  ); CHECK_EQ(str, "00000000000123");
        usf::format_to(str, 128, "{:0=14x}", 123  ); CHECK_EQ(str, "0000000000007b");
        usf::format_to(str, 128, "{:0=14o}", 123  ); CHECK_EQ(str, "00000000000173");
        usf::format_to(str, 128, "{:0=14b}", 123  ); CHECK_EQ(str, "00000001111011");
        usf::format_to(str, 128, "{:0=14f}", 1.234); CHECK_EQ(str, "0000001.234000");
        usf::format_to(str, 128, "{:0=14e}", 1.234); CHECK_EQ(str, "001.234000e+00");
        usf::format_to(str, 128, "{:0=14g}", 1.234); CHECK_EQ(str, "0000000001.234");
        usf::format_to(str, 128, "{:0=14p}", ptr  ); CHECK_EQ(str, "000000000003e8");

        usf::format_to(str, 128, "{:0=14d}", -123  ); CHECK_EQ(str, "-0000000000123");
        usf::format_to(str, 128, "{:0=14x}", -123  ); CHECK_EQ(str, "-000000000007b");
        usf::format_to(str, 128, "{:0=14o}", -123  ); CHECK_EQ(str, "-0000000000173");
        usf::format_to(str, 128, "{:0=14b}", -123  ); CHECK_EQ(str, "-0000001111011");
        usf::format_to(str, 128, "{:0=14f}", -1.234); CHECK_EQ(str, "-000001.234000");
        usf::format_to(str, 128, "{:0=14e}", -1.234); CHECK_EQ(str, "-01.234000e+00");
        usf::format_to(str, 128, "{:0=14g}", -1.234); CHECK_EQ(str, "-000000001.234");
    }
    {
        // ZERO FILL + WIDTH
        usf::format_to(str, 128, "{:014d}", 123  ); CHECK_EQ(str, "00000000000123");
        usf::format_to(str, 128, "{:014x}", 123  ); CHECK_EQ(str, "0000000000007b");
        usf::format_to(str, 128, "{:014o}", 123  ); CHECK_EQ(str, "00000000000173");
        usf::format_to(str, 128, "{:014b}", 123  ); CHECK_EQ(str, "00000001111011");
        usf::format_to(str, 128, "{:014f}", 1.234); CHECK_EQ(str, "0000001.234000");
        usf::format_to(str, 128, "{:014e}", 1.234); CHECK_EQ(str, "001.234000e+00");
        usf::format_to(str, 128, "{:014g}", 1.234); CHECK_EQ(str, "0000000001.234");
        usf::format_to(str, 128, "{:014p}", ptr  ); CHECK_EQ(str, "000000000003e8");

        usf::format_to(str, 128, "{:014d}", -123  ); CHECK_EQ(str, "-0000000000123");
        usf::format_to(str, 128, "{:014x}", -123  ); CHECK_EQ(str, "-000000000007b");
        usf::format_to(str, 128, "{:014o}", -123  ); CHECK_EQ(str, "-0000000000173");
        usf::format_to(str, 128, "{:014b}", -123  ); CHECK_EQ(str, "-0000001111011");
        usf::format_to(str, 128, "{:014f}", -1.234); CHECK_EQ(str, "-000001.234000");
        usf::format_to(str, 128, "{:014e}", -1.234); CHECK_EQ(str, "-01.234000e+00");
        usf::format_to(str, 128, "{:014g}", -1.234); CHECK_EQ(str, "-000000001.234");
    }
    {
        // HASH (integers)
        usf::format_to(str, 128, "{:#x}", 123); CHECK_EQ(str, "0x7b");
        usf::format_to(str, 128, "{:#X}", 123); CHECK_EQ(str, "0X7B");
        usf::format_to(str, 128, "{:#o}", 123); CHECK_EQ(str, "0173");
        usf::format_to(str, 128, "{:#b}", 123); CHECK_EQ(str, "0b1111011");
        usf::format_to(str, 128, "{:#B}", 123); CHECK_EQ(str, "0B1111011");
        usf::format_to(str, 128, "{:#p}", ptr); CHECK_EQ(str, "0x3e8");
        usf::format_to(str, 128, "{:#P}", ptr); CHECK_EQ(str, "0X3E8");

        // HASH (floating point)
        usf::format_to(str, 128, "{:#f}", 1.234); CHECK_EQ(str, "1.234000");
        usf::format_to(str, 128, "{:#.0f}", 1.0); CHECK_EQ(str, "1.");
        usf::format_to(str, 128, "{:#e}", 1.234); CHECK_EQ(str, "1.234000e+00");
        usf::format_to(str, 128, "{:#.0e}", 1.0); CHECK_EQ(str, "1.e+00");
        usf::format_to(str, 128, "{:#g}", 1.234); CHECK_EQ(str, "1.23400");
        usf::format_to(str, 128, "{:#.2g}", 1.0); CHECK_EQ(str, "1.0");
        usf::format_to(str, 128, "{:#.0g}", 1.0); CHECK_EQ(str, "1.");

        // HASH (negative floating point)
        usf::format_to(str, 128, "{:#f}", -1.234); CHECK_EQ(str, "-1.234000");
        usf::format_to(str, 128, "{:#.0f}", -1.0); CHECK_EQ(str, "-1.");
        usf::format_to(str, 128, "{:#e}", -1.234); CHECK_EQ(str, "-1.234000e+00");
        usf::format_to(str, 128, "{:#.0e}", -1.0); CHECK_EQ(str, "-1.e+00");
        usf::format_to(str, 128, "{:#g}", -1.234); CHECK_EQ(str, "-1.23400");
        usf::format_to(str, 128, "{:#.2g}", -1.0); CHECK_EQ(str, "-1.0");
        usf::format_to(str, 128, "{:#.0g}", -1.0); CHECK_EQ(str, "-1.");

        // HASH + INVALID TYPES
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:#c}", 'N'  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:#d}", 123  ), std::runtime_error);
        CHECK_THROWS_AS(usf::format_to(str, 128, "{:#s}", "str"), std::runtime_error);
    }
    {
        // FILL CHAR + ALIGNMENT + HASH (integers)
        usf::format_to(str, 128, "{:*>#14x}", 123); CHECK_EQ(str, "**********0x7b");
        usf::format_to(str, 128, "{:*>#14X}", 123); CHECK_EQ(str, "**********0X7B");
        usf::format_to(str, 128, "{:*>#14o}", 123); CHECK_EQ(str, "**********0173");
        usf::format_to(str, 128, "{:*>#14b}", 123); CHECK_EQ(str, "*****0b1111011");
        usf::format_to(str, 128, "{:*>#14B}", 123); CHECK_EQ(str, "*****0B1111011");
        usf::format_to(str, 128, "{:*>#14p}", ptr); CHECK_EQ(str, "*********0x3e8");
        usf::format_to(str, 128, "{:*>#14P}", ptr); CHECK_EQ(str, "*********0X3E8");

        // FILL CHAR + ALIGNMENT + HASH (negative floating point)
        usf::format_to(str, 128, "{:*>#14f}", -1.234); CHECK_EQ(str, "*****-1.234000");
        usf::format_to(str, 128, "{:*>#14.0f}", -1.0); CHECK_EQ(str, "***********-1.");
        usf::format_to(str, 128, "{:*>#14e}", -1.234); CHECK_EQ(str, "*-1.234000e+00");
        usf::format_to(str, 128, "{:*>#14.0e}", -1.0); CHECK_EQ(str, "*******-1.e+00");
        usf::format_to(str, 128, "{:*>#14g}", -1.234); CHECK_EQ(str, "******-1.23400");
        usf::format_to(str, 128, "{:*>#14.2g}", -1.0); CHECK_EQ(str, "**********-1.0");
        usf::format_to(str, 128, "{:*>#14.0g}", -1.0); CHECK_EQ(str, "***********-1.");
    }
    {
        // FILL CHAR + ALIGNMENT + HASH + ZERO FILL (integers)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, 128, "{:*>#014x}", 123); CHECK_EQ(str, "0x00000000007b");
        usf::format_to(str, 128, "{:*>#014X}", 123); CHECK_EQ(str, "0X00000000007B");
        usf::format_to(str, 128, "{:*>#014o}", 123); CHECK_EQ(str, "00000000000173");
        usf::format_to(str, 128, "{:*>#014b}", 123); CHECK_EQ(str, "0b000001111011");
        usf::format_to(str, 128, "{:*>#014B}", 123); CHECK_EQ(str, "0B000001111011");
        usf::format_to(str, 128, "{:*>#014p}", ptr); CHECK_EQ(str, "0x0000000003e8");
        usf::format_to(str, 128, "{:*>#014P}", ptr); CHECK_EQ(str, "0X0000000003E8");

        // FILL CHAR + ALIGNMENT + HASH (negative floating point)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, 128, "{:*>#014f}", -1.234); CHECK_EQ(str, "-000001.234000");
        usf::format_to(str, 128, "{:*>#014.0f}", -1.0); CHECK_EQ(str, "-000000000001.");
        usf::format_to(str, 128, "{:*>#014e}", -1.234); CHECK_EQ(str, "-01.234000e+00");
        usf::format_to(str, 128, "{:*>#014.0e}", -1.0); CHECK_EQ(str, "-00000001.e+00");
        usf::format_to(str, 128, "{:*>#014g}", -1.234); CHECK_EQ(str, "-0000001.23400");
        usf::format_to(str, 128, "{:*>#014.2g}", -1.0); CHECK_EQ(str, "-00000000001.0");
        usf::format_to(str, 128, "{:*>#014.0g}", -1.0); CHECK_EQ(str, "-000000000001.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH (integers)
        usf::format_to(str, 128, "{:*>+#14x}", 123); CHECK_EQ(str, "*********+0x7b");
        usf::format_to(str, 128, "{:*>+#14X}", 123); CHECK_EQ(str, "*********+0X7B");
        usf::format_to(str, 128, "{:*>+#14o}", 123); CHECK_EQ(str, "*********+0173");
        usf::format_to(str, 128, "{:*>+#14b}", 123); CHECK_EQ(str, "****+0b1111011");
        usf::format_to(str, 128, "{:*>+#14B}", 123); CHECK_EQ(str, "****+0B1111011");

        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH (negative floating point)
        usf::format_to(str, 128, "{:*>+#14f}", -1.234); CHECK_EQ(str, "*****-1.234000");
        usf::format_to(str, 128, "{:*>+#14.0f}", -1.0); CHECK_EQ(str, "***********-1.");
        usf::format_to(str, 128, "{:*>+#14e}", -1.234); CHECK_EQ(str, "*-1.234000e+00");
        usf::format_to(str, 128, "{:*>+#14.0e}", -1.0); CHECK_EQ(str, "*******-1.e+00");
        usf::format_to(str, 128, "{:*>+#14g}", -1.234); CHECK_EQ(str, "******-1.23400");
        usf::format_to(str, 128, "{:*>+#14.2g}", -1.0); CHECK_EQ(str, "**********-1.0");
        usf::format_to(str, 128, "{:*>+#14.0g}", -1.0); CHECK_EQ(str, "***********-1.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH + ZERO FILL (integers)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, 128, "{:*>+#014x}", 123); CHECK_EQ(str, "+0x0000000007b");
        usf::format_to(str, 128, "{:*>+#014X}", 123); CHECK_EQ(str, "+0X0000000007B");
        usf::format_to(str, 128, "{:*>+#014o}", 123); CHECK_EQ(str, "+0000000000173");
        usf::format_to(str, 128, "{:*>+#014b}", 123); CHECK_EQ(str, "+0b00001111011");
        usf::format_to(str, 128, "{:*>+#014B}", 123); CHECK_EQ(str, "+0B00001111011");

        // FILL CHAR + ALIGNMENT + SIGN ('+') + HASH (negative floating point)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, 128, "{:*>+#014f}", -1.234); CHECK_EQ(str, "-000001.234000");
        usf::format_to(str, 128, "{:*>+#014.0f}", -1.0); CHECK_EQ(str, "-000000000001.");
        usf::format_to(str, 128, "{:*>+#014e}", -1.234); CHECK_EQ(str, "-01.234000e+00");
        usf::format_to(str, 128, "{:*>+#014.0e}", -1.0); CHECK_EQ(str, "-00000001.e+00");
        usf::format_to(str, 128, "{:*>+#014g}", -1.234); CHECK_EQ(str, "-0000001.23400");
        usf::format_to(str, 128, "{:*>+#014.2g}", -1.0); CHECK_EQ(str, "-00000000001.0");
        usf::format_to(str, 128, "{:*>+#014.0g}", -1.0); CHECK_EQ(str, "-000000000001.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH (integers)
        usf::format_to(str, 128, "{:*> #14x}", 123); CHECK_EQ(str, "********* 0x7b");
        usf::format_to(str, 128, "{:*> #14X}", 123); CHECK_EQ(str, "********* 0X7B");
        usf::format_to(str, 128, "{:*> #14o}", 123); CHECK_EQ(str, "********* 0173");
        usf::format_to(str, 128, "{:*> #14b}", 123); CHECK_EQ(str, "**** 0b1111011");
        usf::format_to(str, 128, "{:*> #14B}", 123); CHECK_EQ(str, "**** 0B1111011");

        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH (negative floating point)
        usf::format_to(str, 128, "{:*> #14f}", -1.234); CHECK_EQ(str, "*****-1.234000");
        usf::format_to(str, 128, "{:*> #14.0f}", -1.0); CHECK_EQ(str, "***********-1.");
        usf::format_to(str, 128, "{:*> #14e}", -1.234); CHECK_EQ(str, "*-1.234000e+00");
        usf::format_to(str, 128, "{:*> #14.0e}", -1.0); CHECK_EQ(str, "*******-1.e+00");
        usf::format_to(str, 128, "{:*> #14g}", -1.234); CHECK_EQ(str, "******-1.23400");
        usf::format_to(str, 128, "{:*> #14.2g}", -1.0); CHECK_EQ(str, "**********-1.0");
        usf::format_to(str, 128, "{:*> #14.0g}", -1.0); CHECK_EQ(str, "***********-1.");
    }
    {
        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH + ZERO FILL (integers)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, 128, "{:*> #014x}", 123); CHECK_EQ(str, " 0x0000000007b");
        usf::format_to(str, 128, "{:*> #014X}", 123); CHECK_EQ(str, " 0X0000000007B");
        usf::format_to(str, 128, "{:*> #014o}", 123); CHECK_EQ(str, " 0000000000173");
        usf::format_to(str, 128, "{:*> #014b}", 123); CHECK_EQ(str, " 0b00001111011");
        usf::format_to(str, 128, "{:*> #014B}", 123); CHECK_EQ(str, " 0B00001111011");

        // FILL CHAR + ALIGNMENT + SIGN (' ') + HASH (negative floating point)
        // ZERO FILL HAS PRECEDENCE OVER ALIGNMENT + FILL CHAR!
        usf::format_to(str, 128, "{:*> #014f}", -1.234); CHECK_EQ(str, "-000001.234000");
        usf::format_to(str, 128, "{:*> #014.0f}", -1.0); CHECK_EQ(str, "-000000000001.");
        usf::format_to(str, 128, "{:*> #014e}", -1.234); CHECK_EQ(str, "-01.234000e+00");
        usf::format_to(str, 128, "{:*> #014.0e}", -1.0); CHECK_EQ(str, "-00000001.e+00");
        usf::format_to(str, 128, "{:*> #014g}", -1.234); CHECK_EQ(str, "-0000001.23400");
        usf::format_to(str, 128, "{:*> #014.2g}", -1.0); CHECK_EQ(str, "-00000000001.0");
        usf::format_to(str, 128, "{:*> #014.0g}", -1.0); CHECK_EQ(str, "-000000000001.");
    }
}

#endif // #if defined(USF_TEST_FORMAT_SPEC)
