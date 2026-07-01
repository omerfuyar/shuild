#include <stdio.h>

/*
    Including for platform macros, thats also a versatility
    but I think it's not really practical and safe. Because
    user may use macros like SHU_LogInfo which uses internal
    definitions which is not implemented in the final project.
*/

#include "../../../shu/shu.h"
#include "../../shuild.h"

int main(void)
{
    printf("Hello from 7_different_compilers example!\n");

    printf("This program compiled with : %s : %d\n", SHUM_COMPILER_GET_STRING(SHUM_HOST_COMPILER), SHUM_HOST_COMPILER_VERSION);

    return 0;
}