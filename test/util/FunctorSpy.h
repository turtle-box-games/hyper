#ifndef HYPER_TEST_FUNCTORSPY_H
#define HYPER_TEST_FUNCTORSPY_H

template<typename Signature>
class FunctorSpy {};

template<typename ReturnType, typename... Args>
class FunctorSpy<ReturnType(Args...)>
{
private:
    int *_count;

public:
    FunctorSpy(int *count)
            : _count(count)
    {
        // ...
    }

    ReturnType operator()(Args...)
    {
        (*_count)++;
        return ReturnType();
    }
};

#endif //HYPER_TEST_FUNCTORSPY_H