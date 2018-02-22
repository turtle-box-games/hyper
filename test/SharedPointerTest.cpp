#include "gtest/gtest.h"
#include "hyper/SharedPointer.h"

#define SAMPLE_ARRAY_SIZE 100
#define SAMPLE_VALUE 42

using namespace hyper;

class SharedPointerDestructorCapture
{
private:
    bool *_destructorCalled;

public:
    SharedPointerDestructorCapture(bool *flag)
            : _destructorCalled(flag)
    {
        // ...
    }

    ~SharedPointerDestructorCapture()
    {
        *_destructorCalled = true;
    }
};

struct SharedPointerSampleData
{
    int value;

    SharedPointerSampleData() = default;

    SharedPointerSampleData(int val)
            : value(val)
    {
        // ...
    }
};

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

TEST(SharedPointer, Free) {
    bool result = false;
    {
        SharedPointer<SharedPointerDestructorCapture> sp(
                new SharedPointerDestructorCapture(&result)
        );
        // sp should be freed when this scope exits,
        // which will set result to true if the destructor was called.
    }
    EXPECT_TRUE(result);
}

TEST(SharedPointer, Swap) {
    const auto val1 = 42;
    const auto val2 = 24;
    SharedPointer<int> sp1(new int(val1));
    SharedPointer<int> sp2(new int(val2));
    sp1.swap(sp2);
    EXPECT_EQ(val1, *sp2);
    EXPECT_EQ(val2, *sp1);
}

TEST(SharedPointer, DereferenceGet) {
    const auto val = 5;
    SharedPointer<int> sp(new int(val));
    EXPECT_EQ(*sp, val);
}

TEST(SharedPointer, DereferenceSet) {
    const auto val = 42;
    SharedPointer<int> sp;
    *sp = val;
    EXPECT_EQ(*sp, val);
}

TEST(SharedPointer, MemberAccessGet) {
    const auto val = 777;
    SharedPointer<SharedPointerSampleData> sp(new SharedPointerSampleData(val));
    EXPECT_EQ(sp->value, val);
}

TEST(SharedPointer, MemberAccessSet) {
    const auto val = 12345;
    SharedPointer<SharedPointerSampleData> sp;
    sp->value = val;
    EXPECT_EQ(sp->value, val);
}

TEST(SharedPointer, BoolCastTrue) {
    SharedPointer<int> sp(new int);
    EXPECT_TRUE((bool)sp);
}

TEST(SharedPointer, BoolCastFalse) {
    SharedPointer<int> sp(nullptr);
    EXPECT_FALSE((bool)sp);
}

TEST(SharedPointer, ArrayFree) {
    int freeCount = -SAMPLE_ARRAY_SIZE; // Negative because copying instances triggers destructor.
    {
        SharedPointer<SharedArrayDestructorCapture[]> sa(new SharedArrayDestructorCapture[SAMPLE_ARRAY_SIZE]);
        // freeCount == 0 here.
        for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
            sa[i] = SharedArrayDestructorCapture(&freeCount); // Copy occurs, this is why freeCount starts as negative.
        // sa should be freed when this scope exits,
        // which will increment freeCount for every destructor called.
    }
    EXPECT_EQ(freeCount, SAMPLE_ARRAY_SIZE);
}

TEST(SharedPointer, ArraySwap) {
    const auto val1 = 42;
    const auto val2 = 24;
    SharedPointer<int[]> sa1(new int[SAMPLE_ARRAY_SIZE]);
    SharedPointer<int[]> sa2(new int[SAMPLE_ARRAY_SIZE]);
    sa1[0] = val1;
    sa2[0] = val2;
    sa1.swap(sa2);
    EXPECT_EQ(sa1[0], val2);
    EXPECT_EQ(sa2[0], val1);
}

TEST(SharedPointer, SubscriptGet) {
    SharedPointer<SharedArraySampleValue[]> sa(SAMPLE_ARRAY_SIZE);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        EXPECT_EQ(sa[i].value, SAMPLE_VALUE);
}

TEST(SharedPointer, SubscriptSet) {
    SharedPointer<size_t[]> sa(SAMPLE_ARRAY_SIZE);
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i) {
        sa[i] = i;
        EXPECT_EQ(sa[i], i);
    }
}

TEST(SharedPointer, ArrayBoolCastTrue) {
    SharedPointer<int[]> sa(new int[SAMPLE_ARRAY_SIZE]);
    EXPECT_TRUE((bool)sa);
}

TEST(SharedPointer, ArrayBoolCastFalse) {
    SharedPointer<int[]> sa(nullptr);
    EXPECT_FALSE((bool)sa);
}