/// @file Function.h
/// Container for referencing a callable function.

#ifndef HYPER_FUNCTION_H
#define HYPER_FUNCTION_H

namespace hyper {
    template<typename Signature>
    class Function {
    private:
        Signature *_func;

    public:
        constexpr Function() noexcept
                : _func(nullptr) {
            // ...
        }

        constexpr Function(Signature &func) noexcept
                : _func(func) {
            // ...
        }

        constexpr Function(const Function &other) noexcept
                : _func(other._func) {
            // ...
        }

        constexpr Function(Function &&other) noexcept
                : _func(other._func) {
            // ...
        }

        ~Function() noexcept {
            _func = nullptr;
        }

        void swap(Function &other) noexcept {
            // TODO
        }

        /// @brief Explicit bool cast.
        /// @details Checks if the function can be safely called (is not null).
        /// @return True if the function is not null, or false if it is null.
        constexpr explicit operator bool() const noexcept {
            return _func != nullptr;
        }

        /// @brief Assignment operator.
        /// @details Overwrites the current function reference with a copy of another.
        /// @param other Other function to overwrite the existing one with.
        /// @return The current function.
        SharedPointer &operator=(Function other) {
            swap(other);
            return *this;
        }

        /// @brief Equality operator.
        /// @details Checks if two function references are the same.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference the same function.
        /// @return False if the instances reference different function.
        /// @return True if both instances reference null.
        /// @return False if only one instance references null.
        constexpr bool operator==(const Function &other) const noexcept {
            return _func == other._func;
        }

        /// @brief Inequality operator.
        /// @details Checks if two function references are different.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference different functions.
        /// @return False if the instances reference the same function.
        /// @return True if only one instance references null.
        /// @return False if both instances reference null.
        constexpr bool operator!=(const Function &other) const noexcept {
            return _func != other._func;
        }
    };
}

#endif // HYPER_FUNCTION_H