#include "second.h"
#include <stdio.h>

int main(void)
{
    printf("Hello from 12_different_incrementals example!\n");

#ifdef NDEBUG
    printf("This is a RELEASE build.\n");
#else
    printf("This is a DEBUG build.\n");
#endif

    printf("sum of 10 and 21 is : %d\n", sum(10, 21));
}
