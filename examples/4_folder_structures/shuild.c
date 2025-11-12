#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("clang");

    SHU_ModuleBegin("4_folder_structures");

    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceDirectory("src/");

    SHU_ModuleCompileExecutable("");

    return 0;
}