#define SHU_IMPLEMENTATION
#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a project
    with a include/ + src/ file structure.
*/

int main(void)
{
    SHU_CompilerTryConfigure("gcc");

    SHU_ModuleBegin("example", NULL);

    // Add preconfigred flags to add include directory for current module.
    //  Thats why should needs to know your compiler.
    // Path relative to current executable
    SHU_ModuleAddIncludeDirectory("include/");
    // Same function can be used
    SHU_ModuleAddSourceFile("src/");

    SHU_ModuleCompile(NULL, SHUModuleType_Executable);

    return 0;
}