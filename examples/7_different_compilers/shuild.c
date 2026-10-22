#include "../../../shu/shu.h"
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

    SHU_UtilLog("the build script was compiled by " SHUM_LOG_VALUE("%s %d"), SHUCompiler_GetString(SHUM_HOST_COMPILER), SHUM_HOST_COMPILER_VERSION);
    SHU_UtilLog("the project is compiled by " SHUM_LOG_VALUE("%s"), argv[1]);

    SHU_CompilerConfigureTry(argv[1]);

    char buffer[32] = {0};
    snprintf(buffer, sizeof(buffer), "example%s", argv[1]);

    // totally dynamic/runtime configurations

    SHU_MODULE(buffer, NULL, SHUModuleType_Executable, "")
    {
        SHU_ModuleAddSourceFiles("example.c");
    }

    return 0;
}