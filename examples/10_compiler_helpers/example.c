#include <stdio.h>

int main(void)
{
    printf("Hello from 10_compiler_helpers example!\n");

#ifdef NDEBUG
    printf("This is a RELEASE build, optimized for performance.\n");
#else
    printf("This is a DEBUG build, optimized for debugging.\n");
#endif

    return 0;
}