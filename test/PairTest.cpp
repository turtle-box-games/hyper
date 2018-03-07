#include "gtest/gtest.h"
#include "hyper/Pair.h"

using namespace hyper;

TEST(Pair, DefaultConstructor) {
    Pair<int, int> pair;
    EXPECT_EQ(0, pair.first);
    EXPECT_EQ(0, pair.second);
}

TEST(Pair, GeneralConstructor) {
    const int first  = 42;
    const int second = 500;
    Pair<int, int> pair(first, second);
    EXPECT_EQ(first, pair.first);
    EXPECT_EQ(second, pair.second);
}

TEST(Pair, Create) {
    const int   first  = 42;
    const char *second = "foobar";
    auto pair = createPair(first, second);
    EXPECT_EQ(first, pair.first);
    EXPECT_STREQ(second, pair.second);
}