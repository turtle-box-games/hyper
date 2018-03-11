#include "DestructorSpy.h"

DestructorSpy::DestructorSpy()
        : _callCount(nullptr) {
    // ...
}

DestructorSpy::DestructorSpy(int *callCount)
        : _callCount(callCount) {
    // ...
}

DestructorSpy::~DestructorSpy() {
    increment();
}

void DestructorSpy::increment() {
    if(_callCount != nullptr)
        (*_callCount)++;
}

DestructorSpySubclass::DestructorSpySubclass()
        : DestructorSpy() {
    // ...
}

DestructorSpySubclass::DestructorSpySubclass(int *callCount)
        : DestructorSpy(callCount) {
    // ...
}

DestructorSpySubclass::~DestructorSpySubclass() {
    increment();
}