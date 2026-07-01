#define SHU_IMPLEMENTATION
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows preconfigred compiler macros for ease of use.
*/

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");

    if (argc < 2)
    {
        printf("Wrong usage : use with argument d or r");
        return 1;
    }

    if (!strcmp("d", argv[1]))
    {
        // These macros are defined in the header and
        // probably only compatible with gcc and clang.
        SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG);
        SHU_CompilerAddFlags(SHUM_FLAGS_WARNING_HIGH SHUM_FLAGS_WARNING_ERROR);
    }
    else if (!strcmp("r", argv[1]))
    {
        // Just add them as string literal macros.
        SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH);
        SHU_CompilerAddFlags("-DNDEBUG");
    }
    else
    {
        printf("Wrong usage : first argument must be d or r");
        return 1;
    }

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUModuleType_Executable);

    return 0;
}