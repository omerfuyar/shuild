#define SHUILD_IMPLEMENTATION
#define SHUC_ENABLE_INCREMENTAL
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
    // The cache will be configured as '.shu' in current executable directory.
    SHU_CompilerTryConfigure("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_ModuleBegin("exampleLib", "dependencies/exampleLib/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");

    SHU_ModuleCompile("build/lib/", SHUM_MODULE_LIBRARY_STATIC);

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");

    SHU_ModuleLinkLibrary("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUM_MODULE_EXECUTABLE);

    return 0;
}