#include "common.h"
#include "util/DestructorSpy.h"

// Usage of spy as a scalar.
TEST(Foo, ScalarTest) {
    int callCount = 0; // Need to define a counter outside the spy.
    auto spy = new DestructorSpy(&callCount); // Pass the counter to the spy.
    delete spy; // Call the destructor.
    EXPECT_EQ(1, callCount); // Counter should be incremented.
}

// Usage of spy in an array.
TEST(Foo, ArrayTest) {
    const size_t length = 10;
    int callCount = -static_cast<int>(length); // Set counter to negative count to cancel out copy operations.
    auto spies = new DestructorSpy[length]; // Create array of spies.
    for(size_t i = 0; i < length; i++) // Pass counter to each spy.
        spies[i] = DestructorSpy(&callCount); // This causes destructors to be triggered, hence the negative counter earlier.
    delete[] spies; // Call the destructors.
    EXPECT_EQ(length, callCount); // Counter should be incremented.
}