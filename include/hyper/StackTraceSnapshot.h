/// @file StackTraceSnapshot.h
/// Raw stack trace information.

#ifndef HYPER_STACKTRACESNAPSHOT_H
#define HYPER_STACKTRACESNAPSHOT_H

#include <cstddef> // For size_t.

namespace hyper
{
    /// @brief Raw stack trace information.
    /// @details Contains the minimum information needed to generate a stack trace.
    ///   No "human-friendly" information is available from this information.
    ///   This class provides a quick way of capturing the current state of the stack.
    /// @tparam Size Maximum number of stack frames to capture.
    ///   This is a template parameter so that the snapshot can be stored on the stack.
    ///   This also implies there is no dynamic memory allocation when generating a snapshot.
    template<size_t Size = 64>
    class StackTraceSnapshot
    {
    private:
        size_t _frameCount;
        void *_addresses[Size];

    public:
        /// @brief Frame count.
        /// @details Number of frame contained in the snapshot.
        /// @return Number of frames.
        size_t frameCount() const noexcept;

        /// @brief Return addresses.
        /// @details Raw return addresses captured from the stack.
        ///   These addresses refer to points where function calls return to.
        ///   This information can be traced back to the calling functions.
        const void **addresses() const noexcept;
    };
}

#endif //HYPER_STACKTRACESNAPSHOT_H