/// @file byte.h
/// Definition of a raw byte.

#ifndef HYPER_BYTE_H
#define HYPER_BYTE_H

namespace hyper
{
    /// @brief Single byte value that represents raw data.
    /// @details A byte is not intended to be read directly from.
    ///   It is for storing raw data and converting between types,
    ///   such as during a serialization or marshal process.
    enum class byte : unsigned char {};

    /// @brief Left-shift operator.
    /// @details Shifts a byte left by a specified number of bits.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the left.
    /// @return Left-shifted byte.
    inline constexpr byte operator<<(byte b, int shift) noexcept
    {
        return byte(static_cast<unsigned char>(b) << shift);
    }

    /// @brief Left-shift compound assignment operator.
    /// @details Shifts a byte left by a specified number of bits and updates it.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the left.
    /// @return Left-shifted byte.
    inline constexpr byte& operator<<=(byte& b, int shift) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) << shift);
    }

    /// @brief Right-shift operator.
    /// @details Shifts a byte right by a specified number of bits.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the right.
    /// @return Right-shifted byte.
    inline constexpr byte operator>>(byte b, int shift) noexcept
    {
        return byte(static_cast<unsigned char>(b) >> shift);
    }

    /// @brief Right-shift compound assignment operator.
    /// @details Shifts a byte right by a specified number of bits and updates it.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the right.
    /// @return Right-shifted byte.
    inline constexpr byte& operator>>=(byte& b, int shift) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) >> shift);
    }

    /// @brief OR operator.
    /// @details Performs an OR operation on a byte.
    /// @param b Byte to operate on.
    /// @param v Byte to OR against.
    /// @return Result of the OR operation.
    inline constexpr byte operator |(byte b, byte v) noexcept
    {
        return byte(static_cast<unsigned char>(b) | static_cast<unsigned char>(v));
    }

    /// @brief OR compound assignment operator.
    /// @details Performs an OR operation on a byte and updates it.
    /// @param b Byte to operate on.
    /// @param v Byte to OR against.
    /// @return Result of the OR operation.
    inline constexpr byte& operator |=(byte& b, byte v) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) | static_cast<unsigned char>(v));
    }

    /// @brief AND operator.
    /// @details Performs an AND operation on a byte.
    /// @param b Byte to operate on.
    /// @param v Byte to AND against.
    /// @return Result of the AND operation.
    inline constexpr byte operator &(byte b, byte v) noexcept
    {
        return byte(static_cast<unsigned char>(b) & static_cast<unsigned char>(v));
    }

    /// @brief AND compound assignment operator.
    /// @details Performs an AND operation on a byte and updates it.
    /// @param b Byte to operate on.
    /// @param v Byte to AND against.
    /// @return Result of the AND operation.
    inline constexpr byte& operator &=(byte& b, byte v) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) & static_cast<unsigned char>(v));
    }

    /// @brief XOR operator.
    /// @details Performs an XOR operation on a byte.
    /// @param b Byte to operate on.
    /// @param v Byte to XOR against.
    /// @return Result of the XOR operation.
    inline constexpr byte operator ^(byte b, byte v) noexcept
    {
        return byte(static_cast<unsigned char>(b) ^ static_cast<unsigned char>(v));
    }

    /// @brief XOR compound assignment operator.
    /// @details Performs an XOR operation on a byte and updates it.
    /// @param b Byte to operate on.
    /// @param v Byte to XOR against.
    /// @return Result of the XOR operation.
    inline constexpr byte& operator ^=(byte& b, byte v) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) ^ static_cast<unsigned char>(v));
    }

    /// @brief NOT operator.
    /// @details Performs a NOT operation on a byte.
    /// @param b Byte to operate on.
    /// @return Result of the NOT operation.
    inline constexpr byte operator ~(byte b) noexcept
    {
        return byte(~static_cast<unsigned char>(b));
    }

    /// @brief Integer conversion.
    /// @details Convert a byte to an integer.
    /// @param b Byte to convert.
    /// @return Byte value as an integer.
    inline constexpr int toInt(byte b) noexcept
    {
        return static_cast<int>(b);
    }
}

#endif //HYPER_BYTE_H
