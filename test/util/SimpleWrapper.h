#ifndef HYPER_TEST_SIMPLEWRAPPER_H
#define HYPER_TEST_SIMPLEWRAPPER_H

struct SimpleWrapper
{
    static const int defaultValue;
    int value;

    SimpleWrapper();
    explicit SimpleWrapper(int val);
};

#endif //HYPER_TEST_SIMPLEWRAPPER_H