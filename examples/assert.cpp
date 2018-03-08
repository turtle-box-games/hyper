#include <cstdio>
#include "hyper/assert.h"

int main(int argc, char **argv) {
    // Verify that one argument was passed in.
    ASSERT(argc == 2);
    printf("arg[0]: %s\n", argv[0]);
    printf("arg[1]: %s\n", argv[1]);
    return 0;
}