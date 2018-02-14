#include <hyper/SharedPointer.h>

using namespace hyper;

int main(int argc, char **argv)
{
    auto p = new int;
    SharedPointer<int> sp(p);
    {
        *p = 5;
        printf("%i\n", *sp);
        SharedPointer<int> ptr1(sp);
        SharedPointer<int> ptr2(ptr1);
        SharedPointer<int> ptr3(ptr2);

        printf("%i + %i + %i = %i\n", *ptr1, *ptr2, *ptr3, *ptr1 + *ptr2 + *ptr3);
    }

    return 0;
}