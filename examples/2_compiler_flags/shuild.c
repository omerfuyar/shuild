#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerConfigure(SHUM_COMPILER_CLANG, "gcc");

    SHU_CompilerAddFlags("-O0");
    SHU_CompilerAddFlags("-g -Wall");
    SHU_ModuleBegin("exampleDebug");
    SHU_ModuleAddSourceFile("example.c");

    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    //=========

    SHU_CompilerSetFlags("-O3 -DNDEBUG");
    SHU_ModuleBegin("exampleRelease");
    SHU_ModuleAddSourceFile("example.c");

    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}