#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows compiler detection.
    SHU_CompilerDetect lists the gcc and clang compilers on PATH: their versions, the systems and processors they compile for, and whether they have the sanitizers.
    SHU_CompilerConfigureTry with NULL picks the newest one that compiles for this system and its processor, of the family that compiled this script if PATH has one.
*/

int main(void)
{
    usz count = 0;
    SHUCompilerInfo *compilers = SHU_CompilerDetect(&count);

    for (usz i = 0; i < count; i++)
    {
        SHU_UtilLog(SHUM_LOG_NAME("%s") ": " SHUM_LOG_VALUE("%s %u.%u.%u") " for %s (%s), %s sanitizers",
                    compilers[i].command,
                    SHUCompiler_GetString(compilers[i].family),
                    compilers[i].version / 10000,
                    compilers[i].version / 100 % 100,
                    compilers[i].version % 100,
                    SHUPlatform_GetString(compilers[i].target),
                    compilers[i].machine,
                    compilers[i].sanitizers ? "with" : "without");
    }

    SHU_CompilerConfigureTry(NULL);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddSourceFiles("example.c");
    SHU_ModuleCompile("", SHUModuleType_Executable);

    return 0;
}
