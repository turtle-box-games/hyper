#ifndef HYPER_TEST_DELETERMOCK_H
#define HYPER_TEST_DELETERMOCK_H

#include "gmock/gmock.h"

template<typename T>
class DeleterMock
{
    MOCK_METHOD1_T(functor, void(T *&ptr));
    void operator()(T *&ptr)
    {
        functor(ptr);
    }
};

#endif //HYPER_TEST_DELETERMOCK_H