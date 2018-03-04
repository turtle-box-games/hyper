/// @file Pair.h
/// Simple container for holding two values.

#ifndef HYPER_PAIR_H
#define HYPER_PAIR_H

namespace hyper
{
    /// @brief Simple container for holding two values.
    /// @tparam T1 Type of the first value.
    /// @tparam T2 Type of the second value.
    template<typename T1, typename T2>
    struct Pair
    {
        /// @brief First value stored in the pair.
        T1 first;

        /// @brief Second value stored in the pair.
        T2 second;

        /// @brief Default constructor.
        /// @details Creates a pair and assigns the first and second values to the defaults.
        constexpr Pair()
                : first(T1()), second(T2())
        {
            // ...
        }

        /// @brief General constructor.
        /// @details Creates a pair and populates the values with the values specified.
        /// @param a First value.
        /// @param b Second value.
        constexpr Pair(T1 a, T2 b) noexcept
                : first(a), second(b)
        {
            // ...
        }
    };
}

#endif //HYPER_PAIR_H