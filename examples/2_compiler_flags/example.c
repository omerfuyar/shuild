#include <stdio.h>

/*
    This example shows that shuild can compile multiple
    modules as executables.
*/

int main(void)
{
    printf("Hello from 2_compiler_flags example!\n");

#ifdef NDEBUG
    printf("This is a RELEASE build.\n");
#else
    printf("This is a DEBUG build.\n");
#endif

    return 0;
}