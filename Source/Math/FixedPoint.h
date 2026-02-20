#pragma once

#include "Math/Constants.h"

namespace Silent::Math
{
    constexpr int Q4_SHIFT       = 4;
    constexpr int Q6_SHIFT       = 6;
    constexpr int Q8_SHIFT       = 8;
    constexpr int Q12_SHIFT      = 12;
    constexpr int FP_ANGLE_COUNT = 1 << Q12_SHIFT;
    constexpr int FP_PI          = 0x5000 / 2;

    // =====================
    // Arithmetic and Utils
    // =====================

    /** @brief Converts an integer to a fixed-point Q format.
     *
     * @note Deprecated.
     *
     * @param x Integer to convert.
     * @param shift Fixed-point shift.
     * @return `x` converted to fixed-point.
     */
    constexpr int FP_TO(float x, int shift)
    {
        return (int)ROUND(x * (1 << shift));
    }

    /** @brief Converts a float to a fixed-point Q format.
     *
     * @param x Floating-point value to convert.
     * @param shift Fixed-point shift.
     * @return `x` converted to fixed-point.
     */
    constexpr int TO_FIXED(float x, int shift)
    {
        return x * (1 << shift);
    }

    /** @brief Converts an integer from a fixed-point Q format.
     *
     * @param x Integer to convert.
     * @param shift Fixed-point shift.
     * @return `x` converted from fixed-point.
     */
    constexpr int FP_FROM(int x, int shift)
    {
        return x >> shift;
    }

    /** @brief Converts an integer from a fixed-point Q format to floating-point.
     *
     * @param x Fixed-point value to convert.
     * @param shift Fixed-point shift.
     * @return `x` converted to floating-point.
     */
    constexpr float FP_FLOAT(int x, int shift)
    {
        return (float)x / (float)FP_TO(1.0f, shift);
    }

    /** @brief Converts an integer from a scaled fixed-point Q format rounded to the nearest value.
     *
     * @param x Fixed-point value to convert.
     * @param scale Fixed-point scale.
     * @param shift Fixed-point shift.
     * @return `x` rounded and converted from fixed-point.
     */
    constexpr int FP_ROUND_SCALED(int x, int scale, int shift)
    {
        return (x + ((TO_FIXED(1.0f, shift) * scale) - 1)) / (TO_FIXED(1.0f, shift) * scale);
    }

    /** @brief Converts an integer from a fixed-point Q format rounded toward 0.
     *
     * @param x Fixed-point value to convert.
     * @param shift Fixed-point shift.
     * @return `x` rounded toward 0 and converted from fixed-point.
     */
    constexpr int FP_ROUND_TO_ZERO(int x, int shift)
    {
        return (FP_FROM(x, shift) + (x >> 31)) >> 1;
    }

    /** @brief Multiplies two integers in a fixed-point Q format.
     *
     * @param a First fixed-point factor.
     * @param b Second fixed-point factor.
     * @param shift Fixed-point shift.
     * @return Fixed-point product of `a` and `b`.
     */
    constexpr int FP_MULTIPLY(int a, int b, int shift)
    {
        return (a * b) >> shift;
    }

    /** @brief Multiplies two integers in a fixed-point Q format, using 64-bit intermediates for higher precision.
     *
     * @param a First fixed-point factor.
     * @param b Second fixed-point factor.
     * @param shift Fixed-point shift.
     * @return Precise fixed-point product of `a` and `b`.
     */
    constexpr int FP_MULTIPLY_PRECISE(int a, int b, int shift)
    {
        return ((int64)a * (int64)b) >> shift;
    }

    /** @brief Multiplies an integer in a fixed-point Q format by a float converted to a fixed-point Q format.
     *
     * @param a First fixed-point factor.
     * @param b Second floating-point factor.
     * @param shift Fixed-point shift.
     * @return Fixed-point product of `a` and `b`.
     */
    constexpr int FP_MULTIPLY_FLOAT(int a, float b, int shift)
    {
        return FP_MULTIPLY(a, FP_TO(b, shift), shift);
    }

