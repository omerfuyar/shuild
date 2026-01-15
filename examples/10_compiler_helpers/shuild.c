#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");

    if (argc < 2)
    {
        printf("Wrong usage : use with argument d or r");
        return 1;
    }

    if (!strcmp("d", argv[1]))
    {
        SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG);
        SHU_CompilerAddFlags(SHUM_FLAGS_WARNING_HIGH SHUM_FLAGS_WARNING_ERROR);
    }
    else if (!strcmp("r", argv[1]))
    {
        SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH);
    }
    else
    {
        printf("Wrong usage : first argument must be d or r");
        return 1;
    }

    SHU_ModuleBegin("example");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    // Activate this line and save after compiling and running it for the first time, then you can directly run it.
    // SHU_LogInfo("This message is showed automatically!");

    return 0;
}