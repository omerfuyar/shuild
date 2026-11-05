#define SHUC_ENABLE_INCREMENTAL
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows incremental build capabilities of shuild.
    Cache system will automatically handle all the dependencies
    of intermidiate files like source file of the object file,
    headers that source includes and compiler configuration
    (that also means module state) that module has compiled.
*/

int main(int argc, char **argv)
{
    // The cache is .shu/ beside the build script, unless SHU_CacheConfigure sets another.
    SHU_InitializeShuild();
    SHU_UtilAutomate(argc, argv);

    SHU_Module("exampleLib", "dependencies/exampleLib/", SHUModuleType_LibraryStatic, "build/lib/")
    {
        SHU_ModuleAddIncludeDirectories("include/");
        SHU_ModuleAddSourceFiles("src/");
    }

    SHU_Module("example", "", SHUModuleType_Executable, "build/bin/")
    {
        SHU_ModuleAddIncludeDirectories("include/");
        SHU_ModuleAddIncludeDirectories("dependencies/exampleLib/include/");
        SHU_ModuleAddSourceFiles("src/");
        SHU_ModuleAddLibraryDirectories("build/lib/");

        SHU_ModuleLinkLibraries("exampleLib");
    }

    return 0;
}