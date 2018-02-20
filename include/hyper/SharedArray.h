/// @file SharedArray.h
/// Definition of a smart pointer referencing an array that can be shared throughout the application
/// and it will automatically free the entire array when it is no longer referenced.

#ifndef HYPER_SHAREDARRAY_H
#define HYPER_SHAREDARRAY_H

#include "assert.h"
#include "VectorDestructor.h"
#include "ReferenceCounter.h"

namespace hyper
{
    /// @brief Smart pointer referencing an array that can be shared throughout the application.
    /// @details Smart pointer to an array that tracks its references.
    ///   The pointer will automatically be destroyed (and all array resources freed)
    ///   when there are no more references to it.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    /// @tparam T Type the elements in the array.
    template<typename T, typename Destructor = VectorDestructor<T>>
    class SharedArray
    {
    private:
        ReferenceCounter<T, Destructor> *_impl;

    public:
        /// @brief Default constructor.
        /// @details Creates a new shared pointer with the default constructor of type @tparam T.
        constexpr explicit SharedArray(size_t length) noexcept
                : _impl(new ReferenceCounter<T, Destructor>(new T[length]))
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new shared pointer with an existing reference.
        /// @param arr Pointer to array to wrap.
        constexpr explicit SharedArray(T *&&arr) noexcept
                : _impl(new ReferenceCounter<T, Destructor>(arr))
        {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Creates a new shared pointer that references an existing one.
        /// @param other Existing shared pointer.
        SharedArray(const SharedArray &other) noexcept
            : _impl(other._impl)
        {
            _impl->increment();
        }

        /// @brief Move constructor.
        /// @details Creates a new shared pointer from a temporary one.
        /// @param other Temporary shared pointer.
        SharedArray(SharedArray &&other) noexcept
            : _impl(other._impl)
        {
            other._impl = nullptr;
        }

        /// @brief Destructor.
        /// @details Releases the resources referenced by the shared pointer.
        ///   The underlying array will not be released unless all other references have been released.
        ~SharedArray() noexcept
        {
            if(_impl != nullptr)
            {
                // Release reference counter if this instance is the last one using it.
                if(!_impl->decrement())
                    delete _impl;
                _impl = nullptr;
            }
        }

        /// @brief Swaps the contents of two Shared pointers.
        /// @param other Shared pointer to swap with.
        void swap(SharedArray &other) noexcept
        {
            auto temp = other._impl;
            other._impl = _impl;
            _impl = temp;
        }

        /// @brief Subscript operator.
        /// @details Provides access to a specified element in the array.
        /// @param index Base-zero index of the element to access.
        /// @return Element at the specified index.
        T &operator[](size_t index) noexcept
        {
            auto arr = _impl->getReference();
            ASSERTF(arr != nullptr, "Attempt to dereference null pointer");
            return arr[index];
        }

        /// @brief Subscript operator.
        /// @details Retrieves a specified element in the array.
        /// @param index Base-zero index of the element to access.
        /// @return Element at the specified index.
        constexpr T &operator[](size_t index) const noexcept
        {
            auto arr = _impl->getReference();
            ASSERTF(arr != nullptr, "Attempt to dereference null pointer");
            return arr[index];
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept
        {
            return _impl->getReference() != nullptr;
        }

        /// @brief Assignment operator.
        /// @details Overwrites the current pointer with a copy of another.
        /// @param other Other pointer to overwrite the existing one with.
        /// @return The current pointer.
        SharedArray &operator=(SharedArray other)
        {
            swap(other);
            return *this;
        }

        /// @brief Equality operator.
        /// @details Checks if two shared pointers reference the same raw array.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference the same array.
        /// @return False if the instances reference different arrays.
        /// @return True if both instances reference null.
        /// @return False if only one instance references null.
        constexpr bool operator==(const SharedArray &other) const noexcept
        {
            if(_impl == other._impl)
                return true;
            else
                return _impl->getReference() == other._impl->getReference();
        }

        /// @brief Inequality operator.
        /// @details Checks if two shared pointers don't reference the same raw array.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference different arrays.
        /// @return False if the instances reference the same array.
        /// @return True if only one instance references null.
        /// @return False if both instances reference null.
        constexpr bool operator!=(const SharedArray &other) const noexcept
        {
            return !(this == other);
        }
    };

    /// @brief Swaps the references of two shared pointers.
    /// @param first First smart pointer to swap.
    /// @param second Second smart pointer to swap.
    template<typename T>
    void swap(SharedArray<T> &first, SharedArray<T> &second)
    {
        first.swap(second);
    }
}

#endif //HYPER_SHAREDARRAY_H