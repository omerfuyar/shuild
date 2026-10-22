#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a staticly linked library.
*/

int main(void)
{
    SHU_CompilerConfigureTry("gcc");

    SHU_ModuleBegin("exampleLib", "dependencies/exampleLib/");
    SHU_ModuleAddIncludeDirectories("include/");
    SHU_ModuleAddSourceFiles("src/");
    // Compile (archive) the module as a static library.
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryStatic);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectories("include/");
    SHU_ModuleAddIncludeDirectories("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceFiles("src/");

    // Add a library search directory to current module.
    SHU_ModuleAddLibraryDirectories("build/lib/");
    // Link a library to current module. See example 14 for libraries that link other libraries.
    SHU_ModuleLinkLibraries("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUModuleType_Executable);

    return 0;
}