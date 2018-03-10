/// @file Function.h
/// Container for referencing a callable instance.

#ifndef HYPER_FUNCTION_H
#define HYPER_FUNCTION_H

#include "UniquePointer.h"

namespace hyper {
    template<typename Signature>
    class Function {
        // ...
    };

    template<typename ReturnValue, typename... Args>
    class Function<ReturnValue(Args...)> {
    private:
        class Callable {
        public:
            virtual ~Callable() = default;

            virtual ReturnValue invoke(Args...) = 0;
        };

        template<typename Signature>
        class ConcreteCallable : public Callable {
        private:
            Signature _func;

        public:
            explicit ConcreteCallable(const Signature &func)
                    : _func(func) {
                // ...
            }

            ~ConcreteCallable() override = default;

            ReturnValue invoke(Args... args) {
                return _func(args...);
            }
        };

        UniquePointer<Callable> _callable;

    public:
        template<typename Sig>
        Function& operator=(Sig func) {
            _callable = createUnique(new ConcreteCallable<Sig>(func));
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
            return _callable == other._callable;
        }

        /// @brief Inequality operator.
        /// @details Checks if two function references are different.
        /// @param other Other instance to compare against.
        /// @return True if the instances reference different functions.
        /// @return False if the instances reference the same function.
        /// @return True if only one instance references null.
        /// @return False if both instances reference null.
        constexpr bool operator!=(const Function &other) const noexcept {
            return _callable != other._callable;
        }

        ReturnValue operator()(Args... args) const {
            ASSERTF((bool)_callable, "Function pointer is null");
            return _callable->invoke(args...);
        }
    };
}

#endif // HYPER_FUNCTION_H