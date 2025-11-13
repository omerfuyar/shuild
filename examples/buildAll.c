#define SHUILD_IMPLEMENTATION
#include "../shuild.h"

int main(void)
{
    SHU_CompilerTryConfigure("clang");

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("1_single_source/shuild.c");
    SHU_ModuleCompile("1_single_source/", SHUM_MODULE_EXECUTABLE);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("1_single_source\\shuild.exe");
#else
    SHU_Run("./1_single_source/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("2_compiler_flags/shuild.c");
    SHU_ModuleCompile("2_compiler_flags/", SHUM_MODULE_EXECUTABLE);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("2_compiler_flags\\shuild.exe");
#else
    SHU_Run("./2_compiler_flags/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("3_main_arguments/shuild.c");
    SHU_ModuleCompile("3_main_arguments/", SHUM_MODULE_EXECUTABLE);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("3_main_arguments\\shuild.exe");
#else
    SHU_Run("./3_main_arguments/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("4_folder_structures/shuild.c");
    SHU_ModuleCompile("4_folder_structures/", SHUM_MODULE_EXECUTABLE);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("4_folder_structures\\shuild.exe");
#else
    SHU_Run("./4_folder_structures/shuild");
#endif

    SHU_ModuleBegin("shuild");
    SHU_ModuleAddSourcefile("5_library_linking/shuild.c");
    SHU_ModuleCompile("5_library_linking/", SHUM_MODULE_EXECUTABLE);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("5_library_linking\\shuild.exe");
#else
    SHU_Run("./5_library_linking/shuild");
#endif

    return 0;
}