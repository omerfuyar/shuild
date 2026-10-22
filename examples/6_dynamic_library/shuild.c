#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a dynamicly linked library.
*/

int main(void)
{
    SHU_CompilerConfigureTry("gcc");

    // Same thing with previous example but as dynamic.
    SHU_MODULE("exampleLib", "dependencies/exampleLib/", SHUModuleType_LibraryDynamic, "build/lib/")
    {
        SHU_ModuleAddIncludeDirectories("include/");
        SHU_ModuleAddSourceFiles("src/");
    }

    SHU_MODULE("example", NULL, SHUModuleType_Executable, "build/bin/")
    {
        SHU_ModuleAddIncludeDirectories("include/");
        SHU_ModuleAddIncludeDirectories("dependencies/exampleLib/include/");
        SHU_ModuleAddSourceFiles("src/");

        // This path will be baked/embedded to the executable.
        SHU_ModuleAddLibraryDirectories("build/lib/");
        SHU_ModuleLinkLibraries("exampleLib");
    }

    return 0;
}