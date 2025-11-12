#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure(argv[1]);

    for (int i = 2; i < argc; i++)
    {
        SHU_CompilerAddFlags(argv[i]);
    }

    SHU_ModuleBegin("3_main_arguments");
    SHU_ModuleAddSourcefile("example.c");
    SHU_ModuleCompileExecutable("");

    return 0;
}