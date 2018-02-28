#include "gtest/gtest.h"
#include "hyper/SharedPointer.h"

#define SAMPLE_ARRAY_SIZE 100

using namespace hyper;

class ScalarDestructorCapture
{
private:
    bool *_destructorCalled;

public:
    ScalarDestructorCapture(bool *flag)
            : _destructorCalled(flag)
    {
        // ...
    }

    ~ScalarDestructorCapture()
    {
        *_destructorCalled = true;
    }
};

class VectorDestructorCapture
{
private:
    int *_destructorCallCount;

public:
    VectorDestructorCapture()
            : _destructorCallCount(nullptr)
    {
        // ...
    }

    VectorDestructorCapture(int *count)
            : _destructorCallCount(count)
    {
        // ...
    }

    ~VectorDestructorCapture()
    {
        (*_destructorCallCount)++;
    }
};

TEST(DefaultDestructor, Scalar) {
    bool result = false;
    auto sdc    = new ScalarDestructorCapture(&result);
    DefaultDeleter<ScalarDestructorCapture> destructor;
    destructor(sdc);
    EXPECT_TRUE(result);
}

TEST(DefaultDestructor, Vector) {
    int count = -SAMPLE_ARRAY_SIZE;
    auto vdc  = new VectorDestructorCapture[SAMPLE_ARRAY_SIZE];
    for(size_t i = 0; i < SAMPLE_ARRAY_SIZE; ++i)
        vdc[i] = VectorDestructorCapture(&count);
    DefaultDeleter<VectorDestructorCapture[]> destructor;
    destructor(vdc);
    EXPECT_EQ(count, SAMPLE_ARRAY_SIZE);
}