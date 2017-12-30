#ifndef HYPER_TYPES_H
#define HYPER_TYPES_H

#include <cstdint>

namespace hyper
{
    /// 8-bit signed integer.
    /// Values can range from -128 to 127
    typedef int8_t int8;

    /// 8-bit unsigned integer.
    /// Values can range from 0 to 255.
    typedef uint8_t uint8;

    /// 16-bit signed integer.
    /// Values can range from -32,768 to 32,767.
    typedef int16_t int16;

    /// 16-bit unsigned integer.
    /// Values can range from 0 to 65,535.
    typedef uint16_t uint16;

    /// 32-bit signed integer.
    /// Values can range from -2,147,483,648 to 2,147,483,647.
    typedef int32_t int32;

    /// 32-bit unsigned integer.
    /// Values can range from 0 to 4,294,967,295.
    typedef uint32_t uint32;

    /// 64-bit signed integer.
    /// Values can range from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
    typedef int64_t int64;

    /// 64-bit unsigned integer.
    /// Values can range from 0 to 18,446,744,073,709,551,615.
    typedef uint64_t uint64;

    /// 32-bit floating-point value.
    typedef float float32;

    /// 64-bit floating-point value
    typedef double float64;
}

#endif //HYPER_TYPES_H
