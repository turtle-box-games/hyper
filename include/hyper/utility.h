/// @file utility.h
/// C++ language utilities.

#ifndef HYPER_UTILITY_H
#define HYPER_UTILITY_H

namespace hyper
{
    /// @brief Strips reference modifiers from a type.
    /// @tparam T Type to strip references from.
    template<typename T>
    struct removeReference
    {
        /// @brief Non-reference type.
        /// @details This type has all references removed from @p T.
        typedef T type;
    };

    /// @brief Strips reference modifiers from a type.
    /// @details This specialization changes an lvalue reference type to just a type.
    /// @tparam T Type to strip references from.
    template<typename T>
    struct removeReference<T&>
    {
        /// @brief Non-reference type.
        /// @details This type has all references removed from @p T.
        typedef T type;
    };

    /// @brief Strips reference modifiers from a type.
    /// @details This specialization changes an rvalue reference type to just a type.
    /// @tparam T Type to strip references from.
    template<typename T>
    struct removeReference<T&&>
    {
        /// @brief Non-reference type.
        /// @details This type has all references removed from @p T.
        typedef T type;
    };

    /// @brief Forwards an expression reference as-is to another location.
    /// @details Forwards an rvalue reference as an rvalue
    ///   and an lvalue reference as an lvalue reference.
    ///   This can be used to remove unnecessary moving and copying operations.
    /// @param arg Expression to forward.
    /// @return Same expression passed in by @p arg, keeping lvalue and rvalue status.
    template<typename T>
    constexpr T forward(typename removeReference<T>::type &arg) noexcept
    {
        return static_cast<T&&>(arg);
    }

    /// @brief Forces an reference to an instance to become an rvalue.
    /// @details Passes an instance on as an rvalue to another location.
    ///   This forces move-type functions and constructors to be called instead of copy-constructors.
    /// @param arg Instance to move.
    /// @return Instance as an rvalue.
    template<typename T>
    constexpr typename removeReference<T>::type &&move(T &&arg) noexcept
    {
        return static_cast<removeReference<T>::type &&>(arg);
    }

    /// @brief Swaps the value of two variables.
    /// @details Swaps the contents of @p first and @p second.
    /// @param first First value to swap.
    /// @param second Second value to swap.
    /// @tparam T Type of values to swap.
    /// @note Types that have a more efficient swapping method should specialize this method.
    template<typename T>
    void swap(T &first, T &second)
    {
        T temp(move(first));
        first  = move(second);
        second = move(temp);
    }
}

#endif //HYPER_UTILITY_H