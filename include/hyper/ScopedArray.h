/// @file ScopedArray.h
/// Definition of a smart pointer for arrays that frees itself once the scope it was declared in is left.

#ifndef HYPER_SCOPEDARRAY_H
#define HYPER_SCOPEDARRAY_H

#include "pointer_util.h"
#include "assert.h"

namespace hyper
{
    /// @brief Smart array pointer that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    /// @tparam T Type of the array elements.
    template<typename T>
    class ScopedArray
    {
    private:
        T *_ptr;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped pointer for an array.
        /// @param ptr Raw array pointer to wrap.
        constexpr explicit ScopedArray(T *ptr) noexcept
            : _ptr(ptr)
        {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled.
        ScopedArray(ScopedArray const &) = delete;

        /// @brief Destructor.
        /// @details Releases the resources referenced by the pointer.
        ~ScopedArray() noexcept
        {
            checkedDeleteArray(_ptr);
        }

        /// @brief Retrieves the raw pointer being held by this container.
        /// @return Raw array pointer.
        constexpr T *get() const noexcept
        {
            return _ptr;
        }

        /// @brief Forces the pointer to be destroyed and resources released.
        void reset() noexcept
        {
            // Reuse the swap method to reference a nullptr.
            // This temporary scoped pointer to swap with immediately
            // goes out of scope, thus calling the destructor.
            ScopedArray<T>(nullptr).swap(*this);
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
        ScopedArray &operator=(ScopedArray const &) = delete;

        /// @brief Equality operator.
        /// @details Equality operator is disabled.
        ///   Scoped pointers should never reference the same raw pointer.
        void operator==(ScopedArray const &) = delete;

        /// @brief Inequality operator.
        /// @brief Inequality operator is disabled.
        ///   Scoped pointers should never reference the same raw pointer.
        void operator!=(ScopedArray const &) = delete;
    };
}

#endif //HYPER_SCOPEDARRAY_H
