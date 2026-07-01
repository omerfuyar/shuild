#define SHU_IMPLEMENTATION
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows capabilities of a shuild source
    file with command line arguments
*/

int main(int argc, char **argv)
{
    // 'Try' configure will guess the compiler in your system
    // (like 'cc', 'gcc' or 'clang') and configure it for you.
    // Leave it empty to use the host compiler that compiled this script.
    SHU_CompilerTryConfigure("gcc");

    // Add flags from command line.
    for (int i = 1; i < argc; i++)
    {
        SHU_CompilerAddFlags(argv[i]);
    }

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile(NULL, SHUModuleType_Executable);

    return 0;
}