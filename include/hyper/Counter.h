/// @file Counter.h
/// Atomic counter.

#ifndef HYPER_COUNTER_H
#define HYPER_COUNTER_H

#include <cstddef> // For size_t.

namespace hyper {
    /// @brief Non-negative value that can be incremented and decremented.
    /// @todo Make thread-safe.
    class Counter {
    public:
        /// @brief Default constructor.
        /// @details Creates a counter starting at zero.
        constexpr Counter() noexcept;

        /// @brief General constructor.
        /// @details Creates a counter starting at a specified value.
        /// @param initial Value to start the counter at.
        constexpr explicit Counter(size_t initial) noexcept;

        /// @brief Retrieves the current value of the counter.
        /// @return Value of the counter.
        constexpr size_t value() const noexcept;

        /// @brief Increments the counter by one.
        /// @return Value prior to incrementing the counter.
        size_t increment() noexcept;

        /// @brief Decrements the counter by one.
        /// @return Value prior to decrementing the counter.
        /// @note If the value is already zero, then it remains at zero.
        ///   The value will not underflow.
        size_t decrement() noexcept;

        /// @brief Pre-increment operator.
        /// @details Increments the counter and returns the new value.
        /// @return Updated counter after the increase.
        Counter &operator++() noexcept;

        /// @brief Post-increment operator.
        /// @details Increments the counter and returns the old value.
        /// @return Value of the counter before it was incremented.
        const Counter operator++(int) noexcept;

        /// @brief Pre-decrement operator.
        /// @details Decrements the counter and returns the new value.
        /// @return Updated counter after the decrease.
        Counter &operator--() noexcept;

        /// @brief Post-decrement operator.
        /// @details Decrements the counter and returns the old value.
        /// @return Value of the counter before it was decreased.
        const Counter operator--(int) noexcept;

        /// @brief Explicit conversion.
        /// @return Returns the value of the counter.
        explicit operator size_t() const noexcept;

    private:
        size_t _count;
    };
}

#endif // HYPER_COUNTER_H