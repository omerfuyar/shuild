#define SHUC_NO_RUN_ERROR
#define SHUC_ARRAY_INITIAL_COUNT 8        // default 16
#define SHUC_MAX_JOB_COUNT 4             // default 64, at most as many files compile at a time as there are processors
// #define SHUC_NO_MODULE_LOG             // leaves out the line each module logs
#define SHUC_LOG_COMMANDS                 // logs each command, not only the ones that fail
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows configuration capabilities of shuild header.
    You can find all configurations at the very top of the shuild.h file.
*/

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUModuleType_Executable);

    return 0;
}