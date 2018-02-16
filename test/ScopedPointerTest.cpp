#include "gtest/gtest.h"
#include "hyper/ScopedPointer.h"

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
};

TEST(ScopedPointer, Free) {
    bool result = false;
    auto mock = new ScopedPointerDestructorCapture(&result);
    {
        ScopedPointer<ScopedPointerDestructorCapture> sp(mock);
        // sp should be freed when this scope exits,
        // which will set result to true if the destructor was called.
    }
    EXPECT_TRUE(result);
}

TEST(ScopedPointer, ResetNull) {
    auto ptr = new int;
    ScopedPointer<int> sp(ptr);
    sp.expire();
    EXPECT_FALSE((bool)sp);
}

TEST(ScopedPointer, ResetFree) {
    bool result = false;
    auto mock = new ScopedPointerDestructorCapture(&result);
    ScopedPointer<ScopedPointerDestructorCapture> sp(mock);
    sp.expire();
    EXPECT_TRUE(result);
}

TEST(ScopedPointer, Swap) {
    const auto val1 = 42;
    const auto val2 = 24;
    auto ptr1 = new int(val1);
    auto ptr2 = new int(val2);
    ScopedPointer<int> sp1(ptr1);
    ScopedPointer<int> sp2(ptr2);
    sp1.swap(sp2);
    EXPECT_EQ(val1, *sp2);
    EXPECT_EQ(val2, *sp1);
}

TEST(ScopedPointer, DereferenceGet) {
    auto ptr = new int(5);
    ScopedPointer<int> sp(ptr);
    EXPECT_EQ(*sp, 5);
}

TEST(ScopedPointer, DereferenceSet) {
    auto ptr = new int;
    ScopedPointer<int> sp(ptr);
    *sp = 42;
    EXPECT_EQ(*ptr, 42);
}

TEST(ScopedPointer, MemberAccessGet) {
    auto ptr = new ScopedPointerSampleData;
    ptr->value = 777;
    ScopedPointer<ScopedPointerSampleData> sp(ptr);
    EXPECT_EQ(sp->value, 777);
}

TEST(ScopedPointer, MemberAccessSet) {
    auto ptr = new ScopedPointerSampleData;
    ScopedPointer<ScopedPointerSampleData> sp(ptr);
    sp->value = 12345;
    EXPECT_EQ(ptr->value, 12345);
}

TEST(ScopedPointer, BoolCastTrue) {
    auto ptr = new int;
    ScopedPointer<int> sp(ptr);
    EXPECT_TRUE((bool)sp);
}

TEST(ScopedPointer, BoolCastFalse) {
    ScopedPointer<int> sp(nullptr);
    EXPECT_FALSE((bool)sp);
}