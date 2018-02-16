#include "gtest/gtest.h"
#include "hyper/types.h"

using namespace hyper;

TEST(int8, Size) {
    EXPECT_EQ(1, sizeof(int8));
}

TEST(uint8, Size) {
    EXPECT_EQ(1, sizeof(uint8));
}

TEST(int16, Size) {
    EXPECT_EQ(2, sizeof(int16));
}

TEST(uint16, Size) {
    EXPECT_EQ(2, sizeof(uint16));
}

TEST(int32, Size) {
    EXPECT_EQ(4, sizeof(int32));
}

TEST(uint32, Size) {
    EXPECT_EQ(4, sizeof(uint32));
}

TEST(int64, Size) {
    EXPECT_EQ(8, sizeof(int64));
}

TEST(uint64, Size) {
    EXPECT_EQ(8, sizeof(uint64));
}

TEST(float32, Size) {
    EXPECT_EQ(4, sizeof(float32));
}

TEST(float64, Size) {
    EXPECT_EQ(8, sizeof(float64));
}