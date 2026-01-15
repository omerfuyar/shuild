#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    SHU_ModuleBegin("example");

    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceDirectory("src/");

    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}