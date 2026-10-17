#include <stdio.h>

int main(void)
{
    printf("Hello from 16_compiler_detection example!\n");
#if defined(__clang__)
    printf("The newest compiler found on PATH, clang %d, compiled it.\n", __clang_major__);
#elif defined(__GNUC__)
    printf("The newest compiler found on PATH, gcc %d, compiled it.\n", __GNUC__);
#endif
    return 0;
}
