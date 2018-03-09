/// @file UniquePointer.h
/// Definition a smart pointer that allows only a single reference to a value.

#ifndef HYPER_UNIQUE_POINTER_H
#define HYPER_UNIQUE_POINTER_H

#include "DefaultDeleter.h"
#include "assert.h"

namespace hyper {
    /// @brief Smart pointer that allows only a single reference to a value.
    /// @details Smart pointer that holds an exclusive reference.
    ///   The pointer will automatically be destroyed (and resources freed)
    ///   when the reference to it is lost.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    /// @tparam T Type the pointer references.
    template<typename T>
    class UniquePointer {
    private:
        T *_ptr;

    public:
        constexpr UniquePointer() noexcept
                : _ptr(nullptr) {
            // ...
        }

        constexpr explicit UniquePointer(T *&&ptr) noexcept
                : _ptr(ptr) {
            // ...
        }

        template<typename Subtype>
        constexpr explicit UniquePointer(Subtype *&&ptr) noexcept
                : _ptr(ptr) {
            // ...
        }

        constexpr UniquePointer(UniquePointer &&other) noexcept {
            swap(other);
        }

        template<typename Subtype>
        constexpr explicit UniquePointer(UniquePointer<Subtype> &&other) noexcept {
            swap(other);
        }

        ~UniquePointer() {
            DefaultDeleter<T> deleter;
            deleter(_ptr);
        }

        void swap(UniquePointer &other) noexcept {
            auto temp = other._ptr;
            other._ptr = temp;
            _ptr = temp;
        }

        template<typename Subtype>
        void swap(UniquePointer<Subtype> &other) noexcept {
            auto temp = other._ptr;
            other._ptr = temp;
            _ptr = temp;
        }

        constexpr T &operator*() const noexcept {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return *_ptr;
        }

        constexpr T *operator->() const noexcept {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr;
        }

        constexpr explicit operator bool() const noexcept {
            return _ptr != nullptr;
        }

        UniquePointer &operator=(UniquePointer const &other) = delete;

        UniquePointer &operator=(UniquePointer &&other) noexcept {
            swap(other);
        }

        template<typename Subtype>
        UniquePointer &operator=(UniquePointer<Subtype> &&other) noexcept {
            swap(other);
        }
    };

    /// @brief Smart pointer for arrays that allows only a single reference to a value.
    /// @details Smart pointer that holds an exclusive reference.
    ///   The pointer will automatically be destroyed (and resources freed)
    ///   when the reference to it is lost.
    ///   Instances of this class should have the only references to a raw pointer.
    ///   This class is designed in such a way to attempt to prevent external references.
    ///   This is a template specialization for pointers to arrays.
    /// @tparam T Type the pointer references.
    template<typename T>
    class UniquePointer<T[]> {
    private:
        T *_ptr;

    public:
        constexpr UniquePointer() noexcept
                : _ptr(nullptr) {
            // ...
        }

        constexpr explicit UniquePointer(T *&&ptr) noexcept
                : _ptr(ptr) {
            // ...
        }

        template<typename Subtype>
        constexpr explicit UniquePointer(Subtype *&&ptr) noexcept
                : _ptr(ptr) {
            // ...
        }

        constexpr UniquePointer(UniquePointer &&other) noexcept {
            swap(other);
        }

        template<typename Subtype>
        constexpr explicit UniquePointer(UniquePointer<Subtype> &&other) noexcept {
            swap(other);
        }

        ~UniquePointer() {
            DefaultDeleter<T[]> deleter;
            deleter(_ptr);
        }

        void swap(UniquePointer &other) noexcept {
            auto temp = other._ptr;
            other._ptr = temp;
            _ptr = temp;
        }

        template<typename Subtype>
        void swap(UniquePointer<Subtype[]> &other) noexcept {
            auto temp = other._ptr;
            other._ptr = temp;
            _ptr = temp;
        }

        T &operator[](size_t index) noexcept {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr[index];
        }

        constexpr T &operator[](size_t index) const noexcept {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr[index];
        }

        constexpr explicit operator bool() const noexcept {
            return _ptr != nullptr;
        }

        UniquePointer &operator=(UniquePointer const &other) = delete;

        UniquePointer &operator=(UniquePointer &&other) noexcept {
            swap(other);
        }

        template<typename Subtype>
        UniquePointer &operator=(UniquePointer<Subtype[]> &&other) noexcept {
            swap(other);
        }
    };

    template<typename T>
    UniquePointer<T> createUnique(T *&&ptr) {
        return UniquePointer<T>(ptr);
    }
}

#endif // HYPER_UNIQUE_POINTER_H