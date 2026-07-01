#define SHU_IMPLEMENTATION
#define SHUC_ENABLE_INCREMENTAL
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows how to use cache system
    more effectively.
*/

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    // SHU_UtilAutomate(argc, argv);

    // Configure the cache directory of the current project.
    SHU_CacheConfigure(".shu/debug/");

    SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG);

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleCompile("build/debug/", SHUModuleType_Executable);

    // Change the cache configuration and build again.
    SHU_CacheConfigure(".shu/release/");

    SHU_CompilerClearFlags();
    SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH);
    SHU_CompilerAddFlags("-DNDEBUG");

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleCompile("build/release", SHUModuleType_Executable);

    // At the end, this two modules will be considered as different
    // projects and will not share the cache even though they have
    // the same name. They would conflict if the cache directory
    // would be same for both.

    return 0;
}