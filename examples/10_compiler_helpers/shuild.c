#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows preconfigred compiler macros for ease of use.
*/

int main(int argc, char **argv)
{

    SHU_CompilerConfigureTry("gcc");

    // SHU_UtilFail logs the error and ends the build.
    if (argc < 2)
    {
        SHU_UtilFail("use with argument d or r");
    }

    if (!strcmp("d", argv[1]))
    {
        // These macros are defined in the header and
        // probably only compatible with gcc and clang.
        SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG, SHUM_FLAGS_WARNING_MID, SHUM_FLAGS_WARNING_ERROR);
    }
    else if (!strcmp("r", argv[1]))
    {
        // Each macro is one argument, and goes with other flags.
        SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH, "-DNDEBUG");
    }
    else
    {
        SHU_UtilFail("the first argument must be d or r");
    }

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddSourceFiles("example.c");
    SHU_ModuleCompile("", SHUModuleType_Executable);

    return 0;
}