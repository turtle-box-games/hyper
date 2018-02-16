#include "gtest/gtest.h"
#include "hyper/ScopedArray.h"

using namespace hyper;

#define SAMPLE_ARRAY_SIZE 100

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

TEST(ScopedArray, Free) {
    int freeCount = -SAMPLE_ARRAY_SIZE; // Negative because copying instances triggers destructor.
    auto mock = new ScopedArrayDestructorCapture[SAMPLE_ARRAY_SIZE];
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        mock[i] = ScopedArrayDestructorCapture(&freeCount); // Copy occurs, this is why freeCount starts as negative.
    // freeCount == 0 here.
    {
        ScopedArray<ScopedArrayDestructorCapture> sa(mock);
        // sa should be freed when this scope exits,
        // which will increment freeCount for every destructor called.
    }
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE);
}

TEST(ScopedArray, ExpireNull) {
    auto arr = new int[SAMPLE_ARRAY_SIZE];
    ScopedArray<int> sa(arr);
    sa.expire();
    EXPECT_FALSE((bool)sa);
}

TEST(ScopedArray, ExpireFree) {
    int freeCount = 0;
    auto mock = new ScopedArrayDestructorCapture[SAMPLE_ARRAY_SIZE];
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        mock[i] = ScopedArrayDestructorCapture(&freeCount);
    ScopedArray<ScopedArrayDestructorCapture> sa(mock);
    sa.expire();
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE * 2); // x2 because swapping causes two destructor calls per instance.
}

TEST(ScopedArray, Swap) {
    auto arr1 = new int[SAMPLE_ARRAY_SIZE];
    auto arr2 = new int[SAMPLE_ARRAY_SIZE];
    ScopedArray<int> sa1(arr1);
    ScopedArray<int> sa2(arr2);
    sa1.swap(sa2);
    EXPECT_EQ(&sa1[0], arr2);
    EXPECT_EQ(&sa2[0], arr1);
}

TEST(ScopedArray, SubscriptGet) {
    auto arr = new size_t[SAMPLE_ARRAY_SIZE];
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        arr[i] = i;
    ScopedArray<size_t> sa(arr);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        EXPECT_EQ(sa[i], i);
}

TEST(ScopedArray, SubscriptSet) {
    auto arr = new size_t[SAMPLE_ARRAY_SIZE];
    ScopedArray<size_t> sa(arr);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i) {
        sa[i] = i;
        EXPECT_EQ(arr[i], i);
    }
}

TEST(ScopedArray, BoolCastTrue) {
    auto arr = new int[SAMPLE_ARRAY_SIZE];
    ScopedArray<int> sa(arr);
    EXPECT_TRUE((bool)sa);
}

TEST(ScopedArray, BoolCastFalse) {
    ScopedArray<int> sa(nullptr);
    EXPECT_FALSE((bool)sa);
}