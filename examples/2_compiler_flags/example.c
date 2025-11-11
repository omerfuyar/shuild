#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Hello from 2_compiler_flags example!\n");

#ifdef NDEBUG
    printf("This is a RELEASE build.\n");
#else
    printf("This is a DEBUG build.\n");
#endif

    return 0;
}