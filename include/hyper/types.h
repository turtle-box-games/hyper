/// @file types.h
/// Definitions for numerical data types.
/// Defines developer-friendly type names for specifying exactly the size of value needed.

#ifndef HYPER_TYPES_H
#define HYPER_TYPES_H

#include <cstdint> // For integer types.
#include <cfloat>  // For floating-point types.
#include <cmath>   // Ditto.

namespace hyper
{
    /// @brief Gets the minimum value that a type can hold.
    /// @tparam T Type to get the minimum value of.
    /// @return Minimum value that can be contained by @p T.
    template<typename T>
    T min_value();

    /// @brief Gets the maximum value that a type can hold.
    /// @tparam T Type to get the maximum value of.
    /// @return Maximum value that can be contained by @p T.
    template<typename T>
    T max_value();

    /// @brief Gets the representation of infinity for the given type.
    /// @tparam T Type to get infinity for.
    /// @return Infinity for the type.
    template<typename T>
    T infinity();

    /// @brief Gets the representation of negative infinity for the given type.
    /// @tparam T Type to get negative infinity for.
    /// @return Negative infinity for the type.
    template<typename T>
    T negative_infinity();

    /// @brief 8-bit signed integer.
    /// @details Values can range from -128 to 127.
    typedef int8_t int8;

    /// @brief Gets the minimum value that an 8-bit signed integer can hold.
    /// @return -128
    template<>
    inline constexpr int8 min_value() noexcept
    {
        return INT8_MIN;
    }

    /// @brief Gets the maximum value that an 8-bit signed integer can hold.
    /// @return 127
    template<>
    inline constexpr int8 max_value() noexcept
    {
        return INT8_MAX;
    }

    /// @brief 8-bit unsigned integer.
    /// @details Values can range from 0 to 255.
    typedef uint8_t uint8;

    /// @brief Gets the minimum value that an 8-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint8 min_value() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that an 8-bit unsigned integer can hold.
    /// @return 255
    template<>
    inline constexpr uint8 max_value() noexcept
    {
        return UINT8_MAX;
    }

    /// @brief 16-bit signed integer.
    /// @details Values can range from -32,768 to 32,767.
    typedef int16_t int16;

    /// @brief Gets the minimum value that a 16-bit signed integer can hold.
    /// @return -32,768
    template<>
    inline constexpr int16 min_value() noexcept
    {
        return INT16_MIN;
    }

    /// @brief Gets the maximum value that a 16-bit signed integer can hold.
    /// @return 32,767
    template<>
    inline constexpr int16 max_value() noexcept
    {
        return INT16_MAX;
    }

    /// @brief 16-bit unsigned integer.
    /// @details Values can range from 0 to 65,535.
    typedef uint16_t uint16;

    /// @brief Gets the minimum value that a 16-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint16 min_value() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that a 16-bit unsigned integer can hold.
    /// @return 65,535
    template<>
    inline constexpr uint16 max_value() noexcept
    {
        return UINT16_MAX;
    }

    /// @brief 32-bit signed integer.
    /// @details Values can range from -2,147,483,648 to 2,147,483,647.
    typedef int32_t int32;

    /// @brief Gets the minimum value that a 32-bit signed integer can hold.
    /// @return -2,147,483,648
    template<>
    inline constexpr int32 min_value() noexcept
    {
        return INT32_MIN;
    }

    /// @brief Gets the maximum value that a 32-bit signed integer can hold.
    /// @return 2,147,483,647
    template<>
    inline constexpr int32 max_value() noexcept
    {
        return INT32_MAX;
    }

    /// @brief 32-bit unsigned integer.
    /// @details Values can range from 0 to 4,294,967,295.
    typedef uint32_t uint32;

    /// @brief Gets the minimum value that a 32-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint32 min_value() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that a 32-bit unsigned integer can hold.
    /// @return 4,294,967,295
    template<>
    inline constexpr uint32 max_value() noexcept
    {
        return UINT32_MAX;
    }

    /// @brief 64-bit signed integer.
    /// @details Values can range from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
    typedef int64_t int64;

    /// @brief Gets the minimum value that a 64-bit signed integer can hold.
    /// @return -9,223,372,036,854,775,808
    template<>
    inline constexpr int64 min_value() noexcept
    {
        return INT64_MIN;
    }

    /// @brief Gets the maximum value that a 64-bit signed integer can hold.
    /// @return 9,223,372,036,854,775,807
    template<>
    inline constexpr int64 max_value() noexcept
    {
        return INT64_MAX;
    }

    /// @brief 64-bit unsigned integer.
    /// @details Values can range from 0 to 18,446,744,073,709,551,615.
    typedef uint64_t uint64;

    /// @brief Gets the minimum value that a 64-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint64 min_value() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that a 64-bit unsigned integer can hold.
    /// @return 18,446,744,073,709,551,615
    template<>
    inline constexpr uint64 max_value() noexcept
    {
        return UINT64_MAX;
    }

    /// @brief 32-bit floating-point value.
    typedef float float32;

    /// @brief Gets the minimum value that a 32-bit floating-point value can hold.
    /// @return 1.175494 x 10^-38
    template<>
    inline constexpr float32 min_value() noexcept
    {
        return FLT_MIN;
    }

    /// @brief Gets the maximum value that a 32-bit floating-point value can hold.
    /// @return 3.402823 x 10^38
    template<>
    inline constexpr float32 max_value() noexcept
    {
        return FLT_MAX;
    }

    /// @brief Gets the value representing infinity for a 32-bit floating-point value.
    /// @return Infinity.
    template<>
    inline constexpr float32 infinity() noexcept
    {
        return HUGE_VALF;
    }

    /// @brief Gets the value representing negative infinity for a 32-bit floating-point value.
    /// @return Negative infinity.
    template<>
    inline constexpr float32 negative_infinity() noexcept
    {
        return -HUGE_VALF;
    }

    /// @brief 64-bit floating-point value
    typedef double float64;

    /// @brief Gets the minimum value that a 64-bit floating-point value can hold.
    /// @return 2.225074 x 10^-308
    template<>
    inline constexpr float64 min_value() noexcept
    {
        return DBL_MIN;
    }

    /// @brief Gets the maximum value that a 64-bit floating-point value can hold.
    /// @return 1.797693 x 10^308
    template<>
    inline constexpr float64 max_value() noexcept
    {
        return DBL_MAX;
    }

    /// @brief Gets the value representing infinity for a 64-bit floating-point value.
    /// @return Infinity.
    template<>
    inline constexpr float64 infinity() noexcept
    {
        return HUGE_VAL;
    }

    /// @brief Gets the value representing negative infinity for a 64-bit floating-point value.
    /// @return Negative infinity.
    template<>
    inline constexpr float64 negative_infinity() noexcept
    {
        return -HUGE_VAL;
    }
}

#endif //HYPER_TYPES_H
