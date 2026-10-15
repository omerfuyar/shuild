#include <stdio.h>
#include "generated.h"

int Part(void);

int main(void)
{
    printf("Hello from 13_utility_functions example!\n");
    printf("Found %d source files, and a greeting of %d bytes. The part says : %d\n", SOURCE_COUNT, GREETING_SIZE, Part());

    return 0;
}
