#include "gtest/gtest.h"
#include "hyper/types.h"
#include <cfloat>

using namespace hyper;

TEST(int8, Size) {
    EXPECT_EQ(1, sizeof(int8));
}

TEST(int8, MinValue) {
    EXPECT_EQ(-128, min_value<int8>());
}

TEST(int8, MaxValue) {
    EXPECT_EQ(127, max_value<int8>());
}

TEST(uint8, Size) {
    EXPECT_EQ(1, sizeof(uint8));
}

TEST(uint8, MinValue) {
    EXPECT_EQ(0, min_value<uint8>());
}

TEST(uint8, MaxValue) {
    EXPECT_EQ(255, max_value<uint8>());
}

TEST(int16, Size) {
    EXPECT_EQ(2, sizeof(int16));
}

TEST(int16, MinValue) {
    EXPECT_EQ(-32768, min_value<int16>());
}

TEST(int16, MaxValue) {
    EXPECT_EQ(32767, max_value<int16>());
}

TEST(uint16, Size) {
    EXPECT_EQ(2, sizeof(uint16));
}

TEST(uint16, MinValue) {
    EXPECT_EQ(0, min_value<uint16>());
}

TEST(uint16, MaxValue) {
    EXPECT_EQ(65535, max_value<uint16>());
}

TEST(int32, Size) {
    EXPECT_EQ(4, sizeof(int32));
}

TEST(int32, MinValue) {
    EXPECT_EQ(-2147483648, min_value<int32>());
}

TEST(int32, MaxValue) {
    EXPECT_EQ(2147483647, max_value<int32>());
}

TEST(uint32, Size) {
    EXPECT_EQ(4, sizeof(uint32));
}

TEST(uint32, MinValue) {
    EXPECT_EQ(0, min_value<uint32>());
}

TEST(uint32, MaxValue) {
    EXPECT_EQ(4294967295, max_value<uint32>());
}

TEST(int64, Size) {
    EXPECT_EQ(8, sizeof(int64));
}

TEST(int64, MinValue) {
    EXPECT_EQ(-9223372036854775807LL - 1, min_value<int64>());
}

TEST(int64, MaxValue) {
    EXPECT_EQ(9223372036854775807LL, max_value<int64>());
}

TEST(uint64, Size) {
    EXPECT_EQ(8, sizeof(uint64));
}

TEST(uint64, MinValue) {
    EXPECT_EQ(0, min_value<uint64>());
}

TEST(uint64, MaxValue) {
    EXPECT_EQ(18446744073709551615ULL, max_value<uint64>());
}

TEST(float32, Size) {
    EXPECT_EQ(4, sizeof(float32));
}

TEST(float32, MinValue) {
    EXPECT_EQ(FLT_MIN, min_value<float32>());
}

TEST(float32, MaxValue) {
    EXPECT_EQ(FLT_MAX, max_value<float32>());
}

TEST(float32, Infinity) {
    EXPECT_EQ(INFINITY, infinity<float32>());
}

TEST(float32, NegativeInfinity) {
    EXPECT_EQ(-INFINITY, negative_infinity<float32>());
}

TEST(float64, Size) {
    EXPECT_EQ(8, sizeof(float64));
}

TEST(float64, MinValue) {
    EXPECT_EQ(DBL_MIN, min_value<float64>());
}

TEST(float64, MaxValue) {
    EXPECT_EQ(DBL_MAX, max_value<float64>());
}

TEST(float64, Infinity) {
    EXPECT_EQ(INFINITY, infinity<float64>());
}

TEST(float64, NegativeInfinity) {
    EXPECT_EQ(-INFINITY, negative_infinity<float64>());
}