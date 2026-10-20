#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows libraries that link other libraries.
    A static library cannot be linked, so it keeps the libraries it links,
    and a module that links it gets them too, after it, in order.
    A dynamic library is linked with its libraries.
    A library's public include directories go to the modules that link it themselves,
    but not to the ones that get it through another library.
    Each library's file name follows the system the compiler compiles for, so a cross compiler, such as
    x86_64-w64-mingw32-gcc given as the argument, makes Windows' files: libnumbers.a, report.dll and example.exe.
*/

int main(int argc, char **argv)
{
    SHU_CompilerConfigureTry(argc > 1 ? argv[1] : "gcc");

    // The static libraries are compiled into a dynamic library too, so their code must be position independent, except for Windows, where it always is.
    if (SHU_CompilerGetTarget() != SHUPlatform_Windows)
    {
        SHU_CompilerAddFlags("-fPIC");
    }

    SHU_ModuleBegin("numbers", "dependencies/numbers/");
    SHU_ModuleAddPublicIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryStatic);

    // shapes uses numbers, and gets its headers by linking it. It keeps the link, and the directory to find numbers in.
    SHU_ModuleBegin("shapes", "dependencies/shapes/");
    SHU_ModuleAddPublicIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("numbers");
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryStatic);

    // Linker flags go to linking alone, so the compiler does not warn that they are unused. With this one, a dynamic library that uses a function no library it links has fails to link,
    // instead of when it is loaded. macOS's linker refuses such libraries already.
    if (SHU_CompilerGetTarget() != SHUPlatform_MacOS)
    {
        SHU_CompilerAddLinkerFlags("-Wl,--no-undefined");
    }

    // report links only shapes, and is linked with numbers too. It gets shapes' headers, but not numbers', which it does not use.
    SHU_ModuleBegin("report", "dependencies/report/");
    SHU_ModuleAddPublicIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("shapes");
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryDynamic);

    // The executable links shapes and report, and gets their headers. Functions that add to a module take one value or more. It gets numbers after shapes, so the linker finds what shapes needs.
    // On Linux and macOS, it finds report in ../lib/, from its own directory. On Windows, a program finds its DLLs beside itself, so report is copied there.
    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("shapes", "report");

    if (SHU_CompilerGetTarget() == SHUPlatform_Windows)
    {
        SHU_ModuleCopyDynamicLinks();
    }

    SHU_ModuleCompile("build/bin/", SHUModuleType_Executable);

    char *numbers = SHU_UtilLibraryFile("numbers", SHUModuleType_LibraryStatic);
    char *report = SHU_UtilLibraryFile("report", SHUModuleType_LibraryDynamic);
    SHU_UtilLog("the library files are " SHUM_LOG_PATH("%s") " and " SHUM_LOG_PATH("%s"), numbers, report);
    free(numbers);
    free(report);

    return 0;
}
