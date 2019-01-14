// ----------------------------------------------------------------------------
// @file    usf_integer.hpp
// @brief   Integer conversion and helper functions.
// @date    14 January 2019
// ----------------------------------------------------------------------------

#ifndef USF_INTEGER_HPP
#define USF_INTEGER_HPP

namespace usf
{
namespace internal
{

constexpr uint32_t pow10_uint32_lut[]
{
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000
};

constexpr uint64_t pow10_uint64_lut[]
{
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000,
    100000000000,
    1000000000000,
    10000000000000,
    100000000000000,
    1000000000000000,
    10000000000000000,
    100000000000000000,
    1000000000000000000,
    10000000000000000000U
};

constexpr char digits_hex_uppercase[]{"0123456789ABCDEF"};
constexpr char digits_hex_lowercase[]{"0123456789abcdef"};

class Integer
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC STATIC FUNCTIONS
        // --------------------------------------------------------------------

        // -------- POWERS OF 10 ----------------------------------------------
        static USF_CPP14_CONSTEXPR uint32_t pow10_uint32(const int index) noexcept
        {
            assert(index >= 0 && index < 10);

            return pow10_uint32_lut[index];
        }

        static USF_CPP14_CONSTEXPR uint64_t pow10_uint64(const int index) noexcept
        {
            assert(index >= 0 && index < 20);

            return pow10_uint64_lut[index];
        }

        // -------- COUNT DIGITS ----------------------------------------------
        // Based on the code from:
        // http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10
        // --------------------- ----------------------------------------------

        static USF_CPP14_CONSTEXPR int count_digits_dec(const uint32_t n) noexcept
        {
            if(n < 10) return 1;

            // The algorithm below doesn't work when `n` is 0 because:
            // 1. the result of __builtin_clz() is undefined if `n` is 0.
            // 2. the `pow10_uint32_lut` lookup table has the value 1 in
            //    the first element and not a 0 as the algorithm expects.
            // (both cases are covered by the previous if statement or
            //  by the slower commented OR operation below).

            // n = n | 1;

            const int t = (32 - __builtin_clz(n)) * 1233 >> 12;
            return t - (n < pow10_uint32_lut[t]) + 1;
        }

        static USF_CPP14_CONSTEXPR int count_digits_dec(const uint64_t n) noexcept
        {
            if(n <= std::numeric_limits<uint32_t>::max())
            {
                return count_digits_dec(static_cast<uint32_t>(n));
            }

            // The algorithm below doesn't work when `n` is 0 because:
            // 1. the result of __builtin_clzll() is undefined if `n` is 0.
            // 2. the `pow10_uint64_lut` lookup table has the value 1 in
            //    the first element and not a 0 as the algorithm expects.
            // (both cases are covered by the previous if statement or
            //  by the slower commented OR operation below).

            // n = n | 1;

            const int t = (64 - __builtin_clzll(n)) * 1233 >> 12;
            return t - (n < pow10_uint64_lut[t]) + 1;
        }

        static USF_CPP14_CONSTEXPR int count_digits_bin(const uint32_t n) noexcept
        {
            // The result of __builtin_clz() is undefined if `n` is 0.
            return (n < 2) ? 1 : (32 - __builtin_clz(n));
        }

        static USF_CPP14_CONSTEXPR int count_digits_bin(const uint64_t n) noexcept
        {
            // The result of __builtin_clzll() is undefined if `n` is 0.
            return (n < 2) ? 1 : (64 - __builtin_clzll(n));
        }

        template <typename T,
                  typename std::enable_if<std::numeric_limits<T>::is_integer && std::is_unsigned<T>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR int count_digits_oct(T n) noexcept
        {
            int digits = 1;
            while((n >>= 3U) != 0) { ++digits; }
            return digits;
        }

        template <typename T,
                  typename std::enable_if<std::numeric_limits<T>::is_integer && std::is_unsigned<T>::value, bool>::type = true>
        static USF_CPP14_CONSTEXPR int count_digits_hex(T n) noexcept
        {
            int digits = 1;
            while((n >>= 4U) != 0) { ++digits; }
            return digits;
        }

