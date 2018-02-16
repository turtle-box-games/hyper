#include "gtest/gtest.h"
#include "hyper/ScopedArray.h"

using namespace hyper;

#define SAMPLE_ARRAY_SIZE 100
#define SAMPLE_VALUE 42

class ScopedArrayDestructorCapture
{
private:
    int *_destructorCallCount;

public:
    ScopedArrayDestructorCapture()
            : _destructorCallCount(nullptr)
    {
        // ...
    }

    ScopedArrayDestructorCapture(int *count)
            : _destructorCallCount(count)
    {
        // ...
    }

    ~ScopedArrayDestructorCapture()
    {
        (*_destructorCallCount)++;
    }
};

struct ScopedArraySampleValue
{
    int value;

    ScopedArraySampleValue()
            : value(SAMPLE_VALUE)
    {
        // ...
    }
};

TEST(ScopedArray, Free) {
    int freeCount = -SAMPLE_ARRAY_SIZE; // Negative because copying instances triggers destructor.
    {
        ScopedArray<ScopedArrayDestructorCapture> sa(new ScopedArrayDestructorCapture[SAMPLE_ARRAY_SIZE]);
        // freeCount == 0 here.
        for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
            sa[i] = ScopedArrayDestructorCapture(&freeCount); // Copy occurs, this is why freeCount starts as negative.
        // sa should be freed when this scope exits,
        // which will increment freeCount for every destructor called.
    }
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE);
}

TEST(ScopedArray, ExpireNull) {
    ScopedArray<int> sa(new int[SAMPLE_ARRAY_SIZE]);
    sa.expire();
    EXPECT_FALSE((bool)sa);
}

TEST(ScopedArray, ExpireFree) {
    int freeCount = 0;
    ScopedArray<ScopedArrayDestructorCapture> sa(
            new ScopedArrayDestructorCapture[SAMPLE_ARRAY_SIZE]
    );
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        sa[i] = ScopedArrayDestructorCapture(&freeCount);
    sa.expire();
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE * 2); // x2 because swapping causes two destructor calls per instance.
}

TEST(ScopedArray, Swap) {
    const auto val1 = 42;
    const auto val2 = 24;
    ScopedArray<int> sa1(new int[SAMPLE_ARRAY_SIZE]);
    ScopedArray<int> sa2(new int[SAMPLE_ARRAY_SIZE]);
    sa1[0] = val1;
    sa2[0] = val2;
    sa1.swap(sa2);
    EXPECT_EQ(sa1[0], val2);
    EXPECT_EQ(sa2[0], val1);
}

TEST(ScopedArray, SubscriptGet) {
    ScopedArray<ScopedArraySampleValue> sa(new ScopedArraySampleValue[SAMPLE_ARRAY_SIZE]);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        EXPECT_EQ(sa[i].value, SAMPLE_VALUE);
}

TEST(ScopedArray, SubscriptSet) {
    ScopedArray<size_t> sa(new size_t[SAMPLE_ARRAY_SIZE]);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i) {
        sa[i] = i;
        EXPECT_EQ(sa[i], i);
    }
}

TEST(ScopedArray, BoolCastTrue) {
    ScopedArray<int> sa(new int[SAMPLE_ARRAY_SIZE]);
    EXPECT_TRUE((bool)sa);
}

TEST(ScopedArray, BoolCastFalse) {
    ScopedArray<int> sa(nullptr);
    EXPECT_FALSE((bool)sa);
}