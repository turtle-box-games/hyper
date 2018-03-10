#include <hyper/Function.h>

using namespace hyper;

int main(int argc, char **argv) {
    Function<void(void)> fun;
    fun = []() { printf("fun\n"); };
    fun();

    return 0;
}