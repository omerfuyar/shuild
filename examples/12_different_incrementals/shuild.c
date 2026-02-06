#define SHUILD_IMPLEMENTATION
#define SHUC_ENABLE_INCREMENTAL
#include "../../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_CacheConfigure(".shu/debug/");
    SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG);

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleCompile("build/debug/", SHUM_MODULE_EXECUTABLE);

    // change the configuration and build again
    SHU_CacheConfigure(".shu/release/");
    SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH);

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleCompile("build/release/", SHUM_MODULE_EXECUTABLE);

    return 0;
}