    /** @brief Multiplies an integer in a fixed-point Q format by a float converted to fixed-point Q format,
     * using a 64-bit intermediates for higher precision.
     *
     * @param a First fixed-point factor.
     * @param b Second floating-point factor.
     * @param shift Fixed-point shift.
     * @return Precise product of `a` and `b` converted from fixed-point.
     */
    constexpr int FP_MULTIPLY_FLOAT_PRECISE(int a, float b, int shift)
    {
        return FP_MULTIPLY((int64)(a), (int64)TO_FIXED(b, shift), shift);
    }

    /** @brief Divides an integer in a fixed-point Q format by another.
     *
     * @param a Fixed-point numerator.
     * @param b Fixed-point denominator.
     * @return Fixed-point result of `a` divided by `b`.
     */
    constexpr int FP_DIVIDE(int a, int b, int shift)
    {
        return (a << shift) / b;
    }

    /** @brief Squares a fixed-point value.
     *
     * @param x Fixed-point value to be squared.
     * @param shift Fixed-point shift.
     * @return Fixed-point square of `x`.
     */
    constexpr int FP_SQUARE(int x, int shift)
    {
        return FP_MULTIPLY(x, x, shift);
    }

    /** @brief Squares a fixed-point value, using 64-bit intermediates for higher precision.
     *
     * @param x Fixed-point value to be squared.
     * @param shift Fixed-point shift.
     * @return Fixed-point square of `x`.
     */
    constexpr int FP_SQUARE_PRECISE(int x, int shift)
    {
        return FP_MULTIPLY_PRECISE(x, x, shift);
    }

    /** @brief Multiplies two integers in Q19.12 fixed-point.
     *
     * @param a First Q19.12 fixed-point factor.
     * @param b Second Q19.12 fixed-point factor.
     * @return Q19.12 product of `a` and `b`.
     */
    constexpr q19_12 Q12_MULT(q19_12 a, q19_12 b)
    {
        return FP_MULTIPLY(a, b, Q12_SHIFT);
    }

    /** @brief Multiplies two integers in Q19.12 fixed-point, using 64-bit intermediates for higher precision.
     *
     * @param a First Q19.12 fixed-point factor.
     * @param b Second Q19.12 fixed-point factor.
     * @return Precise Q19.12 product of `a` and `b`.
     */
    constexpr q19_12 Q12_MULT_PRECISE(q19_12 a, q19_12 b)
    {
        return FP_MULTIPLY_PRECISE(a, b, Q12_SHIFT);
    }

    /** @brief Multiplies an integer in Q19.12 fixed-point by a float converted to Q19.12 fixed-point.
     *
     * @param a First Q19.12 fixed-point factor.
     * @param b Second floating-point factor.
     * @return Q19.12 product of `a` and `b`.
     */
    constexpr q19_12 Q12_MULT_FLOAT(q19_12 a, float b)
    {
        return FP_MULTIPLY_FLOAT(a, b, Q12_SHIFT);
    }

    /** @brief Multiplies an integer in Q19.12 fixed-point by a float converted to Q19.12 fixed-point,
     * using 64-bit intermediates for higher precision.
     *
     * @param a First Q19.12 fixed-point factor.
     * @param b Second floating-point factor.
     * @return Precise Q19.12 product of `a` and `b`.
     */
    constexpr q19_12 Q12_MULT_FLOAT_PRECISE(q19_12 a, float b)
    {
        return FP_MULTIPLY_FLOAT_PRECISE(a, b, Q12_SHIFT);
    }

    /** @brief Divides an integer in Q19.12 fixed-point by another.
     *
     * @param a Q19.12 fixed-point numerator.
     * @param b Q19.12 fixed-point denominator.
     * @return Q19.12 result of `a` divided by `b`.
     */
    constexpr q19_12 Q12_DIV(q19_12 a, q19_12 b)
    {
        return FP_DIVIDE(a, b, Q12_SHIFT);
    }

    /** @brief Squares a Q19.12 value.
     *
     * @param x Q19.12 value to be squared.
     * @return Q19.12 square of `x`.
     */
    constexpr q19_12 Q12_SQUARE(q19_12 x)
    {
        return FP_SQUARE(x, Q12_SHIFT);
    }

