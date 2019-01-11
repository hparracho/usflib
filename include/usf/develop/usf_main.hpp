// ----------------------------------------------------------------------------
// @file    usf_main.hpp
// @brief   Main process functions and public interface.
// @date    11 January 2019
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




template <typename... Args> USF_CPP14_CONSTEXPR
StringSpan format_to(StringSpan str, StringView fmt, Args&&... args)
{
    return basic_format_to(str, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
ByteStringSpan format_to(ByteStringSpan str, StringView fmt, Args&&... args)
{
    static_assert(CHAR_BIT == 8, "usf::format_to(): invalid char size.");
    char *end = basic_format_to(reinterpret_cast<char*>(str.data()), str.size(), fmt, args...);

    return ByteStringSpan(str.begin(), reinterpret_cast<uint8_t*>(end));
}

template <typename... Args> USF_CPP14_CONSTEXPR
char* format_to(char* str, const std::ptrdiff_t str_count, StringView fmt, Args&&... args)
{
    return basic_format_to(str, str_count, fmt, args...);
}

template <typename... Args> USF_CPP14_CONSTEXPR
uint8_t* format_to(uint8_t* str, const std::ptrdiff_t str_count, StringView fmt, Args&&... args)
{
    static_assert(CHAR_BIT == 8, "usf::format_to(): invalid char size.");
    return reinterpret_cast<uint8_t*>(basic_format_to(reinterpret_cast<char*>(str), str_count, fmt, args...));
}

} // namespace usf

#endif // USF_MAIN_HPP
