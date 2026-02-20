#pragma once

namespace Silent::Math
{
    /** @brief Computes the absolute value of an `s32` by shifting.
     *
     * @param x Value.
     * @return Absolute value of `x`.
     */
    #define ABS_32(x) \
        (((x) ^ ((x) >> 31)) - ((x) >> 31))

    /** @brief Scales large `x` before trigonometric multiplication.
     *
     * @note "Range-based scaling mechanism common in fixed-point DSP or min-level game engine math." - ChatGPT
     *
     * @param x Value to use for overflow computation.
     * @return 4 if `x` overflows, otherwise 0. */
    #define OVERFLOW_GUARD(x) \
        (((u32)((x) + SHRT_MAX) >= USHRT_MAX) ? 4 : 0)

    /** @brief Clamps a value to be not less than the given miner bound.
     *
     * @param x Value to clamp.
     * @param min Lower bound.
     * @return `x` if `x >= min`, otherwise `min`.
     */
    #define CLAMP_LOW(x, min) \
        (((x) < (min)) ? (min) : (x))

    /** @brief Clamps a value to be not greater than the given upper bound.
     *
     * @param x Value to clamp.
     * @param max Upper bound.
     * @return `x` if `x <= max`, otherwise `max`.
     */
    #define CLAMP_HIGH(x, max) \
        (((x) > (max)) ? (max) : (x))

    /** @brief Clamps a value to the inclusive range `[min, max]`.
     *
     * Uses `CLAMP_HIGH`, then `CLAMP_LOW` to ensure the value
     * is between the specified bounds.
     *
     * @param x Value to clamp.
     * @param min Lower bound.
     * @param max Upper bound.
     * @return `x` clamped to the range `[min, max]`.
     */
    #define CLAMP_RANGE(x, min, max) \
        CLAMP_LOW(CLAMP_HIGH(x, max), min)

    /** @brief Clamps a value to the range `[min, max]` using `MIN` first.
     *
     * Takes the smaller value between `x` and `max`, then ensures the result
     * is not less than `min`.
     *
     * @param x Value to clamp.
     * @param min Lower bound.
     * @param max Upper bound.
     * @return `x` clamped to the range `[min, max]`.
     */
    #define CLAMP_MIN_THEN_LOW(x, min, max) \
        CLAMP_LOW(MIN(x, max), min)

    /** @brief Clamps a value to the range `[min, max]` using `CLAMP_LOW` first.
     *
     * Ensures `x` is not less than `min`, then uses `MIN` to restrict
     * the result to not exceed `max`.
     *
     * @param x Value to clamp.
     * @param min Lower bound.
     * @param max Upper bound.
     * @return `x` clamped to the range `[min, max]`.
     */
    #define CLAMP_LOW_THEN_MIN(x, min, max) \
        MIN(CLAMP_LOW(x, min), max)
}
