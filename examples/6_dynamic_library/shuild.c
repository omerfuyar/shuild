#define SHU_IMPLEMENTATION
#include "../../../shu/shu.h"
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
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryDynamic);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceFile("src/");

    // This path will be baked/embedded to the executable.
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUModuleType_Executable);

    return 0;
}