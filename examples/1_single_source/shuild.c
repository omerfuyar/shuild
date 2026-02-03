#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerConfigure(SHUM_COMPILER_CLANG, "gcc");
    SHU_CompilerAddFlags("-DFOO=13");

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);

    return 0;
}
