#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    To test this example, first compile shuild.c file and
    then run the outputted executable. This script will
    compile example.c for you.
*/

int main(void)
{
    // Provide the compiler to use for our build proccess.
    SHU_CompilerConfigure(SHUCompiler_GCC, "gcc");

    // Begin to configure module, A module can be a static/dynamic library or an executable.
    // I want to name it 'example' and root directory of it will be next to executable.
    // When the block ends, the module compiles, and its artifacts go to 'build/' relative to current executable directory.
    // Trailing path separator is not mandatory but definitely recommended.
    // This is NOT relative to modules root directory.
    SHU_MODULE("example", NULL, SHUModuleType_Executable, "build/")
    {
        // Get the file 'example.c' from the root directory of current module.
        SHU_ModuleAddSourceFiles("example.c");
    }

    return 0;
}
