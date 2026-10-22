#define SHU_IMPLEMENTATION
#include "../../shu/shu.h"
#include "../shuild.h"

void ShuildShuild(const char *name, const char *arg)
{
    SHU_ModuleBegin("shuild", NULL);
    char *source = SHU_UtilFormat("%s/shuild.c", name);
    SHU_ModuleAddSourceFiles(source);
    SHU_ModuleCompile(name, SHUModuleType_Executable);
    free(source);

#if SHUM_HOST_WINDOWS
    SHU_UtilRun(".\\%s\\shuild.exe %s", name, arg == NULL ? "" : arg);
#else
    SHU_UtilRun("./%s/shuild %s", name, arg == NULL ? "" : arg);
#endif
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
    char *name = SHU_UtilFormat("%.*s", (int)strlen(path) - 1, path);
    bool built = false;

    for (usz i = 0; i < sizeof(EXAMPLE_ARGUMENTS) / sizeof(*EXAMPLE_ARGUMENTS) && !built; i++)
    {
        if (strcmp(EXAMPLE_ARGUMENTS[i].name, name) == 0)
        {
            for (usz j = 0; j < 2 && EXAMPLE_ARGUMENTS[i].arguments[j] != NULL; j++)
            {
                ShuildShuild(name, EXAMPLE_ARGUMENTS[i].arguments[j]);
            }

            built = true;
        }
    }

    if (!built)
    {
        ShuildShuild(name, NULL);
    }

    free(name);
}

int main(int argc, char **argv)
{
    SHU_CompilerConfigureTry("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_CompilerAddFlags(SHUM_FLAGS_WARNING_LOW, "-Wno-unused-function", "-Wno-format-truncation", SHUM_FLAGS_DEBUG, SHUM_FLAGS_STANDARD_C23);
    SHU_CompilerAddDefinitions("SHU_IMPLEMENTATION", NULL);

    // every numbered directory beside this file is an example, built in the order of their names
    SHU_UtilListDirectory("", false, BuildExample, NULL);

    if (argc > 1) // run all
    {
        SHU_UtilLog("all examples are built; running them");

#if SHUM_HOST_WINDOWS
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
        SHU_UtilRun("16_compiler_detection\\example.exe");
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
        SHU_UtilRun("./16_compiler_detection/example");
#endif
    }

    return 0;
}