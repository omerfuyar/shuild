#define SHU_IMPLEMENTATION
#include "shu/shu.h"
#include "shuild/shuild.h"

/*
    The build script of the tool, which the example's build script builds and runs in this directory.
    Its paths are relative to this directory, as they would be if it were run here by hand.
*/

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");

    // the build that runs it says which kind of build to make
    bool release = argc > 1 && strcmp(argv[1], "release") == 0;

    SHU_ModuleBegin("tool", NULL);
    SHU_CompilerAddDefinitions("BUILD_KIND", release ? "\"release\"" : "\"debug\"");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleCompile("build/", SHUModuleType_Executable);

    return 0;
}
