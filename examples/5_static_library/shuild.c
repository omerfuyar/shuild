#define SHU_IMPLEMENTATION
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a staticly linked library.
*/

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    SHU_ModuleBegin("exampleLib", "dependencies/exampleLib/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    // Compile (archive) the module as a static library.
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryStatic);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceFile("src/");

    // Add a library search directory to current executable module.
    SHU_ModuleAddLibraryDirectory("build/lib/");
    // Link a library to current executable module.
    SHU_ModuleLinkLibrary("exampleLib");

    // These two functions will only work if the module is an executable.
    // todo this design is confusing, consider moving module
    //! identification to ModuleBegin

    SHU_ModuleCompile("build/bin/", SHUModuleType_Executable);

    return 0;
}