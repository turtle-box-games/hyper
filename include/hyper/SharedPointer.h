/// @file SharedPointer.h
/// Type of smart pointer that tracks its references and automatically frees itself when it's no longer used.

#ifndef HYPER_SHARED_POINTER_H
#define HYPER_SHARED_POINTER_H

#include "assert.h"
#include "DefaultDeleter.h"
#include "utility.h"
#include "ReferenceCounter.h"

namespace hyper {
    /// @brief Smart pointer that allows multiple references to a single instance.
    /// @details Smart pointer that holds a shared reference.
    ///   References to the pointer are tracked,
    ///   and when there aren't any references remaining, the pointer will be freed.
    /// @tparam T Type the pointer references.
    template<typename T>
    class SharedPointer {
    public:
        /// @brief Default constructor.
        /// @details Creates a new shared pointer that references null.
        constexpr SharedPointer() noexcept
                : _counter(new Counter(1)), _rawPointer(nullptr) {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new shared pointer that wraps an existing raw pointer.
        /// @param rawPointer Raw pointer to wrap.
        constexpr explicit SharedPointer(T *&&rawPointer) noexcept
                : _counter(new Counter(1)), _rawPointer(rawPointer) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Shares a reference to an existing pointer.
        /// @param other Existing pointer to reference.
        SharedPointer(const SharedPointer &other) noexcept
                : _counter(other._counter), _rawPointer(other._rawPointer) {
            _counter->increment();
        }

        /// @brief Destructor.
        /// @details Releases a reference to the underlying pointer.
        ///   If there are no more references, then the pointer and any resources it holds are released.
        ~SharedPointer() {
            expire();
        }

        /// @brief Force expiration of this reference.
        /// @details Has the same effect as letting the shared pointer go out of scope.
        ///   If there are no more references, then the pointer and any resources it holds are released.
        void expire() noexcept {
            if(_counter != nullptr) {
                if(1 == _counter->decrement()) {
                    delete _counter;
                    DefaultDeleter<T> deleter;
                    deleter(_rawPointer);
                }
                _counter = nullptr;
            }
        }

        /// @brief Re-initializes the shared pointer.
        /// @details Changes the raw pointer that the instance wraps.
        ///   The existing pointer, if it has no other references, is freed.
        /// @param rawPointer New pointer to wrap.
        void reset(T *&&rawPointer = nullptr) noexcept {
            expire();
            _counter    = new Counter(1);
            _rawPointer = rawPointer;
        }

        /// @brief Swaps with another instance.
        /// @details Exchanges the underlying pointer between two instances of the same type.
        /// @param other Other pointer to swap with.
        void swap(SharedPointer &other) noexcept {
            auto tempCounter = _counter;
            auto tempPointer = _rawPointer;
            _counter    = other._counter;
            _rawPointer = other._rawPointer;
            other._counter    = tempCounter;
            other._rawPointer = tempPointer;
        }

        /// @brief Indirect access operator.
        /// @details Provides access to the underlying reference.
        /// @return Underlying reference.
        /// @note Be sure that it is safe to de-reference the pointer.
        ///   The pointer is asserted to be non-null.
        constexpr T &operator*() const noexcept {
            ASSERTF(_rawPointer != nullptr, "Attempt to dereference null pointer");
            return *_rawPointer;
        }

        /// @brief Member access operator.
        /// @details Provides access to the underlying reference.
        /// @return Underlying reference.
        /// @note Be sure that it is safe to de-reference the pointer.
        ///   The pointer is asserted to be non-null.
        constexpr T *operator->() const noexcept {
            ASSERTF(_rawPointer != nullptr, "Attempt to dereference null pointer");
            return _rawPointer;
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept {
            return _rawPointer != nullptr;
        }

        /// @brief Copy assignment operator.
        /// @details Replaces the reference held by this pointer to a copy of another one.
        /// @param other Other reference to copy.
        /// @return Updated version of the existing pointer.
        SharedPointer &operator=(SharedPointer const &other) {
            expire();
            _counter    = other._counter;
            _rawPointer = other._rawPointer;
            _counter->increment();
            return *this;
        }

    private:
        Counter *_counter;
        T *_rawPointer;
    };

    /// @brief Smart pointer for arrays that allows multiple references to a single instance.
    /// @details Smart pointer that holds a shared reference.
    ///   References to the pointer are tracked,
    ///   and when there aren't any references remaining, the pointer will be freed.
    /// @tparam T Type the pointer references.
    template<typename T>
    class SharedPointer<T[]> {
    public:
        /// @brief Default constructor.
        /// @details Creates a new shared pointer that references null.
        constexpr SharedPointer() noexcept
                : _counter(new Counter(1)), _rawPointer(nullptr) {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new shared pointer that wraps an existing raw pointer.
        /// @param rawPointer Raw pointer to wrap.
        constexpr explicit SharedPointer(T *&&rawPointer) noexcept
                : _counter(new Counter(1)), _rawPointer(rawPointer) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Shares a reference to an existing pointer.
        /// @param other Existing pointer to reference.
        SharedPointer(const SharedPointer &other) noexcept
                : _counter(other._counter), _rawPointer(other._rawPointer) {
            _counter->increment();
        }

        /// @brief Destructor.
        /// @details Releases a reference to the underlying pointer.
        ///   If there are no more references, then the pointer and any resources it holds are released.
        ~SharedPointer() {
            expire();
        }

        /// @brief Force expiration of this reference.
        /// @details Has the same effect as letting the shared pointer go out of scope.
        ///   If there are no more references, then the pointer and any resources it holds are released.
        void expire() noexcept {
            if(_counter != nullptr) {
                if(1 == _counter->decrement()) {
                    delete _counter;
                    DefaultDeleter<T[]> deleter;
                    deleter(_rawPointer);
                }
                _counter = nullptr;
            }
        }

        /// @brief Re-initializes the shared pointer.
        /// @details Changes the raw pointer that the instance wraps.
        ///   The existing pointer, if it has no other references, is freed.
        /// @param rawPointer New pointer to wrap.
        void reset(T *&&rawPointer = nullptr) noexcept {
            expire();
            _counter    = new Counter(1);
            _rawPointer = rawPointer;
        }

        /// @brief Swaps with another instance.
        /// @details Exchanges the underlying pointer between two instances of the same type.
        /// @param other Other pointer to swap with.
        void swap(SharedPointer &other) noexcept {
            auto tempCounter = _counter;
            auto tempPointer = _rawPointer;
            _counter    = other._counter;
            _rawPointer = other._rawPointer;
            other._counter    = tempCounter;
            other._rawPointer = tempPointer;
        }

        T &operator[](size_t index) noexcept {
            ASSERTF(_rawPointer != nullptr, "Attempt to dereference null pointer");
            return _rawPointer[index];
        }

        constexpr const T &operator[](size_t index) const noexcept {
            ASSERTF(_rawPointer != nullptr, "Attempt to dereference null pointer");
            return _rawPointer[index];
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept {
            return _rawPointer != nullptr;
        }

        /// @brief Copy assignment operator.
        /// @details Replaces the reference held by this pointer to a copy of another one.
        /// @param other Other reference to copy.
        /// @return Updated version of the existing pointer.
        SharedPointer &operator=(SharedPointer const &other) {
            expire();
            _counter    = other._counter;
            _rawPointer = other._rawPointer;
            _counter->increment();
            return *this;
        }

    private:
        Counter *_counter;
        T *_rawPointer;
    };

    /// @brief Specialized implementation of swap for shared pointers.
    /// @details Swaps the underlying references held by two pointers.
    /// @param first First pointer to swap.
    /// @param second Second pointer to swap.
    /// @tparam T Type the smart pointers reference.
    template<typename T, typename Subtype>
    void swap(SharedPointer<T> first, SharedPointer<Subtype> second) noexcept {
        first.swap(second);
    };

    /// @brief Utility method for creating shared pointers.
    /// @details Infers pointer types and creates a shared pointer for them.
    /// @param ptr Raw pointer to wrap.
    /// @return Newly constructed shared pointer.
    template<typename T>
    inline SharedPointer<T> createShared(T *&&ptr) {
        return SharedPointer<T>(move(ptr));
    }
}

#endif // HYPER_SHARED_POINTER_H