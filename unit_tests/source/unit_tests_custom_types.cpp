
#include "unit_tests_config.hpp"

#if defined(USF_TEST_CUSTOM_TYPES)

// ----------------------------------------------------------------------------
// USER DEFINED CUSTOM TYPES DEMO 1 - DATE / TIME
// ----------------------------------------------------------------------------
enum class DateTime
{
    kCurrentDate,
    kCurrentTime,
    kIsDst
};

namespace usf
{
template <typename CharT>
struct Formatter<CharT, DateTime>
{
    // Gets current date and time.
    // Or... Insert your thread safe favorite variant here!
    static const std::tm* now()
    {
        std::time_t t = std::time(nullptr);
        return std::localtime(&t);
    }

    static BasicStringSpan<CharT> format_to(BasicStringSpan<CharT> dst, const DateTime& date_time)
    {
        const std::tm* dt = now();

        switch(date_time)
        {
            case DateTime::kCurrentDate: return basic_format_to<CharT>(dst, "{}/{:02d}/{:02d}",
                                            1900 + dt->tm_year, 1 + dt->tm_mon, dt->tm_mday);
                                            break;
            case DateTime::kCurrentTime: return basic_format_to<CharT>(dst, "{:02d}:{:02d}:{:02d}",
                                            dt->tm_hour, dt->tm_min, dt->tm_sec);
                                            break;
            case DateTime::kIsDst:       return basic_format_to<CharT>(dst, "{}",
                                            dt->tm_isdst ? "Yes" : "No");
                                            break;
        }

        return basic_format_to<CharT>(dst, "invalid param");
    }
};
} // namespace usf

TEST_CASE("usf::format_to, custom type DateTime")
{
    {
        char str[32]{};

        usf::format_to(str, 32, "Current Date: {}", DateTime::kCurrentDate);
        std::cout << '\n' << str << '\n';

        usf::format_to(str, 32, "Current Time: {}", DateTime::kCurrentTime);
        std::cout << str << '\n';

        usf::format_to(str, 32, "Daylight Saving Time: {}", DateTime::kIsDst);
        std::cout << str << "\n\n";
    }
}


// ----------------------------------------------------------------------------
// USER DEFINED CUSTOM TYPE DEMO 2 - RGB COLOR
// ----------------------------------------------------------------------------

struct Color
{
    // Constructor needed in C++11
    Color(const uint8_t _r, const uint8_t _g, const uint8_t _b)
        : r(_r), g(_g), b(_b) {}

    uint8_t r{0};
    uint8_t g{0};
    uint8_t b{0};
};

namespace usf
{
template <typename CharT>
struct Formatter<CharT, Color>
{
    static BasicStringSpan<CharT> format_to(BasicStringSpan<CharT> dst, const Color& color)
    {
        return basic_format_to<CharT>(dst, "{:#02x}{:02x}{:02x}", color.r, color.g, color.b);
    }
};
} // namespace usf

TEST_CASE("usf::format_to, custom type Color")
{
    {
        char str[32]{};

        usf::format_to(str, 32, "RGB: {}", Color{35,128,255});
        CHECK_EQ(str, "RGB: 0x2380ff");
    }
}

#endif // defined(USF_TEST_CUSTOM_TYPES)
