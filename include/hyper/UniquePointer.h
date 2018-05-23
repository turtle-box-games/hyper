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
    public:
        /// @brief Default constructor.
        /// @details Creates a new unique pointer that references null.
        constexpr UniquePointer() noexcept
                : _rawPointer(nullptr) {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new unique pointer that wraps an existing raw pointer.
        /// @param rawPointer Raw pointer to wrap.
        constexpr explicit UniquePointer(T *&&rawPointer) noexcept
                : _rawPointer(rawPointer) {
            // ...
        }

        /// @brief Move constructor.
        /// @details Creates a new unique pointer from another temporary unique pointer.
        /// @param other Temporary pointer to take ownership of.
        /// @tparam Subtype Any compatible pointer type.
        template<typename Subtype>
        constexpr explicit UniquePointer(UniquePointer<Subtype> &&other) noexcept
                : _rawPointer(other.release()) {
            // ...
        }

        /// @brief Move constructor.
        /// @details Creates a new unique pointer from another temporary unique pointer.
        /// @param other Temporary pointer to take ownership of.
        constexpr UniquePointer(UniquePointer &&other) noexcept
                : _rawPointer(other.release()) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled to maintain exclusive ownership of the raw pointer.
        UniquePointer(const UniquePointer &) = delete;

        /// @brief Destructor.
        /// @details Releases the pointer and any resources it references.
        ~UniquePointer() {
            expire();
        }

        /// @brief Force expiration of pointer.
        /// @details Has the same effect as letting the unique pointer go out of scope.
        ///   The pointer and any resources it references are released.
        void expire() noexcept {
            DefaultDeleter<T> deleter;
            deleter(_rawPointer);
        }

        /// @brief Re-initializes the unique pointer.
        /// @details Changes the raw pointer that the instance wraps.
        ///   The existing pointer, if not null, is freed.
        /// @param rawPointer New pointer to wrap.
        void reset(T *&&rawPointer = nullptr) noexcept {
            expire();
            _rawPointer = rawPointer;
        }

        /// @brief Swaps with another instance.
        /// @details Exchanges the underlying pointer between two instances of the same type.
        /// @param other Other pointer to swap with.
        void swap(UniquePointer &other) noexcept {
            auto temp = other._rawPointer;
            other._rawPointer = _rawPointer;
            _rawPointer = temp;
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
        /// @details This operator is disabled as it violates exclusive ownership of the underlying pointer.
        UniquePointer &operator=(UniquePointer const &other) = delete;

        /// @brief Move assignment operator.
        /// @details Replaces the smart pointer with an instance of another pointer.
        /// @param other Pointer to replace the existing instance with.
        /// @tparam Subtype Any compatible or sub-type of the existing pointer.
        /// @return Updated version of the existing pointer.
        template<typename Subtype>
        UniquePointer &operator=(UniquePointer<Subtype> &&other) noexcept {
            reset(other.release());
            return *this;
        }

        /// @brief Move assignment operator.
        /// @details Replaces the smart pointer with an instance of another pointer.
        /// @param other Pointer to replace the existing instance with.
        /// @return Updated version of the existing pointer.
        UniquePointer &operator=(UniquePointer &&other) noexcept {
            reset(other.release());
            return *this;
        }

        /// @brief Releases the pointer being held and returns it so another instance may own it.
        /// @return Pointer held by the instance.
        /// @private For use by this class only.
        ///   This method exposes the underlying pointer, which makes it not unique.
        ///   However, it is required to share a pointer across template types.
        constexpr T *release() noexcept {
            auto ptr = _rawPointer;
            _rawPointer = nullptr;
            return ptr;
        }

    private:
        T *_rawPointer;
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
    public:
        /// @brief Default constructor.
        /// @details Creates a new unique pointer that references null.
        constexpr UniquePointer() noexcept
                : _rawPointer(nullptr) {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a new unique pointer that wraps an existing raw pointer.
        /// @param ptr Raw pointer to wrap.
        constexpr explicit UniquePointer(T *&&ptr) noexcept
                : _rawPointer(ptr) {
            // ...
        }

        /// @brief Move constructor.
        /// @details Creates a new unique pointer from another temporary unique pointer.
        /// @param other Temporary pointer to take ownership of.
        /// @tparam Subtype Any compatible pointer type.
        template<typename Subtype>
        constexpr explicit UniquePointer(UniquePointer<Subtype[]> &&other) noexcept
                : _rawPointer(other.release()) {
            // ...
        }

        /// @brief Move constructor.
        /// @details Creates a new unique pointer from another temporary unique pointer.
        /// @param other Temporary pointer to take ownership of.
        constexpr UniquePointer(UniquePointer &&other) noexcept
                : _rawPointer(other.release()) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copy constructor is disabled to maintain exclusive ownership of the raw pointer.
        UniquePointer(const UniquePointer &) = delete;

        /// @brief Destructor.
        /// @details Releases the pointer and any resources it references.
        ~UniquePointer() {
            expire();
        }

        /// @brief Force expiration of pointer.
        /// @details Has the same effect as letting the unique pointer go out of scope.
        ///   The pointer and any resources it references are released.
        void expire() noexcept {
            DefaultDeleter<T[]> deleter;
            deleter(_rawPointer);
        }

        /// @brief Re-initializes the unique pointer.
        /// @details Changes the raw pointer that the instance wraps.
        ///   The existing pointer, if not null, is freed.
        /// @param rawPointer New pointer to wrap.
        void reset(T *&&rawPointer = nullptr) noexcept {
            expire();
            _rawPointer = rawPointer;
        }

        /// @brief Swaps with another instance.
        /// @details Exchanges the underlying pointer between two instances of the same type.
        /// @param other Other pointer to swap with.
        void swap(UniquePointer &other) noexcept {
            auto temp = other._rawPointer;
            other._rawPointer = _rawPointer;
            _rawPointer = temp;
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

        /// @brief Copy assignment operator.
        /// @details This operator is disabled as it violates exclusive ownership of the underlying pointer.
        UniquePointer &operator=(UniquePointer const &other) = delete;

        /// @brief Move assignment operator.
        /// @details Replaces the smart pointer with an instance of another pointer.
        /// @param other Pointer to replace the existing instance with.
        /// @tparam Subtype Any compatible or sub-type of the existing pointer.
        /// @return Updated version of the existing pointer.
        template<typename Subtype>
        UniquePointer &operator=(UniquePointer<Subtype[]> &&other) noexcept {
            reset(other.release());
            return *this;
        }

        /// @brief Move assignment operator.
        /// @details Replaces the smart pointer with an instance of another pointer.
        /// @param other Pointer to replace the existing instance with.
        /// @return Updated version of the existing pointer.
        UniquePointer &operator=(UniquePointer &&other) noexcept {
            reset(other.release());
            return *this;
        }

        /// @brief Releases the pointer being held and returns it so another instance may own it.
        /// @return Pointer held by the instance.
        /// @private For use by this class only.
        ///   This method exposes the underlying pointer, which makes it not unique.
        ///   However, it is required to share a pointer across template types.
        constexpr T *release() noexcept {
            auto ptr = _rawPointer;
            _rawPointer = nullptr;
            return ptr;
        }

    private:
        T *_rawPointer;
    };

    /// @brief Specialized implementation of swap for unique pointers.
    /// @details Swaps the underlying references held by two pointers.
    /// @param first First pointer to swap.
    /// @param second Second pointer to swap.
    /// @tparam T Type the smart pointers reference.
    template<typename T>
    void swap(UniquePointer<T> &first, UniquePointer<T> &second) noexcept {
        first.swap(second);
    };

    template<typename T>
    constexpr UniquePointer<T> createUnique(T *&&ptr) noexcept {
        return UniquePointer<T>(forward<T *>(ptr));
    }
}

#endif // HYPER_UNIQUE_POINTER_H