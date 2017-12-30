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

TEST(byte, ToInt) {
    EXPECT_EQ(42, toInt(byte(42)));
}