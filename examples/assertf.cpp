#include <cstdlib>
#include <cstdio>
#include "hyper/assert.h"

int main(int argc, char **argv)
{
    // Verify that two arguments are passed in.
    ASSERTF(argc == 3, "Must pass two arguments to program");
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    // Verify that the two arguments total to 5.
    int z = x + y;
    ASSERTF(z == 5, "Two numbers should equal 5, but was %i", z);
    return 0;
}