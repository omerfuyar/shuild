#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerConfigure(SHUM_COMPILER_CLANG, "clang");

    SHU_CompilerAddFlags("-O0");
    SHU_CompilerAddFlags("-g -Wall");
    SHU_ModuleBegin("exampleDebug");
    SHU_ModuleAddSourcefile("example.c");

    SHU_ModuleCompileExecutable("");

    //=========

    SHU_CompilerSetFlags("-O3 -DNDEBUG");
    SHU_ModuleBegin("exampleRelease");
    SHU_ModuleAddSourcefile("example.c");

    SHU_ModuleCompileExecutable("");

    return 0;
}