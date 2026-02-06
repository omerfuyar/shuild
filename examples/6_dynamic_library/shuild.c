#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

/*
    This example shows building a dynamicly linked library.
*/

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    SHU_ModuleBegin("exampleLib", "dependencies/exampleLib/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    // Same thing with previous example but as dynamic.
    SHU_ModuleCompile("build/lib/", SHUM_MODULE_LIBRARY_DYNAMIC);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceFile("src/");

    // This path will be baked/embedded to the executable.
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUM_MODULE_EXECUTABLE);

    return 0;
}