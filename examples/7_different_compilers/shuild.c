#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        return 1;
    }

    SHU_LogInfo("Compiler info which used to build the shuild source : %s : %d", SHUM_HOST_COMPILER_STRING, SHUM_HOST_COMPILER_VERSION);
    SHU_LogInfo("Compiler command which will be used to build the project : %s", argv[1]);

    SHU_CompilerTryConfigure(argv[1]);

    SHU_ModuleBegin("6_dynamic_library");
    SHU_ModuleAddSourcefile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}