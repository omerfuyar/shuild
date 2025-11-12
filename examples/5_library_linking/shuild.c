#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("clang");

    SHU_ModuleBegin("exampleLib");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("dependencies/exampleLib/src/");
    SHU_ModuleCompile("build/lib/", 1);

    SHU_ModuleBegin("example");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleLinkLibrary("exampleLib");
    SHU_ModuleCompile("build/bin/", 0);

    return 0;
}