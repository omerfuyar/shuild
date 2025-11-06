#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    //===COMPILER===
    SHU_CompilerConfigure(argv[1]);
    SHU_CompilerAddFlags("-dfoo=13");
    SHU_CompilerSetFlags(""); // clears, this exists because different libraries/executables may require different flags

    //===LIBRARIES===
    SHU_ModuleBegin("libraryName");

    SHU_ModuleAddIncludeDirectory("lib/folder");
    SHU_ModuleAddSourcefile("lib/source.c");
    SHU_ModuleAddSourceDirectory("lib/src");

    SHU_LibraryCompile("build/lib"); // clears internal strings from begin... function

    //===EXECUTABLE===
    SHU_ModuleBegin("appName");
    SHU_ModuleAddIncludeDirectory("app/folder");
    SHU_ModuleAddSourcefile("app/source.c");
    SHU_ModuleAddSourceDirectory("app/src");

    SHU_ExecutableLink("m");
    SHU_ExecutableLink("build/lib/libraryName");

    SHU_ExecutableCompile("build/bin"); // clears internal strings from begin... function

    return 0;
}