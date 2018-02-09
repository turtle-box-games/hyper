/// @file StackTrace.h
/// Stack trace information.
/// Helps track where and how a state was reached.

#ifndef HYPER_STACKTRACE_H
#define HYPER_STACKTRACE_H

#include <cstdlib> // For free().
#include "StackTraceSnapshot.h"

namespace hyper
{
    /// @brief Stack trace information.
    /// @details Enables the inspection of the stack frames.
    /// @note Complete stack information, such as function names,
    ///   are only available when the compiled executable has all symbols exposed (@c -rdynamic).
    class StackTrace
    {
    public:
        /// @brief Stack frame information.
        /// @details Information about a single stack frame.
        class Entry
        {
        private:
            void *_returnAddress;
            char *_filename;
            char *_functionName;
            int _functionOffset;

        public:
            /// @brief Default constructor.
            /// @details Creates an empty entry.
            Entry() noexcept;

            /// @brief General constructor.
            /// @param returnAddress Function return address retrieved from the stack.
            Entry(void *returnAddress) noexcept;

            /// @brief Copy constructor.
            /// @details Copies an existing backtrace entry to a new one.
            /// @param other Existing backtrace entry to copy from.
            Entry(const Entry &other) noexcept;

            /// @brief Move constructor.
            /// @details Moves an existing backtrace entry to a separate instance.
            /// @param other Temporary backtrace entry to move.
            Entry(Entry &&other) noexcept;

            /// @brief Destructor.
            /// @details Releases resources that were previously acquired to obtain the frame information.
            ~Entry() noexcept;

            /// @brief Return address.
            /// @details Retrieves the pointer representing the return address.
            ///   This points to a location within a function to return to,
            ///   which indicates where a function made a call to another.
            /// @return Raw stack pointer.
            void *returnAddress() const noexcept;

            /// @brief File name.
            /// @details Name of the source code file.
            /// @return String containing the file name.
            char *filename() const noexcept;

            /// @brief Function name.
            /// @details Name of the function.
            ///   An attempt will be made to demangle the function name.
            /// @return String containing the function name.
            /// @return @c nullptr if symbol information is unavailable.
            /// @note This information is only available if symbols are exported from the executable.
            char *functionName() const noexcept;

            /// @brief Function offset.
            /// @details Offset from the start of the function.
            /// @return Function offset.
            /// @return -1 if symbol information is unavailable.
            /// @note This information is only available if symbols are exported from the executable.
            int functionOffset() const noexcept;

            /// @brief Are function details known?
            /// @details Checks if the function name and offset information is available.
            ///   If this returns @c true, then functionName() and functionOffset() can be used.
            /// @return @c true if symbol information for the function is available.
            /// @return @c false if symbol information for the function is not available.
            bool isFunctionKnown() const noexcept;

            /// @brief Formats the stack frame information as a string.
            /// @return Formatted string containing the stack information.
            char *toString() const;

            /// @brief Copy assignment.
            /// @details Copy an existing backtrace entry over the current one.
            /// @param other Existing backtrace entry to copy from.
            /// @return Reference to the current backtrace entry.
            Entry &operator=(const Entry &other) noexcept;

            /// @brief Move operator.
            /// @details Move an existing backtrace entry and replace the current one with it.
            /// @param other Temporary backtrace entry to move.
            /// @return Reference to the current backtrace entry.
            Entry &operator=(Entry &&other) noexcept;
        };

    private:
        size_t _stackSize;
        Entry _entries[];

        static Entry createEntryFromSymbol(void *returnAddress, char *symbol) noexcept;

        template<size_t Size>
        static size_t createStackEntries(const StackTraceSnapshot <Size> &snapshot, Entry *entries)
        {
            auto addresses  = &snapshot.addresses();
            auto entryCount = snapshot.frameCount();
            auto symbols    = backtrace_symbols(*addresses, entryCount--);
            // Subtract one to skip the top-most frame that called backtrace().
            entries = new Entry[entryCount];
            for(size_t i = 0; i < entryCount; ++i)
                entries[i] = createEntryFromSymbol(*addresses[i], symbols[i]);
            free(symbols);
            return entryCount;
        }

    public:
        /// Creates a stack trace for the current state of the stack.
        /// @tparam Size Maximum number of stack frames to capture.
        /// @return Current stack trace.
        template<size_t Size = 64>
        static StackTrace capture()
        {
            StackTraceSnapshot<Size> snapshot;
            return StackTrace(snapshot);
        }

        /// @brief Default constructor.
        /// @details Generates a trace from a snapshot of a stack.
        /// @param snapshot Snapshot of the stack to analyze.
        /// @tparam Size Maximum number of stack frames to process.
        template<size_t Size>
        StackTrace(const StackTraceSnapshot<Size> &snapshot)
        {
            _stackSize = createStackEntries(snapshot, _entries);
        }

        /// @brief Copy constructor.
        /// @details Copies an existing backtrace to a new one.
        /// @param other Existing backtrace to copy from.
        StackTrace(const StackTrace &other) noexcept;

        /// @brief Move constructor.
        /// @details Moves an existing backtrace to a separate instance.
        /// @param other Temporary backtrace to move.
        StackTrace(StackTrace &&other) noexcept;

        /// @brief Destructor.
        /// @details Releases resources that were previously acquired to obtain the stack trace.
        ~StackTrace() noexcept;

        /// @brief Size of the stack trace.
        /// @return Number of frames in the stack.
        size_t size() const noexcept;

        /// @brief Copy assignment.
        /// @details Copy an existing backtrace over the current one.
        /// @param other Existing backtrace to copy from.
        /// @return Reference to the current backtrace.
        StackTrace &operator=(const StackTrace &other) noexcept;

        /// @brief Move operator.
        /// @details Move an existing backtrace and replace the current one with it.
        /// @param other Temporary backtrace to move.
        /// @return Reference to the current backtrace.
        StackTrace &operator=(StackTrace &&other) noexcept;

        /// @brief Retrieves the specified frame from the stack trace.
        /// @param frame Index of the entry to get information about.
        /// @return Information about the specified frame.
        Entry operator[](size_t frame) const;
    };
}

#endif //HYPER_STACKTRACE_H