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

    SHU_ModuleAddIncludeDirectory("build/");
    SHU_ModuleCompile("build/", SHUModuleType_Executable);

    return 0;
}
