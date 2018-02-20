/// @file ScalarDestructor.h
/// Method for destroying a scalar-based instance.

#ifndef HYPER_SCALARDESTRUCTOR_H
#define HYPER_SCALARDESTRUCTOR_H

namespace hyper
{
    template<typename T>
    class ScalarDestructor
    {
    public:
        void operator()(T *&instance)
        {
            if(instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }
    };
}

#endif //HYPER_SCALARDESTRUCTOR_H
