/// @file pointer_util.h
/// Utility methods for dealing with raw pointers.
/// Makes dealing with raw pointers a little easier with these methods.

#ifndef HYPER_POINTER_UTIL_H
#define HYPER_POINTER_UTIL_H

namespace hyper
{
    /// @brief Check before deleting a pointer.
    /// @details Checks if an instance referenced by a pointer already appears to be deleted before freeing it.
    ///   Afterwards, the pointer is updated to reference NULL so that future calls will do nothing.
    /// @tparam T Type of instance being referenced by a pointer.
    /// @param object Reference to the pointer to delete.
    template<typename T>
    inline void checkedDelete(T *&object) noexcept
    {
        if(object != nullptr)
        {
            delete object;
            object = nullptr;
        }
    }

    /// @brief Check before deleting an array.
    /// @details Checks if an array referenced by a pointer already appears to be deleted before freeing it.
    ///   Afterwards, the pointer is updated to reference NULL so that future calls will do nothing.
    /// @tparam T Type of elements in the array being referenced by a pointer.
    /// @param array Reference to the array to delete.
    template<typename T>
    inline void checkedDeleteArray(T *&array) noexcept
    {
        if(array != nullptr)
        {
            delete[] array;
            array = nullptr;
        }
    }
}

#endif //HYPER_POINTER_UTIL_H
