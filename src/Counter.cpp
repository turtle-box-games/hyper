#include "hyper/Counter.h"

namespace hyper {
    constexpr Counter::Counter() noexcept
        : _count(0) {
        // ...
    }

    constexpr Counter::Counter(size_t initial) noexcept
        : _count(initial) {
        // ...
    }

    constexpr size_t Counter::value() const noexcept {
        return _count;
    }

    size_t Counter::increment() noexcept {
        auto value = _count;
        _count++;
        return value;
    }

    size_t Counter::decrement() noexcept {
        auto value = _count;
        if(_count > 0)
            _count--;
        return value;
    }

    Counter &Counter::operator++() noexcept {
        increment();
        return *this;
    }

    const Counter Counter::operator++(int) noexcept {
        return Counter(increment());
    }

    Counter &Counter::operator--() noexcept {
        decrement();
        return *this;
    }

    const Counter Counter::operator--(int) noexcept {
        return Counter(decrement());
    }

    Counter::operator size_t() const noexcept {
        return value();
    }
}