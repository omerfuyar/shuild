#include <stdio.h>

/*
    This example shows capabilities of a shuild source
    file with command line arguments
*/

int main(void)
{
    printf("Hello from 3_main_arguments example!\n");

#if defined(__clang__) && defined(_MSC_VER)
    printf("Compiled using clang-cl compiler : %d, %d\n", (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__), _MSC_VER);
#elif defined(__clang__)
    printf("Compiled using clang compiler : %d\n", (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__));
#elif defined(_MSC_VER)
    printf("Compiled using msvc compiler : %d\n", _MSC_VER);
#elif defined(__GNUC__)
    printf("Compiled using gcc compiler : %d\n", (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__));
#endif

    return 0;
}