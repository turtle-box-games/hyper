#ifndef HYPER_BYTE_H
#define HYPER_BYTE_H

namespace hyper
{
    /// Single byte value with a range from 0 to 255.
    enum class byte : unsigned char {};

    /// Shifts a byte left by a specified number of bits.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the left.
    /// @return Left-shifted byte.
    inline constexpr byte operator<<(byte b, int shift) noexcept
    {
        return byte(static_cast<unsigned char>(b) << shift);
    }

    /// Shifts a byte left by a specified number of bits and updates it.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the left.
    /// @return Left-shifted byte.
    inline constexpr byte& operator<<=(byte& b, int shift) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) << shift);
    }

    /// Shifts a byte right by a specified number of bits.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the right.
    /// @return Right-shifted byte.
    inline constexpr byte operator>>(byte b, int shift) noexcept
    {
        return byte(static_cast<unsigned char>(b) >> shift);
    }

    /// Shifts a byte right by a specified number of bits and updates it.
    /// @param b Byte to shift.
    /// @param shift Number of bits to shift to the right.
    /// @return Right-shifted byte.
    inline constexpr byte& operator>>=(byte& b, int shift) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) >> shift);
    }

    /// Performs an OR operation on a byte.
    /// @param b Byte to operate on.
    /// @param v Byte to OR against.
    /// @return Result of the OR operation.
    inline constexpr byte operator |(byte b, byte v) noexcept
    {
        return byte(static_cast<unsigned char>(b) | static_cast<unsigned char>(v));
    }

    /// Performs an OR operation on a byte and updates it.
    /// @param b Byte to operate on.
    /// @param v Byte to OR against.
    /// @return Result of the OR operation.
    inline constexpr byte& operator |=(byte& b, byte v) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) | static_cast<unsigned char>(v));
    }

    /// Performs an AND operation on a byte.
    /// @param b Byte to operate on.
    /// @param v Byte to AND against.
    /// @return Result of the AND operation.
    inline constexpr byte operator &(byte b, byte v) noexcept
    {
        return byte(static_cast<unsigned char>(b) & static_cast<unsigned char>(v));
    }

    /// Performs an AND operation on a byte and updates it.
    /// @param b Byte to operate on.
    /// @param v Byte to AND against.
    /// @return Result of the AND operation.
    inline constexpr byte& operator &=(byte& b, byte v) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) & static_cast<unsigned char>(v));
    }

    /// Performs an XOR operation on a byte.
    /// @param b Byte to operate on.
    /// @param v Byte to XOR against.
    /// @return Result of the XOR operation.
    inline constexpr byte operator ^(byte b, byte v) noexcept
    {
        return byte(static_cast<unsigned char>(b) ^ static_cast<unsigned char>(v));
    }

    /// Performs an XOR operation on a byte and updates it.
    /// @param b Byte to operate on.
    /// @param v Byte to XOR against.
    /// @return Result of the XOR operation.
    inline constexpr byte& operator ^=(byte& b, byte v) noexcept
    {
        return b = byte(static_cast<unsigned char>(b) ^ static_cast<unsigned char>(v));
    }

    /// Performs a NOT operation on a byte.
    /// @param b Byte to operate on.
    /// @return Result of the NOT operation.
    inline constexpr byte operator ~(byte b) noexcept
    {
        return byte(~static_cast<unsigned char>(b));
    }

    /// Convert a byte to an integer.
    /// @param b Byte to convert.
    /// @return Byte value as an integer.
    inline constexpr int toInt(byte b) noexcept
    {
        return static_cast<int>(b);
    }
}

#endif //HYPER_BYTE_H
