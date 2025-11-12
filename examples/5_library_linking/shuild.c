#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("clang");

    SHU_ModuleBegin("exampleLib");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("dependencies/exampleLib/src/");
    SHU_ModuleCompileLibrary("build/lib");

    SHU_ModuleBegin("example");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("dependencies/exampleLib/include/");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleExecutableLinkLibrary("exampleLib");
    SHU_ModuleCompileExecutable("build/bin");

    return 0;
}