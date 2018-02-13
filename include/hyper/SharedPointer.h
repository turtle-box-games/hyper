/// @file SharedPointer.h
/// Definition of a smart pointer that can be shared throughout the application
/// and it will automatically be freed when it is no longer referenced.

#ifndef HYPER_SHAREDPOINTER_H
#define HYPER_SHAREDPOINTER_H

#include "pointer_util.h"
#include "assert.h"

namespace hyper
{
    /// @brief Smart pointer that can be shared throughout the application.
    /// @details Smart pointer that tracks its references.
    ///   The pointer will automatically be destroyed (and resources freed)
    ///   when there are no more references to it.
    /// @tparam T Type the pointer references.
    template<typename T>
    class SharedPointer
    {
    private:
        /// @brief Underlying implementation for tracking references.
        /// @details All smart pointers that refer to the same instance share a single instance of this class.
        ///   This allows the smart pointers to "communicate" when they are no longer being used.
        /// @todo Implement locking to be safe in multi-threaded scenarios.
        class ReferenceCounter
        {
        private:
            size_t _count;
            T *_ptr;

        public:
            constexpr ReferenceCounter(T *ptr) noexcept
                : _count(1), _ptr(ptr)
            {
                // ...
            }

            ~ReferenceCounter()
            {
                _count = 0;
                checkedDelete(_ptr);
            }

            void increment() noexcept
            {
                _count++;
            }

            bool decrement() noexcept
            {
                ASSERTF(_count > 0, "Attempted to decrement reference count below zero");
                return 0 < --_count;
            }

            constexpr T *getReference() const noexcept
            {
                return _ptr;
            }
        };

        ReferenceCounter *_impl;

    public:
        /// @brief Default constructor.
        /// @details Creates a new Shared pointer.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit SharedPointer(T *ptr)
            : _impl(new ReferenceCounter(ptr))
        {
            // ...
        }

        /// @brief Copy constructor.
        SharedPointer(const SharedPointer &other) noexcept
            : _impl(other._impl)
        {
            _impl->increment();
        }

        /// @brief Move constructor.
        SharedPointer(SharedPointer &&other) noexcept
            : _impl(other._impl)
        {
            other._impl = nullptr;
        }

        /// @brief Destructor.
        /// @details Releases the resources referenced by the pointer.
        ~SharedPointer() noexcept
        {
            // Release reference counter if this instance is the last one using it.
            if(_impl != nullptr && !_impl->decrement())
                delete _impl;
        }

        /// @brief Retrieves the raw pointer being held by this container.
        /// @return Raw pointer.
        constexpr T *get() const noexcept
        {
            return _impl == nullptr ? nullptr : _impl->getReference();
        }

        /// @brief Forces the pointer to be destroyed and resources released.
        void reset() noexcept
        {
            checkedDelete(_impl);
        }

        /// @brief Swaps the contents of two Shared pointers.
        /// @param other Shared pointer to swap with.
        void swap(SharedPointer &other) noexcept
        {
            auto temp = other._impl;
            other._impl = _impl;
            _impl = temp;
        }

        /// @brief Member access operator.
        /// @details Provides access to the underlying reference.
        /// @return Underlying reference.
        /// @note Be sure that it is safe to de-reference the pointer.
        ///   The pointer is asserted to be non-null.
        constexpr T &operator*() const noexcept
        {
            ASSERTF(_impl != nullptr, "Attempt to use a disposed shared pointer");
            auto ptr = _impl->getReference();
            ASSERTF(ptr != nullptr, "Attempt to dereference null pointer");
            return *ptr;
        }

        /// @brief Member access operator.
        /// @details Provides access to the underlying reference.
        /// @return Underlying reference.
        /// @note Be sure that it is safe to de-reference the pointer.
        ///   The pointer is asserted to be non-null.
        constexpr T *operator->() const noexcept
        {
            ASSERTF(_impl != nullptr, "Attempt to use a disposed shared pointer");
            auto ptr = _impl->getReference();
            ASSERTF(ptr != nullptr, "Attempt to dereference null pointer");
            return ptr;
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept
        {
            return _impl != nullptr && _impl->getReference() != nullptr;
        }

        /// @brief Assignment operator.
        SharedPointer &operator=(SharedPointer other)
        {
            swap(other);
            return *this;
        }

        /// @brief Equality operator.
        constexpr bool operator==(const SharedPointer &other) const noexcept
        {
            if(_impl != nullptr && other._impl != nullptr)
                return _impl->getReference() == other._impl->getReference();
            else
                return _impl == nullptr && other._impl == nullptr;
        }

        /// @brief Inequality operator.
        constexpr bool operator!=(const SharedPointer &other) const noexcept
        {
            return !(this == other);
        }
    };
}

#endif //HYPER_SHAREDPOINTER_H