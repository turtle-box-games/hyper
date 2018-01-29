/// @file Backtrace.cpp
/// Implementation of Backtrace class.

#include "hyper/Backtrace.h"

namespace hyper
{
    Backtrace Backtrace::capture() noexcept
    {
        // TODO
        return Backtrace();
    }

    Backtrace::Backtrace() noexcept
    {
        // TODO
    }

    Backtrace::Backtrace(const Backtrace &other) noexcept
    {
        // TODO
    }

    Backtrace::Backtrace(Backtrace &&other) noexcept
    {
        // TODO
    }

    Backtrace::~Backtrace() noexcept
    {
        // TODO
    }

    size_t Backtrace::size() const noexcept
    {
        // TODO
        return 0;
    }

    Backtrace &Backtrace::operator=(const Backtrace &other) noexcept
    {
        // TODO
        return *this;
    }

    Backtrace &Backtrace::operator=(Backtrace &&other) noexcept
    {
        // TODO
        return *this;
    }

    Backtrace::Entry Backtrace::operator[](size_t frame) const
    {
        // TODO
        return Entry(nullptr);
    }

    Backtrace::Entry::Entry(void *returnAddress) noexcept
    {
        // TODO
    }

    Backtrace::Entry::Entry(const Entry &other) noexcept
    {
        // TODO
    }

    Backtrace::Entry::Entry(Entry &&other) noexcept
    {
        // TODO
    }

    Backtrace::Entry::~Entry() noexcept
    {
        // TODO
    }

    void *Backtrace::Entry::returnAddress() const noexcept
    {
        // TODO
        return nullptr;
    }

    char *Backtrace::Entry::filename() const noexcept
    {
        // TODO
        return nullptr;
    }

    char *Backtrace::Entry::functionName() const noexcept
    {
        // TODO
        return nullptr;
    }

    int Backtrace::Entry::functionOffset() const noexcept
    {
        // TODO
        return -1;
    }

    bool Backtrace::Entry::isFunctionKnown() const noexcept
    {
        // TODO
        return false;
    }

    char *Backtrace::Entry::toString() const
    {
        // TODO
        return nullptr;
    }

    Backtrace::Entry &Backtrace::Entry::operator=(const Entry &other) noexcept
    {
        // TODO
        return *this;
    }

    Backtrace::Entry &Backtrace::Entry::operator=(Entry &&other) noexcept
    {
        // TODO
        return *this;
    }
}