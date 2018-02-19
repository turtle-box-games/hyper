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

    ScopedPointerSampleData() = default;

    ScopedPointerSampleData(int val)
            : value(val)
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
    ScopedPointer<int> sp;
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
    ScopedPointer<ScopedPointerSampleData> sp;
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