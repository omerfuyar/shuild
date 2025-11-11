#include <stdio.h>

/*
    To test this example, first compile shuild.c file and then run
    the outputted executable as said in README.
*/

int main(int argc, char **argv)
{
    printf("Hello from 1_single_source example!\n");

#ifdef FOO
    printf("the FOO value is : %d\n", FOO);
#endif

    return 0;
}
