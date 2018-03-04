#ifndef HYPER_TEST_DELETERMOCK_H
#define HYPER_TEST_DELETERMOCK_H

#include "gmock/gmock.h"

template<typename T>
struct DeleterMock
{
    MOCK_METHOD1_T(functor, void(T *&instance));
    DeleterMock() { }
    DeleterMock(const DeleterMock &) { }
    void operator()(T *&instance) {
        functor(instance);
    }
};

template<typename T>
bool operator==(DeleterMock<T>, DeleterMock<T>) {
    return true;
}

#endif //HYPER_TEST_DELETERMOCK_H