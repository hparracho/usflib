// ----------------------------------------------------------------------------
// @file    usf_argument.hpp
// @brief   Argument format processor class.
// @date    07 January 2019
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

                    const fp_t fp_value {value};

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

        static USF_CPP14_CONSTEXPR void format_string(iterator& it, const_iterator end,
                                                      const Format& format, const CharT* str,
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

// Character
template <typename CharT> inline USF_CPP14_CONSTEXPR
Argument<CharT> make_argument(const char arg)
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
