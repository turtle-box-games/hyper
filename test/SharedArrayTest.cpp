#include "gtest/gtest.h"
#include "hyper/SharedArray.h"

using namespace hyper;

#define SAMPLE_ARRAY_SIZE 100
#define SAMPLE_VALUE 42

class SharedArrayDestructorCapture
{
private:
    int *_destructorCallCount;

public:
    SharedArrayDestructorCapture()
            : _destructorCallCount(nullptr)
    {
        // ...
    }

    SharedArrayDestructorCapture(int *count)
            : _destructorCallCount(count)
    {
        // ...
    }

    ~SharedArrayDestructorCapture()
    {
        (*_destructorCallCount)++;
    }
};

struct SharedArraySampleValue
{
    int value;

    SharedArraySampleValue()
            : value(SAMPLE_VALUE)
    {
        // ...
    }
};

TEST(SharedArray, Free) {
    int freeCount = -SAMPLE_ARRAY_SIZE; // Negative because copying instances triggers destructor.
    {
        SharedArray<SharedArrayDestructorCapture> sa(new SharedArrayDestructorCapture[SAMPLE_ARRAY_SIZE]);
        // freeCount == 0 here.
        for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
            sa[i] = SharedArrayDestructorCapture(&freeCount); // Copy occurs, this is why freeCount starts as negative.
        // sa should be freed when this scope exits,
        // which will increment freeCount for every destructor called.
    }
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE);
}

TEST(SharedArray, Swap) {
    const auto val1 = 42;
    const auto val2 = 24;
    SharedArray<int> sa1(new int[SAMPLE_ARRAY_SIZE]);
    SharedArray<int> sa2(new int[SAMPLE_ARRAY_SIZE]);
    sa1[0] = val1;
    sa2[0] = val2;
    sa1.swap(sa2);
    EXPECT_EQ(sa1[0], val2);
    EXPECT_EQ(sa2[0], val1);
}

TEST(SharedArray, SubscriptGet) {
    SharedArray<SharedArraySampleValue> sa(SAMPLE_ARRAY_SIZE);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        EXPECT_EQ(sa[i].value, SAMPLE_VALUE);
}

TEST(SharedArray, SubscriptSet) {
    SharedArray<size_t> sa(SAMPLE_ARRAY_SIZE);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i) {
        sa[i] = i;
        EXPECT_EQ(sa[i], i);
    }
}

TEST(SharedArray, BoolCastTrue) {
    SharedArray<int> sa(new int[SAMPLE_ARRAY_SIZE]);
    EXPECT_TRUE((bool)sa);
}

TEST(SharedArray, BoolCastFalse) {
    SharedArray<int> sa(nullptr);
    EXPECT_FALSE((bool)sa);
}