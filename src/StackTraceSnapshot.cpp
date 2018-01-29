/// @file StackTraceSnapshot.cpp
/// Implementation of StackTraceSnapshot.

#include "hyper/StackTraceSnapshot.h"

namespace hyper
{
    template<size_t Size>
    size_t StackTraceSnapshot<Size>::frameCount() const noexcept
    {
        // TODO
        return 0;
    }

    template<size_t Size>
    const void** StackTraceSnapshot<Size>::addresses() const noexcept
    {
        // TODO
        return nullptr;
    }
}