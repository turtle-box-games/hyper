#include "gmock/gmock.h"
#include "hyper/ScopedPointer.h"
#include "mocks/DeleterMock.h"
#include "util/FunctorSpy.h"

#define SAMPLE_ARRAY_SIZE 100
#define SAMPLE_VALUE 42

using namespace hyper;

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
    int count = 0;
    FunctorSpy<void(int *), DefaultDeleter<int>> spy(&count, DefaultDeleter<int>());
    {
        ScopedPointer<int, FunctorSpy<void(int *), DefaultDeleter<int>>> sp(new int, spy);
    }
    EXPECT_EQ(count, 1);
}

TEST(ScopedPointer, GetDeleter) {
    ScopedPointer<int, DeleterMock<int>> sp;
    DeleterMock<int> deleter;
    EXPECT_EQ(deleter, sp.getDeleter());
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
    int count = 0;
    FunctorSpy<void(int *), DefaultDeleter<int[]>> spy(&count, DefaultDeleter<int[]>());
    {
        ScopedPointer<int[], FunctorSpy<void(int *), DefaultDeleter<int[]>>> sp(new int[5], spy);
    }
    EXPECT_EQ(count, 1);
}

TEST(ScopedPointer, ArrayGetDeleter) {
    ScopedPointer<int[], DeleterMock<int>> sp;
    DeleterMock<int> deleter;
    EXPECT_EQ(deleter, sp.getDeleter());
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