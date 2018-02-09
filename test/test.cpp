#include <cstdio>
#include "hyper/pointer_util.h"

#include <execinfo.h>
#include <stdlib.h>
#include <hyper/StackTraceSnapshot.h>
#include <hyper/StackTrace.h>

void
print_trace()
{
    auto st = hyper::StackTrace::capture();
    for(size_t i = 0; i < st.size(); ++i)
        printf("%p\n", st[i].returnAddress());
}

void dummy_function()
{
    print_trace();
}

int main(int argc, char **argv)
{
    dummy_function();
    return 0;
}