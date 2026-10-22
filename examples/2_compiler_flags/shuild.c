#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows that shuild can compile multiple
    modules as executables and use different flags while doing it.
*/

int main(void)
{
    SHU_CompilerConfigure(SHUCompiler_GCC, "gcc");

    // Append custom flags to the current compiler flags.
    SHU_CompilerAddFlags("-O0");
    SHU_CompilerAddFlags("-g -Wall");

    SHU_CompilerAddDefinitions("BAZ", NULL, "FOO", "\"foo,bar,baz\"");

    // Leave the output directory NULL to set it current executable directory.
    SHU_MODULE("exampleDebug", NULL, SHUModuleType_Executable, NULL)
    {
        SHU_ModuleAddSourceFiles("example.c");
    }

    // After compilation, all module configurations resets.
    // Compiler configuration doesn't change.

    // Clears all of the accumulated flags, and adds new ones.
    SHU_CompilerClearFlags();
    SHU_CompilerAddFlags("-O3 -DNDEBUG");
    SHU_CompilerAddDefinitions("FOO", "\"this is debug foo\"");

    // An empty output directory has the same behaviour as the one above.
    SHU_MODULE("exampleRelease", NULL, SHUModuleType_Executable, "")
    {
        SHU_ModuleAddSourceFiles("example.c");
    }

    // Clear the flags entirely.
    SHU_CompilerClearFlags();

    return 0;
}