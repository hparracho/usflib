
#include "unit_tests_config.hpp"

#if defined(USF_TEST_POSITIONAL_ARGS)

// ----------------------------------------------------------------------------
// POSITIONAL ARGUMENTS
// ----------------------------------------------------------------------------
TEST_CASE("usf::format_to, positional indices")
{
    char str[32]{};

    usf::format_to(str, 32, "{0}{1}{0}", "abra", "cad");
    CHECK_EQ(str, "abracadabra");

    // The following test shows both the positional and
    // sequencial arguments working seamlessly together.

    usf::format_to(str, 32, "{}{}{0}", "abra", "cad");
    CHECK_EQ(str, "abracadabra");

    usf::format_to(str, 32, "{0}{1}{}", "abra", "cad");
    CHECK_EQ(str, "abracadabra");

    usf::format_to(str, 32, "{}{1}{0}", "abra", "cad");
    CHECK_EQ(str, "abracadabra");
}

#endif // #if defined(USF_TEST_POSITIONAL_ARGS)
