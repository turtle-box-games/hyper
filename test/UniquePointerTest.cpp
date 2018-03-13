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

TEST(UniquePointer, Polymorphism) {
    TEST_DESCRIPTION("Unique pointer should be able to have a sub-type of pointer assigned to it");
    int callCount = 0;
    {
        UniquePointer<DestructorSpy> uniquePointer(new DestructorSpySubclass(&callCount));
    }
    EXPECT_EQ(2, callCount);
}

TEST(UniquePointer, Subtype) {
    TEST_DESCRIPTION("Unique pointer should accept another smart pointer of a sub-type");
    int callCount = 0;
    {
        UniquePointer<DestructorSpy> uniquePointer;
        uniquePointer = UniquePointer<DestructorSpySubclass>(new DestructorSpySubclass(&callCount));
    }
    EXPECT_EQ(2, callCount);
}

TEST(UniquePointer, SubtypeDelete) {
    TEST_DESCRIPTION("Unique pointer should accept another smart pointer of a sub-type");
    int callCount = 0;
    {
        UniquePointer<DestructorSpy> uniquePointer(new DestructorSpy(&callCount));
        uniquePointer = UniquePointer<DestructorSpySubclass>(new DestructorSpySubclass(&callCount));
    }
    EXPECT_EQ(3, callCount);
}

TEST(UniquePointer, SubtypeConstructor) {
    TEST_DESCRIPTION("Unique pointer move constructor should accept another smart pointer of a sub-type");
    int callCount = 0;
    {
        UniquePointer<DestructorSpy> uniquePointer(
                UniquePointer<DestructorSpySubclass>(new DestructorSpySubclass(&callCount))
        );
    }
    EXPECT_EQ(2, callCount);
}

TEST(UniquePointer, Expire) {
    TEST_DESCRIPTION("Unique pointer should set internal reference to null when calling expire");
    UniquePointer<int> uniquePointer(new int);
    uniquePointer.expire();
    EXPECT_FALSE((bool) uniquePointer);
}

TEST(UniquePointer, ExpireDelete) {
    TEST_DESCRIPTION("Unique pointer should delete the existing reference when calling expire");
    int callCount = 0;
    UniquePointer<DestructorSpy> uniquePointer(
            new DestructorSpy(&callCount)
    );
    uniquePointer.expire();
    EXPECT_EQ(1, callCount);
}

TEST(UniquePointer, ExpireDeleteSubtype) {
    TEST_DESCRIPTION("Unique pointer should delete the existing reference correctly for sub-types when calling expire");
    int callCount = 0;
    UniquePointer<DestructorSpy> uniquePointer(
            new DestructorSpySubclass(&callCount)
    );
    uniquePointer.expire();
    EXPECT_EQ(2, callCount);
}

TEST(UniquePointer, Reset) {
    TEST_DESCRIPTION("Unique pointer should be able to reset to a new pointer");
    UniquePointer<int> uniquePointer;
    uniquePointer.reset(new int);
    EXPECT_TRUE((bool) uniquePointer);
}

TEST(UniquePointer, ResetDelete) {
    TEST_DESCRIPTION("Unique pointer should delete existing reference when resetting");
    int callCount = 0;
    UniquePointer<DestructorSpy> uniquePointer(
            new DestructorSpy(&callCount)
    );
    uniquePointer.reset(new DestructorSpy);
    EXPECT_EQ(1, callCount);
}

