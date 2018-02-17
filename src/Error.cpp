#include "hyper/Error.h"

namespace hyper
{
    Error::Error() noexcept
        : _cause(SharedPointer<Error>(nullptr))
    {
        // ...
    }

    Error::Error(SharedPointer<Error> cause) noexcept
        : _cause(cause)
    {
        // ...
    }

    Error::~Error() noexcept = default;

    SharedPointer<Error> Error::cause() const noexcept
    {
        return _cause;
    }
}