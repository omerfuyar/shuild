#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("clang");

    SHU_ModuleBegin("exampleLib");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("dependencies/exampleLib/src/");
    SHU_ModuleCompile("build/lib/", SHUM_MODULE_LIBRARY_DYNAMIC);

    SHU_ModuleBegin("example");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("src/");

    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUM_MODULE_EXECUTABLE);

    return 0;
}