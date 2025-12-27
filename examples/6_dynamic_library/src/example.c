#include "dependency.h"
#include <stdio.h>

int main(void)
{
    printf("Hello from 5_static_library example!\n");

    printf("Sum of 5, 12, 13 taken from DYNAMIC LIBRARY is : %d\n", sum(5, 12, 13));
}