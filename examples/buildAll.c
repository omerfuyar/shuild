#define SHUILD_IMPLEMENTATION
#include "../shuild.h"

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("clang");
    SHU_Automate(argc, argv);

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("1_single_source/shuild.c");
    SHU_ModuleCompile("1_single_source/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("1_single_source\\shuild.exe");
#else
    SHU_Run("./1_single_source/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("2_compiler_flags/shuild.c");
    SHU_ModuleCompile("2_compiler_flags/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("2_compiler_flags\\shuild.exe");
#else
    SHU_Run("./2_compiler_flags/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("3_main_arguments/shuild.c");
    SHU_ModuleCompile("3_main_arguments/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("3_main_arguments\\shuild.exe");
#else
    SHU_Run("./3_main_arguments/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("4_folder_structures/shuild.c");
    SHU_ModuleCompile("4_folder_structures/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("4_folder_structures\\shuild.exe");
#else
    SHU_Run("./4_folder_structures/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("5_static_library/shuild.c");
    SHU_ModuleCompile("5_static_library/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("5_static_library\\shuild.exe");
#else
    SHU_Run("./5_static_library/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("6_dynamic_library/shuild.c");
    SHU_ModuleCompile("6_dynamic_library/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("6_dynamic_library\\shuild.exe clang");
#else
    SHU_Run("./6_dynamic_library/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("7_different_compilers/shuild.c");
    SHU_ModuleCompile("7_different_compilers/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("7_different_compilers\\shuild.exe clang");
#else
    SHU_Run("./7_different_compilers/shuild clang");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("8_header_configuration/shuild.c");
    SHU_ModuleCompile("8_header_configuration/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("8_header_configuration\\shuild.exe clang");
#else
    SHU_Run("./8_header_configuration/shuild clang");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("9_automate/shuild.c");
    SHU_ModuleCompile("9_automate/", SHUM_MODULE_EXECUTABLE);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("9_automate\\shuild.exe clang");
#else
    SHU_Run("./9_automate/shuild");
#endif

    return 0;
}