#define SHUC_SHORT_LOG
#define SHU_IMPLEMENTATION
#include "../shuild.h"

void ShuildShuild(const char *name, const char *arg)
{
    SHU_ModuleBegin("shuild", NULL);
    char buffer[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(buffer, SHUC_MAX_STRING_SIZE, "%s/shuild.c", name);
    SHU_ModuleAddSourceFile(buffer);
    SHU_ModuleCompile(name, SHUM_MODULE_EXECUTABLE);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    snprintf(buffer, SHUC_MAX_STRING_SIZE, ".\\%s\\shuild.exe %s", name, arg == NULL ? "" : arg);
#else
    snprintf(buffer, SHUC_MAX_STRING_SIZE, "./%s/shuild %s", name, arg == NULL ? "" : arg);
#endif

    SHU_UtilRun(buffer);
}

// todo automatically search and build in directory examples.

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH);
    SHU_CompilerAddFlags("-Wno-unused-function -Wno-format-truncation");

    ShuildShuild("1_single_source", NULL);
    ShuildShuild("2_compiler_flags", NULL);
    ShuildShuild("3_main_arguments", NULL);
    ShuildShuild("4_folder_structures", NULL);
    ShuildShuild("5_static_library", NULL);
    ShuildShuild("6_dynamic_library", NULL);
    ShuildShuild("7_different_compilers", "gcc");
    ShuildShuild("8_header_configuration", NULL);
    ShuildShuild("9_automate_builds", NULL);
    ShuildShuild("10_compiler_helpers", "d");
    ShuildShuild("10_compiler_helpers", "r");
    ShuildShuild("11_incremental_builds", NULL);
    ShuildShuild("12_different_incrementals", NULL);

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
#endif
    }

    return 0;
}