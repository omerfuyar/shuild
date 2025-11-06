#define SHUILD_IMPLEMENTATION
#include "../../shuild.h"

int main(int argc, char **argv)
{
    //===COMPILER===
    SHU_CompilerConfigure(argv[1]);
    SHU_CompilerAddFlags("-dfoo=13");
    SHU_CompilerSetFlags(""); // clears, this exists because different libraries/executables may require different flags

    //===LIBRARIES===
    SHU_LibraryBegin("libraryName");

    SHU_IncludeAddDirectory("lib/folder");
    SHU_SourceAddfile("lib/source.c");
    SHU_SourceAddDirectory("lib/src");

    SHU_LibraryCompile("build/lib"); // clears internal strings from begin... function

    //===EXECUTABLE===
    SHU_ExecutableBegin("appName");

    SHU_IncludeAddDirectory("app/folder");
    SHU_SourceAddfile("app/source.c");
    SHU_SourceAddDirectory("app/src");

    SHU_ExecutableLink("m");
    SHU_ExecutableLink("libraryName");

    SHU_ExecutableCompile("build/bin"); // clears internal strings from begin... function

    return 0;
}