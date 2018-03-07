/// @file ScopedPointer.h
/// Definition of a smart pointer that frees itself once the scope it was declared in is left.

#ifndef HYPER_SCOPEDPOINTER_H
#define HYPER_SCOPEDPOINTER_H

#include "assert.h"
#include "DefaultDeleter.h"

namespace hyper
{
    /// @brief Smart pointer that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    /// @tparam T Type the pointer references.
    /// @tparam Deleter Type of functor used to destroy instances.
    template<typename T, typename Deleter = DefaultDeleter<T>>
    class ScopedPointer
    {
    private:
        T *_ptr;
        Deleter _deleter;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped pointer that references null.
        ///   This constructor is intended for assigning a usable pointer later.
        constexpr explicit ScopedPointer() noexcept
                : _ptr(nullptr)
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

        /// @brief Specific constructor.
        /// @details Creates a new scoped pointer with an existing reference and deleter.
        /// @param ptr Raw pointer to wrap.
        /// @param deleter Functor used to delete @p ptr.
        constexpr explicit ScopedPointer(T *&&ptr, Deleter deleter) noexcept
                : _ptr(ptr), _deleter(deleter)
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
            _deleter(_ptr);
        }

        /// @brief Retrieves the deleter used to free memory referenced by the pointer.
        /// @return Deleter instance.
        constexpr Deleter getDeleter() const noexcept
        {
            return _deleter;
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

    /// @brief Smart pointer for arrays that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    ///   This is a template specialization for pointers to arrays.
    /// @tparam T Type the pointer references.
    /// @tparam Deleter Type of functor used to destroy instances.
    template<typename T, typename Deleter>
    class ScopedPointer<T[], Deleter>
    {
    private:
        T *_ptr;
        Deleter _deleter;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped pointer that references null.
        ///   This constructor is intended for assigning a usable pointer later.
        constexpr explicit ScopedPointer() noexcept
                : _ptr(nullptr)
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

        /// @brief Specific constructor.
        /// @details Creates a new scoped pointer with an existing reference and deleter.
        /// @param ptr Raw pointer to wrap.
        /// @param deleter Functor used to delete @p ptr.
        constexpr explicit ScopedPointer(T *&&ptr, Deleter deleter) noexcept
                : _ptr(ptr), _deleter(deleter)
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
            _deleter(_ptr);
        }

        /// @brief Retrieves the deleter used to free memory referenced by the pointer.
        /// @return Deleter instance.
        constexpr Deleter getDeleter() const noexcept
        {
            return _deleter;
        }

        /// @brief Swaps the contents of two scoped pointers.
        /// @param other Scoped pointer to swap with.
        void swap(ScopedPointer &other) noexcept
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

    /// @brief Swaps the references of two scoped pointers.
    /// @param first First smart pointer to swap.
    /// @param second Second smart pointer to swap.
    template<typename T>
    void swap(ScopedPointer<T> &first, ScopedPointer<T> &second)
    {
        first.swap(second);
    }
}

#endif //HYPER_SCOPEDPOINTER_H
