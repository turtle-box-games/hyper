/// @file ScopedPointer.h
/// Definition a smart pointer that limits usage to the scope it is declared in.

#ifndef HYPER_SCOPED_POINTER_H
#define HYPER_SCOPED_POINTER_H

#include "assert.h"
#include "DefaultDeleter.h"
#include "utility.h"

namespace hyper {
    /// @brief Smart pointer that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    ///   The smart pointer cannot be updated to reference a different pointer.
    /// @tparam T Type the pointer references.
    template<typename T>
    class ScopedPointer {
    private:
        T *_rawPointer;

    public:
        /// @brief Default constructor.
        /// @details Creates a new scoped pointer that references a default construction of @c T.
        constexpr explicit ScopedPointer() noexcept
                : _rawPointer(new T) {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new scoped pointer with an existing reference.
        /// @param rawPointer Raw pointer to wrap.
        constexpr explicit ScopedPointer(T *&&rawPointer) noexcept
                : _rawPointer(rawPointer) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled.
        ///   Copy operation would violate single reference.
        ScopedPointer(const ScopedPointer &) = delete;

        /// @brief Move constructor.
        /// @details Move constructor is disabled.
        ///   Move operation would violate scope of pointer.
        ScopedPointer(ScopedPointer &&) = delete;

        /// @brief Destructor.
        /// @details Releases the resources referenced by the pointer.
        ~ScopedPointer() noexcept {
            DefaultDeleter<T> deleter;
            deleter(_rawPointer);
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
    };

    /// @brief Smart pointer for an array that can't be shared outside its scope.
    /// @details Smart pointer with a lifetime limited to its scope.
    ///   This operates on the RAII principle.
    ///   The smart pointer cannot be updated to reference a different pointer.
    ///   This is a template specialization for pointers to arrays.
    /// @tparam T Type the pointer references.
    template<typename T>
    class ScopedPointer<T[]> {
    private:
        T *_rawPointer;

    public:
        /// @brief General constructor.
        /// @details Creates a new scoped pointer with an existing reference.
        /// @param rawPointer Raw pointer to wrap.
        constexpr explicit ScopedPointer(T *&&rawPointer) noexcept
                : _rawPointer(rawPointer) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled.
        ///   Copy operation would violate single reference.
        ScopedPointer(const ScopedPointer &) = delete;

        /// @brief Move constructor.
        /// @details Move constructor is disabled.
        ///   Move operation would violate scope of pointer.
        ScopedPointer(ScopedPointer &&) = delete;

        /// @brief Destructor.
        /// @details Releases the resources referenced by the pointer.
        ~ScopedPointer() noexcept {
            DefaultDeleter<T[]> deleter;
            deleter(_rawPointer);
        }

        /// @brief Subscript operator.
        /// @details Provides access to a specified element in the array.
        /// @param index Index of the element to access, starting at zero.
        /// @return Element at the specified index.
        T &operator[](size_t index) noexcept {
            ASSERTF(_rawPointer != nullptr, "Attempt to dereference null pointer");
            return _rawPointer[index];
        }

        /// @brief Subscript operator.
        /// @details Retrieves a specified element in the array.
        /// @param index Index of the element to access, starting at zero.
        /// @return Element at the specified index.
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
    };
}

#endif // HYPER_SCOPED_POINTER_H
