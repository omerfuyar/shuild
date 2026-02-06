#include <stdio.h>

int main(void)
{
    printf("Hello from 2_compiler_flags example!\n");

#ifdef NDEBUG
    printf("This is a RELEASE build.\n");
#else
    printf("This is a DEBUG build.\n");
#endif

#ifdef FOO
    printf("the FOO value is : %d\n", FOO);
#endif

    return 0;
}