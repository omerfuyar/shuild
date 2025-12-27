#define SHUC_NO_MODULE_LOG
#define SHUC_NO_RUN_LOG
#define SHUC_NO_RUN_ERROR
#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"
// You can find all configurations at the very top of the shuild.h file.

int main(void)
{
    SHU_CompilerTryConfigure("clang");

    SHU_ModuleBegin("example");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);
    return 0;
}