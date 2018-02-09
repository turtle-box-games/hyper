#ifndef HYPER_EXCEPTION_H
#define HYPER_EXCEPTION_H

#include "StackTrace.h"

namespace hyper
{
    namespace exceptions
    {
        class Exception
        {
        private:
            const Exception *_cause;
            const StackTrace _backtrace;

        public:

            virtual const char *message() noexcept;

            /*constexpr*/ const Exception *cause() noexcept;

            const StackTrace& backtrace() const noexcept;

            void raise() const;
        };
    }
}

#endif //HYPER_EXCEPTION_H
