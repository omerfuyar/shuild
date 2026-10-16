#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows libraries that link other libraries.
    A static library cannot be linked, so it keeps the libraries it links,
    and a module that links it gets them too, after it, in order.
    A dynamic library is linked with its libraries.
*/

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    // The static libraries are compiled into a dynamic library too, so their code must be position independent.
    SHU_CompilerAddFlags("-fPIC");

    SHU_ModuleBegin("numbers", "dependencies/numbers/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryStatic);

    // shapes uses numbers. It keeps the link, and the directory to find numbers in.
    SHU_ModuleBegin("shapes", "dependencies/shapes/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("../numbers/include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("numbers");
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryStatic);

    // report links only shapes, and is linked with numbers too.
    SHU_ModuleBegin("report", "dependencies/report/");
    SHU_ModuleAddIncludeDirectory("include/");
    SHU_ModuleAddIncludeDirectory("../shapes/include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("shapes");
    SHU_ModuleCompile("build/lib/", SHUModuleType_LibraryDynamic);

    // The executable links shapes and report. It gets numbers after shapes, so the linker finds what shapes needs.
    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddIncludeDirectory("dependencies/shapes/include/");
    SHU_ModuleAddIncludeDirectory("dependencies/report/include/");
    SHU_ModuleAddSourceFile("src/");
    SHU_ModuleAddLibraryDirectory("build/lib/");
    SHU_ModuleLinkLibrary("shapes");
    SHU_ModuleLinkLibrary("report");
    SHU_ModuleCompile("build/bin/", SHUModuleType_Executable);

    return 0;
}
