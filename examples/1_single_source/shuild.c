#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerConfigure(SHUM_COMPILER_CLANG, "clang");
    SHU_CompilerAddFlags("-DFOO=13");

    SHU_ModuleBegin("1_single_source");
    SHU_ModuleAddSourceFile("example.c");

    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);

    return 0;
}
