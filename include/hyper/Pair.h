/// @file Pair.h
/// Simple container for holding two values.

#ifndef HYPER_PAIR_H
#define HYPER_PAIR_H

#include "utility.h"

namespace hyper {
    /// @brief Simple container for holding two values.
    /// @tparam T1 Type of the first value.
    /// @tparam T2 Type of the second value.
    template<typename T1, typename T2>
    struct Pair {
        /// @brief First value stored in the pair.
        T1 first;

        /// @brief Second value stored in the pair.
        T2 second;

        /// @brief Default constructor.
        /// @details Creates a pair and assigns the first and second values to the defaults.
        constexpr Pair()
                : first(), second() {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a pair and populates the values with the values specified.
        /// @param a First value.
        /// @param b Second value.
        constexpr Pair(const T1 &a, const T2 &b) noexcept
                : first(a), second(b) {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a pair and populates the values with the values specified.
        /// @param a First value.
        /// @param b Second value.
        constexpr Pair(T1 &&a, T2 &&b) noexcept
                : first(forward<T1>(a)), second(forward<T2>(b)) {
            // ...
        }

        /// @brief Copy constructor.
        /// @details Copies the values from an existing pair into a new pair.
        /// @param other Other pair to copy values from.
        constexpr Pair(Pair const &other) noexcept
                : first(other.first), second(other.second) {
            // ...
        }

        /// @brief Move constructor.
        /// @details Moves the values from a temporary pair into a new pair.
        /// @param other Other pair to move values from.
        constexpr Pair(Pair &&other) noexcept
                : first(move(other.first)), second(move(other.second)) {
            // ...
        }

        /// @brief Swaps values with another pair of the same type.
        /// @param other Other pair to swap values with.
        void swap(Pair &other) noexcept {
            using ::hyper::swap;
            swap(first, other.first);
            swap(second, other.second);
        }

        /// @brief Equality operator.
        /// @details Compares against another pair of the same type.
        /// @return True if the first and second values of both pairs are equal, false otherwise.
        constexpr inline bool operator==(Pair const &other) const noexcept {
            return first == other.first && second == other.second;
        }

        /// @brief Inequality operator.
        /// @details Compares against another pair of the same type.
        /// @return True if the first or second values of both pairs are different, true otherwise.
        constexpr inline bool operator!=(Pair const &other) const noexcept {
            return !(this == other);
        }

        /// @brief Less-than comparison operator.
        /// @details Compares against another pair of the same type to order them.
        /// @return True if the first value is less than the first value in the other pair,
        ///   or the first values are equal and the second value is less than the other pair's.
        constexpr inline bool operator<(Pair const &other) const noexcept {
            return first < other.first || (!(other.first < first) && second < other.second);
        }

        /// @brief Greater-than comparison operator.
        /// @details Compares against another pair of the same type to order them.
        /// @return True if the this pair is greater than the other pair.
        constexpr inline bool operator>(Pair const &other) const noexcept {
            return other < *this;
        }

        /// @brief Less-than or equal to comparison operator.
        /// @details Compares against another pair of the same type to order them.
        /// @return True if this pair is less-than or equal to the other pair.
        constexpr inline bool operator<=(Pair const &other) const noexcept {
            return !(other < *this);
        }

        /// @brief Greater-than or equal to comparison operator.
        /// @details Compares against another pair of the same type to order them.
        /// @return True if this pair is greater-than or equal to the other pair.
        constexpr inline bool operator>=(Pair const &other) const noexcept {
            return !(*this < other);
        }

        /// @brief Copy assignment operator.
        /// @details Copies values from another pair into this instance.
        /// @param other Other pair to copy values from.
        /// @return Reference to updated this instance.
        constexpr inline Pair &operator=(Pair const &other) noexcept {
            first  = other.first;
            second = other.second;
            return *this;
        }

        /// @brief Move assignment operator.
        /// @details Moves values from another pair into this instance.
        /// @param other Other pair to move values from.
        /// @return Reference to updated this instance.
        constexpr inline Pair &operator=(Pair &&other) noexcept {
            swap(other);
            return *this;
        }
    };

    /// @brief Creates a new pair.
    /// @details Infers template parameters to create a new pair.
    /// @tparam T1 Type of the first value.
    /// @tparam T2 Type of the second value.
    /// @param first First value.
    /// @param second Second value.
    /// @return Pair created from @c first and @c second.
    template<typename T1, typename T2>
    inline constexpr Pair<typename RemoveReference<T1>::type, typename RemoveReference<T2>::type> createPair(T1 &&first, T2 &&second) noexcept {
        return Pair<typename RemoveReference<T1>::type, typename RemoveReference<T2>::type>(forward<T1>(first), forward<T2>(second));
    }

    /// @brief Swaps the values of two pairs.
    /// @param first First pair to swap.
    /// @param second Second pair to swap.
    /// @tparam T1 Type of the first value in both pairs.
    /// @tparam T2 Type of the second value in both pairs.
    template<typename T1, typename T2>
    inline void swap(Pair<T1, T2> &first, Pair<T1, T2> &second) noexcept {
        first.swap(second);
    };
}

#endif // HYPER_PAIR_H