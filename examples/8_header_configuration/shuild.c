#define SHUC_NO_RUN_ERROR
#define SHUC_ARRAY_INITIAL_COUNT 8        // default 16
#define SHUC_MAX_STRING_SIZE 128          // default 256, all internal string operations uses this buffer size
#define SHUC_MAX_COMMAND_BUFFER_SIZE 8192 // default 4096, even though enough for most, big projects may require more
// #define SHUC_NO_MODULE_LOG
// #define SHUC_NO_RUN_LOG
#define SHUC_SHORT_LOG // Show minimal logs
#define SHU_IMPLEMENTATION
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
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    return 0;
}