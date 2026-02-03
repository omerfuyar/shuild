#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    // SHU_CompilerTryConfigure(argv[1]);
    SHU_CompilerTryConfigure("gcc");

    for (int i = 1; i < argc; i++)
    {
        SHU_CompilerAddFlags(argv[i]);
    }

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}