    /** @brief Squares a fixed-point value, using 64-bit intermediates for higher precision.
     *
     * @param x Q19.12 value to be squared.
     * @return Q19.12 square of `x`.
     */
    constexpr q19_12 Q12_SQUARE_PRECISE(q19_12 x)
    {
        return FP_SQUARE_PRECISE(x, Q12_SHIFT);
    }

    /** @brief Computes the square 2D distance between two positions in Q19.12 fixed-point,
     * using Q21.8 fixed-point intermediates to avoid overflow.
     *
     * @param from First position.
     * @param to Second position.
     * @param return 2D distance between two positions.
     */
    #define Q12_2D_DISTANCE_SQR(from, to)         \
        (SQUARE(Q12_TO_Q8((to).vx - (from).vx)) + \
        SQUARE(Q12_TO_Q8((to).vz - (from).vz)))

    // ==================================
    // Raw Q Format Conversion and Utils
    // ==================================

    /** @brief Converts a floating-point value to Q*.4 fixed-point.
     *
     * @param x Value to convert (`float`).
     * @return `x` converted to Q*.4 fixed-point.
     */
    #define Q4(x) \
        TO_FIXED(x, Q4_SHIFT)

    /** @brief Converts a floating-point value to Q*.6 fixed-point.
     *
     * @param x Value to convert (`float`).
     * @return `x` converted to Q*.6 fixed-point.
     */
    #define Q6(x) \
        TO_FIXED(x, Q6_SHIFT)

    /** @brief Converts a floating-point value to Q*.8 fixed-point.
     *
     * @param x Value to convert (`float`).
     * @return `x` converted to Q*.8 fixed-point.
     */
    #define Q8(x) \
        TO_FIXED(x, Q8_SHIFT)

    /** @brief Converts a floating-point value to clamped Q*.8 fixed-point.
     *
     * @param x Value to convert (`float`).
     * @return `x` converted to clamped Q*.8 fixed-point.
     */
    #define Q8_CLAMPED(x) \
        CLAMP(Q8(x), 0, Q8(1.0f) - 1)

    /** @brief Converts a floating-point value to Q*.12 fixed-point.
     *
     * @param x Value to convert (`float`).
     * @return `x` converted to Q*.12 fixed-point.
     */
    #define Q12(x) \
        TO_FIXED(x, Q12_SHIFT)

    /** @brief Converts a floating-point value to clamped Q*.12 fixed-point.
     *
     * @param x Value to convert (`float`).
     * @return `x` converted to clamped Q*.12 fixed-point.
     */
    #define Q12_CLAMPED(x) \
        CLAMP(Q12(x), 0, Q12(1.0f) - 1)

    /** @brief Converts a fixed-point value from Q*.4 to Q*.8.
     *
     * @param x Q*.4 fixed-point value to convert.
     * @return `x` converted to Q*.8 fixed-point.
     */
    #define Q4_TO_Q8(x) \
        ((x) << 4)

    /** @brief Converts a fixed-point value from Q*.4 to Q*.12.
     *
     * @param x Q*.4 fixed-point value to convert.
     * @return `x` converted to Q*.12 fixed-point.
     */
    #define Q4_TO_Q12(x) \
        ((x) << 8)

    /** @brief Converts a fixed-point value from Q*.6 to Q*.12.
     *
     * @param x Q*.6 fixed-point value to convert.
     * @return `x` converted to Q*.12 fixed-point.
     */
    #define Q6_TO_Q12(x) \
        ((x) << 6)

    /** @brief Converts a fixed-point value from Q*.8 to Q*.12.
     *
     * @param x Q*.8 fixed-point value to convert.
     * @return `x` converted to Q*.12 fixed-point.
     */
    #define Q8_TO_Q12(x) \
        ((x) << 4)

    /** @brief Converts a fixed-point value from Q*.8 to Q*.4.
     *
     * @param x Q*.8 fixed-point value to convert.
     * @return `x` converted to Q*.4 fixed-point.
     */
    #define Q8_TO_Q4(x) \
        ((x) >> 4)

