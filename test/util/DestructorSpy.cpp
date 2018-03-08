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
    (*_callCount)++;
}