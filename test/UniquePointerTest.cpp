#include "common.h"
#include "hyper/UniquePointer.h"
#include "util/DestructorSpy.h"
#include "util/SimpleWrapper.h"

using namespace hyper;

TEST(UniquePointer, DefaultConstructor) {
    TEST_DESCRIPTION("Default constructor should set pointer to null");
    UniquePointer<int> uniquePointer;
    EXPECT_FALSE((bool) uniquePointer);
}

TEST(UniquePointer, Destructor) {
    TEST_DESCRIPTION("Destructor should be called when the scope is left");
    int callCount = 0;
    {
        UniquePointer<DestructorSpy> uniquePointer(
                new DestructorSpy(&callCount)
        );
    }
    EXPECT_EQ(1, callCount);
}

TEST(UniquePointer, GetDereference) {
    TEST_DESCRIPTION("Should be able to retrieve value through pointer");
    const int value = 42;
    UniquePointer<int> uniquePointer(new int(value));
    EXPECT_EQ(value, *uniquePointer);
}

TEST(UniquePointer, SetDereference) {
    TEST_DESCRIPTION("Should be able to update value through pointer");
    const int value = 42;
    UniquePointer<int> uniquePointer(new int);
    *uniquePointer = value;
    EXPECT_EQ(value, *uniquePointer);
}

TEST(UniquePointer, GetIndirect) {
    TEST_DESCRIPTION("Should be able to retrieve member through pointer");
    UniquePointer<SimpleWrapper> uniquePointer(new SimpleWrapper);
    EXPECT_EQ(SimpleWrapper::defaultValue, uniquePointer->value);
}

TEST(UniquePointer, SetIndirect) {
    TEST_DESCRIPTION("Should be able to update member through pointer");
    const int value = 12345;
    UniquePointer<SimpleWrapper> uniquePointer(new SimpleWrapper);
    uniquePointer->value = value;
    EXPECT_EQ(value, uniquePointer->value);
}

TEST(UniquePointer, BoolCastTrue) {
    TEST_DESCRIPTION("Cast to bool should return true for non-null pointers");
    UniquePointer<int> uniquePointer(new int);
    EXPECT_TRUE((bool) uniquePointer);
}

TEST(UniquePointer, BoolCastFalse) {
    TEST_DESCRIPTION("Cast to bool should return false for null pointers");
    UniquePointer<int> uniquePointer(nullptr);
    EXPECT_FALSE((bool) uniquePointer);
}

TEST(UniquePointer, ArraySpecializationDefaultConstructor) {
    TEST_DESCRIPTION("Default constructor should set pointer to null");
    UniquePointer<int[]> uniquePointer;
    EXPECT_FALSE((bool) uniquePointer);
}

TEST(UniquePointer, ArraySpecializationDestructor) {
    TEST_DESCRIPTION("Destructor should be called on all elements when the scope is left");
    const size_t length = 5;
    int callCount = -static_cast<int>(length);
    {
        UniquePointer<DestructorSpy[]> uniquePointer(
                new DestructorSpy[length]
        );
        for (size_t i = 0; i < length; i++)
            uniquePointer[i] = DestructorSpy(&callCount);
    }
    EXPECT_EQ(length, callCount);
}

TEST(UniquePointer, ArraySpecializationGetSubscript) {
    TEST_DESCRIPTION("Able to retrieve value from an element");
    UniquePointer<SimpleWrapper[]> uniquePointer(new SimpleWrapper[5]);
    EXPECT_EQ(SimpleWrapper::defaultValue, uniquePointer[0].value);
}

TEST(UniquePointer, ArraySpecializationSetSubscript) {
    TEST_DESCRIPTION("Able to set value of an element");
    const int value = 12345;
    UniquePointer<int[]> uniquePointer(new int[5]);
    uniquePointer[1] = value;
    EXPECT_EQ(value, uniquePointer[1]);
}

TEST(UniquePointer, ArraySpecializationBoolCastTrue) {
    TEST_DESCRIPTION("Cast to bool should return true for non-null pointers");
    UniquePointer<int[]> uniquePointer(new int[5]);
    EXPECT_TRUE((bool) uniquePointer);
}

TEST(UniquePointer, ArraySpecializationBoolCastFalse) {
    TEST_DESCRIPTION("Cast to bool should return false for null pointers");
    UniquePointer<int[]> uniquePointer(nullptr);
    EXPECT_FALSE((bool) uniquePointer);
}