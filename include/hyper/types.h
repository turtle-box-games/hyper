/// @file types.h
/// Definitions for numerical data types.
/// Defines developer-friendly type names for specifying exactly the size of value needed.

#ifndef HYPER_TYPES_H
#define HYPER_TYPES_H

#include <cstdint> // For integer types.

namespace hyper
{
    /// @brief 8-bit signed integer.
    /// @details Values can range from -128 to 127
    typedef int8_t int8;

    /// @brief 8-bit unsigned integer.
    /// @details Values can range from 0 to 255.
    typedef uint8_t uint8;

    /// @brief 16-bit signed integer.
    /// @details Values can range from -32,768 to 32,767.
    typedef int16_t int16;

    /// @brief 16-bit unsigned integer.
    /// @details Values can range from 0 to 65,535.
    typedef uint16_t uint16;

    /// @brief 32-bit signed integer.
    /// @details Values can range from -2,147,483,648 to 2,147,483,647.
    typedef int32_t int32;

    /// @brief 32-bit unsigned integer.
    /// @details Values can range from 0 to 4,294,967,295.
    typedef uint32_t uint32;

    /// @brief 64-bit signed integer.
    /// @details Values can range from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
    typedef int64_t int64;

    /// @brief 64-bit unsigned integer.
    /// @details Values can range from 0 to 18,446,744,073,709,551,615.
    typedef uint64_t uint64;

    /// @brief 32-bit floating-point value.
    typedef float float32;

    /// @brief 64-bit floating-point value
    typedef double float64;
}

#endif //HYPER_TYPES_H
