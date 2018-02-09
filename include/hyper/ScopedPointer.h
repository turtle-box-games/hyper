/// @headerfile <hyper/ScopedPointer.h>

#ifndef HYPER_SCOPEDPOINTER_H
#define HYPER_SCOPEDPOINTER_H

#include "pointer_util.h"

namespace hyper
{
    /// Smart pointer with a lifetime limited to its scope.
    /// This operates on the RAII principle.
    /// @tparam T Type the pointer references.
    template<typename T>
    class ScopedPointer
    {
    private:
        T *_ptr;

    public:
        /// Creates a new scoped pointer.
        /// @param ptr Raw pointer to wrap.
        explicit ScopedPointer(T *ptr) noexcept
            : _ptr(ptr)
        {
            // ...
        }

        /// Copy constructor is disabled.
        ScopedPointer(ScopedPointer const &) = delete;

        /// Releases the resources referenced by the pointer.
        ~ScopedPointer() noexcept
        {
            checkedDelete(_ptr);
        }

        /// Retrieves the raw pointer being held by this container.
        /// @return Raw pointer.
        T *get() const noexcept
        {
            return _ptr;
        }

        /// Forces the pointer to be destroyed and resources released.
        void reset() noexcept
        {
            // Reuse the swap method to reference a nullptr.
            // This temporary scoped pointer to swap with immediately
            // goes out of scope, thus calling the destructor.
            ScopedPointer<T>(nullptr).swap(*this);
        }

        /// Swaps the contents of two scoped pointers.
        /// @param other Scoped pointer to swap with.
        void swap(ScopedPointer &other) noexcept
        {
            T *temp = other._ptr;
            other._ptr = _ptr;
            _ptr = temp;
        }

        T &operator*() const
        {
            // TODO: Check for nullptr.
            return *_ptr;
        }

        T *operator->() const
        {
            // TODO: Check for nullptr.
            return _ptr;
        }

        explicit operator bool() const noexcept
        {
            return _ptr != nullptr;
        }

        /// Assignment operator is disabled.
        /// Assigning pointer values would invalidate the scope of the pointer.
        ScopedPointer &operator=(ScopedPointer const &) = delete;

        /// Equality operator is disabled.
        /// Scoped pointers should never reference the same raw pointer.
        void operator==(ScopedPointer const &) = delete;

        /// Inequality operator is disabled.
        /// Scoped pointers should never reference the same raw pointer.
        void operator!=(ScopedPointer const &) = delete;
    };
}

#endif //HYPER_SCOPEDPOINTER_H
