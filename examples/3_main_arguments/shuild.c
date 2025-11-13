#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    // SHU_CompilerTryConfigure(argv[1]);
    SHU_CompilerTryConfigure("clang");

    for (int i = 1; i < argc; i++)
    {
        SHU_CompilerAddFlags(argv[i]);
    }

    SHU_ModuleBegin("3_main_arguments");
    SHU_ModuleAddSourcefile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}