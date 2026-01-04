#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    SHU_ModuleBegin("4_folder_structures");

    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceDirectory("src/");

    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}