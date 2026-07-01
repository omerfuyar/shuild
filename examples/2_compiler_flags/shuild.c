#define SHU_IMPLEMENTATION
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows that shuild can compile multiple
    modules as executables and use different flags while doing it.
*/

int main(void)
{
    SHU_CompilerConfigure(SHUM_COMPILER_CLANG, "gcc");

    // Append custom flags to the current compiler flags.
    SHU_CompilerAddFlags("-O0");
    SHU_CompilerAddFlags("-g -Wall");

    SHU_CompilerAddDefinitions("BAZ", NULL, "FOO", "\"foo,bar,baz\"");

    SHU_ModuleBegin("exampleDebug", NULL);
    SHU_ModuleAddSourceFile("example.c");

    // Leave the output directory NULL to set it current executable directory.
    SHU_ModuleCompile(NULL, SHUModuleType_Executable);

    // After compilation, all module configurations resets.
    // Compiler configuration doesn't change.

    // Clears all of the accumulated flags and starts a new buffer.
    SHU_CompilerSetFlags("-O3 -DNDEBUG");
    SHU_CompilerAddDefinitions("FOO", "\"this is debug foo\"");

    SHU_ModuleBegin("exampleRelease", NULL);
    SHU_ModuleAddSourceFile("example.c");

    // Same behaviour as the one above.
    SHU_ModuleCompile("", SHUModuleType_Executable);

    // Clear the flags entirely.
    SHU_CompilerClearFlags();

    return 0;
}