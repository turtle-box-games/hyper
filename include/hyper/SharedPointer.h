/// @file SharedPointer.h
/// Definition of a smart pointer that can be shared throughout the application
/// and it will automatically be freed when it is no longer referenced.

#ifndef HYPER_SHAREDPOINTER_H
#define HYPER_SHAREDPOINTER_H

#include "assert.h"
#include "DefaultDeleter.h"
#include "ReferenceCounter.h"

namespace hyper
{
    /// @brief Smart pointer that can be shared throughout the application.
    /// @details Smart pointer that tracks its references.
    ///   The pointer will automatically be destroyed (and resources freed)
    ///   when there are no more references to it.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    /// @tparam T Type the pointer references.
    /// @tparam Deleter Type of functor used to destroy instances.
    template<typename T, typename Deleter = DefaultDeleter<T>>
    class SharedPointer
    {
    private:
        ReferenceCounter<T, Deleter> *_impl;

    public:
        /// @brief Default constructor.
        /// @details Creates a new shared pointer with the default constructor of type @tparam T.
        constexpr explicit SharedPointer() noexcept
                : _impl(new ReferenceCounter<T, Deleter>(new T))
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new shared pointer with an existing reference.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit SharedPointer(T *&&ptr) noexcept
                : _impl(new ReferenceCounter<T, Deleter>(ptr))
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
            auto ptr = _impl->getPointer();
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
            auto ptr = _impl->getPointer();
            ASSERTF(ptr != nullptr, "Attempt to dereference null pointer");
            return ptr;
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept
        {
            return _impl->getPointer() != nullptr;
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
            else
                return _impl->getPointer() == other._impl->getPointer();
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

    /// @brief Smart pointer for arrays that can be shared throughout the application.
    /// @details Smart pointer that tracks its references.
    ///   The pointer will automatically be destroyed (and resources freed)
    ///   when there are no more references to it.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    ///   This is a template specialization for pointers to arrays.
    /// @tparam T Type the pointer references.
    /// @tparam Deleter Type of functor used to destroy instances.
    template<typename T, typename Deleter>
    class SharedPointer<T[], Deleter>
    {
    private:
        ReferenceCounter<T, Deleter> *_impl;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped pointer to a new array.
        /// @param size Number of items in the array.
        constexpr explicit SharedPointer(size_t size) noexcept
                : _impl(new ReferenceCounter<T, Deleter>(new T[size]))
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new shared pointer with an existing reference.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit SharedPointer(T *&&ptr) noexcept
                : _impl(new ReferenceCounter<T, Deleter>(ptr))
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
        void swap(SharedPointer &other) noexcept
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
            auto arr = _impl->getPointer();
            ASSERTF(arr != nullptr, "Attempt to dereference null pointer");
            return arr[index];
        }

        /// @brief Subscript operator.
        /// @details Retrieves a specified element in the array.
        /// @param index Base-zero index of the element to access.
        /// @return Element at the specified index.
        constexpr T &operator[](size_t index) const noexcept
        {
            auto arr = _impl->getPointer();
            ASSERTF(arr != nullptr, "Attempt to dereference null pointer");
            return arr[index];
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the pointer can be safely de-referenced (is not null).
        /// @return True if the pointer is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept
        {
            return _impl->getPointer() != nullptr;
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
            else
                return _impl->getPointer() == other._impl->getPointer();
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

    /// @brief Swaps the references of two shared pointers.
    /// @param first First smart pointer to swap.
    /// @param second Second smart pointer to swap.
    template<typename T>
    void swap(SharedPointer<T> &first, SharedPointer<T> &second)
    {
        first.swap(second);
    }
}

#endif //HYPER_SHAREDPOINTER_H