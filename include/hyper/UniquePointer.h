/// @file UniquePointer.h
/// Definition a smart pointer that allows only a single reference to a value.

#ifndef HYPER_UNIQUE_POINTER_H
#define HYPER_UNIQUE_POINTER_H

#include "assert.h"
#include "DefaultDeleter.h"
#include "utility.h"

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
        constexpr explicit UniquePointer(UniquePointer<Subtype> &&other) noexcept
                : _ptr(other.release()) {
            // ...
        }

        UniquePointer(const UniquePointer &) = delete;

        ~UniquePointer() {
            expire();
        }

        void expire() noexcept {
            DefaultDeleter<T> deleter;
            deleter(_ptr);
        }

        void swap(UniquePointer &other) noexcept {
            auto temp = other._ptr;
            other._ptr = _ptr;
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

        template<typename Subtype>
        UniquePointer &operator=(UniquePointer<Subtype> &&other) noexcept {
            expire();
            _ptr = other.release();
            return *this;
        }

        /// @private For use by this class only.
        ///   This method exposes the underlying pointer, which makes it not unique.
        ///   However it is required to share a pointer across template types.
        constexpr T *release() noexcept {
            auto ptr = _ptr;
            _ptr = nullptr;
            return ptr;
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
        constexpr explicit UniquePointer(UniquePointer<Subtype[]> &&other) noexcept
                : _ptr(other.release()) {
            // ...
        }

        UniquePointer(const UniquePointer &) = delete;

        ~UniquePointer() {
            expire();
        }

        void expire() noexcept {
            DefaultDeleter<T[]> deleter;
            deleter(_ptr);
        }

        void swap(UniquePointer &other) noexcept {
            auto temp = other._ptr;
            other._ptr = _ptr;
            _ptr = temp;
        }

        T &operator[](size_t index) noexcept {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr[index];
        }

        constexpr const T &operator[](size_t index) const noexcept {
            ASSERTF(_ptr != nullptr, "Attempt to dereference null pointer");
            return _ptr[index];
        }

        constexpr explicit operator bool() const noexcept {
            return _ptr != nullptr;
        }

        UniquePointer &operator=(UniquePointer const &other) = delete;

        template<typename Subtype>
        UniquePointer &operator=(UniquePointer<Subtype[]> &&other) noexcept {
            expire();
            _ptr = other.release();
            return *this;
        }

        /// @private For use by this class only.
        ///   This method exposes the underlying pointer, which makes it not unique.
        ///   However it is required to share a pointer across template types.
        constexpr T *release() noexcept {
            auto ptr = _ptr;
            _ptr = nullptr;
            return ptr;
        }
    };

    template<typename T, typename Subtype>
    void swap(UniquePointer<T> first, UniquePointer<Subtype> second) noexcept {
        first.swap(second);
    };

    template<typename T>
    UniquePointer<T> createUnique(T *&&ptr) {
        return UniquePointer<T>(move(ptr));
    }
}

#endif // HYPER_UNIQUE_POINTER_H