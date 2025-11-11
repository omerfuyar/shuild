#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerConfigure("clang");
    SHU_CompilerAddFlags("-DFOO=13");

    SHU_ModuleBegin("1_single_source");
    SHU_ModuleAddSourcefile("example.c");

    SHU_ExecutableCompile("build/");

    return 0;
}