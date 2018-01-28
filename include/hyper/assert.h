/// @file assert.h
/// Macros for requiring a condition is met before proceeding.
/// These assertions will cause the program to immediately exit if the condition is false.
/// However, if the program is compiled for release, with @c -DNDEBUG, then the assertions are removed.

#ifndef HYPER_ASSERT_H
#define HYPER_ASSERT_H

#include <cstdlib> // For abort()
#include <cstdio>  // For fprintf()

// Workaround for converting the line number in a file to a string.
#define STRINGIFY(X) #X
#define TOSTRING(X) STRINGIFY(X)

/// @def SOURCE_LOCATION
/// @brief Current location in the source code as a string.
/// @details Inserts the current location in the source code as a constant string.
///   The string is formatted as @c FILE:LINE
#define SOURCE_LOCATION __FILE__ ":" TOSTRING(__LINE__)

#ifdef NDEBUG
// Define assertions as no-ops when compiling in release mode.
#define ASSERT(condition) ((void)0)
#define ASSERTF(condition, message, vars...) ((void)0)
#else

/// @def ASSERT(condition)
/// @brief Require that a condition be met.
/// @details If the condition fails, then an error is printed and the program exits immediately.
///   This macro should only be used in exceptional circumstances when program stability is questioned.
///   When building the program in release mode, specifically with @c NDEBUG defined,
///   then this check is a no-op - the check is not performed.
/// @param condition Boolean condition to ensure is true.
/// @example assert.cpp
///   Example of asserting a condition is true without a message.
#define ASSERT(condition) \
do \
{ \
    if(!(condition)) \
    { \
        fprintf(stderr, "Assertion failed: " #condition "\n" \
            "\tat " SOURCE_LOCATION  "\n"); \
        abort(); \
    } \
} while(false)

/// @def ASSERTF(condition, message, vars...)
/// @brief Require that a condition be met and display a message if not.
/// @details If the condition fails, then an error is printed and the program exits immediately.
///   This macro should only be used in exceptional circumstances when program stability is questioned.
///   When building the program in release mode, specifically with @c NDEBUG defined,
///   then this check is a no-op - the check is not performed.
/// @param condition Boolean condition to ensure is true.
/// @param message String describing the condition that must be met.
///   This string can contain @p printf() format specifiers.
/// @param vars Optional list of variables to substitute into the @p message.
/// @example assertf.cpp
///   Example of asserting with a custom message and formatting variables.
#define ASSERTF(condition, message, vars...) \
do \
{ \
    if(!(condition)) \
    { \
        fprintf(stderr, "Assertion failed: " #condition "\n" \
            "\tat " SOURCE_LOCATION "\n"); \
        fprintf(stderr, "\t" message "\n", ##vars); \
        abort(); \
    } \
} while(false)

/* There is a separate call to fprintf() for message
 * because #condition could contain %,
 * which would mess up the formatting. */
#endif

#endif //HYPER_ASSERT_H