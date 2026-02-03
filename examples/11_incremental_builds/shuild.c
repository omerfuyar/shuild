#define SHUILD_IMPLEMENTATION
#define SHUC_ENABLE_INCREMENTAL
#include "../../shuild.h"

int main(int argc, char **argv)
{
    // initialize the cache if doesn't exist
    SHU_CompilerTryConfigure("gcc");

    // configure compiler and module until compilation.
    SHU_CompilerAddFlags("-DFOO");
    SHU_ModuleBegin("exampleLib", "dependencies/exampleLib/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceDirectory("src/");

    // check the module cache and cleanup if compiler and module configuration changed/not existent.
    // check the object file exist and up to date for all source files
    // check header cache file exist and up to date for all source files and their header dependencies
    SHU_ModuleCompile("build/lib/", SHUM_MODULE_LIBRARY_STATIC);

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");

    SHU_ModuleLinkLibrary("exampleLib");

    SHU_ModuleCompile("build/bin/", SHUM_MODULE_EXECUTABLE);

    return 0;
}