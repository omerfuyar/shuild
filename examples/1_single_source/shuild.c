#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    To test this example, first compile shuild.c file and
    then run the outputted executable. This script will
    compile example.c for you.
*/

int main(void)
{
    // Set shuild up with the newest compiler on PATH. Example 3 shows how to choose one.
    SHU_InitializeShuild();

    // Begin to configure module, A module can be a static/dynamic library or an executable.
    // I want to name it 'example' and root directory of it will be next to executable.
    // When the block ends, the module compiles, and its artifacts go to 'build/' relative to current executable directory.
    // Trailing path separator is not mandatory but definitely recommended.
    // This is NOT relative to modules root directory.
    SHU_Module("example", NULL, SHUModuleType_Executable, "build/")
    {
        // Get the file 'example.c' from the root directory of current module.
        SHU_ModuleAddSourceFiles("example.c");
    }

    return 0;
}
