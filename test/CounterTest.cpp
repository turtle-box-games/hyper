#include "gtest/gtest.h"
#include "hyper/Counter.h"
#include "common.h"

using namespace hyper;

TEST(Counter, DefaultConstructor) {
    TEST_DESCRIPTION("Counter should be initialized to zero");
    Counter counter;
    EXPECT_EQ(0, counter.value());
}

TEST(Counter, InitialConstructor) {
    TEST_DESCRIPTION("Counter should be initialized to expected value");
    const size_t initial = 42;
    Counter counter(initial);
    EXPECT_EQ(initial, counter.value());
}

TEST(Counter, Increment) {
    TEST_DESCRIPTION("Incremented value should be one higher than previous value");
    const size_t initial  = 42;
    const size_t expected = initial + 1;
    Counter counter(initial);
    counter.increment();
    EXPECT_EQ(expected, counter.value());
}

TEST(Counter, IncrementValue) {
    TEST_DESCRIPTION("Increment method should return original value");
    const size_t initial = 42;
    Counter counter(initial);
    EXPECT_EQ(initial, counter.increment());
}

TEST(Counter, Decrement) {
    TEST_DESCRIPTION("Decremented value should be one lower than previous value");
    const size_t initial  = 42;
    const size_t expected = initial - 1;
    Counter counter(initial);
    counter.decrement();
    EXPECT_EQ(expected, counter.value());
}

TEST(Counter, DecrementValue) {
    TEST_DESCRIPTION("Decrement method should return original value");
    const size_t initial = 42;
    Counter counter(initial);
    EXPECT_EQ(initial, counter.decrement());
}

TEST(Counter, PreIncrement) {
    const size_t initial  = 42;
    const size_t expected = initial + 1;
    Counter counter(initial);
    EXPECT_EQ(expected, (++counter).value());
}

TEST(Counter, PostIncrement) {
    const size_t initial = 42;
    Counter counter(initial);
    EXPECT_EQ(initial, (counter++).value());
}

TEST(Counter, PreDecrement) {
    const size_t initial  = 42;
    const size_t expected = initial - 1;
    Counter counter(initial);
    EXPECT_EQ(expected, (--counter).value());
}

TEST(Counter, PostDecrement) {
    const size_t initial = 42;
    Counter counter(initial);
    EXPECT_EQ(initial, (counter--).value());
}

TEST(Counter, Cast) {
    TEST_DESCRIPTION("Explicit cast to integer should equal the counter's value");
    const size_t initial = 42;
    Counter counter(initial);
    EXPECT_EQ(initial, (size_t)counter);
}