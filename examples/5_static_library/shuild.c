#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a staticly linked library.
*/

int main(void)
{
    SHU_CompilerConfigureTry("gcc");

    // Compile (archive) the module as a static library.
    SHU_MODULE("exampleLib", "dependencies/exampleLib/", SHUModuleType_LibraryStatic, "build/lib/")
    {
        SHU_ModuleAddIncludeDirectories("include/");
        SHU_ModuleAddSourceFiles("src/");
    }

    SHU_MODULE("example", NULL, SHUModuleType_Executable, "build/bin/")
    {
        SHU_ModuleAddIncludeDirectories("include/");
        SHU_ModuleAddIncludeDirectories("dependencies/exampleLib/include/");
        SHU_ModuleAddSourceFiles("src/");

        // Add a library search directory to current module.
        SHU_ModuleAddLibraryDirectories("build/lib/");
        // Link a library to current module. See example 14 for libraries that link other libraries.
        SHU_ModuleLinkLibraries("exampleLib");
    }

    return 0;
}