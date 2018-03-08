#include "common.h"
#include "hyper/ScopedPointer.h"
#include "util/DestructorSpy.h"
#include "util/SimpleWrapper.h"

using namespace hyper;

TEST(ScopedPointer, DefaultConstructor) {
    TEST_DESCRIPTION("Default constructor should set pointer to default");
    ScopedPointer<int> scopedPointer;
    EXPECT_TRUE((bool) scopedPointer);
}

TEST(ScopedPointer, Destructor) {
    TEST_DESCRIPTION("Destructor should be called when the scope is left");
    int callCount = 0;
    {
        ScopedPointer<DestructorSpy> scopedPointer(
                new DestructorSpy(&callCount)
        );
    }
    EXPECT_EQ(1, callCount);
}

TEST(ScopedPointer, GetDereference) {
    TEST_DESCRIPTION("Should be able to retrieve value through pointer");
    const int value = 42;
    ScopedPointer<int> scopedPointer(new int(value));
    EXPECT_EQ(value, *scopedPointer);
}

TEST(ScopedPointer, SetDereference) {
    TEST_DESCRIPTION("Should be able to update value through pointer");
    const int value = 42;
    ScopedPointer<int> scopedPointer(new int);
    *scopedPointer = value;
    EXPECT_EQ(value, *scopedPointer);
}

TEST(ScopedPointer, GetIndirect) {
    TEST_DESCRIPTION("Should be able to retrieve member through pointer");
    ScopedPointer<SimpleWrapper> scopedPointer(new SimpleWrapper);
    EXPECT_EQ(SimpleWrapper::defaultValue, scopedPointer->value);
}

TEST(ScopedPointer, SetIndirect) {
    TEST_DESCRIPTION("Should be able to update member through pointer");
    const int value = 12345;
    ScopedPointer<SimpleWrapper> scopedPointer(new SimpleWrapper);
    scopedPointer->value = value;
    EXPECT_EQ(value, scopedPointer->value);
}

TEST(ScopedPointer, BoolCastTrue) {
    TEST_DESCRIPTION("Cast to bool should return true for non-null pointers");
    ScopedPointer<int> scopedPointer(new int);
    EXPECT_TRUE((bool) scopedPointer);
}

TEST(ScopedPointer, BoolCastFalse) {
    TEST_DESCRIPTION("Cast to bool should return false for null pointers");
    ScopedPointer<int> scopedPointer(nullptr);
    EXPECT_FALSE((bool) scopedPointer);
}

TEST(ScopedPointer, ArraySpecializationDefaultConstructor) {
    TEST_DESCRIPTION("Default constructor should set pointer to null");
    ScopedPointer<int[]> scopedPointer;
    EXPECT_FALSE((bool) scopedPointer);
}

TEST(ScopedPointer, ArraySpecializationDestructor) {
    TEST_DESCRIPTION("Destructor should be called on all elements when the scope is left");
    const size_t length = 5;
    int callCount = -static_cast<int>(length);
    {
        ScopedPointer<DestructorSpy[]> scopedPointer(
                new DestructorSpy[length]
        );
        for (size_t i = 0; i < length; i++)
            scopedPointer[i] = DestructorSpy(&callCount);
    }
    EXPECT_EQ(length, callCount);
}

TEST(ScopedPointer, ArraySpecializationGetSubscript) {
    TEST_DESCRIPTION("Able to retrieve value from an element");
    ScopedPointer<SimpleWrapper[]> scopedPointer(new SimpleWrapper[5]);
    EXPECT_EQ(SimpleWrapper::defaultValue, scopedPointer[0].value);
}

TEST(ScopedPointer, ArraySpecializationSetSubscript) {
    TEST_DESCRIPTION("Able to set value of an element");
    const int value = 12345;
    ScopedPointer<int[]> scopedPointer(new int[5]);
    scopedPointer[1] = value;
    EXPECT_EQ(value, scopedPointer[1]);
}

TEST(ScopedPointer, ArraySpecializationBoolCastTrue) {
    TEST_DESCRIPTION("Cast to bool should return true for non-null pointers");
    ScopedPointer<int[]> scopedPointer(new int[5]);
    EXPECT_TRUE((bool) scopedPointer);
}

TEST(ScopedPointer, ArraySpecializationBoolCastFalse) {
    TEST_DESCRIPTION("Cast to bool should return false for null pointers");
    ScopedPointer<int[]> scopedPointer(nullptr);
    EXPECT_FALSE((bool) scopedPointer);
}