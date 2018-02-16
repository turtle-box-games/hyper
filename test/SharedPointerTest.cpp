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
};

TEST(SharedPointer, GetPointer) {
    auto ptr = new int;
    SharedPointer<int> sp(ptr);
    EXPECT_EQ(ptr, sp.get());
}

TEST(SharedPointer, Free) {
    bool result = false;
    auto mock = new SharedPointerDestructorCapture(&result);
    {
        SharedPointer<SharedPointerDestructorCapture> sp(mock);
        // sp should be freed when this scope exits,
        // which will set result to true if the destructor was called.
    }
    EXPECT_TRUE(result);
}

TEST(SharedPointer, ExpireNull) {
    auto ptr = new int;
    SharedPointer<int> sp(ptr);
    sp.expire();
    EXPECT_FALSE((bool)sp);
}

TEST(SharedPointer, ExpireFree) {
    bool result = false;
    auto mock = new SharedPointerDestructorCapture(&result);
    SharedPointer<SharedPointerDestructorCapture> sp(mock);
    sp.expire();
    EXPECT_TRUE(result);
}

TEST(SharedPointer, Swap) {
    auto ptr1 = new int;
    auto ptr2 = new int;
    SharedPointer<int> sp1(ptr1);
    SharedPointer<int> sp2(ptr2);
    sp1.swap(sp2);
    EXPECT_EQ(sp1.get(), ptr2);
    EXPECT_EQ(sp2.get(), ptr1);
}

TEST(SharedPointer, DereferenceGet) {
    auto ptr = new int(5);
    SharedPointer<int> sp(ptr);
    EXPECT_EQ(*sp, 5);
}

TEST(SharedPointer, DereferenceSet) {
    auto ptr = new int;
    SharedPointer<int> sp(ptr);
    *sp = 42;
    EXPECT_EQ(*ptr, 42);
}

TEST(SharedPointer, MemberAccessGet) {
    auto ptr = new SharedPointerSampleData;
    ptr->value = 777;
    SharedPointer<SharedPointerSampleData> sp(ptr);
    EXPECT_EQ(sp->value, 777);
}

TEST(SharedPointer, MemberAccessSet) {
    auto ptr = new SharedPointerSampleData;
    SharedPointer<SharedPointerSampleData> sp(ptr);
    sp->value = 12345;
    EXPECT_EQ(ptr->value, 12345);
}

TEST(SharedPointer, BoolCastTrue) {
    auto ptr = new int;
    SharedPointer<int> sp(ptr);
    EXPECT_TRUE((bool)sp);
}

TEST(SharedPointer, BoolCastFalse) {
    SharedPointer<int> sp(nullptr);
    EXPECT_FALSE((bool)sp);
}