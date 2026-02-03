#define SHUILD_IMPLEMENTATION
#include "../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_Automate(argc, argv);

    SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG);
    SHU_CompilerAddFlags("-Wno-unused-function -Wno-format-truncation");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("1_single_source/shuild.c");
    SHU_ModuleCompile("1_single_source/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("1_single_source\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("2_compiler_flags/shuild.c");
    SHU_ModuleCompile("2_compiler_flags/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("2_compiler_flags\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("3_main_arguments/shuild.c");
    SHU_ModuleCompile("3_main_arguments/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("3_main_arguments\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("4_folder_structures/shuild.c");
    SHU_ModuleCompile("4_folder_structures/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("4_folder_structures\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("5_static_library/shuild.c");
    SHU_ModuleCompile("5_static_library/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("5_static_library\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("6_dynamic_library/shuild.c");
    SHU_ModuleCompile("6_dynamic_library/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("6_dynamic_library\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("7_different_compilers/shuild.c");
    SHU_ModuleCompile("7_different_compilers/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("7_different_compilers\\shuild.exe gcc");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("8_header_configuration/shuild.c");
    SHU_ModuleCompile("8_header_configuration/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("8_header_configuration\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("9_automate/shuild.c");
    SHU_ModuleCompile("9_automate/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("9_automate\\shuild.exe");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("10_compiler_helpers/shuild.c");
    SHU_ModuleCompile("10_compiler_helpers/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("10_compiler_helpers\\shuild.exe d");
    SHU_Run("10_compiler_helpers\\shuild.exe r");

    SHU_ModuleBegin("shuild", "");
    SHU_ModuleAddSourceFile("11_incremental_builds/shuild.c");
    SHU_ModuleCompile("11_incremental_builds/", SHUM_MODULE_EXECUTABLE);
    SHU_Run("11_incremental_builds\\shuild");

    if (argc > 1) // run all
    {
        SHU_LogInfo("\n\n\nAll examples are built. Running all examples...\n\n");
        SHU_Run("1_single_source\\build\\example.exe");
        SHU_Run("2_compiler_flags\\exampleDebug.exe");
        SHU_Run("2_compiler_flags\\exampleRelease.exe");
        SHU_Run("3_main_arguments\\example.exe");
        SHU_Run("4_folder_structures\\example.exe");
        SHU_Run("5_static_library\\build\\bin\\example.exe");
        SHU_Run("set PATH=6_dynamic_library\\build\\lib;%%PATH%% && 6_dynamic_library\\build\\bin\\example.exe");
        SHU_Run("7_different_compilers\\examplegcc.exe");
        SHU_Run("8_header_configuration\\example.exe");
        SHU_Run("9_automate\\example.exe");
        SHU_Run("10_compiler_helpers\\example.exe d");
        SHU_Run("10_compiler_helpers\\example.exe r");
        SHU_Run("11_incremental_builds\\build\\bin\\example");
    }

    return 0;
}