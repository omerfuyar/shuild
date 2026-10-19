#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows compiler detection.
    SHU_CompilerDetect lists the gcc and clang compilers on PATH: their versions, the systems and processors they compile for, and whether they have the sanitizers.
    SHU_CompilerTryConfigure with NULL picks the newest one that compiles for this system and its processor, of the family that compiled this script if PATH has one.
*/

int main(void)
{
    usz count = 0;
    const SHUCompilerInfo *compilers = SHU_CompilerDetect(&count);

    for (usz i = 0; i < count; i++)
    {
        SHU_UtilLog(SHUM_LOG_NAME("%s") ": " SHUM_LOG_VALUE("%s %u.%u.%u") " for %s (%s), %s sanitizers",
                    compilers[i].command,
                    SHUM_COMPILER_GET_STRING(compilers[i].identifier),
                    compilers[i].version / 10000,
                    compilers[i].version / 100 % 100,
                    compilers[i].version % 100,
                    SHUM_PLATFORM_GET_STRING(compilers[i].target),
                    compilers[i].machine,
                    compilers[i].sanitizers ? "with" : "without");
    }

    SHU_CompilerTryConfigure(NULL);

    SHU_ModuleBegin("example", NULL);
    SHU_ModuleAddSourceFile("example.c");
    SHU_ModuleCompile("", SHUModuleType_Executable);

    return 0;
}
