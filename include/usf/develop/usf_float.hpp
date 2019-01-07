// ----------------------------------------------------------------------------
// @file    usf_float.hpp
// @brief   Floating point conversion and helper functions. Naive and limited
//          implementation with the usual precision/rounding errors (good for now).
// @date    07 January 2019
// ----------------------------------------------------------------------------

#if !defined(USF_DISABLE_FLOAT_SUPPORT)

#ifndef USF_FLOAT_HPP
#define USF_FLOAT_HPP

namespace usf
{
namespace internal
{

class Float
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC STATIC FUNCTIONS
        // --------------------------------------------------------------------

        template <typename CharT> static USF_CPP14_CONSTEXPR
        int convert(CharT* const significand, int& exponent,
                    double value, const bool format_fixed, const int precision) noexcept
        {
            uint64_t ipart = 0;
            uint64_t fpart = 0;

            int ipart_digits = 0;
            int fpart_digits = 0;

            int fpart_padding = 0;

            if(value < 1)
            {
                // Negative exponent

                value *= 1e19;

                fpart = static_cast<uint64_t>(value);
                fpart_digits = Integer::count_digits_dec(fpart);

                exponent = fpart_digits - 20;

                fpart_padding = -exponent - 1;

                //if(!format_fixed && precision > 19 - fpart_padding)
                if(fpart_padding > 14 - precision)
                {
                    fpart = static_cast<uint64_t>(value * static_cast<double>(Integer::pow10_uint64(fpart_padding)));
                    fpart_digits = Integer::count_digits_dec(fpart);
                }
            }
            else
            {
                // Positive exponent

                ipart = static_cast<uint64_t>(value);
                ipart_digits = Integer::count_digits_dec(ipart);

                fpart = static_cast<uint64_t>((value - static_cast<double>(ipart)) * 1e14);
                fpart_digits = Integer::count_digits_dec(fpart);

                exponent = ipart_digits - 1;

                fpart_padding = 14 - fpart_digits;
            }

            const auto round_index = 1 + precision + (format_fixed ? exponent : 0);

            if(round_index < 0)
            {
                // Specified precision higher than converted value.
                // Should print all zeros. Bail!
                significand[0] = '0';
                exponent = 0;
                return 1;
            }

            CharT* it = significand;

            if(ipart != 0)
            {
                it += ipart_digits;
                Integer::convert_dec(it, ipart);
            }

            if(fpart != 0)
            {
                if(ipart != 0)
                {
                    CharTraits::assign(it, '0', fpart_padding);
                }

                it += fpart_digits;
                Integer::convert_dec(it, fpart);
            }

            const auto significand_size = remove_trailing_zeros(significand, it);

            if(significand_size <= round_index)
            {
                // Rounding not needed. Bail!
                return significand_size;
            }

            //Round to the specified precision.
            return round(significand, significand_size, exponent, format_fixed, round_index);
        }

        private:

        // --------------------------------------------------------------------
        // PRIVATE STATIC FUNCTIONS
        // --------------------------------------------------------------------

        template <typename CharT> static USF_CPP14_CONSTEXPR
        int round(CharT* const significand, const int significand_size, int& exponent,
                  const bool format_fixed, const int round_index) noexcept
        {
            CharT* it = significand + round_index;

            bool round_up = false;

            if(round_index == significand_size - 1)
            {
                // Round the last digit of the significand buffer.
                // It can simultaneously be the first one if the
                // significant buffer has only one digit.

                const bool prev_digit_odd = (round_index > 0) ? (('0' - *(it - 1)) & 1) != 0 : false;

                if(*it > '5' || (*it == '5' && prev_digit_odd))
                {
                    // Round up if digit is:
                    // 1) greater than 5
                    //    e.g. 2.6 -> 3
                    // 2) exactly 5 and previous digit is odd
                    //    e.g. 2.5 -> 2
                    //    e.g. 3.5 -> 3
                    round_up = true;
                }
            }
            else if(*it >= '5')
            {
                // Round any digit except the last one. Since the trailing zeros were
                // removed, we only need to test if the digit is at least '5' because it
                // is granted that other non-zero digits are present after this position.
                round_up = true;
            }

            if(round_up)
            {
                bool carry = false;

                if(round_index > 0)
                {
                    --it;

                    do
                    {
                        if(*it < '9')
                        {
                            carry = false;
                            ++(*it);
                        }
                        else
                        {
                            carry = true;
                            *it = '0';
                        }
                    }while(--it >= significand && carry);
                }
                else
                {
                    carry = true;
                }

                // Buffer termination is not necessary since the caller functions
                // rely on the returned size and not on null terminator.

                if(carry)
                {
                    significand[0] = '1';
                    ++exponent;
                    return 1;
                }
            }
            else if(round_index == 0)
            {
                significand[0] = '0';
                exponent = 0;
                return 1;
            }

            // Do not remove the trailing zeros if format is fixed.
            if(format_fixed) { return round_index; }

            return remove_trailing_zeros(significand, significand + round_index);
        }

        // Evaluates the range [first, last), truncates all the trailing zeros and return the
        // new range size. Keeps always at least 1 element of the range (even if it is zero).
        template <typename CharT> static USF_CPP14_CONSTEXPR
        int remove_trailing_zeros(const CharT* const first, const CharT* last) noexcept
        {
            while((last - 1) > first && *(last - 1) == '0') { --last; }

            // Buffer termination is not really necessary since the caller
            // functions rely on the returned size and not on null terminator.

            return static_cast<int>(last - first);
        }
};

} // namespace internal
} // namespace usf

#endif // USF_FLOAT_HPP
#endif // !defined(USF_DISABLE_FLOAT_SUPPORT)
