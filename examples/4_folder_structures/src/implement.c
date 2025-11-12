#include "include.h"

int power(int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }

    int sum = 1;

    for (int i = 0; i < exponent; i++)
    {
        sum *= base;
    }

    return sum;
}