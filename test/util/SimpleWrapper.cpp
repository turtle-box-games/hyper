#include "SimpleWrapper.h"

const int SimpleWrapper::defaultValue = 42;

SimpleWrapper::SimpleWrapper()
        : value(defaultValue) {
    // ...
}

SimpleWrapper::SimpleWrapper(int val)
        : value(val) {
    // ...
}