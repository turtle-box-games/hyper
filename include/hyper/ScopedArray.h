/// @file ScopedArray.h
/// Definition of a smart pointer for arrays that frees itself once the scope it was declared in is left.

#ifndef HYPER_SCOPEDARRAY_H
#define HYPER_SCOPEDARRAY_H

#include "pointer_utility.h"
#include "assert.h"

namespace hyper
{
    /// @brief Smart array pointer that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    /// @tparam T Type of the array elements.
    template<typename T>
    class ScopedArray
    {
    private:
        T *_ptr;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped array with the default constructor of type @tparam T.
        /// @param length Size of the array to create.
        constexpr explicit ScopedArray(size_t length) noexcept
                : _ptr(new T[length])
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new scoped array with an existing reference.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit ScopedArray(T *&&ptr) noexcept
                : _ptr(ptr)
        {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled.
        ScopedArray(const ScopedArray &) = delete;

        /// @brief Destructor.
        /// @details Releases the resources referenced by the pointer.
        ~ScopedArray() noexcept
        {
            checkedDeleteArray(_ptr);
        }

        /// @brief Swaps the contents of two scoped pointers.
        /// @param other Scoped pointer to swap with.
        void swap(ScopedArray &other) noexcept
        {
            T *temp = other._ptr;
            other._ptr = _ptr;
            _ptr = temp;
        }

        /// @brief Subscript operator.
        /// @details Provides access to a specified element in the array.
        /// @param index Base-zero index of the element to access.
        /// @return Element at the specified index.
        T &operator[](size_t index) noexcept
        {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr[index];
        }

        /// @brief Subscript operator.
        /// @details Retrieves a specified element in the array.
        /// @param index Base-zero index of the element to access.
        /// @return Element at the specified index.
        constexpr T &operator[](size_t index) const noexcept
        {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr[index];
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept
        {
            return _ptr != nullptr;
        }

        /// @brief Assignment operator.
        /// @details Assignment operator is disabled.
        ///   Assigning pointer values would invalidate the scope of the pointer.
        ScopedArray &operator=(const ScopedArray &) = delete;

        /// @brief Equality operator.
        /// @details Equality operator is disabled.
        ///   Scoped pointers should never reference the same raw pointer.
        bool operator==(const ScopedArray &) = delete;

        /// @brief Inequality operator.
        /// @brief Inequality operator is disabled.
        ///   Scoped pointers should never reference the same raw pointer.
        bool operator!=(const ScopedArray &) = delete;
    };

    /// @brief Swaps the references of two scoped arrays.
    /// @param first First smart pointer to swap.
    /// @param second Second smart pointer to swap.
    template<typename T>
    void swap(ScopedArray<T> &first, ScopedArray<T> &second)
    {
        first.swap(second);
    }
}

#endif //HYPER_SCOPEDARRAY_H
