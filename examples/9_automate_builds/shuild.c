#define SHU_IMPLEMENTATION
#include "../../shuild.h"

/*
    This example shows Automate function and it's usage.
*/

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    // Even automate function must be called after compiler configuration.
    SHU_UtilAutomate(argc, argv);

    SHU_ModuleBegin("example", "");
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUM_MODULE_EXECUTABLE);

    // Compile this program without the code below,
    // activate this line and save, then you can directly run it.
    // It will automatically rebuild itself and show the message.
    // SHU_LogInfo(SHUM_COLOR_GREEN("This message is showed after auto build!"));

    return 0;
}