        // -------- FAST DIVIDE BY 10 -----------------------------------------
        // Based on the code from Hacker's Delight:
        // http://www.hackersdelight.org/divcMore.pdf
        // --------------------- ----------------------------------------------
        static USF_CPP14_CONSTEXPR uint32_t div10(const uint32_t n) noexcept
        {
#if defined(__arm__)
            uint32_t q = (n >> 1) + (n >> 2);
            q += (q >> 4);
            q += (q >> 8);
            q += (q >> 16);
            q >>= 3;

            const uint32_t r = n - (q << 3) - (q << 1);

            return q + ((r + 6) >> 4);
            // return q + (r > 9);
#else
            return n / 10;
#endif
        }

        static USF_CPP14_CONSTEXPR uint64_t div10(const uint64_t n) noexcept
        {
#if defined(__arm__)
            uint64_t q = (n >> 1) + (n >> 2);
            q += (q >> 4);
            q += (q >> 8);
            q += (q >> 16);
            q += (q >> 32);
            q >>= 3;

            const uint64_t r = n - (q << 3) - (q << 1);

            return q + ((r + 6) >> 4);
            // return q + (r > 9);
#else
            return n / 10;
#endif
        }

        // -------- CONVERTERS ------------------------------------------------
        // The following converters write the value from back to front.
        // It is assumed that the pointer `dst` is already placed at the
        // position after the last character. The pointer position is
        // calculated using the corresponding count_digits_xxx() functions.

        // Example:
        // value ->  1234
        // array -> [........]
        // dst   ->      ^

        // -------- DECIMAL CONVERSION ----------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_dec(CharT* dst, uint32_t value) noexcept
        {
            do
            {
                const uint32_t v = value;
                value = div10(value);
                *(--dst) = static_cast<CharT>('0' + (v - (value * 10)));
            }while(value);
        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_dec(CharT* dst, uint64_t value) noexcept
        {
            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value = div10(value);
                *(--dst) = static_cast<CharT>('0' + (v - (value * 10)));
            }

            convert_dec(dst, static_cast<uint32_t>(value));
        }

        // -------- BINARY CONVERSION -----------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_bin(CharT* dst, uint32_t value) noexcept
        {
            do
            {
                const uint32_t v = value;
                value >>= 1U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 1U)));
            }while(value);
        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_bin(CharT* dst, uint64_t value) noexcept
        {
            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value >>= 1U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 1U)));
            }

            convert_bin(dst, static_cast<uint32_t>(value));
        }

        // -------- OCTAL CONVERSION ------------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_oct(CharT* dst, uint32_t value) noexcept
        {
            do
            {
                const uint32_t v = value;
                value >>= 3U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 3U)));
            }while(value);
        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_oct(CharT* dst, uint64_t value) noexcept
        {
            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value >>= 3U;
                *(--dst) = static_cast<CharT>('0' + (v - (value << 3U)));
            }

            convert_oct(dst, static_cast<uint32_t>(value));
        }

        // -------- HEXADECIMAL CONVERSION ------------------------------------
        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_hex(CharT* dst, uint32_t value, const bool uppercase) noexcept
        {
            const char* digits = uppercase ? digits_hex_uppercase : digits_hex_lowercase;

            do
            {
                const uint32_t v = value;
                value >>= 4U;
                *(--dst) = static_cast<CharT>(digits[v - (value << 4U)]);
            }while(value);

        }

        template <typename CharT>
        static USF_CPP14_CONSTEXPR void convert_hex(CharT* dst, uint64_t value, const bool uppercase) noexcept
        {
            const char* digits = uppercase ? digits_hex_uppercase : digits_hex_lowercase;

            while(value > std::numeric_limits<uint32_t>::max())
            {
                const uint64_t v = value;
                value >>= 4U;
                *(--dst) = static_cast<CharT>(digits[v - (value << 4U)]);
            }

            convert_hex(dst, static_cast<uint32_t>(value), uppercase);
        }
};

} // namespace internal
} // namespace usf

#endif // USF_INTEGER_HPP
