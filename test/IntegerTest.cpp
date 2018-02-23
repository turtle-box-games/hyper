#include "gtest/gtest.h"
#include "hyper/integer.h"

using namespace hyper;

TEST(int8, Size) {
    EXPECT_EQ(1, sizeof(int8));
}

TEST(int8, MinValue) {
    EXPECT_EQ(-128, minValue<int8>());
}

TEST(int8, MaxValue) {
    EXPECT_EQ(127, maxValue<int8>());
}

TEST(uint8, Size) {
    EXPECT_EQ(1, sizeof(uint8));
}

TEST(uint8, MinValue) {
    EXPECT_EQ(0, minValue<uint8>());
}

TEST(uint8, MaxValue) {
    EXPECT_EQ(255, maxValue<uint8>());
}

TEST(int16, Size) {
    EXPECT_EQ(2, sizeof(int16));
}

TEST(int16, MinValue) {
    EXPECT_EQ(-32768, minValue<int16>());
}

TEST(int16, MaxValue) {
    EXPECT_EQ(32767, maxValue<int16>());
}

TEST(uint16, Size) {
    EXPECT_EQ(2, sizeof(uint16));
}

TEST(uint16, MinValue) {
    EXPECT_EQ(0, minValue<uint16>());
}

TEST(uint16, MaxValue) {
    EXPECT_EQ(65535, maxValue<uint16>());
}

TEST(int32, Size) {
    EXPECT_EQ(4, sizeof(int32));
}

TEST(int32, MinValue) {
    EXPECT_EQ(-2147483648, minValue<int32>());
}

TEST(int32, MaxValue) {
    EXPECT_EQ(2147483647, maxValue<int32>());
}

TEST(uint32, Size) {
    EXPECT_EQ(4, sizeof(uint32));
}

TEST(uint32, MinValue) {
    EXPECT_EQ(0, minValue<uint32>());
}

TEST(uint32, MaxValue) {
    EXPECT_EQ(4294967295, maxValue<uint32>());
}

TEST(int64, Size) {
    EXPECT_EQ(8, sizeof(int64));
}

TEST(int64, MinValue) {
    EXPECT_EQ(-9223372036854775807LL - 1, minValue<int64>());
}

TEST(int64, MaxValue) {
    EXPECT_EQ(9223372036854775807LL, maxValue<int64>());
}

TEST(uint64, Size) {
    EXPECT_EQ(8, sizeof(uint64));
}

TEST(uint64, MinValue) {
    EXPECT_EQ(0, minValue<uint64>());
}

TEST(uint64, MaxValue) {
    EXPECT_EQ(18446744073709551615ULL, maxValue<uint64>());
}