/// @file Error.h
/// Base for all error types.

#ifndef HYPER_ERROR_H
#define HYPER_ERROR_H

namespace hyper
{
    /// @brief Base class for all error types.
    /// @details Error instances are used instead of throwing exceptions.
    /// @see Result
    class Error
    {
    private:
        Error *_cause;

    public:
        /// @brief Default constructor.
        /// @details Creates a new error with no nested cause.
        constexpr Error() noexcept;

        /// @brief General constructor.
        /// @details Creates a new error with a nested caused.
        /// @param cause Underlying error that caused the current one.
        constexpr Error(Error *cause) noexcept;

        /// @brief Destructor.
        virtual ~Error() noexcept;

        /// @brief Error message.
        /// @details Reason for the error or why it happened.
        /// @return String containing the error message.
        virtual const char *message() const noexcept = 0;

        /// @brief Nested cause.
        /// @details Retrieves the underlying error that caused this one.
        /// @return Underlying error or null if there was none.
        Error *cause() const noexcept;
    };
}

#endif //HYPER_ERROR_H