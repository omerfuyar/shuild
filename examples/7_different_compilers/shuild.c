#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

/*
    This example shows shuild logic combined with C.
*/

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    SHU_LogInfo("Compiler info which used to build the shuild source : %s : %d", SHUM_HOST_COMPILER_STRING, SHUM_HOST_COMPILER_VERSION);
    SHU_LogInfo("Compiler command which will be used to build the project : %s", argv[1]);

    SHU_CompilerTryConfigure(argv[1]);

    char buffer[32] = {0};
    snprintf(buffer, sizeof(buffer), "example%s", argv[1]);

    // totally dynamic/runtime configurations

    SHU_ModuleBegin(buffer, NULL);
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}