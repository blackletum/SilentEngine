#pragma once

#include "Framework.h"

namespace Silent::Math
{
    constexpr float PI           = glm::pi<float>();
    constexpr float PI_MUL_2     = PI * 2.0f;
    constexpr float PI_MUL_4     = PI * 4.0f;
    constexpr float PI_DIV_2     = PI / 2.0f;
    constexpr float PI_DIV_4     = PI / 4.0f;
    constexpr float SQRT_2       = 1.41421356237f;
    constexpr float EPSILON      = 0.00001f;
    constexpr uint  GOLDEN_RATIO = 0x9E3779B9;

    constexpr int TRI_VERTEX_COUNT  = 3;
    constexpr int QUAD_VERTEX_COUNT = 4;

    enum class ContainmentType
    {
        None,
        Intersects,
        Contains
    };

    /** @brief Squares a value.
     *
     * @param x Value to be squared.
     * @return `x` squared.
     */
    constexpr auto SQUARE = [](auto x)
    {
        return x * x;
    };

    /** @brief Determines the smaller of two values.
     *
     * @param a First value.
     * @param b Second value.
     * @return `true` if `a` is smaller than `b`, `false` otherwise.
     */
    constexpr auto MIN = [](auto a, auto b)
    {
        return (a < b) ? a : b;
    };

    /** @brief Determines the larger of two values.
     *
     * @param a First value.
     * @param b Second value.
     * @return `true` if `a` is larger than `b`, `false` otherwise.
     */
    constexpr auto MAX = [](auto a, auto b)
    {
        return (a > b) ? a : b;
    };

    /** @brief Clamps a value to the range `[min, max]`.
     *
     * @param x Value to clamp.
     * @param min Lower range.
     * @param max Upper range.
     * @return `x` clamped to the range `[min, max]`.
     */
    constexpr auto CLAMP = [](auto x, auto min, auto max)
    {
        return (x < min) ? min : ((x > max) ? max : x);
    };

    /** @brief Computes the absolute value.
     *
     * @param x Value.
     * @return Absolute value of `x`.
     */
    constexpr auto ABS = [](auto x)
    {
        return (x < 0) ? -x : x;
    };

    /** @brief Computes the absolute value of an `s32` by shifting.
     *
     * @param x Value.
     * @return Absolute value of `x`.
     */
    #define ABS_32(x) \
        (((x) ^ ((x) >> 31)) - ((x) >> 31))

    /** @brief Computes the absolute sum of two values.
     *
     * @param a First value.
     * @param b Second value.
     * @return Absolute sum of `a` and `b`.
     */
    constexpr auto ABS_ADD = [](auto a, auto b)
    {
        return (a >= 0) ? (b + a) : (b - a);
    };

    /** @brief Computes the absolute difference between two values.
     *
     * @param a First value.
     * @param b Second value.
     * @return Absolute difference between `a` and `b`.
     */
    constexpr auto ABS_DIFF = [](auto a, auto b)
    {
        return ABS(a - b);
    };

    /** @brief Checks if two values have different signs.
     *
     * @param a First value.
     * @param b Second value.
     * @return `true` if `a` and `b` have different signs, `false` otherwise.
     */
    constexpr auto DIFF_SIGN = [](auto a, auto b)
    {
        return (a >= 0 && b < 0) || (a < 0 && b >= 0);
    };

    /** @brief Rounds a floating-point value.
     *
     * @param x Value to round.
     * @return `x` rounded to the closest integer.
     */
    constexpr float ROUND(float x)
    {
        return (float)((x > 0.0f) ? (int)(x + 0.5f) : (int)(x - 0.5f));
    }

    /** @brief Floors a floating-point value.
     *
     * @param x Value to floor.
     * @return `x` floored to the closest integer.
     */
    constexpr float FLOOR(float x)
    {
        return (float)((int)x - ((x < 0.0f) && x != (int)x));
    }

    /** @brief Floors a value to the closest step.
     *
     * @param x Value to floor.
     * @param step Flooring step.
     * @return `x` floored to the closest `step`.
     */
    #define FLOOR_TO_STEP(x, step) \
        (((x) >= 0) ? ((x) / (step)) : (((x) - ((step) - 1)) / (step)))

    /** @brief Ceils a floating-point value.
     *
     * @param x Value to ceil.
     * @return `x` ceiled to the closest integer.
     */
    constexpr float CEIL(float x)
    {
        return (float)((int)x + ((x > 0.0f) && x != (int)x));
    }

    /** @brief Converts degrees to radians.
     *
     * @param deg Angle in degrees to covnert.
     * @return Angle converted to radians.
     */
    constexpr float DEG_TO_RAD(float deg)
    {
        return (deg * PI) / 180.0f;
    }
}
