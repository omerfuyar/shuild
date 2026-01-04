#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_Automate(argc, argv);

    SHU_ModuleBegin("example");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    // Activate this line and save after compiling and running it for the first time, then you can directly run it.
    // SHU_LogInfo("This message is showed automatically!");

    return 0;
}