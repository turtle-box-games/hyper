/// @file Function.h
/// Container for referencing a callable instance.

#ifndef HYPER_FUNCTION_H
#define HYPER_FUNCTION_H

#include "SharedPointer.h"

namespace hyper {
    /// @brief Base function container class.
    /// @details This class and type parameters allow for abbreviated syntax for functions.
    /// @tparam Signature Function signature in the form: RETURN_TYPE(ARGUMENT_TYPES...)
    template<typename Signature>
    class Function {
        // ...
    };

    /// @brief Specialized function container class.
    /// @details This class is able to extract type parameters from the abbreviated syntax.
    /// @tparam ReturnValue Type of the return value of the function.
    /// @tparam Args Types for the arguments the function expects when called.
    template<typename ReturnValue, typename... Args>
    class Function<ReturnValue(Args...)> {
    private:
        /// @brief Abstract base class for all callable types.
        /// @details Provides type-erasure for callable types.
        class Callable {
        public:
            /// @brief Destructor.
            virtual ~Callable() = default;

            /// @brief Calls the instance.
            /// @details Passes the arguments onto the callable instance and passed the return value back.
            virtual ReturnValue invoke(Args...) = 0;
        };

        /// @brief Concrete implementation of a callable type.
        /// @details By using a template, all callable types that match the return type and parameters will work.
        /// @tparam CallableType Type of the "thing" being called.
        template<typename CallableType>
        class ConcreteCallable : public Callable {
        private:
            CallableType _func;

        public:
            /// @brief Constructor.
            /// @param func Callable instance.
            explicit ConcreteCallable(const CallableType &func)
                    : _func(func) {
                // ...
            }

            /// @brief Destructor.
            ~ConcreteCallable() override = default;

            /// @brief Calls the instance.
            /// @details Passes the arguments onto the callable instance and passed the return value back.
            /// @param args Arguments to pass to the callable instance.
            /// @return Return value passed back from the callable instance.
            ReturnValue invoke(Args... args) {
                return _func(args...);
            }
        };

        SharedPointer<Callable> _callable;

    public:
        /// @brief Default constructor.
        /// @details Creates a function that references null.
        Function() = default;

        /// @brief Copy constructor.
        /// @param other Existing function to copy from.
        Function(const Function &other)
                : _callable(other._callable) {
            // ...
        }

        /// @brief Move constructor.
        /// @param other Existing function to take ownership of.
        Function(Function &&other) noexcept
                : _callable(other._callable) {
            // ...
        }

        /// @brief General constructor.
        /// @param func Function to wrap.
        /// @tparam CallableType Callable instance that satisfies the function signature.
        template<typename CallableType>
        explicit Function(CallableType func)
                : _callable(createShared(new ConcreteCallable<CallableType>(func))) {
            // ...
        }

        /// @brief Copy assignment operator.
        /// @param other Existing function to copy from.
        /// @return Reference to this instance after it has been updated.
        Function &operator=(const Function &other) noexcept {
            _callable = other._callable;
            return *this;
        }

        /// @brief Move assignment operator.
        /// @param other Existing function to take ownership of.
        /// @return Reference to this instance after it has been updated.
        Function &operator=(Function &&other) noexcept {
            _callable = other._callable;
            return *this;
        }

        /// @brief Assignment operator.
        /// @param func Function to store.
        /// @tparam CallableType Callable instance that satisfies the function signature.
        /// @return Reference to this instance after it has been updated.
        template<typename CallableType>
        Function &operator=(CallableType func) {
            _callable = createShared(new ConcreteCallable<CallableType>(func));
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

        /// @brief Functor operator.
        /// @details Calls the underlying function.
        /// @param args Arguments to pass to the function.
        /// @return Value returned from the function.
        ReturnValue operator()(Args... args) const {
            ASSERTF((bool)_callable, "Attempt to call null function");
            return _callable->invoke(args...);
        }

        /// @brief Explicit bool cast.
        /// @details Checks whether the function can be safely invoked.
        /// @return True if the function references a callable instance.
        /// @return False if the function points to null.
        explicit operator bool() const noexcept {
            return (bool)_callable;
        }
    };
}

#endif // HYPER_FUNCTION_H