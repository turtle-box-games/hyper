#include "gtest/gtest.h"
#include "hyper/SharedPointer.h"

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

TEST(SharedPointer, ResetNull) {
    SharedPointer<int> sp(new int);
    sp.expire();
    EXPECT_FALSE((bool)sp);
}

TEST(SharedPointer, ResetFree) {
    bool result = false;
    SharedPointer<SharedPointerDestructorCapture> sp(
            new SharedPointerDestructorCapture(&result)
    );
    sp.expire();
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