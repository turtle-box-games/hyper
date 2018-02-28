#include "gtest/gtest.h"
#include "hyper/ScopedPointer.h"

#define SAMPLE_ARRAY_SIZE 100
#define SAMPLE_VALUE 42

using namespace hyper;

class ScopedPointerDestructorCapture
{
private:
    bool *_destructorCalled;

public:
    ScopedPointerDestructorCapture(bool *flag)
            : _destructorCalled(flag)
    {
        // ...
    }

    ~ScopedPointerDestructorCapture()
    {
        *_destructorCalled = true;
    }
};

struct ScopedPointerSampleData
{
    int value;

    ScopedPointerSampleData() = default;

    ScopedPointerSampleData(int val)
            : value(val)
    {
        // ...
    }
};

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

TEST(ScopedPointer, Free) {
    bool result = false;
    {
        ScopedPointer<ScopedPointerDestructorCapture> sp(
                new ScopedPointerDestructorCapture(&result)
        );
        // sp should be freed when this scope exits,
        // which will set result to true if the destructor was called.
    }
    EXPECT_TRUE(result);
}

TEST(ScopedPointer, Swap) {
    const auto val1 = 42;
    const auto val2 = 24;
    ScopedPointer<int> sp1(new int(val1));
    ScopedPointer<int> sp2(new int(val2));
    sp1.swap(sp2);
    EXPECT_EQ(val1, *sp2);
    EXPECT_EQ(val2, *sp1);
}

TEST(ScopedPointer, DereferenceGet) {
    const auto val = 5;
    ScopedPointer<int> sp(new int(val));
    EXPECT_EQ(*sp, val);
}

TEST(ScopedPointer, DereferenceSet) {
    const auto val = 42;
    ScopedPointer<int> sp(new int);
    *sp = val;
    EXPECT_EQ(*sp, val);
}

TEST(ScopedPointer, MemberAccessGet) {
    const auto val = 777;
    ScopedPointer<ScopedPointerSampleData> sp(new ScopedPointerSampleData(val));
    EXPECT_EQ(sp->value, val);
}

TEST(ScopedPointer, MemberAccessSet) {
    const auto val = 12345;
    ScopedPointer<ScopedPointerSampleData> sp(new ScopedPointerSampleData);
    sp->value = val;
    EXPECT_EQ(sp->value, val);
}

TEST(ScopedPointer, BoolCastTrue) {
    ScopedPointer<int> sp(new int);
    EXPECT_TRUE((bool)sp);
}

TEST(ScopedPointer, BoolCastFalse) {
    ScopedPointer<int> sp(nullptr);
    EXPECT_FALSE((bool)sp);
}

TEST(ScopedPointer, ArrayFree) {
    int freeCount = -SAMPLE_ARRAY_SIZE; // Negative because copying instances triggers destructor.
    {
        ScopedPointer<ScopedArrayDestructorCapture[]> sa(new ScopedArrayDestructorCapture[SAMPLE_ARRAY_SIZE]);
        // freeCount == 0 here.
        for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
            sa[i] = ScopedArrayDestructorCapture(&freeCount); // Copy occurs, this is why freeCount starts as negative.
        // sa should be freed when this scope exits,
        // which will increment freeCount for every destructor called.
    }
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE);
}

TEST(ScopedPointer, ArraySwap) {
    const auto val1 = 42;
    const auto val2 = 24;
    ScopedPointer<int[]> sa1(new int[SAMPLE_ARRAY_SIZE]);
    ScopedPointer<int[]> sa2(new int[SAMPLE_ARRAY_SIZE]);
    sa1[0] = val1;
    sa2[0] = val2;
    sa1.swap(sa2);
    EXPECT_EQ(sa1[0], val2);
    EXPECT_EQ(sa2[0], val1);
}

TEST(ScopedPointer, SubscriptGet) {
    ScopedPointer<ScopedArraySampleValue[]> sa(new ScopedArraySampleValue[SAMPLE_ARRAY_SIZE]);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        EXPECT_EQ(sa[i].value, SAMPLE_VALUE);
}

TEST(ScopedPointer, SubscriptSet) {
    ScopedPointer<size_t[]> sa(new size_t[SAMPLE_ARRAY_SIZE]);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i) {
        sa[i] = i;
        EXPECT_EQ(sa[i], i);
    }
}

TEST(ScopedPointer, ArrayBoolCastTrue) {
    ScopedPointer<int[]> sa(new int[SAMPLE_ARRAY_SIZE]);
    EXPECT_TRUE((bool)sa);
}

TEST(ScopedPointer, ArrayBoolCastFalse) {
    ScopedPointer<int[]> sa(nullptr);
    EXPECT_FALSE((bool)sa);
}