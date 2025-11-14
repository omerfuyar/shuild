#include "example.h"
#include "dependency.h"
#include <stdio.h>

int main(void)
{
    printf("Hello from 5_static_library example!\n");

    printf("Sum of 5, 12, 13 is : %d\n", sum(5, 12, 13));
    printf("5 * 12 * 13 = %f\n", multiply(5, 12, 13));
}