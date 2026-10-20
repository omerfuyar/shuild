#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows a build script that builds another one, as for a project inside this one.
    The other script is compiled with the configured compiler, and runs in its own directory with the arguments it is given.
*/

int main(int argc, char **argv)
{
    SHU_CompilerConfigureTry("gcc");
    SHU_UtilAutomate(argc, argv);

    // The flags are the other script's include directories, where shu/ and shuild/ are; the arguments go to its main.
    char *flags = SHU_UtilFormat("-I%s../../../", SHU_UtilGetExecutablePath());
    SHU_UtilBuildScript("tool/shuild.c", "tool/shuild", flags, "release");
    free(flags);

    return 0;
}
