/// @file Backtrace.cpp
/// Implementation of Backtrace class.

#include "hyper/StackTrace.h"

namespace hyper
{
    StackTrace::StackTrace(const StackTrace &other) noexcept
    {
        // TODO
    }

    StackTrace::StackTrace(StackTrace &&other) noexcept
    {
        // TODO
    }

    StackTrace::~StackTrace() noexcept
    {
        // TODO
    }

    size_t StackTrace::size() const noexcept
    {
        // TODO
        return _stackSize;
    }

    StackTrace &StackTrace::operator=(const StackTrace &other) noexcept
    {
        // TODO
        return *this;
    }

    StackTrace &StackTrace::operator=(StackTrace &&other) noexcept
    {
        // TODO
        return *this;
    }

    StackTrace::Entry StackTrace::operator[](size_t frame) const
    {
        // TODO
        return _entries[frame];
    }

    StackTrace::Entry StackTrace::createEntryFromSymbol(void *returnAddress, char *symbol) noexcept
    {
        // TODO
        return Entry(returnAddress);
    }

    StackTrace::Entry::Entry() noexcept
    {
        // TODO
    }

    StackTrace::Entry::Entry(void *returnAddress) noexcept
        : _returnAddress(returnAddress)
    {
        // TODO
    }

    StackTrace::Entry::Entry(const Entry &other) noexcept
    {
        // TODO
    }

    StackTrace::Entry::Entry(Entry &&other) noexcept
    {
        // TODO
    }

    StackTrace::Entry::~Entry() noexcept
    {
        // TODO
    }

    void *StackTrace::Entry::returnAddress() const noexcept
    {
        // TODO
        return _returnAddress;
    }

    char *StackTrace::Entry::filename() const noexcept
    {
        // TODO
        return nullptr;
    }

    char *StackTrace::Entry::functionName() const noexcept
    {
        // TODO
        return nullptr;
    }

    int StackTrace::Entry::functionOffset() const noexcept
    {
        // TODO
        return -1;
    }

    bool StackTrace::Entry::isFunctionKnown() const noexcept
    {
        // TODO
        return false;
    }

    char *StackTrace::Entry::toString() const
    {
        // TODO
        return nullptr;
    }

    StackTrace::Entry &StackTrace::Entry::operator=(const Entry &other) noexcept
    {
        // TODO
        return *this;
    }

    StackTrace::Entry &StackTrace::Entry::operator=(Entry &&other) noexcept
    {
        // TODO
        return *this;
    }
}