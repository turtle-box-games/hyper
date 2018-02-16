/// @file utility.h
/// C++ language utilities.

#ifndef HYPER_UTILITY_H
#define HYPER_UTILITY_H

namespace hyper
{
    /// @brief Swaps the value of two variables.
    /// @details Swaps the contents of @p first and @p second.
    /// @param first First value to swap.
    /// @param second Second value to swap.
    /// @tparam T Type of values to swap.
    /// @note Types that have a more efficient swapping method should specialize this method.
    template<typename T>
    void swap(T &first, T &second)
    {
        T temp = first;
        first  = second;
        second = temp;
    }
}

#endif //HYPER_UTILITY_H