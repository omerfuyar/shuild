#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows building a project
    with a include/ + src/ file structure.
*/

int main(void)
{
    SHU_CompilerConfigureTry("gcc");

    SHU_MODULE("example", NULL, SHUModuleType_Executable, NULL)
    {
        // Add preconfigred flags to add include directory for current module.
        //  Thats why should needs to know your compiler.
        // Path relative to current executable
        SHU_ModuleAddIncludeDirectories("include/");
        // Same function can be used
        SHU_ModuleAddSourceFiles("src/");
    }

    return 0;
}