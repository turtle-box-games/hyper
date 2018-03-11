#include "common.h"
#include "hyper/SharedPointer.h"
#include "util/DestructorSpy.h"
#include "util/SimpleWrapper.h"

using namespace hyper;

TEST(SharedPointer, DefaultConstructor) {
    TEST_DESCRIPTION("Default constructor should set pointer to null");
    SharedPointer<int> sharedPointer;
    EXPECT_FALSE((bool) sharedPointer);
}

TEST(SharedPointer, Destructor) {
    TEST_DESCRIPTION("Destructor should be called when the scope is left");
    int callCount = 0;
    {
        SharedPointer<DestructorSpy> sharedPointer(
                new DestructorSpy(&callCount)
        );
    }
    EXPECT_EQ(1, callCount);
}

TEST(SharedPointer, GetDereference) {
    TEST_DESCRIPTION("Should be able to retrieve value through pointer");
    const int value = 42;
    SharedPointer<int> sharedPointer(new int(value));
    EXPECT_EQ(value, *sharedPointer);
}

TEST(SharedPointer, SetDereference) {
    TEST_DESCRIPTION("Should be able to update value through pointer");
    const int value = 42;
    SharedPointer<int> sharedPointer(new int);
    *sharedPointer = value;
    EXPECT_EQ(value, *sharedPointer);
}

TEST(SharedPointer, GetIndirect) {
    TEST_DESCRIPTION("Should be able to retrieve member through pointer");
    SharedPointer<SimpleWrapper> sharedPointer(new SimpleWrapper);
    EXPECT_EQ(SimpleWrapper::defaultValue, sharedPointer->value);
}

TEST(SharedPointer, SetIndirect) {
    TEST_DESCRIPTION("Should be able to update member through pointer");
    const int value = 12345;
    SharedPointer<SimpleWrapper> sharedPointer(new SimpleWrapper);
    sharedPointer->value = value;
    EXPECT_EQ(value, sharedPointer->value);
}

TEST(SharedPointer, BoolCastTrue) {
    TEST_DESCRIPTION("Cast to bool should return true for non-null pointers");
    SharedPointer<int> sharedPointer(new int);
    EXPECT_TRUE((bool) sharedPointer);
}

TEST(SharedPointer, BoolCastFalse) {
    TEST_DESCRIPTION("Cast to bool should return false for null pointers");
    SharedPointer<int> sharedPointer(nullptr);
    EXPECT_FALSE((bool) sharedPointer);
}

TEST(SharedPointer, ArraySpecializationDefaultConstructor) {
    TEST_DESCRIPTION("Default constructor should set pointer to null");
    SharedPointer<int[]> sharedPointer;
    EXPECT_FALSE((bool) sharedPointer);
}

TEST(SharedPointer, ArraySpecializationDestructor) {
    TEST_DESCRIPTION("Destructor should be called on all elements when the scope is left");
    const size_t length = 5;
    int callCount = -static_cast<int>(length);
    {
        SharedPointer<DestructorSpy[]> sharedPointer(
                new DestructorSpy[length]
        );
        for (size_t i = 0; i < length; i++)
            sharedPointer[i] = DestructorSpy(&callCount);
    }
    EXPECT_EQ(length, callCount);
}

TEST(SharedPointer, ArraySpecializationGetSubscript) {
    TEST_DESCRIPTION("Able to retrieve value from an element");
    SharedPointer<SimpleWrapper[]> sharedPointer(new SimpleWrapper[5]);
    EXPECT_EQ(SimpleWrapper::defaultValue, sharedPointer[0].value);
}

TEST(SharedPointer, ArraySpecializationSetSubscript) {
    TEST_DESCRIPTION("Able to set value of an element");
    const int value = 12345;
    SharedPointer<int[]> sharedPointer(new int[5]);
    sharedPointer[1] = value;
    EXPECT_EQ(value, sharedPointer[1]);
}

TEST(SharedPointer, ArraySpecializationBoolCastTrue) {
    TEST_DESCRIPTION("Cast to bool should return true for non-null pointers");
    SharedPointer<int[]> sharedPointer(new int[5]);
    EXPECT_TRUE((bool) sharedPointer);
}

TEST(SharedPointer, ArraySpecializationBoolCastFalse) {
    TEST_DESCRIPTION("Cast to bool should return false for null pointers");
    SharedPointer<int[]> sharedPointer(nullptr);
    EXPECT_FALSE((bool) sharedPointer);
}