/// @file ReferenceCounter.h
/// Underlying implementation for tracking references.

#ifndef HYPER_REFERENCE_COUNTER_H
#define HYPER_REFERENCE_COUNTER_H

#include <cstddef>
#include "assert.h"
#include "Counter.h"
#include "DefaultDeleter.h"

namespace hyper {
    /// @brief Internal implementation for tracking references in smart pointers.
    /// @details All smart pointers that refer to the same instance share a single instance of this class.
    ///   This allows the smart pointers to "communicate" when they are no longer being used.
    /// @tparam T Type of instance to reference.
    /// @todo Implement locking to be safe in multi-threaded scenarios.
    template<typename T>
    class ReferenceCounter {
    public:
        /// @brief Default constructor.
        /// @details Creates a new reference counter.
        /// @param ptr Pointer to count references to.
        constexpr explicit ReferenceCounter(T *ptr) noexcept
                : _counter(1), _rawPointer(ptr) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is deleted.
        ReferenceCounter(const ReferenceCounter &other) = delete;

        /// @brief Destructor.
        /// @details Resets the count to zero and releases the memory held by the pointer, if any.
        ~ReferenceCounter() {
            DefaultDeleter<T> deleter;
            deleter(_rawPointer);
        }

        /// @brief Increments the reference count by one.
        void increment() noexcept {
            _counter.increment();
        }

        /// @brief Decrements the reference count by one.
        /// @return True if there are still references to the pointer.
        /// @return False if the last reference was just released and the pointer can be freed.
        bool decrement() noexcept {
            auto count = _counter.decrement();
            ASSERTF(count > 0, "Attempted to decrement reference count below zero");
            return count > 1;
        }

        /// @brief Retrieves the raw pointer.
        /// @return Pointer being counted.
        constexpr T *getPointer() const noexcept {
            return _rawPointer;
        }

        /// @brief Assignment operator.
        /// @details Assignment operator is deleted.
        ReferenceCounter *operator=(const ReferenceCounter &other) = delete;

    private:
        Counter _counter;
        T *_rawPointer;
    };

    /// @brief Internal implementation for tracking references in smart pointers.
    /// @details All smart pointers that refer to the same instance share a single instance of this class.
    ///   This allows the smart pointers to "communicate" when they are no longer being used.
    ///   This is a template specialization for pointers to arrays.
    /// @tparam T Type of instance to reference.
    /// @todo Implement locking to be safe in multi-threaded scenarios.
    template<typename T>
    class ReferenceCounter<T[]> {
    public:
        /// @brief Default constructor.
        /// @details Creates a new reference counter.
        /// @param ptr Pointer to count references to.
        constexpr explicit ReferenceCounter(T *ptr) noexcept
                : _counter(1), _rawPointer(ptr) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is deleted.
        ReferenceCounter(const ReferenceCounter &other) = delete;

        /// @brief Destructor.
        /// @details Resets the count to zero and releases the memory held by the pointer, if any.
        ~ReferenceCounter() {
            DefaultDeleter<T[]> deleter;
            deleter(_rawPointer);
        }

        /// @brief Increments the reference count by one.
        void increment() noexcept {
            _counter.increment();
        }

        /// @brief Decrements the reference count by one.
        /// @return True if there are still references to the pointer.
        /// @return False if the last reference was just released and the pointer can be freed.
        bool decrement() noexcept {
            auto count = _counter.decrement();
            ASSERTF(count > 0, "Attempted to decrement reference count below zero");
            return count > 1;
        }

        /// @brief Retrieves the raw pointer.
        /// @return Pointer being counted.
        constexpr T *getPointer() const noexcept {
            return _rawPointer;
        }

        /// @brief Assignment operator.
        /// @details Assignment operator is deleted.
        ReferenceCounter *operator=(const ReferenceCounter &other) = delete;

    private:
        Counter _counter;
        T *_rawPointer;
    };
}

#endif // HYPER_REFERENCE_COUNTER_H