#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows utility functions for files and directories.
    The source files are found by listing a directory and matching their names,
    and a header is generated from what is found, before the module is compiled.
*/

static void AddSource(const char *path, SHUFileType type, void *data)
{
    usz *sourceCount = (usz *)data;

    // Paths are relative to current executable, like the ones other functions take.
    SHU_LogInfo("Found %s '%s'", type == SHUFileType_Directory ? "directory" : "file", path);

    if (type == SHUFileType_Regular && SHU_UtilMatch(path, "*.c"))
    {
        SHU_ModuleAddSourceFile(path);
        (*sourceCount)++;
    }
}

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_ModuleBegin("example", NULL);

    // Entries are given sorted by name, and with recursive, the directories inside are listed too.
    usz sourceCount = 0;
    SHU_UtilListDirectory("src/", true, AddSource, &sourceCount);

    // Files can be read and written whole.
    SHUSlice greeting = SHU_UtilReadFile("greeting.txt");

    char header[SHUC_MAX_MESSAGE_BUFFER_SIZE] = {0};
    int headerLength = snprintf(header, sizeof(header),
                                "#define SOURCE_COUNT %zu\n#define GREETING_SIZE %zu\n",
                                sourceCount,
                                greeting.size);
    free(greeting.data);

    SHU_UtilCreateDirectory("build/");
    SHU_UtilWriteFile("build/generated.h", csv(cs(header, (usz)headerLength)));

    // A file is copied into a directory under its own name. A file that has the content already is left as is, by copying and by writing,
    // so its edit time stays and what includes it does not compile again.
    SHU_UtilCopyFile("greeting.txt", "build/");
    SHU_Assert(SHU_UtilFileExists("build/greeting.txt") == SHUFileType_Regular, "The greeting is not copied.");

    // A command that may fail runs with SHU_UtilTryRun, which gives its exit code instead of stopping the build.
    i32 exitCode = SHU_UtilTryRun("exit 3");
    SHU_LogInfo("The command that may fail gave %d.", exitCode);

    SHU_ModuleAddIncludeDirectory("build/");
    SHU_ModuleCompile("build/", SHUModuleType_Executable);

    return 0;
}
