#include "gmock/gmock.h"
#include "hyper/SharedPointer.h"
#include "mocks/DeleterMock.h"
#include "util/FunctorSpy.h"
#include "util/SimpleWrapper.h"

#define SAMPLE_ARRAY_SIZE 100

using namespace hyper;

TEST(SharedPointer, Free) {
    int count = 0;
    FunctorSpy<void(int *), DefaultDeleter<int>> spy(&count, DefaultDeleter<int>());
    {
        SharedPointer<int, FunctorSpy<void(int *), DefaultDeleter<int>>> sp(new int, spy);
    }
    EXPECT_EQ(count, 1);
}

TEST(SharedPointer, GetDeleter) {
    SharedPointer<int, DeleterMock<int>> sp;
    DeleterMock<int> deleter;
    EXPECT_EQ(deleter, sp.getDeleter());
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
    SharedPointer<int> sp(new int);
    *sp = val;
    EXPECT_EQ(*sp, val);
}

TEST(SharedPointer, MemberAccessGet) {
    const auto val = 777;
    SharedPointer<SimpleWrapper> sp(new SimpleWrapper(val));
    EXPECT_EQ(sp->value, val);
}

TEST(SharedPointer, MemberAccessSet) {
    const auto val = 12345;
    SharedPointer<SimpleWrapper> sp(new SimpleWrapper);
    sp->value = val;
    EXPECT_EQ(sp->value, val);
}

TEST(SharedPointer, BoolCastTrue) {
    SharedPointer<int> sp(new int);
    EXPECT_TRUE((bool) sp);
}

TEST(SharedPointer, BoolCastFalse) {
    SharedPointer<int> sp(nullptr);
    EXPECT_FALSE((bool) sp);
}

TEST(SharedPointer, ArrayFree) {
    int count = 0;
    FunctorSpy<void(int *), DefaultDeleter<int[]>> spy(&count, DefaultDeleter<int[]>());
    {
        SharedPointer<int[], FunctorSpy<void(int *), DefaultDeleter<int[]>>> sp(new int[5], spy);
    }
    EXPECT_EQ(count, 1);
}

TEST(SharedPointer, ArrayGetDeleter) {
    SharedPointer<int[], DeleterMock<int>> sp(nullptr);
    DeleterMock<int> deleter;
    EXPECT_EQ(deleter, sp.getDeleter());
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
    SharedPointer<SimpleWrapper[]> sa(new SimpleWrapper[SAMPLE_ARRAY_SIZE]);
    for (size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        EXPECT_EQ(sa[i].value, SimpleWrapper::defaultValue);
}

TEST(SharedPointer, SubscriptSet) {
    SharedPointer<size_t[]> sa(new size_t[SAMPLE_ARRAY_SIZE]);
    for (size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i) {
        sa[i] = i;
        EXPECT_EQ(sa[i], i);
    }
}

TEST(SharedPointer, ArrayBoolCastTrue) {
    SharedPointer<int[]> sa(new int[SAMPLE_ARRAY_SIZE]);
    EXPECT_TRUE((bool) sa);
}

TEST(SharedPointer, ArrayBoolCastFalse) {
    SharedPointer<int[]> sa(nullptr);
    EXPECT_FALSE((bool) sa);
}