    /** @brief Converts a fixed-point value from Q*.10 to Q*.12.
     *
     * @param x Q*.10 fixed-point value to convert.
     * @return `x` converted to Q*.12 fixed-point.
     */
    #define Q10_TO_Q12(x) \
        ((x) << 2)

    /** @brief Converts a fixed-point value from Q*.12 to Q*.4.
     *
     * @param x Q*.12 fixed-point value to convert.
     * @return `x` converted to Q*.4 fixed-point.
     */
    #define Q12_TO_Q4(x) \
        ((x) >> 8)

    /** @brief Converts a fixed-point value from Q*.12 to Q*.6.
     *
     * @param x Q*.12 fixed-point value to convert.
     * @return `x` converted to Q*.6 fixed-point.
     */
    #define Q12_TO_Q6(x) \
        ((x) >> 6)

    /** @brief Converts a fixed-point value from Q*.12 to Q*.8.
     *
     * @param x Q*.12 fixed-point value to convert.
     * @return `x` converted to Q*.8 fixed-point.
     */
    #define Q12_TO_Q8(x) \
        ((x) >> 4)

    /** @brief Converts a fixed-point value from Q*.12 to Q*.10.
     *
     * @param x Q*.12 fixed-point value to convert.
     * @return `x` converted to Q*.10 fixed-point.
     */
    #define Q12_TO_Q10(x) \
        ((x) >> 2)

    /** @brief Extracts the fractional part of a value in Q*.12 fixed-point.
     *
     * @param x Q*.12 fixed-point value.
     * @return Fractional part of `x` in Q*.12 fixed-point.
     */
    #define Q12_FRACT(x) \
        ((x) & 0xFFF)

    // =======================================
    // Abstract Q Format Conversion and Utils
    // =======================================

    /** @brief Converts a normalized floating-point analog stick value in the range `[-1.0f, 1.0f]` to Q0.7 fixed-point,
     * clamped integer range `[-128, 127]`.
     *
     * @param analog Analog stick value (`float`).
     * @return Analog stick value in Q0.7 fixed-point, clamped integer range `[-128, 127]`.
     */
    #define FP_STICK(analog)                                                  \
        (s8)(((analog) >= 0) ? CLAMP(Q8(analog) / 2, 0, (Q8(1.0f) / 2) - 1) : \
                            -CLAMP(Q8(ABS(analog)) / 2, 0, Q8(1.0f) / 2))

    /** @brief Converts a normalized floating-point color component in the range `[0.0f, 1.0f]` to Q0.8 fixed-point,
     * integer range `[0, 255]`.
     *
     * TODO: Deprecated, don't use. Doesn't make sense to have `float` color components in this project.
     *
     * @param comp Floating-point color component.
     * @return Q0.8 fixed-point color component, clamped integer range `[0, 255]` (`u8`).
     */
    constexpr uchar FP_COLOR(float comp)
    {
        return (uchar)(comp * (FP_TO(1.0f, Q8_SHIFT) - 1));
    }

    /** @brief Converts an 8-bit color value in the range `[0, 255]` to a normalized color format in the range
     * `[0.0f, 1.0f]`.
     *
     * @param comp Fixed-point color component.
     * @return Floating-point color component.
     */
    constexpr float FP_COLOR_FROM(uchar comp)
    {
        return (comp == FP_COLOR(1.0f)) ? 1.0f : std::clamp((float)comp / (float)FP_TO(1.0f, Q8_SHIFT), 0.0f, 1.0f);
    }

    /** @brief Converts floating-point degrees to signed Q3.12 fixed-point, full rotation integer range `[0, 4096]`.
     *
     * This angle format is used in world space.
     *
     * @note 1 degree = 11.377778 units.
     *
     * @param deg Degrees (`float`).
     * @return Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]`.
     */
    constexpr q3_12 FP_ANGLE(float deg)
    {
        return (q3_12)ROUND(deg * (360.0f / (float)FP_ANGLE_COUNT));
    }

    /** @brief Converts floating-point radians to fixed-point degrees in Q1.15 format.
     *
     * @param rad Angle in radians.
     * @return Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]`.
     */
    constexpr q3_12 FP_ANGLE_FROM_RAD(float rad)
    {
        return FP_ANGLE(rad / (PI / 180.0f));
    }

