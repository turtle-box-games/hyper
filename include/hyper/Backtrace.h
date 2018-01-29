/// @file Backtrace.h
/// Stack trace information.
/// Helps track where and how a state was reached.

#ifndef HYPER_BACKTRACE_H
#define HYPER_BACKTRACE_H

#include <cstddef> // For size_t.

namespace hyper
{
    /// @brief Stack trace information.
    /// @details Enables the inspection of the stack frames.
    /// @note Complete stack information, such as function names,
    ///   are only available when the compiled executable has all symbols exposed (@c -rdynamic).
    class Backtrace
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
        /// Hard-coded max stack size to capture.
        /// This allows for allocating the a backtrace on the stack with no dynamic memory allocation.
        static const size_t maxEntries = 64;

        size_t _stackSize;
        void *_returnAddresses[maxEntries];

    public:
        /// @brief Takes a snapshot of the current stack.
        /// @details Creates a backtrace from the current state of the stack.
        ///   This method will be removed from the trace.
        /// @return Current stack trace.
        static Backtrace capture() noexcept;

        /// @brief Default constructor.
        /// @details Creates a backtrace from the current state of the stack.
        Backtrace() noexcept;

        /// @brief Copy constructor.
        /// @details Copies an existing backtrace to a new one.
        /// @param other Existing backtrace to copy from.
        Backtrace(const Backtrace &other) noexcept;

        /// @brief Move constructor.
        /// @details Moves an existing backtrace to a separate instance.
        /// @param other Temporary backtrace to move.
        Backtrace(Backtrace &&other) noexcept;

        /// @brief Destructor.
        /// @details Releases resources that were previously acquired to obtain the stack trace.
        ~Backtrace() noexcept;

        /// @brief Size of the stack trace.
        /// @return Number of frames in the stack.
        size_t size() const noexcept;

        /// @brief Copy assignment.
        /// @details Copy an existing backtrace over the current one.
        /// @param other Existing backtrace to copy from.
        /// @return Reference to the current backtrace.
        Backtrace &operator=(const Backtrace &other) noexcept;

        /// @brief Move operator.
        /// @details Move an existing backtrace and replace the current one with it.
        /// @param other Temporary backtrace to move.
        /// @return Reference to the current backtrace.
        Backtrace &operator=(Backtrace &&other) noexcept;

        /// @brief Retrieves the specified frame from the stack trace.
        /// @param frame Index of the entry to get information about.
        /// @return Information about the specified frame.
        Entry operator[](size_t frame) const;
    };
}

#endif //HYPER_BACKTRACE_H