/// @file integer.h
/// Definitions for integer data types.
/// Defines developer-friendly type names for specifying exactly the size of value needed.

#ifndef HYPER_INTEGER_H
#define HYPER_INTEGER_H

#include <cstdint>  // For integer types.
#include "limits.h" // For minValue() and maxValue().

namespace hyper
{
    /// @brief 8-bit signed integer.
    /// @details Values can range from -128 to 127.
    typedef int8_t int8;

    /// @brief Gets the minimum value that an 8-bit signed integer can hold.
    /// @return -128
    template<>
    inline constexpr int8 minValue() noexcept
    {
        return INT8_MIN;
    }

    /// @brief Gets the maximum value that an 8-bit signed integer can hold.
    /// @return 127
    template<>
    inline constexpr int8 maxValue() noexcept
    {
        return INT8_MAX;
    }

    /// @brief 8-bit unsigned integer.
    /// @details Values can range from 0 to 255.
    typedef uint8_t uint8;

    /// @brief Gets the minimum value that an 8-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint8 minValue() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that an 8-bit unsigned integer can hold.
    /// @return 255
    template<>
    inline constexpr uint8 maxValue() noexcept
    {
        return UINT8_MAX;
    }

    /// @brief 16-bit signed integer.
    /// @details Values can range from -32,768 to 32,767.
    typedef int16_t int16;

    /// @brief Gets the minimum value that a 16-bit signed integer can hold.
    /// @return -32,768
    template<>
    inline constexpr int16 minValue() noexcept
    {
        return INT16_MIN;
    }

    /// @brief Gets the maximum value that a 16-bit signed integer can hold.
    /// @return 32,767
    template<>
    inline constexpr int16 maxValue() noexcept
    {
        return INT16_MAX;
    }

    /// @brief 16-bit unsigned integer.
    /// @details Values can range from 0 to 65,535.
    typedef uint16_t uint16;

    /// @brief Gets the minimum value that a 16-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint16 minValue() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that a 16-bit unsigned integer can hold.
    /// @return 65,535
    template<>
    inline constexpr uint16 maxValue() noexcept
    {
        return UINT16_MAX;
    }

    /// @brief 32-bit signed integer.
    /// @details Values can range from -2,147,483,648 to 2,147,483,647.
    typedef int32_t int32;

    /// @brief Gets the minimum value that a 32-bit signed integer can hold.
    /// @return -2,147,483,648
    template<>
    inline constexpr int32 minValue() noexcept
    {
        return INT32_MIN;
    }

    /// @brief Gets the maximum value that a 32-bit signed integer can hold.
    /// @return 2,147,483,647
    template<>
    inline constexpr int32 maxValue() noexcept
    {
        return INT32_MAX;
    }

    /// @brief 32-bit unsigned integer.
    /// @details Values can range from 0 to 4,294,967,295.
    typedef uint32_t uint32;

    /// @brief Gets the minimum value that a 32-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint32 minValue() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that a 32-bit unsigned integer can hold.
    /// @return 4,294,967,295
    template<>
    inline constexpr uint32 maxValue() noexcept
    {
        return UINT32_MAX;
    }

    /// @brief 64-bit signed integer.
    /// @details Values can range from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
    typedef int64_t int64;

    /// @brief Gets the minimum value that a 64-bit signed integer can hold.
    /// @return -9,223,372,036,854,775,808
    template<>
    inline constexpr int64 minValue() noexcept
    {
        return INT64_MIN;
    }

    /// @brief Gets the maximum value that a 64-bit signed integer can hold.
    /// @return 9,223,372,036,854,775,807
    template<>
    inline constexpr int64 maxValue() noexcept
    {
        return INT64_MAX;
    }

    /// @brief 64-bit unsigned integer.
    /// @details Values can range from 0 to 18,446,744,073,709,551,615.
    typedef uint64_t uint64;

    /// @brief Gets the minimum value that a 64-bit unsigned integer can hold.
    /// @return 0
    template<>
    inline constexpr uint64 minValue() noexcept
    {
        return 0;
    }

    /// @brief Gets the maximum value that a 64-bit unsigned integer can hold.
    /// @return 18,446,744,073,709,551,615
    template<>
    inline constexpr uint64 maxValue() noexcept
    {
        return UINT64_MAX;
    }
}

#endif // HYPER_INTEGER_H
