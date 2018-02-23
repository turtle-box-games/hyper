#include "gtest/gtest.h"
#include "hyper/float.h"

using namespace hyper;

TEST(float32, Size) {
EXPECT_EQ(4, sizeof(float32));
}

TEST(float32, MinValue) {
EXPECT_EQ(FLT_MIN, minValue<float32>());
}

TEST(float32, MaxValue) {
EXPECT_EQ(FLT_MAX, maxValue<float32>());
}

TEST(float32, Infinity) {
EXPECT_EQ(INFINITY, infinity<float32>());
}

TEST(float32, NegativeInfinity) {
EXPECT_EQ(-INFINITY, negativeInfinity<float32>());
}

TEST(float64, Size) {
EXPECT_EQ(8, sizeof(float64));
}

TEST(float64, MinValue) {
EXPECT_EQ(DBL_MIN, minValue<float64>());
}

TEST(float64, MaxValue) {
EXPECT_EQ(DBL_MAX, maxValue<float64>());
}

TEST(float64, Infinity) {
EXPECT_EQ(INFINITY, infinity<float64>());
}

TEST(float64, NegativeInfinity) {
EXPECT_EQ(-INFINITY, negativeInfinity<float64>());
}