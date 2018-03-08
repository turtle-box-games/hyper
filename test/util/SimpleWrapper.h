#ifndef HYPER_TEST_SIMPLE_WRAPPER_H
#define HYPER_TEST_SIMPLE_WRAPPER_H

struct SimpleWrapper
{
    static const int defaultValue;
    int value;

    SimpleWrapper();
    explicit SimpleWrapper(int val);
};

#endif // HYPER_TEST_SIMPLE_WRAPPER_H