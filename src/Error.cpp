#include "hyper/Error.h"

namespace hyper
{
    constexpr Error::Error() noexcept
        : _cause(nullptr)
    {
        // ...
    }

    constexpr Error::Error(Error *cause) noexcept
        : _cause(cause)
    {
        // ...
    }

    Error::~Error() noexcept
    {
        _cause = nullptr;
    }

    constexpr Error *Error::cause() const noexcept
    {
        return _cause;
    }
}