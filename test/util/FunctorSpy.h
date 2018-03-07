#ifndef HYPER_TEST_FUNCTORSPY_H
#define HYPER_TEST_FUNCTORSPY_H

template<typename Signature, typename Implementation>
class FunctorSpy {};

template<typename ReturnType, typename... Args, typename Implementation>
class FunctorSpy<ReturnType(Args...), Implementation>
{
private:
    int *_count;
    Implementation _impl;

public:
    FunctorSpy(int *count, Implementation impl)
            : _count(count), _impl(impl)
    {
        // ...
    }

    ReturnType operator()(Args... args)
    {
        (*_count)++;
        return _impl(args...);
    }
};

#endif //HYPER_TEST_FUNCTORSPY_H