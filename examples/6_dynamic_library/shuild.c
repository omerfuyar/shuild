#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a dynamicly linked library.
*/

int main(void)
{
    SHU_CompilerConfigureTry("gcc");

    SHU_ModuleBegin("exampleLib", "dependencies/exampleLib/");
    SHU_ModuleAddIncludeDirectories("include/");
    SHU_ModuleAddSourceFiles("src/");
    // Same thing with previous example but as dynamic.
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryDynamic);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectories("include/");
    SHU_ModuleAddIncludeDirectories("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceFiles("src/");

    // This path will be baked/embedded to the executable.
    SHU_ModuleAddLibraryDirectories("build/lib/");
    SHU_ModuleLinkLibraries("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUModuleType_Executable);

    return 0;
}