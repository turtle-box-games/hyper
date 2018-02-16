/// @file SharedPointer.h
/// Definition of a smart pointer that can be shared throughout the application
/// and it will automatically be freed when it is no longer referenced.

#ifndef HYPER_SHAREDPOINTER_H
#define HYPER_SHAREDPOINTER_H

#include "pointer_utility.h"
#include "assert.h"

namespace hyper
{
    /// @brief Smart pointer that can be shared throughout the application.
    /// @details Smart pointer that tracks its references.
    ///   The pointer will automatically be destroyed (and resources freed)
    ///   when there are no more references to it.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
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
            /// @brief Default constructor.
            /// @details Creates a new reference counter.
            /// @param ptr Pointer to count references to.
            constexpr ReferenceCounter(T *ptr) noexcept
                : _count(1), _ptr(ptr)
            {
                // ...
            }

            /// @brief Destructor.
            /// @details Resets the count to zero and releases the memory held by the pointer, if any.
            ~ReferenceCounter()
            {
                _count = 0;
                checkedDelete(_ptr);
            }

            /// @brief Increments the reference count by one.
            void increment() noexcept
            {
                _count++;
            }

            /// @brief Decrements the reference count by one.
            /// @return True if there are still references to the pointer.
            /// @return False if the last reference was just released and the pointer can be freed.
            bool decrement() noexcept
            {
                ASSERTF(_count > 0, "Attempted to decrement reference count below zero");
                return 0 < --_count;
            }

            /// @brief Retrieves the raw pointer.
            /// @return Pointer being counted.
            constexpr T *getReference() const noexcept
            {
                return _ptr;
            }
        };

        ReferenceCounter *_impl;

    public:
        /// @brief Default constructor.
        /// @details Creates a new shared pointer with the default constructor of type @tparam T.
        constexpr explicit SharedPointer() noexcept
                : _impl(new ReferenceCounter(new T))
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new shared pointer with an existing reference.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit SharedPointer(T *&&ptr) noexcept
                : _impl(new ReferenceCounter(ptr))
        {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Creates a new shared pointer that references an existing one.
        /// @param other Existing shared pointer.
        SharedPointer(const SharedPointer &other) noexcept
            : _impl(other._impl)
        {
            _impl->increment();
        }

        /// @brief Move constructor.
        /// @details Creates a new shared pointer from a temporary one.
        /// @param other Temporary shared pointer.
        SharedPointer(SharedPointer &&other) noexcept
            : _impl(other._impl)
        {
            other._impl = nullptr;
        }

        /// @brief Destructor.
        /// @details Releases the resources referenced by the shared pointer.
        ///   The underlying pointer will not be released unless all other references have been released.
        ~SharedPointer() noexcept
        {
            expire();
        }

        /// @brief Removes this pointer's reference to the raw pointer.
        void expire() noexcept
        {
            if(_impl != nullptr)
            {
                // Release reference counter if this instance is the last one using it.
                if(!_impl->decrement())
                    delete _impl;
                _impl = nullptr;
            }
        }

        /// @brief Forces the pointer to be destroyed, all references invalidated, and resources released.
        void release() noexcept
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
        /// @details Overwrites the current pointer with a copy of another.
        /// @param other Other pointer to overwrite the existing one with.
        /// @return The current pointer.
        SharedPointer &operator=(SharedPointer other)
        {
            swap(other);
            return *this;
        }

        /// @brief Equality operator.
        /// @details Checks if two shared pointers reference the same raw pointer.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference the same pointer.
        /// @return False if the instances reference different pointers.
        /// @return True if both instances reference null.
        /// @return False if only one instance references null.
        constexpr bool operator==(const SharedPointer &other) const noexcept
        {
            if(_impl == other._impl)
                return true;
            else if(_impl != nullptr && other._impl != nullptr)
            {
                if(_impl->getReference() == other._impl->getReference())
                    return true;
            }
            else
                return false;
        }

        /// @brief Inequality operator.
        /// @details Checks if two shared pointers don't reference the same raw pointer.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference different pointers.
        /// @return False if the instances reference the same pointer.
        /// @return True if only one instance references null.
        /// @return False if both instances reference null.
        constexpr bool operator!=(const SharedPointer &other) const noexcept
        {
            return !(this == other);
        }
    };
}

#endif //HYPER_SHAREDPOINTER_H