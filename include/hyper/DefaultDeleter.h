/// @file DefaultDestructor.h
/// Strategy for destroying runtime instantiated objects using the default delete methods.

#ifndef HYPER_DEFAULTDESTRUCTOR_H
#define HYPER_DEFAULTDESTRUCTOR_H

namespace hyper
{
    /// @brief General template for deleting scalar instances.
    /// @details Strategy for freeing memory by using the @c delete method.
    ///   Create an instance of this class and use it as a functor
    ///   to destroy runtime instantiated objects.
    /// @tparam T Type of instance to delete.
    template<typename T>
    class DefaultDeleter
    {
    public:
        /// @brief Deletes and frees memory held by an instance.
        /// @details If the pointer is already null, then the delete operation is skipped.
        ///   The pointer is set to null after it is freed.
        /// @param instance Instance to delete.
        inline void operator()(T *&instance)
        {
            if(instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }
    };

    /// @brief Array specialization for freeing vector instances.
    /// @details Strategy for freeing memory by using the @c delete[] method.
    ///   Create an instance of this class and use it as a functor
    ///   to destroy runtime instantiated objects.
    /// @tparam T Type of scalar instance to delete.
    template<typename T>
    class DefaultDeleter<T[]>
    {
    public:
        /// @brief Deletes and frees memory held by an instance.
        /// @details If the pointer is already null, then the delete operation is skipped.
        ///   The pointer is set to null after it is freed.
        /// @param instance Instance to delete.
        inline void operator()(T *&instance)
        {
            if(instance != nullptr)
            {
                delete[] instance;
                instance = nullptr;
            }
        }
    };
}

#endif //HYPER_DEFAULTDESTRUCTOR_H