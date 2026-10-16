#define SHUC_NO_RUN_LOG
#define SHU_IMPLEMENTATION
#include "../../shu/shu.h"
#include "../shuild.h"

void ShuildShuild(const char *name, const char *arg)
{
    SHU_ModuleBegin("shuild", NULL);
    char buffer[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(buffer, SHUC_MAX_STRING_SIZE, "%s/shuild.c", name);
    SHU_ModuleAddSourceFile(buffer);
    SHU_ModuleCompile(name, SHUModuleType_Executable);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    snprintf(buffer, SHUC_MAX_STRING_SIZE, ".\\%s\\shuild.exe %s", name, arg == NULL ? "" : arg);
#else
    snprintf(buffer, SHUC_MAX_STRING_SIZE, "./%s/shuild %s", name, arg == NULL ? "" : arg);
#endif

    SHU_UtilRun("%s", buffer);
}

/// @brief The examples whose builds take arguments: each argument is given to a build of its own. The others build once, without one.
static const struct
{
    const char *name;
    const char *arguments[2];
} EXAMPLE_ARGUMENTS[] = {
    {"7_different_compilers", {"gcc", NULL}},
    {"10_compiler_helpers", {"d", "r"}},
};

/// @brief Builds an example: a directory whose name starts with its number, such as 1_single_source/.
void BuildExample(const char *path, SHUFileType type, void *data)
{
    (void)data;

    if (type != SHUFileType_Directory || path[0] < '0' || path[0] > '9')
    {
        return;
    }

    // the directory's name, without the separator at its end
    char name[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(name, sizeof(name), "%.*s", (int)strlen(path) - 1, path);

    for (usz i = 0; i < sizeof(EXAMPLE_ARGUMENTS) / sizeof(*EXAMPLE_ARGUMENTS); i++)
    {
        if (strcmp(EXAMPLE_ARGUMENTS[i].name, name) == 0)
        {
            for (usz j = 0; j < 2 && EXAMPLE_ARGUMENTS[i].arguments[j] != NULL; j++)
            {
                ShuildShuild(name, EXAMPLE_ARGUMENTS[i].arguments[j]);
            }

            return;
        }
    }

    ShuildShuild(name, NULL);
}

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_CompilerAddFlags(SHUM_FLAGS_WARNING_LOW);
    SHU_CompilerAddFlags("-Wno-unused-function -Wno-format-truncation" SHUM_FLAGS_DEBUG SHUM_FLAGS_STANDARD_C23);
    SHU_CompilerAddDefinitions("SHU_IMPLEMENTATION", NULL, "SHUC_NO_RUN_LOG", NULL);

    // every numbered directory beside this file is an example, built in the order of their names
    SHU_UtilListDirectory("", false, BuildExample, NULL);

    if (argc > 1) // run all
    {
        SHU_LogInfo("\n\n\nAll examples have been completed. Running all examples...\n\n");

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
        SHU_UtilRun("1_single_source\\build\\example.exe");
        SHU_UtilRun("2_compiler_flags\\exampleDebug.exe");
        SHU_UtilRun("2_compiler_flags\\exampleRelease.exe");
        SHU_UtilRun("3_main_arguments\\example.exe");
        SHU_UtilRun("4_folder_structures\\example.exe");
        SHU_UtilRun("5_static_library\\build\\bin\\example.exe");
        SHU_UtilRun("set PATH=6_dynamic_library\\build\\lib;%%PATH%% && 6_dynamic_library\\build\\bin\\example.exe");
        SHU_UtilRun("7_different_compilers\\examplegcc.exe");
        SHU_UtilRun("8_header_configuration\\example.exe");
        SHU_UtilRun("9_automate_builds\\example.exe");
        SHU_UtilRun("10_compiler_helpers\\example.exe d");
        SHU_UtilRun("10_compiler_helpers\\example.exe r");
        SHU_UtilRun("11_incremental_builds\\build\\bin\\example.exe");
        SHU_UtilRun("12_different_incrementals\\build\\debug\\example.exe");
        SHU_UtilRun("12_different_incrementals\\build\\release\\example.exe");
        SHU_UtilRun("13_utility_functions\\build\\example.exe");
        SHU_UtilRun("set PATH=14_linked_libraries\\build\\lib;%%PATH%% && 14_linked_libraries\\build\\bin\\example.exe");
        SHU_UtilRun("15_build_scripts\\tool\\build\\tool.exe");
#else
        SHU_UtilRun("./1_single_source/build/example");
        SHU_UtilRun("./2_compiler_flags/exampleDebug");
        SHU_UtilRun("./2_compiler_flags/exampleRelease");
        SHU_UtilRun("./3_main_arguments/example");
        SHU_UtilRun("./4_folder_structures/example");
        SHU_UtilRun("./5_static_library/build/bin/example");
        SHU_UtilRun("./6_dynamic_library/build/bin/example");
        SHU_UtilRun("./7_different_compilers/examplegcc");
        SHU_UtilRun("./8_header_configuration/example");
        SHU_UtilRun("./9_automate_builds/example");
        SHU_UtilRun("./10_compiler_helpers/example d");
        SHU_UtilRun("./10_compiler_helpers/example r");
        SHU_UtilRun("./11_incremental_builds/build/bin/example");
        SHU_UtilRun("./12_different_incrementals/build/debug/example");
        SHU_UtilRun("./12_different_incrementals/build/release/example");
        SHU_UtilRun("./13_utility_functions/build/example");
        SHU_UtilRun("./14_linked_libraries/build/bin/example");
        SHU_UtilRun("./15_build_scripts/tool/build/tool");
#endif
    }

    return 0;
}