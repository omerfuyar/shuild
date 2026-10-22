#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows capabilities of a shuild source
    file with command line arguments
*/

int main(int argc, char **argv)
{

    // 'Try' configure asks the compiler for its family
    // (gcc or clang) and configures it for you.
    // Leave it NULL to use the newest compiler on PATH.
    SHU_CompilerConfigureTry("gcc");

    // Add flags from command line.
    for (int i = 1; i < argc; i++)
    {
        SHU_CompilerAddFlags(argv[i]);
    }

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddSourceFiles("example.c");
    SHU_ModuleCompile(NULL, SHUModuleType_Executable);

    return 0;
}