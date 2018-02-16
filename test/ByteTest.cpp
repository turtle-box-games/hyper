#include "gtest/gtest.h"
#include "hyper/byte.h"

using namespace hyper;

TEST(byte, LeftShift) {
    EXPECT_EQ(byte(168), byte(42) << 2);
}

TEST(byte, LeftShiftTruncate) {
    EXPECT_EQ(byte(128), byte(42) << 6);
}

TEST(byte, LeftShiftOver) {
    EXPECT_EQ(byte(0), byte(1) << 8);
}

TEST(byte, LeftShiftZero) {
    EXPECT_EQ(byte(0), byte(0) << 1);
}

TEST(byte, RightShift) {
    EXPECT_EQ(byte(10), byte(42) >> 2);
}

TEST(byte, RightShiftOver) {
    EXPECT_EQ(byte(0), byte(255) >> 8);
}

TEST(byte, RightShiftZero) {
    EXPECT_EQ(byte(0), byte(0) >> 1);
}

TEST(byte, LeftShiftRef) {
    byte b = byte(42);
    b <<= 2;
    EXPECT_EQ(byte(168), b);
}

TEST(byte, LeftShiftTruncateRef) {
    byte b = byte(42);
    b <<= 6;
    EXPECT_EQ(byte(128), b);
}

TEST(byte, LeftShiftOverRef) {
    byte b = byte(1);
    b <<= 8;
    EXPECT_EQ(byte(0), b);
}

TEST(byte, LeftShiftZeroRef) {
    byte b = byte(0);
    b <<= 1;
    EXPECT_EQ(byte(0), b);
}

TEST(byte, RightShiftRef) {
    byte b = byte(42);
    b >>= 2;
    EXPECT_EQ(byte(10), b);
}

TEST(byte, RightShiftOverRef) {
    byte b = byte(255);
    b >>= 8;
    EXPECT_EQ(byte(0), b);
}

TEST(byte, RightShiftZeroRef) {
    byte b = byte(0);
    b >>= 1;
    EXPECT_EQ(byte(0), b);
}

TEST(byte, Or) {
    EXPECT_EQ(byte(186), byte(42) | byte(146));
}

TEST(byte, OrZero) {
    EXPECT_EQ(byte(42), byte(42) | byte(0));
}

TEST(byte, OrMax) {
    EXPECT_EQ(byte(255), byte(42) | byte(255));
}

TEST(byte, OrRef) {
    byte b = byte(42);
    b |= byte(146);
    EXPECT_EQ(byte(186), b);
}

TEST(byte, OrZeroRef) {
    byte b = byte(42);
    b |= byte(0);
    EXPECT_EQ(byte(42), b);
}

TEST(byte, OrMaxRef) {
    byte b = byte(42);
    b |= byte(255);
    EXPECT_EQ(byte(255), b);
}

TEST(byte, And) {
    EXPECT_EQ(byte(2), byte(42) & byte(146));
}

TEST(byte, AndZero) {
    EXPECT_EQ(byte(0), byte(42) & byte(0));
}

TEST(byte, AndMax) {
    EXPECT_EQ(byte(42), byte(42) & byte(255));
}

TEST(byte, AndRef) {
    byte b = byte(42);
    b &= byte(146);
    EXPECT_EQ(byte(2), b);
}

TEST(byte, AndZeroRef) {
    byte b = byte(42);
    b &= byte(0);
    EXPECT_EQ(byte(0), b);
}

TEST(byte, AndMaxRef) {
    byte b = byte(42);
    b &= byte(255);
    EXPECT_EQ(byte(42), b);
}

TEST(byte, Xor) {
    EXPECT_EQ(byte(184), byte(42) ^ byte(146));
}

TEST(byte, XorZero) {
    EXPECT_EQ(byte(42), byte(42) ^ byte(0));
}

TEST(byte, XorMax) {
    EXPECT_EQ(byte(213), byte(42) ^ byte(255));
}

TEST(byte, XorRef) {
    byte b = byte(42);
    b ^= byte(146);
    EXPECT_EQ(byte(184), b);
}

TEST(byte, XorZeroRef) {
    byte b = byte(42);
    b ^= byte(0);
    EXPECT_EQ(byte(42), b);
}

TEST(byte, XorMaxRef) {
    byte b = byte(42);
    b ^= byte(255);
    EXPECT_EQ(byte(213), b);
}

TEST(byte, Not) {
    EXPECT_EQ(byte(213), ~byte(42));
}

TEST(byte, NotZero) {
    EXPECT_EQ(byte(255), ~byte(0));
}

TEST(byte, NotMax) {
    EXPECT_EQ(byte(0), ~byte(255));
}

TEST(byte, ToInt) {
    EXPECT_EQ(42, toInt(byte(42)));
}

TEST(byte, ToIntZero) {
    EXPECT_EQ(0, toInt(byte(0)));
}

TEST(byte, ToIntMax) {
    EXPECT_EQ(255, toInt(byte(255)));
}

TEST(byte, MinValue) {
    EXPECT_EQ(byte(0), min_value<byte>());
}

TEST(byte, MaxValue) {
    EXPECT_EQ(byte(255), max_value<byte>());
}