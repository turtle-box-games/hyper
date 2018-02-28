/// @file ReferenceCounter.h
/// Underlying implementation for tracking references.

#ifndef HYPER_REFERENCECOUNTER_H
#define HYPER_REFERENCECOUNTER_H

#include <cstddef>
#include "assert.h"

namespace hyper
{
    /// @brief Internal implementation for tracking references in smart pointers.
    /// @details All smart pointers that refer to the same instance share a single instance of this class.
    ///   This allows the smart pointers to "communicate" when they are no longer being used.
    /// @tparam T Type of instance to reference.
    /// @tparam Deleter Type that acts as a functor for destroying the reference.
    /// @todo Implement locking to be safe in multi-threaded scenarios.
    template<typename T, typename Deleter>
    class ReferenceCounter
    {
    private:
        size_t _count;
        T *_ptr;
        Deleter _deleter;

    public:
        /// @brief Default constructor.
        /// @details Creates a new reference counter.
        /// @param ptr Pointer to count references to.
        constexpr explicit ReferenceCounter(T *ptr) noexcept
                : _count(1), _ptr(ptr)
        {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is deleted.
        ReferenceCounter(const ReferenceCounter &other) = delete;

        /// @brief Destructor.
        /// @details Resets the count to zero and releases the memory held by the pointer, if any.
        ~ReferenceCounter()
        {
            _count = 0;
            _deleter(_ptr);
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
        constexpr T *getPointer() const noexcept
        {
            return _ptr;
        }

        /// @brief Assignment operator.
        /// @details Assignment operator is deleted.
        ReferenceCounter *operator=(const ReferenceCounter &other) = delete;
    };
}

#endif //HYPER_REFERENCECOUNTER_H