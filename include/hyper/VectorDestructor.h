/// @file VectorDestructor.h
/// Method for destroying a vector-based instance (array).

#ifndef HYPER_VECTORDESTRUCTOR_H
#define HYPER_VECTORDESTRUCTOR_H

namespace hyper
{
    template<typename T>
    class VectorDestructor
    {
    public:
        void operator()(T *&instance)
        {
            if(instance != nullptr)
            {
                delete[] instance;
                instance = nullptr;
            }
        }
    };
}

#endif //HYPER_VECTORDESTRUCTOR_H
