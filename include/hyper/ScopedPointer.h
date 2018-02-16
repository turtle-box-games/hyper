/// @file ScopedPointer.h
/// Definition of a smart pointer that frees itself once the scope it was declared in is left.

#ifndef HYPER_SCOPEDPOINTER_H
#define HYPER_SCOPEDPOINTER_H

#include "pointer_util.h"
#include "assert.h"

namespace hyper
{
    /// @brief Smart pointer that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    /// @tparam T Type the pointer references.
    template<typename T>
    class ScopedPointer
    {
    private:
        T *_ptr;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped pointer with the default constructor of type @tparam T.
        constexpr explicit ScopedPointer() noexcept
            : _ptr(new T)
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new scoped pointer with an existing reference.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit ScopedPointer(T *&&ptr) noexcept
            : _ptr(ptr)
        {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled.
        ScopedPointer(const ScopedPointer &) = delete;

        /// @brief Destructor.
        /// @details Releases the resources referenced by the pointer.
        ~ScopedPointer() noexcept
        {
            checkedDelete(_ptr);
        }

        /// @brief Forces the pointer to be destroyed and resources released.
        void expire() noexcept
        {
            // Reuse the swap method to reference a nullptr.
            // This temporary scoped pointer to swap with immediately
            // goes out of scope, thus calling the destructor.
            ScopedPointer<T>(nullptr).swap(*this);
        }

        /// @brief Swaps the contents of two scoped pointers.
        /// @param other Scoped pointer to swap with.
        void swap(ScopedPointer &other) noexcept
        {
            T *temp = other._ptr;
            other._ptr = _ptr;
            _ptr = temp;
        }

        /// @brief Member access operator.
        /// @details Provides access to the underlying reference.
        /// @return Underlying reference.
        /// @note Be sure that it is safe to de-reference the pointer.
        ///   The pointer is asserted to be non-null.
        constexpr T &operator*() const noexcept
        {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return *_ptr;
        }

        /// @brief Member access operator.
        /// @details Provides access to the underlying reference.
        /// @return Underlying reference.
        /// @note Be sure that it is safe to de-reference the pointer.
        ///   The pointer is asserted to be non-null.
        constexpr T *operator->() const noexcept
        {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr;
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
        ScopedPointer &operator=(const ScopedPointer &) = delete;

        /// @brief Equality operator.
        /// @details Equality operator is disabled.
        ///   Scoped pointers should never reference the same raw pointer.
        bool operator==(const ScopedPointer &) = delete;

        /// @brief Inequality operator.
        /// @brief Inequality operator is disabled.
        ///   Scoped pointers should never reference the same raw pointer.
        bool operator!=(const ScopedPointer &) = delete;
    };
}

#endif //HYPER_SCOPEDPOINTER_H
