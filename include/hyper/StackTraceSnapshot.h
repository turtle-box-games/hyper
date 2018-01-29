/// @file StackTraceSnapshot.h
/// Raw stack trace information.

#ifndef HYPER_STACKTRACESNAPSHOT_H
#define HYPER_STACKTRACESNAPSHOT_H

#include <cstddef> // For size_t.
#include <execinfo.h> // For backtrace().

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
    public:
        /// @brief Short-hand for addresses.
        /// @details Fixed array of raw pointers.
        typedef void *AddressArray[Size];

        /// @brief Default constructor.
        /// @details Creates a snapshot of the current stack state.
        StackTraceSnapshot() noexcept
        {
            _frameCount = backtrace(_addresses, Size);
        }

        /// @brief Frame count.
        /// @details Number of frame contained in the snapshot.
        /// @return Number of frames.
        size_t frameCount() const noexcept
        {
            return _frameCount;
        }

        /// @brief Return addresses.
        /// @details Raw return addresses captured from the stack.
        ///   These addresses refer to points where function calls return to.
        ///   This information can be traced back to the calling functions.
        AddressArray const &addresses() const noexcept
        {
            return _addresses;
        }

    private:
        size_t _frameCount;
        AddressArray _addresses;
    };
}

#endif //HYPER_STACKTRACESNAPSHOT_H