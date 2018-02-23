/// @file bounds.h
/// Template methods for getting upper and lower bounds of value types.

#ifndef HYPER_BOUNDS_H
#define HYPER_BOUNDS_H

namespace hyper
{
    /// @brief Gets the minimum value that a type can hold.
    /// @tparam T Type to get the minimum value of.
    /// @return Minimum value that can be contained by @p T.
    template<typename T>
    T minValue();

    /// @brief Gets the maximum value that a type can hold.
    /// @tparam T Type to get the maximum value of.
    /// @return Maximum value that can be contained by @p T.
    template<typename T>
    T maxValue();
}

#endif //HYPER_BOUNDS_H