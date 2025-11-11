#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerConfigure(SHUM_COMPILER_CLANG, "clang");

    SHU_CompilerAddFlags("-O0");
    SHU_CompilerAddFlags("-g -Wall");
    SHU_ModuleBegin("exampleDebug");
    SHU_ModuleAddSourcefile("example.c");

    SHU_ExecutableCompile("");

    //=========

    SHU_CompilerSetFlags("-O3 -DNDEBUG");
    SHU_ModuleBegin("exampleRelease");
    SHU_ModuleAddSourcefile("example.c");

    SHU_ExecutableCompile("");

    return 0;
}