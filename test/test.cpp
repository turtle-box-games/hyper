#include <hyper/SharedPointer.h>

using namespace hyper;

int main(int argc, char **argv) {
    SharedPointer<int> sp(new int(5));
    {
        printf("%i\n", *sp);
        SharedPointer<int> ptr1(sp);
        SharedPointer<int> ptr2(ptr1);
        SharedPointer<int> ptr3(ptr2);

        printf("%i + %i + %i = %i\n", *ptr1, *ptr2, *ptr3, *ptr1 + *ptr2 + *ptr3);
        swap(ptr1, ptr2);
    }

    return 0;
}