TEST(UniquePointer, ResetDeleteSubtype) {
    TEST_DESCRIPTION("Unique pointer should delete the existing reference correctly for sub-types when resetting");
    int callCount = 0;
    UniquePointer<DestructorSpy> uniquePointer(
            new DestructorSpySubclass(&callCount)
    );
    uniquePointer.reset(new DestructorSpy);
    EXPECT_EQ(2, callCount);
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

TEST(UniquePointer, ArraySpecializationPolymorphism) {
    TEST_DESCRIPTION("Unique pointer should be able to have a sub-type of pointer assigned to it");
    const size_t length = 5;
    int callCount = -static_cast<int>(length * 2);
    {
        UniquePointer<DestructorSpy[]> uniquePointer(
                new DestructorSpySubclass[length]
        );
        for (size_t i = 0; i < length; i++)
            uniquePointer[i] = DestructorSpySubclass(&callCount);
    }
    EXPECT_EQ(length * 2, callCount);
}

TEST(UniquePointer, ArraySpecializationSubtype) {
    TEST_DESCRIPTION("Unique pointer should accept another smart pointer of a sub-type");
    const size_t length = 5;
    int callCount = -static_cast<int>(length * 2);
    {
        UniquePointer<DestructorSpy[]> uniquePointer;
        uniquePointer = UniquePointer<DestructorSpySubclass[]>(new DestructorSpySubclass[length]);
        for (size_t i = 0; i < length; i++)
            uniquePointer[i] = DestructorSpySubclass(&callCount);
    }
    EXPECT_EQ(length * 2, callCount);
}

TEST(UniquePointer, ArraySpecializationSubtypeDelete) {
    TEST_DESCRIPTION("Unique pointer should delete original reference upon reassignment");
    const size_t length = 5;
    int callCount = -static_cast<int>(length * 2);
    {
        UniquePointer<DestructorSpy[]> uniquePointer(new DestructorSpy[length]);
        for (size_t i = 0; i < length; i++)
            uniquePointer[i] = DestructorSpy(&callCount);
        uniquePointer = UniquePointer<DestructorSpySubclass[]>(new DestructorSpySubclass[length]);
        for (size_t i = 0; i < length; i++)
            uniquePointer[i] = DestructorSpySubclass(&callCount);
    }
    EXPECT_EQ(length * 4, callCount);
}

TEST(UniquePointer, ArraySpecializationSubtypeConstructor) {
    TEST_DESCRIPTION("Unique pointer move constructor should accept another smart pointer of a sub-type");
    const size_t length = 5;
    int callCount = -static_cast<int>(length * 2);
    {
        UniquePointer<DestructorSpy[]> uniquePointer(
                UniquePointer<DestructorSpySubclass[]>(new DestructorSpySubclass[length])
        );
        for (size_t i = 0; i < length; i++)
            uniquePointer[i] = DestructorSpySubclass(&callCount);
    }
    EXPECT_EQ(length * 2, callCount);
}

TEST(UniquePointer, ArraySpecializationExpire) {
    TEST_DESCRIPTION("Unique pointer should set internal reference to null when calling expire");
    UniquePointer<int[]> uniquePointer(new int[5]);
    uniquePointer.expire();
    EXPECT_FALSE((bool) uniquePointer);
}

TEST(UniquePointer, ArraySpecializationExpireDelete) {
    TEST_DESCRIPTION("Unique pointer should delete the existing reference when calling expire");
    const size_t length = 5;
    int callCount = -static_cast<int>(length);
    UniquePointer<DestructorSpy[]> uniquePointer(
            new DestructorSpy[length]
    );
    for (size_t i = 0; i < length; i++)
        uniquePointer[i] = DestructorSpy(&callCount);
    uniquePointer.expire();
    EXPECT_EQ(length, callCount);
}

TEST(UniquePointer, ArraySpecializationExpireDeleteSubtype) {
    TEST_DESCRIPTION("Unique pointer should delete the existing reference correctly for sub-types when calling expire");
    const size_t length = 5;
    int callCount = -static_cast<int>(length * 2);
    UniquePointer<DestructorSpy[]> uniquePointer(
            new DestructorSpySubclass[length]
    );
    for (size_t i = 0; i < length; i++)
        uniquePointer[i] = DestructorSpySubclass(&callCount);
    uniquePointer.expire();
    EXPECT_EQ(length * 2, callCount);
}

TEST(UniquePointer, ArraySpecializationReset) {
    TEST_DESCRIPTION("Unique pointer should be able to reset to a new pointer");
    UniquePointer<int[]> uniquePointer;
    uniquePointer.reset(new int[5]);
    EXPECT_TRUE((bool) uniquePointer);
}

TEST(UniquePointer, ArraySpecializationResetDelete) {
    TEST_DESCRIPTION("Unique pointer should delete existing reference when resetting");
    const size_t length = 5;
    int callCount = -static_cast<int>(length);
    UniquePointer<DestructorSpy[]> uniquePointer(
            new DestructorSpy[length]
    );
    for (size_t i = 0; i < length; i++)
        uniquePointer[i] = DestructorSpy(&callCount);
    uniquePointer.reset(new DestructorSpy[length]);
    EXPECT_EQ(length, callCount);
}

TEST(UniquePointer, ArraySpecializationResetDeleteSubtype) {
    TEST_DESCRIPTION("Unique pointer should delete the existing reference correctly for sub-types when resetting");
    const size_t length = 5;
    int callCount = -static_cast<int>(length * 2);
    UniquePointer<DestructorSpy[]> uniquePointer(
            new DestructorSpySubclass[length]
    );
    for (size_t i = 0; i < length; i++)
        uniquePointer[i] = DestructorSpySubclass(&callCount);
    uniquePointer.reset(new DestructorSpy[length]);
    EXPECT_EQ(length * 2, callCount);
}