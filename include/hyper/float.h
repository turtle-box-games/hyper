/// @file float.h
/// Definitions for floating-point numerical data types.
/// Defines developer-friendly type names for specifying exactly the size of value needed.

#ifndef HYPER_FLOAT_H
#define HYPER_FLOAT_H

#include <cfloat>   // For floating-point types.
#include <cmath>    // For infinity values.
#include "limits.h" // For minValue() and maxValue().

namespace hyper {
    /// @brief Gets the representation of infinity for the given type.
    /// @tparam T Type to get infinity for.
    /// @return Infinity for the type.
    template<typename T>
    T infinity();

    /// @brief Gets the representation of negative infinity for the given type.
    /// @tparam T Type to get negative infinity for.
    /// @return Negative infinity for the type.
    template<typename T>
    T negativeInfinity();

    /// @brief 32-bit floating-point value.
    typedef float float32;

    /// @brief Gets the minimum value that a 32-bit floating-point value can hold.
    /// @return 1.175494 x 10^-38
    template<>
    inline constexpr float32 minValue() noexcept {
        return FLT_MIN;
    }

    /// @brief Gets the maximum value that a 32-bit floating-point value can hold.
    /// @return 3.402823 x 10^38
    template<>
    inline constexpr float32 maxValue() noexcept {
        return FLT_MAX;
    }

    /// @brief Gets the value representing infinity for a 32-bit floating-point value.
    /// @return Infinity.
    template<>
    inline constexpr float32 infinity() noexcept {
        return HUGE_VALF;
    }

    /// @brief Gets the value representing negative infinity for a 32-bit floating-point value.
    /// @return Negative infinity.
    template<>
    inline constexpr float32 negativeInfinity() noexcept {
        return -HUGE_VALF;
    }

    /// @brief 64-bit floating-point value
    typedef double float64;

    /// @brief Gets the minimum value that a 64-bit floating-point value can hold.
    /// @return 2.225074 x 10^-308
    template<>
    inline constexpr float64 minValue() noexcept {
        return DBL_MIN;
    }

    /// @brief Gets the maximum value that a 64-bit floating-point value can hold.
    /// @return 1.797693 x 10^308
    template<>
    inline constexpr float64 maxValue() noexcept {
        return DBL_MAX;
    }

    /// @brief Gets the value representing infinity for a 64-bit floating-point value.
    /// @return Infinity.
    template<>
    inline constexpr float64 infinity() noexcept {
        return HUGE_VAL;
    }

    /// @brief Gets the value representing negative infinity for a 64-bit floating-point value.
    /// @return Negative infinity.
    template<>
    inline constexpr float64 negativeInfinity() noexcept {
        return -HUGE_VAL;
    }
}

#endif // HYPER_FLOAT_H