    /** @brief Converts fixed-point degrees in Q1.15 format to floating-point radians.
     *
     * @param deg Angle in degrees.
     * @return Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]`
     */
    constexpr float FP_ANGLE_TO_RAD(q3_12 deg)
    {
        return (deg * (360.0f / (float)FP_ANGLE_COUNT)) * (PI / 180.0f);
    }

    /** @brief Converts floating-point degrees to unsigned Q0.8 fixed-point, clamped full rotation integer range `[0, 255]`.
     *
     * This angle format is used in map data.
     *
     * @note 1 degree = 0.711111 units.
     *
     * @param deg Degrees (`float`).
     * @return Unsigned Q0.8 fixed-point packed angle, clamped full rotation integer range `[0, 255]` (`u8`).
     */
    #define FP_ANGLE_PACKED(deg) \
        (u8)Q8_CLAMPED((deg) / 360.0f)

    /** @brief Converts a signed Q3.12 fixed-point angle, full rotation integer range `[0, 4096]` to
     * unsigned Q0.8 fixed-point, integer range `[0, 255]`.
     *
     * @param angle Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]`.
     * @return Unsigned Q0.8 fixed-point packed angle, full rotation integer range `[0, 255]` (`short`).
     */
    #define FP_ANGLE_TO_PACKED(angle) \
        Q12_TO_Q8(deg);

    /** @brief Converts an unsigned Q0.8 fixed-point packed angle, full rotation integer range `[0, 255]` to
     * unsigned Q3.12 fixed-point, full rotation integer range `[0, 4096]`.
     *
     * @param packedAngle Unsigned Q0.8 fixed-point packed angle, full rotation integer range `[0, 255]`.
     * @return Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]` (`short`).
     */
    #define FP_ANGLE_FROM_PACKED(packedAngle) \
        (short)Q8_TO_Q12(packedAngle)

    /** @brief Normalizes a signed Q3.12 fixed-point angle to the clamped unsigned integer range `[0, 4095]`.
     *
     * @note Has the same effect as `FP_ANGLE_NORM_U`. Could they somehow be combined?
     *
     * @param angle Signed Q3.12 fixed-point angle, full rotation integer range `[-2048, 2047]`.
     * @return Unsigned Q3.12 fixed-point angle, wrapped to the clamped integer range `[0, 4095]` (`short`).
     */
    #define FP_ANGLE_ABS(angle) \
        Q12_FRACT((angle) + FP_ANGLE(360.0f))

    /** @brief Normalizes an unsigned Q3.12 fixed-point angle to the clamped signed integer range `[-2048, 2047]`.
     *
     * @param angle Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4095]`.
     * @return Signed Q3.12 fixed-point angle wrapped to the clamped integer range `[-2048, 2047]` (`short`).
     */
    #define FP_ANGLE_NORM_S(angle) \
        (((angle) << 20) >> 20)

    /** @brief Normalizes a signed Q3.12 fixed-point angle to the clamped unsigned range `[0, 4095]`.
     *
     * @param angle Signed Q3.12 fixed-point angle, full rotation integer range `[-2048, 2047]`.
     * @return Unsigned Q3.12 fixed-point angle, wrapped to the clamped integer range `[0, 4095]` (`short`).
     */
    #define FP_ANGLE_NORM_U(angle) \
        ((angle) & (FP_ANGLE(360.0f) - 1))

    /** @brief Converts floating-point radians in the range `[-PI, PI]` to the fixed-point full rotation,
     * integer range `[0, 20480]`.
     *
     * This angle format is only used in `vcSetDataToVwSystem`.
     *
     * @note π = 10240 units.
     *
     * @param rad Radians.
     * @return Fixed-point radian representation, full rotation integer range `[0, 20480]`.
     */
    constexpr int FP_RADIAN(float rad)
    {
        return (((rad < 0.0f) ? (PI + (PI - ABS(rad))) : rad) * ((float)FP_PI / PI)) *
               ((rad < 0.0f || rad >= PI) ? 1.0f : 2.0f);
    }
}
