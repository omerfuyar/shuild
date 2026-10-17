// You can define various macros to configure Shuild before including this file.
// define SHU_IMPLEMENTATION in one file to include the implementation.
// define SHUC_ENABLE_INCREMENTAL to enable incremental builds.
// define SHUC_NO_MODULE_LOG to leave out the line that each module logs when it compiles.
// define SHUC_LOG_COMMANDS to log each command that runs. Otherwise a command is logged only when it fails.
// define SHUC_NO_RUN_ERROR to disable termination on run error.
// define SHUC_MAX_JOB_COUNT 1 to compile one file at a time instead of as many as there are processors.
// define SHUC_MAX_<...> <limit> to customize limits.

// todo add macro helpers like module(...){...} for easy module begin and compile, like shujsn, shuarg or clay.
// todo rename macros to SHUILD_<...>

#pragma once

#ifndef SHU_HEADER
#ifdef SHU
#include SHU
#else
#include "../shu/shu.h"
#endif
#endif

/// @brief Build flags to build shuild.c files
#define SHUILD_BUILD " -O3 -Wno-format-truncation"

#pragma region Platform Detection

#define SHUM_PLATFORM_UNKNOWN 0
#define SHUM_PLATFORM_WINDOWS 1
#define SHUM_PLATFORM_LINUX 2
#define SHUM_PLATFORM_MACOS 3

#if defined(_WIN32)
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_WINDOWS
#elif defined(__linux__)
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_MACOS
#else
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_UNKNOWN
#endif

/// @brief Get the name of the given platform.
#define SHUM_PLATFORM_GET_STRING(platform) (platform == SHUM_PLATFORM_LINUX     ? "Linux"   \
                                            : platform == SHUM_PLATFORM_WINDOWS ? "Windows" \
                                            : platform == SHUM_PLATFORM_MACOS   ? "MacOS"   \
                                                                                : "Unknown")

/// @brief Either the given platform is the host compiler or not.
#define SHUM_PLATFORM_IS_HOST(platform) (SHUM_HOST_PLATFORM == platform)

#pragma endregion Platform Detection

#pragma region Compiler Detection

#define SHUM_COMPILER_UNKNOWN 0
#define SHUM_COMPILER_CLANG 1
#define SHUM_COMPILER_GCC 2

#if defined(__clang__)
/// @brief Current host compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_HOST_COMPILER SHUM_COMPILER_CLANG
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
/// @brief Current host compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_HOST_COMPILER SHUM_COMPILER_GCC
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
/// @brief Current host compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_HOST_COMPILER SHUM_COMPILER_UNKNOWN
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION 0
#endif

/// @brief Get the name of the given compiler.
#define SHUM_COMPILER_GET_STRING(compiler) (compiler == SHUM_COMPILER_CLANG ? "Clang" \
                                            : compiler == SHUM_COMPILER_GCC ? "GCC"   \
                                                                            : "Unknown")

/// @brief Get the command of the given compiler.
#define SHUM_COMPILER_GET_COMMAND(compiler) (compiler == SHUM_COMPILER_CLANG ? "clang" \
                                             : compiler == SHUM_COMPILER_GCC ? "gcc"   \
                                                                             : "Unknown")

/// @brief Either the given compiler is the host compiler or not.
#define SHUM_COMPILER_IS_HOST(compiler) (SHUM_HOST_COMPILER == compiler)

#pragma endregion Compiler Detection

#pragma region Configurations and Constants

#ifndef SHUC_ARRAY_INITIAL_COUNT
#define SHUC_ARRAY_INITIAL_COUNT 16
#endif

#ifndef SHUC_ARRAY_RESIZE_FACTOR
#define SHUC_ARRAY_RESIZE_FACTOR 2.0f
#endif

#ifndef SHUC_MAX_JOB_COUNT
#define SHUC_MAX_JOB_COUNT 64
#endif

#ifndef SHUC_MAX_HASH_BUFFER_SIZE
#define SHUC_MAX_HASH_BUFFER_SIZE 32
#endif

#ifdef SHUC_ENABLE_INCREMENTAL
#define SHUC_DEFAULT_CACHE_DIRECTORY ".shu/"

#ifndef SHUC_MODULE_FILE_EXTENSION
#define SHUC_MODULE_FILE_EXTENSION "shum"
#endif
#endif

#ifndef SHUC_FILE_EXTENSION
#define SHUC_FILE_EXTENSION "shu"
#endif

#define SHUM_FLAGS_DEBUG " -g"

#define SHUM_FLAGS_OPTIMIZATION_DEBUG " -Og"
#define SHUM_FLAGS_OPTIMIZATION_SIZE " -Os"
#define SHUM_FLAGS_OPTIMIZATION_LOW " -O1"
#define SHUM_FLAGS_OPTIMIZATION_MID " -O2"
#define SHUM_FLAGS_OPTIMIZATION_HIGH " -O3"

#define SHUM_FLAGS_WARNING_LOW " -Wall -Wextra"
#define SHUM_FLAGS_WARNING_MID " -Wall -Wextra -Wshadow -Wpedantic -Wconversion -Wformat=2 -fstack-protector-strong"
#define SHUM_FLAGS_WARNING_HIGH " -Wall -Wextra -Wshadow -Wpedantic -Wconversion -fstack-protector-strong -Wpointer-arith -Wcast-align -Wcast-qual -Wformat=2 -Winit-self -Wmissing-declarations -Wredundant-decls -Wsign-conversion -Wpointer-to-int-cast -Wint-to-pointer-cast"
#define SHUM_FLAGS_WARNING_ERROR " -Werror"

#define SHUM_FLAGS_STANDARD_C89 " -std=c89"
#define SHUM_FLAGS_STANDARD_C99 " -std=c99"
#define SHUM_FLAGS_STANDARD_C11 " -std=c11"
#define SHUM_FLAGS_STANDARD_C17 " -std=c17"
#define SHUM_FLAGS_STANDARD_C23 " -std=c23"
#define SHUM_FLAGS_STANDARD_C2Y " -std=c2y"
#define SHUM_FLAGS_STANDARD_C2X " -std=c2x"

#define SHUM_COLOR_RESET "\x1b[0m"
#define SHUM_COLOR_RED(string) "\x1b[31m" string SHUM_COLOR_RESET
#define SHUM_COLOR_GREEN(string) "\x1b[32m" string SHUM_COLOR_RESET
#define SHUM_COLOR_YELLOW(string) "\x1b[33m" string SHUM_COLOR_RESET
#define SHUM_COLOR_BLUE(string) "\x1b[34m" string SHUM_COLOR_RESET
#define SHUM_COLOR_MAGENTA(string) "\x1b[35m" string SHUM_COLOR_RESET
#define SHUM_COLOR_CYAN(string) "\x1b[36m" string SHUM_COLOR_RESET
#define SHUM_COLOR_WHITE(string) "\x1b[37m" string SHUM_COLOR_RESET
#define SHUM_COLOR_BOLD(string) "\x1b[1m" string SHUM_COLOR_RESET

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
#define SHUM_PATH_SEPARATOR '\\'
#define SHUM_PATH_SEPARATOR_STR "\\"
#else
#define SHUM_PATH_SEPARATOR '/'
#define SHUM_PATH_SEPARATOR_STR "/"
#endif

#pragma endregion Configurations and Constants

#pragma region Declarations

typedef enum SHUFileType
{
    SHUFileType_Invalid,
    SHUFileType_Regular,
    SHUFileType_Directory,
} SHUFileType;

typedef enum SHUModuleType
{
    SHUModuleType_Executable,
    SHUModuleType_LibraryStatic,
    SHUModuleType_LibraryDynamic,
} SHUModuleType;

/// @brief A compiler that SHU_CompilerDetect found.
typedef struct SHUCompilerInfo
{
    const char *command; // the name it runs by, as found on PATH (eg. gcc-14, x86_64-w64-mingw32-clang)
    u8 identifier;       // SHUM_COMPILER_<...>
    u8 target;           // the system it compiles for, SHUM_PLATFORM_<...>
    u32 version;         // major * 10000 + minor * 100 + patch, as SHUM_HOST_COMPILER_VERSION
    bool sanitizers;     // it compiles and links a program with -fsanitize=address,undefined
} SHUCompilerInfo;

/// @brief Function that SHU_UtilListDirectory calls for each entry.
/// @param path Path of the entry, relative to current executable. Directories end with a separator. (eg. src/utils/)
/// @param type Type of the entry.
/// @param data Data given to SHU_UtilListDirectory.
typedef void (*SHUListFunction)(const char *path, SHUFileType type, void *data);

#define SHUModuleType_GetString(module) (module == SHUModuleType_Executable       ? "Executable"      \
                                         : module == SHUModuleType_LibraryStatic  ? "Static Library"  \
                                         : module == SHUModuleType_LibraryDynamic ? "Dynamic Library" \
                                                                                  : "Unknown")

#pragma region Utility

///!!! This function is not meant to be used directly. Use SHU_UtilAutomate macro instead. !!!
void SHUI_UAutomate(int argc, char **argv, const char *sourceName);

/// @brief Enables autonomously rebuilding the build script when the source or header is edited. It works only if the build system is one script. Run after configuring the compiler.
/// @param argc Argument count from main function.
/// @param argv Argument array from main function.
#define SHU_UtilAutomate(argc, argv) SHUI_UAutomate(argc, argv, __FILE__)

/// @brief Formats a string, as printf does, into new memory. Shuild never frees its memory, as the system frees it when the build exits, so the string stays valid.
/// @param format Format of the string. (eg. "%sbin/", directory)
/// @return The new string.
char *SHU_UtilFormat(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Internal command runner function.
/// @param command Command to run with the shell, through system. (eg. clang example.c -o example) Modules run the compiler without a shell.
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
i32 SHU_UtilRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a command like SHU_UtilRun, but its failure does not stop the build, even without SHUC_NO_RUN_ERROR. Use it for a command that may fail.
/// @param command Command to run with the shell, through system. (eg. ./tests --quick)
/// @return Exit code of the command.
i32 SHU_UtilTryRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a command like SHU_UtilRun, with its output and errors written to a log file in place of the terminal. When the command fails, the end of the log is shown.
/// @param log Log file to write, relative to current executable. Its directory is created if it doesn't exist. (eg. .shu/cmake.log)
/// @param command Command to run with the shell, through system. (eg. cmake --build build/)
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
i32 SHU_UtilRunLogged(const char *log, const char *commandFormat, ...) __attribute__((format(printf, 2, 3)));

/// @brief Builds another build script and runs it in its own directory, as for a project inside this one. The script is compiled with the configured compiler and SHUILD_BUILD.
/// @param script Build script to compile, relative to current executable. (eg. plugins/shuild.c)
/// @param program Program to compile it into, relative to current executable, without .exe. (eg. plugins/shuild)
/// @param flags More flags for the compiler, such as the script's include directories, or an empty string. (eg. -Idependencies)
/// @param arguments Arguments for the program, or an empty string. (eg. -b release)
void SHU_UtilBuildScript(const char *script, const char *program, const char *flags, const char *arguments);

/// @brief Spawns a new process synchronously.
/// @param executable Path to executable.
/// @param argv Arguments array (NULL terminated).
/// @return Exit code of the process.
i32 SHU_UtilSpawnProcessSync(const char *executable, char *const *argv);

/// @brief Platform-specific helper to get executable path.
/// @return Address of the executable path string. Do not free or edit it.
const char *SHU_UtilGetExecutablePath(void);

/// @brief Checks if a file exist in the environment.
/// @param file File to check.
/// @return SHUM_FILE_<...> macro accordingly.
SHUFileType SHU_UtilFileExists(const char *file);

/// @brief Creates a directory relative to current executable if the directory doesn't exists.
/// @param directory Directory to create (eg. resources/)
void SHU_UtilCreateDirectory(const char *directory);

/// @brief Deletes a file or directory recursively.
/// @param file File to delete. Relative to current executable.
void SHU_UtilDeleteFile(const char *file);

/// @brief Copies a file into a directory, or a directory's contents into a directory recursively. A file that has the same content already is left as is, so its edit time stays and what includes it does not compile again. Copies keep the file's permissions on Linux and macOS.
/// @param file File or directory to copy, relative to current executable. (eg. include/foo.h or resources/)
/// @param directory Directory to copy into, relative to current executable. It is created if it doesn't exist. (eg. build/include/)
void SHU_UtilCopyFile(const char *file, const char *directory);

/// @brief Renames a file.
/// @param file File to rename.
/// @param name New name of the file.
void SHU_UtilRenameFile(const char *file, const char *name);

/// @brief Gets the edit time of a file.
/// @param file File to get time of edit.
/// @return Timestamp of the file if found.
i64 SHU_GetFileEditTime(const char *file);

/// @brief Calls a function for each entry of a directory, sorted by name. Entries whose names start with a dot are left out.
/// @param directory Directory to list, relative to current executable. Leave it empty string to list the executable's directory. (eg. src/)
/// @param recursive Lists the directories inside too, each right after its own entry.
/// @param function Function to call for each entry.
/// @param data Data to give to function. Can be NULL.
void SHU_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data);

/// @brief Checks if a string matches a pattern, where '*' matches any characters and '?' matches one. (eg. "*.c" or "test_?.lua")
/// @param string String to check, like a file name.
/// @param pattern Pattern to match.
/// @return Either the string matches the pattern or not.
bool SHU_UtilMatch(const char *string, const char *pattern);

/// @brief Reads a whole file.
/// @param file File to read, relative to current executable.
/// @return Slice of the file's contents, followed by a terminating zero that the size does not count. It stays valid until the build exits.
SHUSlice SHU_UtilReadFile(const char *file);

/// @brief Writes a file, replacing it if it exists. A file that has the content already is left as is, so its edit time stays and what includes it does not compile again.
/// @param file File to write, relative to current executable.
/// @param content Content to write.
void SHU_UtilWriteFile(const char *file, SHUSliceView content);

/// @brief Gets the file name that shuild gives a library on the system the compiler compiles for. A module links it as -l<name> on every system.
/// Linux: libname.a and libname.so. macOS: libname.a and libname.dylib. Windows, with MinGW's gcc or LLVM: libname.a, and name.dll with its import library libname.dll.a.
/// @param name Name of the library's module. (eg. math)
/// @param type SHUModuleType_LibraryStatic or SHUModuleType_LibraryDynamic.
/// @return The file name, without a directory. (eg. libmath.so)
char *SHU_UtilLibraryFile(const char *name, SHUModuleType type);

#pragma endregion Utility

#ifdef SHUC_ENABLE_INCREMENTAL

#pragma region Cache

/// @brief Configures the cache directory for incremental builds.
/// @param cacheDirectory Cache directory relative to current executable.
void SHU_CacheConfigure(const char *cacheDirectory);

/// @brief Clears the cache for a module
/// @param moduleName Name of the module whose cache directory should be cleared.
void SHU_CacheClearModule(const char *moduleName);

/// @brief Clears the cache directory.
void SHU_CacheClearAll(void);

#pragma endregion Cache

#endif

#pragma region Compiler

/// @brief Configures the compiler to be used for compiling modules. Must be called before any other function. See SHU_CompilerTryConfigure for easier configuration.
/// @param compiler Compiler specifier. Use with SHUM_COMPILER_<...> macros.
/// @param compilerCommand Command to invoke the compiler. (eg. clang)
void SHU_CompilerConfigure(u8 compiler, const char *compilerCommand);

/// @brief Tries to configure the compiler by checking gcc or clang substring inside the string.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc).
/// If NULL or empty, the newest compiler on PATH that compiles for the host is used, of the family that compiled shuild.c if there is one, as SHU_CompilerDetect finds it;
/// without one, the host compiler's own command. (eg. gcc-14 when gcc is gcc 13)
void SHU_CompilerTryConfigure(const char *compilerCommand);

/// @brief Finds the gcc and clang compilers on PATH, cross compilers such as x86_64-w64-mingw32-gcc included, and asks each for its version and its target.
/// Each that compiles for the host is also tried with the sanitizers, by compiling a small program. The first of each name on PATH is kept.
/// @param retCount Number of compilers found. Must not be NULL.
/// @return The compilers, sorted by name. Valid until the build exits.
const SHUCompilerInfo *SHU_CompilerDetect(usz *retCount);

///!!! This function is not meant to be used directly. Use SHU_CompilerAddFlags macro instead. !!!
void SHUI_CompilerAddFlags(const char *flags, ...);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add, one string or more. Each can include multiple flags separated by spaces as you want, quoted as in a shell. On Windows, a backslash escapes only a quote, so paths keep theirs. (eg. "-DFOO=31", "-Wall")
#define SHU_CompilerAddFlags(flags, ...) SHUI_CompilerAddFlags(flags, ##__VA_ARGS__, NULL)

/// @brief Clears the compiler and linker flags, and sets the compiler flags.
/// @param flags Flags to set. Can include multiple flags separated by spaces as you want.
void SHU_CompilerSetFlags(const char *flags);

/// @brief Clears the current compiler flags, and the linker flags.
void SHU_CompilerClearFlags(void);

///!!! This function is not meant to be used directly. Use SHU_CompilerAddLinkerFlags macro instead. !!!
void SHUI_CompilerAddLinkerFlags(const char *flags, ...);

/// @brief Adds flags that only linking gets, not compiling, so the compiler does not warn that they are unused.
/// @param flags Flags to add, one string or more, written as SHU_CompilerAddFlags takes them. (eg. "-Wl,--as-needed")
/// @note Executables and dynamic libraries are linked with them; SHU_CompilerClearFlags clears them.
#define SHU_CompilerAddLinkerFlags(flags, ...) SHUI_CompilerAddLinkerFlags(flags, ##__VA_ARGS__, NULL)

/// @brief Gets the current configured compiler flags.
/// @param buffer Slice to write the flags string into. buffer.data must not be NULL.
/// @return Length of the flags string written into buffer.
usz SHU_CompilerGetFlags(SHUSlice buffer);

///!!! This function is not meant to be used directly. Use SHU_CompilerAddDefinitions macro instead. !!!
void SHUI_CompilerAddDefinition(const char *macros, ...);

/// @brief Add a definition to current compiler flags.
/// @param defineName Name of the macro to define. Use with quotes
/// @param defineValue Value of the previous macro in parameters. Leave NULL to just define macro without value. use backslash-ed quotes inside (\"\") for string macros.
/// @note Parameters must be complete name,value pairs. (eg. ("DEBUG", NULL, "BUFFER_SIZE", "31", "MY_STR", "\"this is my string\""))
#define SHU_CompilerAddDefinitions(macros, ...) SHUI_CompilerAddDefinition(macros, ##__VA_ARGS__, NULL)

/// @brief Gets the identifier of the configured compiler.
/// @return Compiler identifier. Use it with SHUM_COMPILER_<...> macros.
u8 SHU_CompilerGetIdentifier(void);

/// @brief Gets the system that the configured compiler compiles for, which the compiler tells: the host's, or another's for a cross compiler such as x86_64-w64-mingw32-gcc.
/// The names of executables and libraries, and how they find their dynamic libraries, follow it. Build scripts are compiled for the host.
/// @return Platform identifier. Use it with SHUM_PLATFORM_<...> macros.
u8 SHU_CompilerGetTarget(void);

#pragma endregion Compiler

#pragma region Module

/// @brief Begins a new module with the given name. A module can be an executable or a library. Must be called before any other Module function.
/// @param name Name of the module. Which will be used also for output file name. (eg. myLibName, myAppName)
/// @param root Root directory of the module. Will be used to relatively point other files and directories for module. Relative to current executable. Leave it empty string or NULL to ignore. (eg. dependencies/library/)
void SHU_ModuleBegin(const char *name, const char *root);

///!!! This function is not meant to be used directly. Use SHU_ModuleAddIncludeDirectory macro instead. !!!
void SHUI_ModuleAddIncludeDirectory(const char *directory, ...);

/// @brief Adds include directories to the module.
/// @param directory Include directories to add to the current module, one or more. Relative to root directory specified in ModuleBegin (eg. "include/", "src/")
#define SHU_ModuleAddIncludeDirectory(directory, ...) SHUI_ModuleAddIncludeDirectory(directory, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleAddPublicIncludeDirectory macro instead. !!!
void SHUI_ModuleAddPublicIncludeDirectory(const char *directory, ...);

/// @brief Adds include directories to the module, and gives them to the modules that link the module, as system headers, so their warnings stay out.
/// Only the modules that link the library themselves get them, not the ones that get the library through another library.
/// @param directory Include directories of the library's interface, one or more. Relative to root directory specified in ModuleBegin (eg. "include/")
#define SHU_ModuleAddPublicIncludeDirectory(directory, ...) SHUI_ModuleAddPublicIncludeDirectory(directory, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleAddSourceFile macro instead. !!!
void SHUI_ModuleAddSourceFile(const char *file, ...);

/// @brief Adds source files to the module. Each is a single file or a directory, added with its subdirectories.
/// @param file Files or directories to add to the current module, one or more. Relative to root directory specified in ModuleBegin (eg. "main.c", "src/")
/// @note A header file is compiled as C, so a single header library can be added with the definition of its implementation. (eg. clay.h with CLAY_IMPLEMENTATION)
#define SHU_ModuleAddSourceFile(file, ...) SHUI_ModuleAddSourceFile(file, ##__VA_ARGS__, NULL)

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name. Relative to current executable directory. (eg. build/)
/// @param module Current module mode. Use with SHUM_MODULE_<...> macros. (eg. SHUModuleType_LibraryStatic)
void SHU_ModuleCompile(const char *directory, SHUModuleType module);

/// @brief Adds a directory to search for the libraries that the current module links. A static library keeps it for the modules that link it, as it keeps its libraries.
/// On Linux and macOS, a directory that holds a dynamic library the module links is embedded in it, relative to the module's own directory ($ORIGIN or @loader_path),
/// so the library is found at run time, also after both are moved together. On Windows, see SHU_ModuleCopyDynamicLinks.
/// @param directory Directories to search for libraries, one or more. Relative to current executable directory. (eg. "build/arc/")
#define SHU_ModuleAddLibraryDirectory(directory, ...) SHUI_ModuleAddLibraryDirectory(directory, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleAddLibraryDirectory macro instead. !!!
void SHUI_ModuleAddLibraryDirectory(const char *directory, ...);

/// @brief Links a library to the current module. An executable or a dynamic library is linked with it.
/// A static library cannot be linked, so it keeps the library: a module that links the static library later gets the library too, after it, with its directories.
/// @param library Libraries to link with the module, one or more, in order. Shouldn't include any path, use `SHU_ModuleAddLibraryDirectory` to search inside. (eg. "shapes", "numbers")
#define SHU_ModuleLinkLibrary(library, ...) SHUI_ModuleLinkLibrary(library, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleLinkLibrary macro instead. !!!
void SHUI_ModuleLinkLibrary(const char *library, ...);

/// @brief Copies the dynamic libraries that the current module links into its output directory when it compiles, so they are found beside it.
/// Windows needs this, as a program finds its DLLs beside itself or on PATH, not in the directories it was linked with. A copy that has the content already is left as is.
/// Only the module's own links are copied, with those that its static libraries bring, not the ones that its dynamic libraries link.
void SHU_ModuleCopyDynamicLinks(void);

#pragma endregion Module

#pragma endregion Declarations

#pragma region Definitions

#ifdef SHU_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
#include <windows.h>
#include <process.h>
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <ftw.h>
#endif

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_MACOS)
#include <mach-o/dyld.h>
#endif

#pragma region Internals

// calls function with each string argument of a variadic function, from first until the NULL that its macro adds
#define SHUI_EACH_ARGUMENT(first, function)                                                           \
    do                                                                                                \
    {                                                                                                 \
        va_list args;                                                                                 \
        va_start(args, first);                                                                        \
        for (const char *argument = (first); argument != NULL; argument = va_arg(args, const char *)) \
        {                                                                                             \
            function(argument);                                                                       \
        }                                                                                             \
        va_end(args);                                                                                 \
    } while (0)

#ifdef SHUC_ENABLE_INCREMENTAL
typedef u64 SHUI_Hash;
#endif

// strings and lists are allocated and never freed: a build runs for a short time, and the system frees its memory when it exits

typedef struct SHUI_StringList
{
    usz count;
    usz capacity;
    char **data;
} SHUI_StringList;

/// @brief A string that grows as characters are added, for strings made one character at a time.
typedef struct SHUI_Builder
{
    usz length;
    usz capacity;
    char *data;
} SHUI_Builder;

/// @brief A library and what a module that links it gets: its public include directories, and for a static library, the libraries it links.
typedef struct SHUI_Library
{
    char *name;
    SHUI_StringList links;
    SHUI_StringList linkDirectories;
    SHUI_StringList includeDirectories;
} SHUI_Library;

#ifdef SHUC_ENABLE_INCREMENTAL
static bool SHUI_CDependencyDirty(const char *dependencyFile, const char *objectFile);
#endif

static struct
{
    char *currentExecutableDirectory;

#ifdef SHUC_ENABLE_INCREMENTAL
    char *cacheDirectory;
#endif

    struct
    {
        u8 identifier;
        u8 target; // the platform it compiles for
        char *command;
        SHUI_StringList flags;
        SHUI_StringList linkerFlags;
    } COMPILER;

    struct
    {
        i64 processes[SHUC_MAX_JOB_COUNT];
        char *commands[SHUC_MAX_JOB_COUNT]; // shown when the job fails
        usz count;
        usz limit;
        i32 failure;
    } JOBS;

    struct
    {
        char *name;
        char *root;
        SHUI_StringList includeDirectories;
        SHUI_StringList sourceFiles;
        SHUI_StringList links;
        SHUI_StringList linkDirectories;
        SHUI_StringList publicIncludeDirectories; // given to the modules that link it
        SHUI_StringList linkedIncludeDirectories; // the public include directories of the libraries it links
        bool copyDynamicLinks;
        usz compiledCount; // for the module's line in the log
        char *output;      // the file it linked or packed, or NULL when it was up to date
    } MODULE;

    // the libraries compiled so far, with what the modules that link them get
    struct
    {
        usz count;
        usz capacity;
        SHUI_Library *data;
    } LIBRARIES;
} SHUILD = {0};

static void *SHUI_Allocate(usz size)
{
    void *memory = malloc(size);
    SHU_Assert(memory != NULL, "Internal: Memory allocation failed for size '%zu'.", size);

    return memory;
}

// the old memory is left, as nothing is freed
static void *SHUI_Grow(void *memory, usz oldSize, usz newSize)
{
    void *grown = SHUI_Allocate(newSize);

    if (oldSize != 0)
    {
        memcpy(grown, memory, oldSize);
    }

    return grown;
}

static usz SHUI_GrowCapacity(usz capacity)
{
    return capacity == 0 ? SHUC_ARRAY_INITIAL_COUNT : (usz)((float)capacity * SHUC_ARRAY_RESIZE_FACTOR);
}

static char *SHUI_VFormat(const char *format, va_list args)
{
    va_list copy;
    va_copy(copy, args);
    i32 length = vsnprintf(NULL, 0, format, copy);
    va_end(copy);

    SHU_Assert(length >= 0, "Internal: Formatting '%s' failed.", format);

    char *string = (char *)SHUI_Allocate((usz)length + 1);
    vsnprintf(string, (usz)length + 1, format, args);

    return string;
}

static char *SHUI_Format(const char *format, ...) __attribute__((format(printf, 1, 2)));
static char *SHUI_Format(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char *string = SHUI_VFormat(format, args);
    va_end(args);

    return string;
}

// shuild's own messages are one short line each, with paths from the build script's directory
static void SHUI_LogLine(const char *kind, const char *format, va_list args)
{
    fprintf(SHU_LOG_STREAM, SHUM_COLOR_BOLD("[shuild]") " %s%s\n", kind, SHUI_VFormat(format, args));
}

static void SHUI_Log(const char *format, ...) __attribute__((format(printf, 1, 2)));
static void SHUI_Log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine("", format, args);
    va_end(args);
}

static void SHUI_Warn(const char *format, ...) __attribute__((format(printf, 1, 2)));
static void SHUI_Warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_YELLOW("warning: "), format, args);
    va_end(args);
}

/// @brief Logs an error, and ends the build with the code unless it is 0.
static void SHUI_Fail(i32 code, const char *format, ...) __attribute__((format(printf, 2, 3)));
static void SHUI_Fail(i32 code, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_RED("error: "), format, args);
    va_end(args);

    if (code != 0)
    {
        exit(code);
    }
}

/// @brief A path from the build script's directory, for logs.
static const char *SHUI_SShort(const char *path)
{
    usz length = SHUILD.currentExecutableDirectory == NULL ? 0 : (usz)strlen(SHUILD.currentExecutableDirectory);

    return length != 0 && strncmp(path, SHUILD.currentExecutableDirectory, length) == 0 ? path + length : path;
}

static void SHUI_BAppendChar(SHUI_Builder *builder, char character)
{
    if (builder->length + 1 >= builder->capacity)
    {
        usz capacity = SHUI_GrowCapacity(builder->capacity);
        builder->data = (char *)SHUI_Grow(builder->data, builder->length, capacity);
        builder->capacity = capacity;
    }

    builder->data[builder->length++] = character;
    builder->data[builder->length] = '\0';
}

static void SHUI_BAppend(SHUI_Builder *builder, const char *string)
{
    for (const char *c = string; *c != '\0'; c++)
    {
        SHUI_BAppendChar(builder, *c);
    }
}

// the string is the caller's, and the builder starts a new one
static char *SHUI_BTake(SHUI_Builder *builder)
{
    char *string = builder->data == NULL ? SHUI_Format("%s", "") : builder->data;
    *builder = (SHUI_Builder){0};

    return string;
}

static bool SHUI_SEndsWithC(const char *string, const char *suffix)
{
    usz stringLength = (usz)strlen(string);
    usz suffixLength = (usz)strlen(suffix);

    return stringLength >= suffixLength && strcmp(string + stringLength - suffixLength, suffix) == 0;
}

static bool SHUI_SIsSeparator(char character)
{
    return character == '/' || character == SHUM_PATH_SEPARATOR;
}

static void SHUI_SNormalizePath(char *string)
{
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    for (char *c = string; *c != '\0'; c++)
    {
        if (*c == '/')
        {
            *c = '\\';
        }
    }
#else
    (void)string;
#endif
}

/// @brief Joins a base path and a path. A directory ends with a separator. On Windows, the separators are backslashes.
static char *SHUI_SPath(const char *base, const char *path, bool directory)
{
    char *joined = SHUI_Format("%s%s", base, path);
    usz length = (usz)strlen(joined);

    if (directory && (length == 0 || !SHUI_SIsSeparator(joined[length - 1])))
    {
        joined = SHUI_Format("%s" SHUM_PATH_SEPARATOR_STR, joined);
    }

    SHUI_SNormalizePath(joined);

    return joined;
}

/// @brief The directory of a path, with its separator at the end, or an empty string.
static char *SHUI_SDirectory(const char *path)
{
    usz length = (usz)strlen(path);

    while (length > 0 && !SHUI_SIsSeparator(path[length - 1]))
    {
        length--;
    }

    return SHUI_Format("%.*s", (int)length, path);
}

static void SHUI_SLAdd(SHUI_StringList *list, char *string);

/// @brief A path without . and .. segments, so two paths to a directory can be compared. (eg. /a/b/../c/ is /a/c/)
static char *SHUI_SClean(const char *path)
{
    SHUI_StringList segments = {0};
    const char *start = path;

    for (const char *c = path;; c++)
    {
        if (*c != '\0' && !SHUI_SIsSeparator(*c))
        {
            continue;
        }

        char *segment = SHUI_Format("%.*s", (int)(c - start), start);

        if (strcmp(segment, "..") == 0 && segments.count > 0 && strcmp(segments.data[segments.count - 1], "..") != 0)
        {
            segments.count--;
        }
        else if (segment[0] != '\0' && strcmp(segment, ".") != 0)
        {
            SHUI_SLAdd(&segments, segment);
        }

        if (*c == '\0')
        {
            break;
        }

        start = c + 1;
    }

    SHUI_Builder clean = {0};

    if (SHUI_SIsSeparator(path[0]))
    {
        SHUI_BAppendChar(&clean, SHUM_PATH_SEPARATOR);
    }

    for (usz i = 0; i < segments.count; i++)
    {
        SHUI_BAppend(&clean, segments.data[i]);

        if (i + 1 < segments.count || (path[0] != '\0' && SHUI_SIsSeparator(path[strlen(path) - 1])))
        {
            SHUI_BAppendChar(&clean, SHUM_PATH_SEPARATOR);
        }
    }

    return SHUI_BTake(&clean);
}

/// @brief The path from one directory to another, both ending with a separator. (eg. from /a/bin/ to /a/lib/ is ../lib/)
static char *SHUI_SRelative(const char *from, const char *to)
{
    from = SHUI_SClean(from);
    to = SHUI_SClean(to);

    usz common = 0;

    for (usz i = 0; from[i] != '\0' && from[i] == to[i]; i++)
    {
        if (SHUI_SIsSeparator(from[i]))
        {
            common = i + 1;
        }
    }

    SHUI_Builder relative = {0};

    for (const char *c = from + common; *c != '\0'; c++)
    {
        if (SHUI_SIsSeparator(*c))
        {
            SHUI_BAppend(&relative, ".." SHUM_PATH_SEPARATOR_STR);
        }
    }

    SHUI_BAppend(&relative, to + common);

    return SHUI_BTake(&relative);
}

static void SHUI_SLAdd(SHUI_StringList *list, char *string)
{
    if (list->count >= list->capacity)
    {
        usz capacity = SHUI_GrowCapacity(list->capacity);
        list->data = (char **)SHUI_Grow(list->data, sizeof(char *) * list->count, sizeof(char *) * capacity);
        list->capacity = capacity;
    }

    list->data[list->count++] = string;
}

static bool SHUI_SLContains(const SHUI_StringList *list, const char *string)
{
    for (usz i = 0; i < list->count; i++)
    {
        if (strcmp(list->data[i], string) == 0)
        {
            return true;
        }
    }

    return false;
}

static void SHUI_CAddArgument(SHUI_StringList *command, const char *argument)
{
    SHUI_SLAdd(command, SHUI_Format("%s", argument));
}

// a backslash escapes the next character, as in a POSIX shell; on Windows, where paths hold backslashes, it escapes only a quote, as the C runtime's own splitting does
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
#define SHUI_C_ESCAPES(next) ((next) == '"' || (next) == '\'')
#define SHUI_C_ESCAPES_QUOTED(next) ((next) == '"')
#else
#define SHUI_C_ESCAPES(next) ((next) != '\0')
#define SHUI_C_ESCAPES_QUOTED(next) ((next) == '"' || (next) == '\\' || (next) == '$' || (next) == '`')
#endif

static void SHUI_CAddArguments(SHUI_StringList *command, const char *arguments)
{
    // splits the arguments the way a POSIX shell does: spaces separate them, quotes group them and backslashes escape
    SHUI_Builder argument = {0};
    bool inArgument = false;
    char quote = '\0';

    for (const char *c = arguments; *c != '\0'; c++)
    {
        if (quote == '\'')
        {
            if (*c == '\'')
            {
                quote = '\0';
            }
            else
            {
                SHUI_BAppendChar(&argument, *c);
            }
        }
        else if (quote == '"')
        {
            if (*c == '"')
            {
                quote = '\0';
            }
            else if (*c == '\\' && SHUI_C_ESCAPES_QUOTED(c[1]))
            {
                SHUI_BAppendChar(&argument, *++c);
            }
            else
            {
                SHUI_BAppendChar(&argument, *c);
            }
        }
        else if (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r')
        {
            if (inArgument)
            {
                SHUI_SLAdd(command, SHUI_BTake(&argument));
                inArgument = false;
            }
        }
        else if (*c == '\'' || *c == '"')
        {
            quote = *c;
            inArgument = true;
        }
        else if (*c == '\\' && SHUI_C_ESCAPES(c[1]))
        {
            SHUI_BAppendChar(&argument, *++c);
            inArgument = true;
        }
        else
        {
            SHUI_BAppendChar(&argument, *c);
            inArgument = true;
        }
    }

    SHU_Assert(quote == '\0', "Unclosed quote in arguments '%s'.", arguments);

    if (inArgument)
    {
        SHUI_SLAdd(command, SHUI_BTake(&argument));
    }
}

static void SHUI_CAddFlags(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        SHUI_CAddArguments(command, SHUILD.COMPILER.flags.data[i]);
    }
}

static void SHUI_CAddLinkerFlags(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.COMPILER.linkerFlags.count; i++)
    {
        SHUI_CAddArguments(command, SHUILD.COMPILER.linkerFlags.data[i]);
    }
}

static void SHUI_CAddIncludeDirectories(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        SHUI_SLAdd(command, SHUI_Format("-I%s", SHUILD.MODULE.includeDirectories.data[i]));
    }

    // the headers of linked libraries are another module's, so their warnings stay out
    for (usz i = 0; i < SHUILD.MODULE.linkedIncludeDirectories.count; i++)
    {
        SHUI_CAddArgument(command, "-isystem");
        SHUI_SLAdd(command, SHUILD.MODULE.linkedIncludeDirectories.data[i]);
    }
}

// build scripts run on the host, so a cross compiler leaves them to the host's own
static const char *SHUI_CScriptCompiler(void)
{
    return SHUM_PLATFORM_IS_HOST(SHUILD.COMPILER.target) ? SHUILD.COMPILER.command : SHUM_COMPILER_GET_COMMAND(SHUM_HOST_COMPILER);
}

// the archiver of the compiler's toolchain: llvm-ar for clang, which reads objects of any system,
// and for gcc the gcc-ar of the same prefix and version, such as x86_64-w64-mingw32-gcc-ar or gcc-ar-14
static const char *SHUI_CArchiver(void)
{
    if (SHUILD.COMPILER.identifier == SHUM_COMPILER_CLANG)
    {
        return "llvm-ar";
    }

    const char *gcc = NULL;

    for (const char *found = strstr(SHUILD.COMPILER.command, "gcc"); found != NULL; found = strstr(found + 1, "gcc"))
    {
        gcc = found;
    }

    return gcc == NULL ? "ar" : SHUI_Format("%.*sgcc-ar%s", (int)(gcc - SHUILD.COMPILER.command), SHUILD.COMPILER.command, gcc + 3);
}

// the first line that the compiler prints for an option, such as -dumpmachine, or an empty string
static char *SHUI_CAsk(const char *command, const char *option)
{
    char line[256] = {0};

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    FILE *pipe = _popen(SHUI_Format("%s %s 2>NUL", command, option), "r");
#else
    FILE *pipe = popen(SHUI_Format("%s %s 2>/dev/null", command, option), "r");
#endif

    if (pipe != NULL)
    {
        if (fgets(line, sizeof(line), pipe) == NULL)
        {
            line[0] = '\0';
        }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    }

    line[strcspn(line, "\r\n")] = '\0';
    return SHUI_Format("%s", line);
}

// the compiler names the system it compiles for, such as x86_64-linux-gnu, x86_64-w64-mingw32 or arm64-apple-darwin23
static u8 SHUI_CDetectTarget(const char *command)
{
    char *machine = SHUI_CAsk(command, "-dumpmachine");

    if (strstr(machine, "mingw") != NULL || strstr(machine, "windows") != NULL)
    {
        return SHUM_PLATFORM_WINDOWS;
    }

    if (strstr(machine, "apple") != NULL || strstr(machine, "darwin") != NULL)
    {
        return SHUM_PLATFORM_MACOS;
    }

    if (strstr(machine, "linux") != NULL)
    {
        return SHUM_PLATFORM_LINUX;
    }

    // a compiler that does not tell compiles for the host
    return SHUM_HOST_PLATFORM;
}

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
static char *SHUI_CQuoteArgument(char *argument)
{
    // _spawnvp joins the arguments with spaces, so they are quoted the way the C runtime splits them back
    if (argument[0] != '\0' && strpbrk(argument, " \t\"") == NULL)
    {
        return argument;
    }

    SHUI_Builder quoted = {0};
    SHUI_BAppendChar(&quoted, '"');

    usz backslashes = 0;

    for (const char *c = argument; *c != '\0'; c++)
    {
        if (*c == '\\')
        {
            backslashes++;
            continue;
        }

        for (usz j = 0; j < (*c == '"' ? backslashes * 2 + 1 : backslashes); j++)
        {
            SHUI_BAppendChar(&quoted, '\\');
        }

        SHUI_BAppendChar(&quoted, *c);
        backslashes = 0;
    }

    for (usz j = 0; j < backslashes * 2; j++)
    {
        SHUI_BAppendChar(&quoted, '\\');
    }

    SHUI_BAppendChar(&quoted, '"');

    return SHUI_BTake(&quoted);
}
#endif

/// @param line Gets the command as one line, for a log, or NULL.
static i64 SHUI_CStart(const SHUI_StringList *command, char **line)
{
    SHU_Assert(command->count > 0, "Internal: Empty command.");

    // the arguments, with a NULL after the last
    char **argv = (char **)SHUI_Allocate(sizeof(char *) * (command->count + 1));

    for (usz i = 0; i < command->count; i++)
    {
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        argv[i] = SHUI_CQuoteArgument(command->data[i]);
#else
        argv[i] = command->data[i];
#endif
    }
    argv[command->count] = NULL;

    SHUI_Builder joined = {0};

    for (usz i = 0; i < command->count; i++)
    {
        if (i != 0)
        {
            SHUI_BAppendChar(&joined, ' ');
        }

        SHUI_BAppend(&joined, argv[i]);
    }

    char *commandLine = SHUI_BTake(&joined);

    if (line != NULL)
    {
        *line = commandLine;
    }

#ifdef SHUC_LOG_COMMANDS
    SHUI_Log("$ %s", commandLine);
#endif

    i64 process = -1;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    process = (i64)_spawnvp(_P_NOWAIT, argv[0], (const char *const *)argv);
#else
    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(argv[0], argv);
        SHUI_Fail(0, "'%s' cannot start: %s", argv[0], strerror(errno));
        _exit(127);
    }

    process = pid > 0 ? (i64)pid : -1;
#endif

    return process;
}

static i32 SHUI_CWait(i64 process)
{
    if (process < 0)
    {
        return -1;
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    int status = 0;
    return _cwait(&status, (intptr_t)process, _WAIT_CHILD) == -1 ? -1 : (i32)status;
#else
    int status = 0;

    while (waitpid((pid_t)process, &status, 0) == -1)
    {
        if (errno != EINTR)
        {
            return -1;
        }
    }

    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
#endif
}

// a failed command is shown whole, so it can be run again by hand
static void SHUI_CReport(i32 result, bool terminateOnError, const char *line)
{
    if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        (void)terminateOnError;
        SHUI_Fail(0, "command failed with exit code %d: %s", result, line);
#else
        SHUI_Fail(terminateOnError ? result : 0, "command failed with exit code %d: %s", result, line);
#endif
    }
}

static i32 SHUI_CRun(const SHUI_StringList *command, bool terminateOnError)
{
    char *line = NULL;
    i32 result = SHUI_CWait(SHUI_CStart(command, &line));
    SHUI_CReport(result, terminateOnError, line);

    return result;
}

static void SHUI_CWaitJob(void)
{
    // the first job that ends; on Windows, the oldest one
    usz index = 0;
    i32 result = -1;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    result = SHUI_CWait(SHUILD.JOBS.processes[0]);
#else
    // a child that is not a job, like one the build script started itself, is passed over
    int status = 0;
    index = SHUILD.JOBS.count;

    while (index == SHUILD.JOBS.count)
    {
        pid_t pid = waitpid(-1, &status, 0);

        if (pid == -1 && errno == EINTR)
        {
            continue;
        }

        if (pid == -1)
        {
            // nothing can be waited for, so the first job counts as failed
            index = 0;
            status = -1;
            break;
        }

        index = 0;
        while (index < SHUILD.JOBS.count && SHUILD.JOBS.processes[index] != (i64)pid)
        {
            index++;
        }
    }

    result = status != -1 && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
#endif

    char *line = SHUILD.JOBS.commands[index];
    SHUILD.JOBS.count--;
    SHUILD.JOBS.processes[index] = SHUILD.JOBS.processes[SHUILD.JOBS.count];
    SHUILD.JOBS.commands[index] = SHUILD.JOBS.commands[SHUILD.JOBS.count];

    if (result != 0)
    {
        SHUI_CReport(result, false, line);

        if (SHUILD.JOBS.failure == 0)
        {
            SHUILD.JOBS.failure = result;
        }
    }
}

static void SHUI_CStartJob(const SHUI_StringList *command)
{
    if (SHUILD.JOBS.limit == 0)
    {
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        SYSTEM_INFO systemInfo = {0};
        GetSystemInfo(&systemInfo);
        usz processors = (usz)systemInfo.dwNumberOfProcessors;
#else
        long processorCount = sysconf(_SC_NPROCESSORS_ONLN);
        usz processors = processorCount > 0 ? (usz)processorCount : 1;
#endif

        SHUILD.JOBS.limit = SHUMax((usz)1, SHUMin(processors, (usz)SHUC_MAX_JOB_COUNT));
    }

#ifndef SHUC_NO_RUN_ERROR
    // after a failure, the jobs that run are waited for, and no new ones start
    if (SHUILD.JOBS.failure != 0)
    {
        return;
    }
#endif

    if (SHUILD.JOBS.count >= SHUILD.JOBS.limit)
    {
        SHUI_CWaitJob();
    }

    char *line = NULL;
    i64 process = SHUI_CStart(command, &line);

    if (process < 0)
    {
        SHUI_CReport(-1, false, line);
        SHUILD.JOBS.failure = SHUILD.JOBS.failure == 0 ? -1 : SHUILD.JOBS.failure;
        return;
    }

    SHUILD.JOBS.processes[SHUILD.JOBS.count] = process;
    SHUILD.JOBS.commands[SHUILD.JOBS.count++] = line;
}

static void SHUI_CWaitJobs(void)
{
    while (SHUILD.JOBS.count > 0)
    {
        SHUI_CWaitJob();
    }

    i32 failure = SHUILD.JOBS.failure;
    SHUILD.JOBS.failure = 0;

#ifndef SHUC_NO_RUN_ERROR
    if (failure != 0)
    {
        SHUI_Fail(failure, "'%s' failed to compile.", SHUILD.MODULE.name);
    }
#else
    (void)failure;
#endif
}

static SHUFileType SHUI_UFileExists(const char *path)
{
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    DWORD attributes = GetFileAttributesA(path);

    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        return SHUFileType_Invalid;
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return SHUFileType_Directory;
    }

    return SHUFileType_Regular;
#else
    struct stat stats;
    if (stat(path, &stats) == 0)
    {
        if (S_ISDIR(stats.st_mode))
        {
            return SHUFileType_Directory;
        }
        return SHUFileType_Regular;
    }
    return SHUFileType_Invalid;
#endif
}

static void SHUI_UMakeDirectory(const char *path)
{
    i32 result = 0;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    result = _mkdir(path);
#else
    result = mkdir(path, 0755);
#endif

    if (result != 0 && errno != EEXIST)
    {
        SHUI_Fail(result, "directory '%s' cannot be made: %s", SHUI_SShort(path), strerror(errno));
    }
}

static void SHUI_UMakeDirectoryRecursive(const char *path)
{
    // each directory on the way is made, ending the path after it for a moment
    char *partial = SHUI_Format("%s", path);

    for (usz i = 1; partial[i] != '\0'; i++)
    {
        if (partial[i] == SHUM_PATH_SEPARATOR)
        {
            partial[i] = '\0';
            SHUI_UMakeDirectory(partial);
            partial[i] = SHUM_PATH_SEPARATOR;
        }
    }

    SHUI_UMakeDirectory(partial);
}

static void SHUI_UDeleteSingleFile(const char *path)
{
    i32 result = remove(path);

    if (result != 0)
    {
        SHUI_Fail(result, "file '%s' cannot be deleted: %s", SHUI_SShort(path), strerror(errno));
    }
}

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
static void SHUI_UDeleteDirectory(const char *path)
{
    i32 result = _rmdir(path);

    if (result != 0)
    {
        SHUI_Fail(result, "directory '%s' cannot be deleted: %s", SHUI_SShort(path), strerror(errno));
    }
}
#else
static int SHUI_UNftwCallback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    (void)sb;
    (void)ftwbuf;

    if (typeflag == FTW_D || typeflag == FTW_DP)
    {
        return rmdir(fpath);
    }

    return remove(fpath);
}
#endif

static void SHUI_UDeleteRecursive(const char *path)
{
    SHUFileType fileType = SHUI_UFileExists(path);

    SHU_Assert(fileType != SHUFileType_Invalid, "File '%s' does not exist.", path);

    if (fileType == SHUFileType_Regular)
    {
        SHUI_UDeleteSingleFile(path);
        return;
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd;
    HANDLE hFind = FindFirstFileA(SHUI_Format("%s\\*", path), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        char *subPath = SHUI_Format("%s\\%s", path, ffd.cFileName);

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            SHUI_UDeleteRecursive(subPath);
        }
        else
        {
            SHUI_UDeleteSingleFile(subPath);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
    SHUI_UDeleteDirectory(path);
#else
    nftw(path, SHUI_UNftwCallback, 64, FTW_DEPTH | FTW_PHYS);
#endif
}

static SHUSlice SHUI_UReadFile(const char *path)
{
    FILE *fileHandle = fopen(path, "rb");

    if (fileHandle == NULL)
    {
        SHUI_Fail(SHUResult_ErrFile, "file '%s' cannot be read: %s", SHUI_SShort(path), strerror(errno));
    }

    fseek(fileHandle, 0, SEEK_END);
    long fileLength = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    SHU_Assert(fileLength >= 0, "File size getting failed for '%s'.", path);

    char *buffer = (char *)SHUI_Allocate((usz)fileLength + 1);

    usz fileRead = (usz)fread(buffer, 1, (size_t)fileLength, fileHandle);
    SHU_Assert(fileRead == (usz)fileLength, "File read failed for '%s'.", path);
    buffer[fileLength] = '\0';
    fclose(fileHandle);

    return cs(buffer, (usz)fileLength);
}

static void SHUI_UWriteFile(const char *path, SHUSliceView content)
{
    SHU_Assert(content.data != NULL || content.size == 0, "Content to write to '%s' is NULL.", path);

    // a file that has the content already is left as is, so its edit time stays and what includes it does not compile again
    if (SHUI_UFileExists(path) == SHUFileType_Regular)
    {
        SHUSlice old = SHUI_UReadFile(path);

        if (old.size == content.size && (content.size == 0 || memcmp(old.data, content.data, content.size) == 0))
        {
            return;
        }
    }

    FILE *fileHandle = fopen(path, "wb");

    if (fileHandle == NULL)
    {
        SHUI_Fail(SHUResult_ErrFile, "file '%s' cannot be written: %s", SHUI_SShort(path), strerror(errno));
    }

    usz fileWritten = content.size == 0 ? 0 : (usz)fwrite(content.data, 1, content.size, fileHandle);
    SHU_Assert(fileWritten == content.size, "File write failed for '%s'.", path);
    fclose(fileHandle);
}

static void SHUI_UCopySingleFile(const char *src, const char *dst)
{
    SHUI_UWriteFile(dst, csv(SHUI_UReadFile(src)));

#if !SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    // the copy keeps the permissions, so a copied program or script still runs
    struct stat stats;

    if (stat(src, &stats) == 0 && chmod(dst, stats.st_mode & 07777) != 0)
    {
        SHUI_Fail(SHUResult_ErrFile, "permissions of '%s' cannot be set: %s", SHUI_SShort(dst), strerror(errno));
    }
#endif
}

static void SHUI_UCopyRecursive(const char *src, const char *dst)
{
    SHUFileType fileType = SHUI_UFileExists(src);

    SHU_Assert(fileType != SHUFileType_Invalid, "File '%s' does not exist", src);

    if (fileType == SHUFileType_Regular)
    {
        SHUI_UCopySingleFile(src, dst);
        return;
    }

    SHUFileType destinationType = SHUI_UFileExists(dst);

    SHU_Assert(destinationType != SHUFileType_Regular, "Directory '%s' already exist as a regular file", src);

    if (destinationType == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(dst);
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd;
    HANDLE hFind = FindFirstFileA(SHUI_Format("%s\\*", src), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHUI_Fail(SHUResult_ErrInternal, "directory '%s' cannot be opened.", SHUI_SShort(src));
    }

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
        {
            continue;
        }

        SHUI_UCopyRecursive(SHUI_Format("%s\\%s", src, ffd.cFileName), SHUI_Format("%s\\%s", dst, ffd.cFileName));
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(src);
    if (!dir)
    {
        SHUI_Fail(SHUResult_ErrInternal, "directory '%s' cannot be opened.", SHUI_SShort(src));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        SHUI_UCopyRecursive(SHUI_Format("%s/%s", src, entry->d_name), SHUI_Format("%s/%s", dst, entry->d_name));
    }

    closedir(dir);
#endif
}

static void SHUI_URenameFile(const char *file, const char *name)
{
    if (SHUI_UFileExists(name) != SHUFileType_Invalid)
    {
        SHUI_UDeleteRecursive(name);
    }

    i32 result = rename(file, name);

    if (result != 0)
    {
        SHUI_Fail(result, "'%s' cannot be renamed to '%s': %s", SHUI_SShort(file), SHUI_SShort(name), strerror(errno));
    }
}

static i64 SHUI_UGetFileEditTime(const char *file)
{
    // in nanoseconds, so a file edited in the same second as its object was compiled is still seen as newer
    struct stat attr;
    i32 result = stat(file, &attr);

    if (result != 0)
    {
        SHUI_Fail(SHUResult_ErrInternal, "file '%s' cannot be found: %s", SHUI_SShort(file), strerror(errno));
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_LINUX)
    return (i64)attr.st_mtim.tv_sec * 1000000000LL + (i64)attr.st_mtim.tv_nsec;
#elif SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_MACOS)
    return (i64)attr.st_mtimespec.tv_sec * 1000000000LL + (i64)attr.st_mtimespec.tv_nsec;
#else
    return (i64)attr.st_mtime * 1000000000LL;
#endif
}

static bool SHUI_CDependencyDirty(const char *dependencyFile, const char *targetFile)
{
    i64 objectTime = SHUI_UGetFileEditTime(targetFile);

    SHUSlice dependencies = SHUI_UReadFile(dependencyFile);
    const char *text = (const char *)dependencies.data;
    usz length = dependencies.size;

    // the target ends at a colon followed by a space or the end of the line, so a Windows drive, as in D:\project\main.o, is part of its path
    usz offset = 0;
    while (offset < length && !(text[offset] == ':' && (offset + 1 == length || text[offset + 1] == ' ' || text[offset + 1] == '\t' || text[offset + 1] == '\r' || text[offset + 1] == '\n')))
    {
        offset++;
    }
    offset++;

    // the compiler escapes a space in a file name with a backslash, and ends a line that goes on with one
    SHUI_Builder dependentFile = {0};

    while (offset <= length)
    {
        char c = offset < length ? text[offset] : '\0';

        if (c == '\\' && offset + 1 < length && text[offset + 1] == ' ')
        {
            SHUI_BAppendChar(&dependentFile, ' ');
            offset += 2;
            continue;
        }

        if (c == '\\' && offset + 1 < length && (text[offset + 1] == '\r' || text[offset + 1] == '\n'))
        {
            offset++;
            continue;
        }

        if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\0')
        {
            if (dependentFile.length != 0 && objectTime < SHUI_UGetFileEditTime(SHUI_BTake(&dependentFile)))
            {
                return true;
            }
        }
        else
        {
            SHUI_BAppendChar(&dependentFile, c);
        }

        offset++;
    }

    return false;
}

void SHUI_UAutomate(int argc, char **argv, const char *sourceName)
{
    SHU_AssertNullPointer(sourceName);
    SHU_AssertNullPointer(argv);
    SHU_Assert(argc > 0, "Invalid argument count");

    usz exeNameStartIndex = (usz)strlen(argv[0]) - 1;

    while (exeNameStartIndex > 0 && argv[0][exeNameStartIndex - 1] != SHUM_PATH_SEPARATOR)
    {
        exeNameStartIndex--;
    }
    const char *executableFileName = argv[0] + exeNameStartIndex;

    usz sourceNameStartIndex = (usz)strlen(sourceName) - 1;

    while (sourceNameStartIndex > 0 && sourceName[sourceNameStartIndex - 1] != SHUM_PATH_SEPARATOR)
    {
        sourceNameStartIndex--;
    }
    const char *sourceFileName = sourceName + sourceNameStartIndex;

    char *executablePath = SHUI_Format("%s%s", SHUILD.currentExecutableDirectory, executableFileName);
    char *sourcePath = SHUI_Format("%s%s", SHUILD.currentExecutableDirectory, sourceFileName);

    i64 exeTime = SHUI_UGetFileEditTime(executablePath);
    i64 sourceTime = SHUI_UGetFileEditTime(sourcePath);

    bool rebuild = (exeTime < sourceTime);

    if (!rebuild)
    {
        char *depFileMap = SHUI_Format("%s." SHUC_FILE_EXTENSION, executablePath);

        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUI_CScriptCompiler());
        SHUI_CAddArgument(&command, "-MM");
        SHUI_CAddArgument(&command, sourcePath);
        SHUI_CAddArgument(&command, "-MF");
        SHUI_CAddArgument(&command, depFileMap);
        // when the dependencies cannot be listed, the rebuild shows why
        if (SHUI_CRun(&command, false) != 0 || SHUI_CDependencyDirty(depFileMap, executablePath))
        {
            rebuild = true;
        }

        if (SHUI_UFileExists(depFileMap) == SHUFileType_Regular)
        {
            SHUI_UDeleteSingleFile(depFileMap);
        }
    }

    if (!rebuild)
    {
        return;
    }

    SHUI_Log("the build script changed; rebuilding it");

    char *oldExePath = SHUI_Format("%s.old", executablePath);
    SHUI_URenameFile(executablePath, oldExePath);

    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUI_CScriptCompiler());
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, executablePath);
    SHUI_CAddArgument(&command, sourcePath);
    SHUI_CAddArguments(&command, SHUILD_BUILD);
    i32 result = SHUI_CRun(&command, false);

    if (result == 0)
    {
        i32 spawnResult = SHU_UtilSpawnProcessSync(executablePath, argv);
        exit(spawnResult);
    }
    else
    {
        SHUI_URenameFile(oldExePath, executablePath);
        SHUI_Fail(result, "the build script cannot be rebuilt.");
    }
}

#ifdef SHUC_ENABLE_INCREMENTAL
static SHUI_Hash SHUI_CModuleStateHash(void)
{
    SHUI_Hash hash = 14695981039346656037ULL;

#define SHUI_HASH_BYTE(byte) hash = ((hash ^ (SHUI_Hash)(byte)) * 1099511628211ULL)
#define SHUI_HASH_MIX hash ^= (hash >> 17)
#define SHUI_HASH_STRING(string)                    \
    for (const char *c = (string); *c != '\0'; c++) \
    {                                               \
        SHUI_HASH_BYTE((u8)*c);                     \
    }                                               \
    SHUI_HASH_MIX
    // the count tells an empty list from none
#define SHUI_HASH_LIST(list)                  \
    SHUI_HASH_BYTE((list).count);             \
    for (usz i = 0; i < (list).count; i++)    \
    {                                         \
        SHUI_HASH_STRING((list).data[i]);     \
    }

    SHUI_HASH_STRING(SHUILD.cacheDirectory);

    SHUI_HASH_BYTE(SHUILD.COMPILER.identifier);
    SHUI_HASH_MIX;

    SHUI_HASH_STRING(SHUILD.COMPILER.command);
    SHUI_HASH_LIST(SHUILD.COMPILER.flags);
    SHUI_HASH_LIST(SHUILD.COMPILER.linkerFlags);
    SHUI_HASH_STRING(SHUILD.currentExecutableDirectory);
    SHUI_HASH_STRING(SHUILD.MODULE.name);
    SHUI_HASH_STRING(SHUILD.MODULE.root);
    SHUI_HASH_LIST(SHUILD.MODULE.includeDirectories);
    SHUI_HASH_LIST(SHUILD.MODULE.sourceFiles);
    SHUI_HASH_LIST(SHUILD.MODULE.linkDirectories);
    SHUI_HASH_LIST(SHUILD.MODULE.links);

#undef SHUI_HASH_LIST
#undef SHUI_HASH_STRING

    return hash;
}

static char *SHUI_CModuleStateFile(const char *moduleName)
{
    return SHUI_Format("%s%s%c%s.%s", SHUILD.cacheDirectory, moduleName, SHUM_PATH_SEPARATOR, moduleName, SHUC_MODULE_FILE_EXTENSION);
}

static void SHUI_CModuleStateUpdate(const char *moduleName)
{
    char *moduleCacheFile = SHUI_CModuleStateFile(moduleName);

    SHUI_UMakeDirectoryRecursive(SHUI_Format("%s%s%c", SHUILD.cacheDirectory, moduleName, SHUM_PATH_SEPARATOR));

    SHUI_Hash currentConfig = SHUI_CModuleStateHash();

    FILE *cacheFileHandle = fopen(moduleCacheFile, "w+");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile);
    fprintf(cacheFileHandle, "%llu", (unsigned long long)currentConfig);
    fclose(cacheFileHandle);
}

static bool SHUI_CModuleStateDirty(const char *moduleName)
{
    char *moduleCacheFile = SHUI_CModuleStateFile(moduleName);

    if (SHUI_UFileExists(moduleCacheFile) != SHUFileType_Regular)
    {
        return true;
    }

    SHUI_Hash currentConfig = SHUI_CModuleStateHash();

    char buffer[SHUC_MAX_HASH_BUFFER_SIZE] = {0};

    FILE *cacheFileHandle = fopen(moduleCacheFile, "r");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile);
    usz bufferRead = (usz)fread(buffer, 1, sizeof(buffer), cacheFileHandle);
    SHU_Assert(bufferRead < sizeof(buffer), "Buffer overflow for '%s'", moduleCacheFile);
    fclose(cacheFileHandle);

    SHUI_Hash savedConfig = strtoull(buffer, NULL, 10);

    return currentConfig != savedConfig;
}

static bool SHUI_CUnitRequiresCompilation(const char *sourceFile, char **retObjectFile, char **retDependencyFile)
{
    // the source's path in the module, without its extension's last letter
    usz fileStartIndex = (usz)strlen(SHUILD.MODULE.root);
    int unitLength = (int)((usz)strlen(sourceFile) - fileStartIndex - 1);

    *retDependencyFile = SHUI_Format("%s%s%c%.*s%s",
                                     SHUILD.cacheDirectory,
                                     SHUILD.MODULE.name,
                                     SHUM_PATH_SEPARATOR,
                                     unitLength,
                                     sourceFile + fileStartIndex,
                                     SHUC_FILE_EXTENSION);

    *retObjectFile = SHUI_Format("%s%s%c%.*s%s",
                                 SHUILD.cacheDirectory,
                                 SHUILD.MODULE.name,
                                 SHUM_PATH_SEPARATOR,
                                 unitLength,
                                 sourceFile + fileStartIndex,
                                 "o");

    if (SHUI_UFileExists(*retObjectFile) == SHUFileType_Regular &&
        SHUI_UFileExists(*retDependencyFile) == SHUFileType_Regular &&
        !SHUI_CDependencyDirty(*retDependencyFile, *retObjectFile))
    {
        return false;
    }

    SHUI_UMakeDirectoryRecursive(SHUI_SDirectory(*retObjectFile));
    return true;
}
#endif

static void SHUI_CCompileUnit(const char *sourceFile, const char *objectFile, const char *dependencyFile, const char *extraFlag)
{
    // the compiler writes the dependency file as it compiles, with the module's flags, so the headers that definitions include are in it too
    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUILD.COMPILER.command);
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, objectFile);
    SHUI_CAddArgument(&command, "-c");

    if (extraFlag != NULL)
    {
        SHUI_CAddArgument(&command, extraFlag);
    }

    // a single header library is compiled as C, with the definition that holds its implementation, instead of as a precompiled header
    if (SHUI_SEndsWithC(sourceFile, ".h"))
    {
        SHUI_CAddArgument(&command, "-x");
        SHUI_CAddArgument(&command, "c");
    }

    SHUI_CAddArgument(&command, sourceFile);
    SHUI_CAddFlags(&command);
    SHUI_CAddIncludeDirectories(&command);

    if (dependencyFile != NULL)
    {
        SHUI_CAddArgument(&command, "-MMD");
        SHUI_CAddArgument(&command, "-MF");
        SHUI_CAddArgument(&command, dependencyFile);
    }

    SHUI_CStartJob(&command);
    SHUILD.MODULE.compiledCount++;
}

static void SHUI_MAddSourceDirectoryRecursive(const char *path)
{
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd = {0};
    HANDLE hFind = FindFirstFileA(SHUI_Format("%s*", path), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
        {
            continue;
        }

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            SHUI_MAddSourceDirectoryRecursive(SHUI_Format("%s%s\\", path, ffd.cFileName));
        }
        else if (SHUI_SEndsWithC(ffd.cFileName, ".c"))
        {
            SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, SHUI_Format("%s%s", path, ffd.cFileName));
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path);

    if (!dir)
    {
        SHUI_Fail(SHUResult_ErrInternal, "directory '%s' cannot be opened.", SHUI_SShort(path));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char *entryPath = SHUI_Format("%s%s", path, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0 && S_ISDIR(st.st_mode))
        {
            SHUI_MAddSourceDirectoryRecursive(SHUI_Format("%s/", entryPath));
        }
        else if (SHUI_SEndsWithC(entry->d_name, ".c"))
        {
            SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, entryPath);
        }
    }

    closedir(dir);
#endif
}

static SHUI_Library *SHUI_MFindLibrary(const char *name)
{
    for (usz i = 0; i < SHUILD.LIBRARIES.count; i++)
    {
        if (strcmp(SHUILD.LIBRARIES.data[i].name, name) == 0)
        {
            return &SHUILD.LIBRARIES.data[i];
        }
    }

    return NULL;
}

// a library keeps its public include directories for the modules that link it;
// a static library cannot be linked with other libraries, so it keeps the ones it links too, and the module that links it gets them
static void SHUI_MRecordLibrary(bool keepLinks)
{
    SHUI_Library *library = SHUI_MFindLibrary(SHUILD.MODULE.name);

    if (library == NULL)
    {
        if (SHUILD.LIBRARIES.count >= SHUILD.LIBRARIES.capacity)
        {
            usz capacity = SHUI_GrowCapacity(SHUILD.LIBRARIES.capacity);
            SHUILD.LIBRARIES.data = (SHUI_Library *)SHUI_Grow(SHUILD.LIBRARIES.data, sizeof(SHUI_Library) * SHUILD.LIBRARIES.count, sizeof(SHUI_Library) * capacity);
            SHUILD.LIBRARIES.capacity = capacity;
        }

        library = &SHUILD.LIBRARIES.data[SHUILD.LIBRARIES.count++];
        library->name = SHUILD.MODULE.name;
    }

    // the module's lists stay with the record, as the next module starts new ones
    library->includeDirectories = SHUILD.MODULE.publicIncludeDirectories;
    library->links = keepLinks ? SHUILD.MODULE.links : (SHUI_StringList){0};
    library->linkDirectories = keepLinks ? SHUILD.MODULE.linkDirectories : (SHUI_StringList){0};
}

// the module gets the public include directories of the libraries it links itself, but not of the libraries those link
static void SHUI_MAddLinkedIncludes(void)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        const SHUI_Library *library = SHUI_MFindLibrary(SHUILD.MODULE.links.data[i]);

        for (usz j = 0; library != NULL && j < library->includeDirectories.count; j++)
        {
            if (!SHUI_SLContains(&SHUILD.MODULE.linkedIncludeDirectories, library->includeDirectories.data[j]))
            {
                SHUI_SLAdd(&SHUILD.MODULE.linkedIncludeDirectories, library->includeDirectories.data[j]);
            }
        }
    }
}

static void SHUI_MExpandLink(SHUI_StringList *links, char *link, usz depth)
{
    // a library that links itself through others would expand forever
    SHU_Assert(depth < 64, "Library '%s' links itself through other libraries.", link);

    SHUI_SLAdd(links, link);

    const SHUI_Library *library = SHUI_MFindLibrary(link);

    if (library == NULL)
    {
        return;
    }

    for (usz i = 0; i < library->linkDirectories.count; i++)
    {
        if (!SHUI_SLContains(&SHUILD.MODULE.linkDirectories, library->linkDirectories.data[i]))
        {
            SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, library->linkDirectories.data[i]);
        }
    }

    for (usz i = 0; i < library->links.count; i++)
    {
        SHUI_MExpandLink(links, library->links.data[i], depth + 1);
    }
}

// each static library the module links brings the libraries it keeps, after it, so the linker finds what it needs in order
static void SHUI_MExpandLinks(void)
{
    SHUI_StringList links = {0};

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_MExpandLink(&links, SHUILD.MODULE.links.data[i], 0);
    }

    // a library that comes more than once stays in its last place, after every library that needs it
    SHUI_StringList reversed = {0};

    for (usz i = links.count; i > 0; i--)
    {
        if (!SHUI_SLContains(&reversed, links.data[i - 1]))
        {
            SHUI_SLAdd(&reversed, links.data[i - 1]);
        }
    }

    SHUILD.MODULE.links = (SHUI_StringList){0};

    for (usz i = reversed.count; i > 0; i--)
    {
        SHUI_SLAdd(&SHUILD.MODULE.links, reversed.data[i - 1]);
    }
}

// the dynamic library's file where the linker finds it: on Windows, its import library, which names the DLL
static char *SHUI_MLinkedDynamicFile(const char *name)
{
    return SHUILD.COMPILER.target == SHUM_PLATFORM_WINDOWS ? SHUI_Format("lib%s.dll.a", name) : SHU_UtilLibraryFile(name, SHUModuleType_LibraryDynamic);
}

#ifdef SHUC_ENABLE_INCREMENTAL
// a module is linked again when a library it links is newer than its output
static bool SHUI_MLinksNewer(const char *outFile)
{
    i64 outTime = SHUI_UGetFileEditTime(outFile);

    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.links.count; j++)
        {
            const char *files[] = {
                SHU_UtilLibraryFile(SHUILD.MODULE.links.data[j], SHUModuleType_LibraryStatic),
                SHUI_MLinkedDynamicFile(SHUILD.MODULE.links.data[j]),
            };

            for (usz k = 0; k < sizeof(files) / sizeof(*files); k++)
            {
                char *libFile = SHUI_Format("%s%s", SHUILD.MODULE.linkDirectories.data[i], files[k]);

                if (SHUI_UFileExists(libFile) == SHUFileType_Regular &&
                    SHUI_UGetFileEditTime(libFile) > outTime)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
#endif

// a directory is searched at run time only if it holds a dynamic library that the module links
static bool SHUI_MHoldsDynamicLink(const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        if (SHUI_UFileExists(SHUI_Format("%s%s", directory, SHU_UtilLibraryFile(SHUILD.MODULE.links.data[i], SHUModuleType_LibraryDynamic))) == SHUFileType_Regular)
        {
            return true;
        }
    }

    return false;
}

/// @param directory Output directory of the module, from which its run-time search paths start.
static void SHUI_MAddLinks(SHUI_StringList *command, const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        const char *linkDirectory = SHUILD.MODULE.linkDirectories.data[i];

        SHUI_SLAdd(command, SHUI_Format("-L%s", linkDirectory));

        // the path from the module's own directory, so the two can move together; Windows has none, see SHU_ModuleCopyDynamicLinks
        if (SHUILD.COMPILER.target != SHUM_PLATFORM_WINDOWS && SHUI_MHoldsDynamicLink(linkDirectory))
        {
            char *relative = SHUI_SRelative(directory, linkDirectory);
            usz length = (usz)strlen(relative);

            SHUI_SLAdd(command, SHUI_Format("-Wl,-rpath,%s%s%.*s",
                                            SHUILD.COMPILER.target == SHUM_PLATFORM_MACOS ? "@loader_path" : "$ORIGIN",
                                            length == 0 ? "" : "/",
                                            (int)(length == 0 ? 0 : length - 1),
                                            relative));
        }
    }

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_SLAdd(command, SHUI_Format("-l%s", SHUILD.MODULE.links.data[i]));
    }
}

// the dynamic libraries the module links go beside it, from the first directory that holds each
static void SHUI_MCopyDynamicLinks(const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        char *file = SHU_UtilLibraryFile(SHUILD.MODULE.links.data[i], SHUModuleType_LibraryDynamic);

        for (usz j = 0; j < SHUILD.MODULE.linkDirectories.count; j++)
        {
            char *library = SHUI_Format("%s%s", SHUILD.MODULE.linkDirectories.data[j], file);

            if (SHUI_UFileExists(library) == SHUFileType_Regular)
            {
                if (strcmp(SHUI_SClean(SHUILD.MODULE.linkDirectories.data[j]), SHUI_SClean(directory)) != 0)
                {
                    SHUI_UCopySingleFile(library, SHUI_Format("%s%s", directory, file));
                }

                break;
            }
        }
    }
}

static void SHUI_MCompileExecutable(const char *directory)
{
    SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, SHUILD.currentExecutableDirectory);

    bool skipExePacking = true;

    SHUI_StringList inputFiles = {0};
    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *objectFile = NULL;
        char *dependencyFile = NULL;

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, objectFile, dependencyFile, NULL);

            skipExePacking = false;
        }

        SHUI_SLAdd(&inputFiles, objectFile);
#else
        skipExePacking = false;
        SHUILD.MODULE.compiledCount++;

        SHUI_SLAdd(&inputFiles, sourceFile);
#endif
    }

    SHUI_CWaitJobs();

    char *outFile = SHUI_Format("%s%s%s",
                                directory,
                                SHUILD.MODULE.name,
                                SHUILD.COMPILER.target == SHUM_PLATFORM_WINDOWS ? ".exe" : "");

#ifdef SHUC_ENABLE_INCREMENTAL
    if (SHUI_UFileExists(outFile) != SHUFileType_Regular || SHUI_MLinksNewer(outFile))
    {
        skipExePacking = false;
    }
#endif

    if (!skipExePacking)
    {
        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command);
        SHUI_CAddArgument(&command, "-o");
        SHUI_CAddArgument(&command, outFile);
        SHUI_CAddIncludeDirectories(&command);

        for (usz i = 0; i < inputFiles.count; i++)
        {
            SHUI_SLAdd(&command, inputFiles.data[i]);
        }

        SHUI_MAddLinks(&command, directory);

        SHUI_CAddFlags(&command);
        SHUI_CAddLinkerFlags(&command);
        SHUI_CRun(&command, true);
        SHUILD.MODULE.output = outFile;
    }
}

static void SHUI_MCompileLibraryStatic(const char *directory)
{
    SHUI_StringList objFiles = {0};

    bool skipLibPacking = true;

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        char *objectFile = NULL;
        char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *dependencyFile = NULL;

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, objectFile, dependencyFile, NULL);

            skipLibPacking = false;
        }
#else
        skipLibPacking = false;

        objectFile = SHUI_Format("%.*so", (int)(strlen(sourceFile) - 1), sourceFile);

        SHUI_CCompileUnit(sourceFile, objectFile, NULL, NULL);
#endif

        SHUI_SLAdd(&objFiles, objectFile);
    }

    SHUI_CWaitJobs();

    char *libraryFile = SHUI_Format("%s%s", directory, SHU_UtilLibraryFile(SHUILD.MODULE.name, SHUModuleType_LibraryStatic));

    if (SHUI_UFileExists(libraryFile) != SHUFileType_Regular)
    {
        skipLibPacking = false;
    }

    if (!skipLibPacking)
    {
        // ar adds to an archive that exists, so the archive is made again, without the objects of sources that are gone
        if (SHUI_UFileExists(libraryFile) == SHUFileType_Regular)
        {
            SHUI_UDeleteSingleFile(libraryFile);
        }

        SHUI_StringList command = {0};
        SHUI_CAddArgument(&command, SHUI_CArchiver());
        SHUI_CAddArgument(&command, "rcs");
        SHUI_SLAdd(&command, libraryFile);

        for (usz i = 0; i < objFiles.count; i++)
        {
            SHUI_SLAdd(&command, objFiles.data[i]);
        }

        SHUI_CRun(&command, true);
        SHUILD.MODULE.output = libraryFile;
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (usz i = 0; i < objFiles.count; i++)
    {
        SHUI_UDeleteSingleFile(objFiles.data[i]);
    }
#endif
}

static void SHUI_MCompileLibraryDynamic(const char *directory)
{
    SHUI_StringList objFiles = {0};

    bool skipLibPacking = true;

    // code for a DLL needs no position-independent flag, and some compilers refuse it
    const char *positionIndependent = SHUILD.COMPILER.target == SHUM_PLATFORM_WINDOWS ? NULL : "-fPIC";

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        char *objectFile = NULL;
        char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *dependencyFile = NULL;

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, objectFile, dependencyFile, positionIndependent);

            skipLibPacking = false;
        }
#else
        skipLibPacking = false;

        objectFile = SHUI_Format("%.*so", (int)(strlen(sourceFile) - 1), sourceFile);

        SHUI_CCompileUnit(sourceFile, objectFile, NULL, positionIndependent);
#endif

        SHUI_SLAdd(&objFiles, objectFile);
    }

    SHUI_CWaitJobs();

    char *libraryFile = SHUI_Format("%s%s", directory, SHU_UtilLibraryFile(SHUILD.MODULE.name, SHUModuleType_LibraryDynamic));

    if (SHUI_UFileExists(libraryFile) != SHUFileType_Regular)
    {
        skipLibPacking = false;
    }
#ifdef SHUC_ENABLE_INCREMENTAL
    else if (SHUI_MLinksNewer(libraryFile))
    {
        skipLibPacking = false;
    }
#endif

    if (!skipLibPacking)
    {
        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command);
        SHUI_CAddArgument(&command, "-shared");
        SHUI_CAddArgument(&command, "-o");
        SHUI_SLAdd(&command, libraryFile);

        // a DLL is linked through its import library, which -l finds as lib<name>.dll.a
        if (SHUILD.COMPILER.target == SHUM_PLATFORM_WINDOWS)
        {
            SHUI_SLAdd(&command, SHUI_Format("-Wl,--out-implib,%s%s", directory, SHUI_MLinkedDynamicFile(SHUILD.MODULE.name)));
        }

        for (usz i = 0; i < objFiles.count; i++)
        {
            SHUI_SLAdd(&command, objFiles.data[i]);
        }

        SHUI_MAddLinks(&command, directory);
        SHUI_CAddLinkerFlags(&command);
        SHUI_CRun(&command, true);
        SHUILD.MODULE.output = libraryFile;
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (usz i = 0; i < objFiles.count; i++)
    {
        SHUI_UDeleteSingleFile(objFiles.data[i]);
    }
#endif
}

#pragma endregion Internals

#pragma region Utility

static i32 SHUI_URunCommand(bool stopOnFailure, const char *command)
{
#ifdef SHUC_LOG_COMMANDS
    SHUI_Log("$ %s", command);
#endif

    i32 result = system(command);

#if !SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    // system returns the wait status, not the exit code
    result = result == -1 ? -1 : WIFEXITED(result) ? WEXITSTATUS(result) : -1;
#endif

    if (result != 0 && !stopOnFailure)
    {
        SHUI_Warn("command failed with exit code %d: %s", result, command);
    }
    else
    {
        SHUI_CReport(result, true, command);
    }

    return result;
}

char *SHU_UtilFormat(const char *format, ...)
{
    SHU_AssertNullPointer(format);

    va_list args;
    va_start(args, format);
    char *string = SHUI_VFormat(format, args);
    va_end(args);

    return string;
}

i32 SHU_UtilRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    return SHUI_URunCommand(true, command);
}

i32 SHU_UtilTryRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    return SHUI_URunCommand(false, command);
}

i32 SHU_UtilRunLogged(const char *log, const char *commandFormat, ...)
{
    SHU_AssertNullPointer(log);
    SHU_AssertNullPointer(commandFormat);

    char *logPath = SHUI_Format("%s%s", SHUILD.currentExecutableDirectory, log);

    // the log's directory is made first, as the shell does not make it
    SHUI_UMakeDirectoryRecursive(SHUI_SDirectory(logPath));

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    // both POSIX shells and cmd.exe send the output and the errors to the file this way
    i32 result = SHUI_URunCommand(false, SHUI_Format("%s > \"%s\" 2>&1", command, logPath));

    if (result != 0)
    {
        // the end of the log tells why it failed
        SHUSlice text = SHUI_UReadFile(logPath);
        const char *start = (const char *)text.data + text.size;

        for (usz lines = 0; start > (const char *)text.data && lines <= 20; start--)
        {
            lines += start[-1] == '\n';
        }

        fprintf(SHU_LOG_STREAM, "%s\n", start);

#ifdef SHUC_NO_RUN_ERROR
        SHUI_Fail(0, "command failed with exit code %d; '%s' has its output: %s", result, SHUI_SShort(logPath), command);
#else
        SHUI_Fail(result, "command failed with exit code %d; '%s' has its output: %s", result, SHUI_SShort(logPath), command);
#endif
    }

    return result;
}

void SHU_UtilBuildScript(const char *script, const char *program, const char *flags, const char *arguments)
{
    SHU_AssertNullPointer(script);
    SHU_AssertNullPointer(program);
    SHU_AssertNullPointer(flags);
    SHU_AssertNullPointer(arguments);

    char *scriptPath = SHUI_SPath(SHUILD.currentExecutableDirectory, script, false);
    char *programPath = SHUI_SPath(SHUILD.currentExecutableDirectory, SHUI_Format("%s%s", program, SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? ".exe" : ""), false);

    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUI_CScriptCompiler());
    SHUI_CAddArgument(&command, "-o");
    SHUI_SLAdd(&command, programPath);
    SHUI_SLAdd(&command, scriptPath);
    SHUI_CAddArguments(&command, SHUILD_BUILD);
    SHUI_CAddArguments(&command, flags);
    SHUI_CRun(&command, true);

    // it runs in its own directory, as it would if it were run there by hand, and the build goes on here after it
    char *directory = SHUI_SDirectory(programPath);
    char *run = SHUI_Format("\"%s\" %s", programPath, arguments);

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    char *previous = _getcwd(NULL, 0);
    SHU_Assert(previous != NULL && _chdir(directory) == 0, "Cannot run '%s' in its directory.", programPath);
    SHUI_URunCommand(true, run);
    SHU_Assert(_chdir(previous) == 0, "Cannot go back to '%s'.", previous);
#else
    char *previous = getcwd(NULL, 0);
    SHU_Assert(previous != NULL && chdir(directory) == 0, "Cannot run '%s' in its directory.", programPath);
    SHUI_URunCommand(true, run);
    SHU_Assert(chdir(previous) == 0, "Cannot go back to '%s'.", previous);
#endif
}

i32 SHU_UtilSpawnProcessSync(const char *executable, char *const *argv)
{
    i32 result = 0;

#ifdef SHUC_LOG_COMMANDS
    SHUI_Log("$ %s", executable);
#endif

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    result = (i32)_spawnv(_P_WAIT, executable, (const char *const *)argv);
#else
    pid_t pid = fork();

    if (pid == 0)
    {
        execv(executable, argv);
        _exit(127);
    }
    else if (pid > 0)
    {
        int status;
        while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
        {
        }

        result = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
    else
    {
        result = -1;
    }
#endif

    SHUI_CReport(result, true, executable);

    return result;
}

const char *SHU_UtilGetExecutablePath(void)
{
    return SHUILD.currentExecutableDirectory;
}

SHUFileType SHU_UtilFileExists(const char *file)
{
    SHU_AssertNullPointer(file);

    return SHUI_UFileExists(SHUI_SPath(SHUILD.currentExecutableDirectory, file, false));
}

void SHU_UtilCreateDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    char *directoryPath = SHUI_SPath(SHUILD.currentExecutableDirectory, directory, true);

    if (SHUI_UFileExists(directoryPath) == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(directoryPath);
    }
}

void SHU_UtilDeleteFile(const char *file)
{
    SHU_AssertNullPointer(file);

    SHUI_UDeleteRecursive(SHUI_SPath(SHUILD.currentExecutableDirectory, file, false));
}

void SHU_UtilCopyFile(const char *file, const char *directory)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(directory);

    char *directoryPath = SHUI_SPath(SHUILD.currentExecutableDirectory, directory, false);
    char *filePath = SHUI_SPath(SHUILD.currentExecutableDirectory, file, false);

    if (SHUI_UFileExists(directoryPath) == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(directoryPath);
    }

    // a file goes into the directory under its own name, and a directory's contents go into it
    if (SHUI_UFileExists(filePath) == SHUFileType_Regular)
    {
        const char *name = file + strlen(file);

        while (name > file && !SHUI_SIsSeparator(name[-1]))
        {
            name--;
        }

        directoryPath = SHUI_SPath(SHUI_SPath(directoryPath, "", true), name, false);
    }

    SHUI_UCopyRecursive(filePath, directoryPath);
}

void SHU_UtilRenameFile(const char *file, const char *name)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(name);

    SHUI_URenameFile(SHUI_SPath(SHUILD.currentExecutableDirectory, file, false), SHUI_SPath(SHUILD.currentExecutableDirectory, name, false));
}

i64 SHU_GetFileEditTime(const char *file)
{
    SHU_AssertNullPointer(file);

    return SHUI_UGetFileEditTime(SHUI_SPath(SHUILD.currentExecutableDirectory, file, false)) / 1000000000LL;
}

static int SHUI_SCompare(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}

static void SHUI_UListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    char *path = SHUI_Format("%s%s", SHUILD.currentExecutableDirectory, directory);

    SHUI_StringList names = {0};

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd = {0};
    HANDLE hFind = FindFirstFileA(SHUI_Format("%s*", path), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHUI_Fail(SHUResult_ErrNotFound, "directory '%s' to list does not exist.", SHUI_SShort(path));
    }

    do
    {
        if (ffd.cFileName[0] != '.')
        {
            SHUI_SLAdd(&names, SHUI_Format("%s", ffd.cFileName));
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path);

    if (!dir)
    {
        SHUI_Fail(SHUResult_ErrNotFound, "directory '%s' to list does not exist.", SHUI_SShort(path));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            SHUI_SLAdd(&names, SHUI_Format("%s", entry->d_name));
        }
    }

    closedir(dir);
#endif

    if (names.count > 1)
    {
        qsort(names.data, names.count, sizeof(char *), SHUI_SCompare);
    }

    for (usz i = 0; i < names.count; i++)
    {
        SHUFileType type = SHUI_UFileExists(SHUI_Format("%s%s", path, names.data[i]));
        char *entryPath = SHUI_Format("%s%s%s", directory, names.data[i], type == SHUFileType_Directory ? SHUM_PATH_SEPARATOR_STR : "");

        function(entryPath, type, data);

        if (type == SHUFileType_Directory && recursive)
        {
            SHUI_UListDirectory(entryPath, recursive, function, data);
        }
    }
}

void SHU_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    SHU_AssertNullPointer(directory);
    SHU_AssertNullPointer(function);

    // the executable's own directory is listed with an empty path
    SHUI_UListDirectory(directory[0] == '\0' ? "" : SHUI_SPath("", directory, true), recursive, function, data);
}

bool SHU_UtilMatch(const char *string, const char *pattern)
{
    SHU_AssertNullPointer(string);
    SHU_AssertNullPointer(pattern);

    // after a '*', a mismatch goes back to it and lets it match one more character
    const char *starPattern = NULL;
    const char *starString = NULL;

    while (*string != '\0')
    {
        if (*pattern == '*')
        {
            starPattern = pattern++;
            starString = string;
        }
        else if (*pattern == '?' || *pattern == *string)
        {
            pattern++;
            string++;
        }
        else if (starPattern != NULL)
        {
            pattern = starPattern + 1;
            string = ++starString;
        }
        else
        {
            return false;
        }
    }

    while (*pattern == '*')
    {
        pattern++;
    }

    return *pattern == '\0';
}

SHUSlice SHU_UtilReadFile(const char *file)
{
    SHU_AssertNullPointer(file);

    return SHUI_UReadFile(SHUI_Format("%s%s", SHUILD.currentExecutableDirectory, file));
}

void SHU_UtilWriteFile(const char *file, SHUSliceView content)
{
    SHU_AssertNullPointer(file);

    SHUI_UWriteFile(SHUI_Format("%s%s", SHUILD.currentExecutableDirectory, file), content);
}

char *SHU_UtilLibraryFile(const char *name, SHUModuleType type)
{
    SHU_AssertNullPointer(name);
    SHU_Assert(type == SHUModuleType_LibraryStatic || type == SHUModuleType_LibraryDynamic, "Module type '%s' is not a library.", SHUModuleType_GetString(type));

    if (type == SHUModuleType_LibraryStatic)
    {
        return SHUI_Format("lib%s.a", name);
    }

    switch (SHUILD.COMPILER.target)
    {
    case SHUM_PLATFORM_WINDOWS:
        return SHUI_Format("%s.dll", name);
    case SHUM_PLATFORM_MACOS:
        return SHUI_Format("lib%s.dylib", name);
    default:
        return SHUI_Format("lib%s.so", name);
    }
}

#pragma endregion Utility

#ifdef SHUC_ENABLE_INCREMENTAL
#pragma region Cache

void SHU_CacheConfigure(const char *cacheDirectory)
{
    SHU_AssertNullPointer(cacheDirectory);

    SHUILD.cacheDirectory = SHUI_SPath(SHUILD.currentExecutableDirectory, cacheDirectory, true);

    SHUI_UMakeDirectoryRecursive(SHUILD.cacheDirectory);
}

void SHU_CacheClearModule(const char *moduleName)
{
    SHU_Assert(SHUILD.cacheDirectory != NULL, "Cache directory is not configured.");

    char *moduleCacheDirectory = SHUI_Format("%s%s", SHUILD.cacheDirectory, moduleName);

    if (SHUI_UFileExists(moduleCacheDirectory) != SHUFileType_Invalid)
    {
        SHUI_UDeleteRecursive(moduleCacheDirectory);
    }

    SHUI_UMakeDirectoryRecursive(moduleCacheDirectory);
}

void SHU_CacheClearAll(void)
{
    SHU_Assert(SHUILD.cacheDirectory != NULL, "Cache directory is not configured.");

    SHUI_UDeleteRecursive(SHUILD.cacheDirectory);
    SHUI_UMakeDirectoryRecursive(SHUILD.cacheDirectory);
}

#pragma endregion Cache

#endif // SHUC_ENABLE_INCREMENTAL

#pragma region Compiler

static char *SHUI_CExecutableDirectory(void)
{
    // the buffer grows until the whole path fits
    char *path = NULL;
    usz length = 0;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    for (DWORD size = 256;; size *= 2)
    {
        path = (char *)SHUI_Allocate(size);
        length = (usz)GetModuleFileNameA(NULL, (LPSTR)path, size);

        if (length < size)
        {
            break;
        }
    }
#elif SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_MACOS)
    u32 size = 0;
    _NSGetExecutablePath(NULL, &size);
    path = (char *)SHUI_Allocate(size);
    _NSGetExecutablePath(path, &size);
    length = (usz)strlen(path);
#else
    for (usz size = 256;; size *= 2)
    {
        path = (char *)SHUI_Allocate(size);
        ssize_t read = readlink("/proc/self/exe", path, size);
        SHU_Assert(read >= 0, "Internal: The executable's path cannot be read.");

        if ((usz)read < size)
        {
            length = (usz)read;
            break;
        }
    }
#endif

    while (length > 0 && path[length - 1] != SHUM_PATH_SEPARATOR)
    {
        length--;
    }
    path[length] = '\0';

    return path;
}

// a compiler's name on PATH is gcc or clang, maybe with a version (gcc-14) and the target's triple before it (x86_64-w64-mingw32-gcc), which has two dashes or more;
// other tools, such as gcc-ar, clang-format or c99-gcc, are not compilers to pick
static u8 SHUI_CNameCompiler(const char *name)
{
    const char *families[] = {"gcc", "clang"};
    const u8 identifiers[] = {SHUM_COMPILER_GCC, SHUM_COMPILER_CLANG};

    for (usz i = 0; i < sizeof(families) / sizeof(*families); i++)
    {
        for (const char *found = strstr(name, families[i]); found != NULL; found = strstr(found + 1, families[i]))
        {
            usz dashes = 0;

            for (const char *c = name; c < found; c++)
            {
                dashes += *c == '-';
            }

            bool prefixed = found == name || (found[-1] == '-' && dashes >= 2);
            const char *rest = found + strlen(families[i]);
            bool versioned = rest[0] == '\0' || (rest[0] == '-' && rest[1] != '\0' && strspn(rest + 1, "0123456789.") == strlen(rest + 1));

            if (prefixed && versioned)
            {
                return identifiers[i];
            }
        }
    }

    return SHUM_COMPILER_UNKNOWN;
}

// "14.2.0" is 140200, and "14" is 140000
static u32 SHUI_CParseVersion(const char *text)
{
    u32 parts[3] = {0};
    sscanf(text, "%u.%u.%u", &parts[0], &parts[1], &parts[2]);
    return parts[0] * 10000 + parts[1] * 100 + parts[2];
}

// the sanitizers need their libraries, which a compiler may not have, so a small program is compiled and linked with them
static bool SHUI_CHasSanitizers(const char *command)
{
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    (void)command;
    return false; // MinGW has no sanitizers
#else
    return system(SHUI_Format("printf 'int main(void){return 0;}' | %s -x c - -fsanitize=address,undefined -o /dev/null >/dev/null 2>&1", command)) == 0;
#endif
}

// the gcc and clang compilers on PATH, the first of each name, sorted by name; with sanitizers, each that compiles for the host is tried with them
static SHUCompilerInfo *SHUI_CFind(usz *retCount, bool sanitizers)
{
    SHUI_StringList names = {0};
    const char *path = getenv("PATH");

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    const char separator = ';';
#else
    const char separator = ':';
#endif

    while (path != NULL && *path != '\0')
    {
        const char *end = strchr(path, separator);
        usz length = end == NULL ? strlen(path) : (usz)(end - path);
        char *directory = SHUI_Format("%.*s", (int)length, path);
        path = end == NULL ? NULL : end + 1;

        if (length == 0)
        {
            continue;
        }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        WIN32_FIND_DATAA ffd = {0};
        HANDLE hFind = FindFirstFileA(SHUI_Format("%s\\*.exe", directory), &ffd);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            continue;
        }

        do
        {
            char *name = SHUI_Format("%.*s", (int)(strlen(ffd.cFileName) - 4), ffd.cFileName);
#else
        DIR *dir = opendir(directory);

        if (dir == NULL)
        {
            continue;
        }

        for (struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir))
        {
            char *name = SHUI_Format("%s", entry->d_name);

            if (access(SHUI_Format("%s/%s", directory, name), X_OK) != 0)
            {
                continue;
            }
#endif
            bool skip = SHUI_CNameCompiler(name) == SHUM_COMPILER_UNKNOWN;

            for (usz i = 0; i < names.count && !skip; i++)
            {
                skip = strcmp(names.data[i], name) == 0;
            }

            if (!skip)
            {
                SHUI_SLAdd(&names, name);
            }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        } while (FindNextFileA(hFind, &ffd));

        FindClose(hFind);
#else
        }

        closedir(dir);
#endif
    }

    if (names.count > 1)
    {
        qsort(names.data, names.count, sizeof(char *), SHUI_SCompare);
    }

    SHUCompilerInfo *compilers = calloc(names.count + 1, sizeof(SHUCompilerInfo));
    SHU_AssertNullPointer(compilers);

    for (usz i = 0; i < names.count; i++)
    {
        compilers[i].command = names.data[i];
        compilers[i].identifier = SHUI_CNameCompiler(names.data[i]);
        compilers[i].target = SHUI_CDetectTarget(names.data[i]);
        // gcc's -dumpversion may give only the major version, and clang knows no -dumpfullversion
        char *version = SHUI_CAsk(names.data[i], "-dumpfullversion");
        compilers[i].version = SHUI_CParseVersion(version[0] != '\0' ? version : SHUI_CAsk(names.data[i], "-dumpversion"));
        compilers[i].sanitizers = sanitizers && compilers[i].target == SHUM_HOST_PLATFORM && SHUI_CHasSanitizers(names.data[i]);
    }

    *retCount = names.count;
    return compilers;
}

// the newest compiler that compiles for the host, of the host compiler's family if one is found; a shorter name wins a tie, so gcc is kept over x86_64-linux-gnu-gcc
static const SHUCompilerInfo *SHUI_CPick(void)
{
    usz count = 0;
    const SHUCompilerInfo *compilers = SHUI_CFind(&count, false);
    const SHUCompilerInfo *best = NULL;

    for (usz i = 0; i < count; i++)
    {
        const SHUCompilerInfo *compiler = &compilers[i];

        if (compiler->target != SHUM_HOST_PLATFORM || compiler->version == 0)
        {
            continue;
        }

        if (best == NULL)
        {
            best = compiler;
            continue;
        }

        bool family = compiler->identifier == SHUM_HOST_COMPILER;
        bool bestFamily = best->identifier == SHUM_HOST_COMPILER;

        if (family != bestFamily)
        {
            best = family ? compiler : best;
        }
        else if (compiler->version != best->version)
        {
            best = compiler->version > best->version ? compiler : best;
        }
        else if (strlen(compiler->command) < strlen(best->command))
        {
            best = compiler;
        }
    }

    return best;
}

void SHU_CompilerConfigure(u8 compiler, const char *compilerCommand)
{
    SHU_AssertNullPointer(compilerCommand);

    SHUILD.COMPILER.identifier = compiler;
    SHUILD.COMPILER.command = SHUI_Format("%s", compilerCommand);
    SHUILD.COMPILER.target = SHUI_CDetectTarget(compilerCommand);

    if (SHUILD.currentExecutableDirectory == NULL)
    {
        SHUILD.currentExecutableDirectory = SHUI_CExecutableDirectory();

#ifdef SHUC_ENABLE_INCREMENTAL
        SHU_CacheConfigure(SHUC_DEFAULT_CACHE_DIRECTORY);
#endif
    }
}

void SHU_CompilerTryConfigure(const char *compilerCommand)
{
    if (compilerCommand == NULL || strlen(compilerCommand) == 0)
    {
        const SHUCompilerInfo *picked = SHUI_CPick();

        if (picked == NULL)
        {
            SHU_CompilerConfigure(SHUM_HOST_COMPILER, SHUM_COMPILER_GET_COMMAND(SHUM_HOST_COMPILER));
        }
        else
        {
            SHU_CompilerConfigure(picked->identifier, picked->command);
        }
    }
    else if (strstr(compilerCommand, "clang") != 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_CLANG, compilerCommand);
    }
    else if (strstr(compilerCommand, "gcc") != 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_GCC, compilerCommand);
    }
    else
    {
        SHUI_Fail(SHUResult_Err, "compiler '%s' is not known; configure it with SHU_CompilerConfigure.", compilerCommand);
    }
}

const SHUCompilerInfo *SHU_CompilerDetect(usz *retCount)
{
    SHU_AssertNullPointer(retCount);

    return SHUI_CFind(retCount, true);
}

static void SHUI_CAddFlag(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHUI_SLAdd(&SHUILD.COMPILER.flags, SHUI_Format("%s", flags));
}

void SHUI_CompilerAddFlags(const char *flags, ...)
{
    SHU_AssertNullPointer(flags);
    SHUI_EACH_ARGUMENT(flags, SHUI_CAddFlag);
}

void SHU_CompilerSetFlags(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHU_CompilerClearFlags();
    SHUI_CAddFlag(flags);
}

void SHU_CompilerClearFlags(void)
{
    SHUILD.COMPILER.flags.count = 0;
    SHUILD.COMPILER.linkerFlags.count = 0;
}

static void SHUI_CAddLinkerFlag(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHUI_SLAdd(&SHUILD.COMPILER.linkerFlags, SHUI_Format("%s", flags));
}

void SHUI_CompilerAddLinkerFlags(const char *flags, ...)
{
    SHU_AssertNullPointer(flags);
    SHUI_EACH_ARGUMENT(flags, SHUI_CAddLinkerFlag);
}

usz SHU_CompilerGetFlags(SHUSlice buffer)
{
    SHU_AssertNullPointer(buffer.data);

    SHU_Assert(buffer.size > 0, "Buffer for compiler flags is empty.");

    char *chars = (char *)buffer.data;
    usz bufferIndex = 0;

    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        i32 written = snprintf(chars + bufferIndex,
                               buffer.size - bufferIndex,
                               "%s ",
                               SHUILD.COMPILER.flags.data[i]);

        if (written < 0 || (usz)written >= buffer.size - bufferIndex)
        {
            SHUI_Warn("the buffer is too small for the compiler flags, so they are cut.");
            bufferIndex = buffer.size - 1;
            break;
        }

        bufferIndex += (usz)written;
    }

    chars[bufferIndex] = '\0';

    return bufferIndex;
}

void SHUI_CompilerAddDefinition(const char *macros, ...)
{
    va_list args;
    va_start(args, macros);

    // the arguments are names and values in pairs, until a NULL name
    while (macros != NULL)
    {
        const char *value = va_arg(args, const char *);

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        SHUI_SLAdd(&SHUILD.COMPILER.flags, value == NULL ? SHUI_Format("-D%s", macros) : SHUI_Format("-D%s=\"\"%s\"\"", macros, value));
#else
        SHUI_SLAdd(&SHUILD.COMPILER.flags, value == NULL ? SHUI_Format("-D%s", macros) : SHUI_Format("-D%s='%s'", macros, value));
#endif

        macros = va_arg(args, const char *);
    }

    va_end(args);
}

u8 SHU_CompilerGetIdentifier(void)
{
    return SHUILD.COMPILER.identifier;
}

u8 SHU_CompilerGetTarget(void)
{
    return SHUILD.COMPILER.target;
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name, const char *root)
{
    SHU_AssertNullPointer(name);

    SHUILD.MODULE.name = SHUI_Format("%s", name);
    SHUILD.MODULE.root = root != NULL && strlen(root) != 0 ? SHUI_SPath(SHUILD.currentExecutableDirectory, root, true) : SHUILD.currentExecutableDirectory;
}

static void SHUI_MAddIncludeDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    SHUI_SLAdd(&SHUILD.MODULE.includeDirectories, SHUI_SPath(SHUILD.MODULE.root, directory, true));
}

void SHUI_ModuleAddIncludeDirectory(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_MAddIncludeDirectory);
}

static void SHUI_MAddPublicIncludeDirectory(const char *directory)
{
    SHUI_MAddIncludeDirectory(directory);
    SHUI_SLAdd(&SHUILD.MODULE.publicIncludeDirectories, SHUILD.MODULE.includeDirectories.data[SHUILD.MODULE.includeDirectories.count - 1]);
}

void SHUI_ModuleAddPublicIncludeDirectory(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_MAddPublicIncludeDirectory);
}

static void SHUI_MAddSourceFile(const char *file)
{
    SHU_AssertNullPointer(file);

    char *path = SHUI_SPath(SHUILD.MODULE.root, file, false);

    SHUFileType fileType = SHUI_UFileExists(path);
    if (fileType == SHUFileType_Directory)
    {
        SHUI_MAddSourceDirectoryRecursive(SHUI_SPath(path, "", true));
    }
    else if (fileType == SHUFileType_Regular)
    {
        SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, path);
    }
    else
    {
        SHUI_Fail(SHUResult_ErrNotFound, "source '%s' does not exist.", SHUI_SShort(path));
    }
}

void SHUI_ModuleAddSourceFile(const char *file, ...)
{
    SHU_AssertNullPointer(file);
    SHUI_EACH_ARGUMENT(file, SHUI_MAddSourceFile);
}

void SHU_ModuleCompile(const char *directory, SHUModuleType module)
{
    char *directoryPath = SHUILD.currentExecutableDirectory;

    if (directory != NULL && strlen(directory) != 0)
    {
        directoryPath = SHUI_SPath(SHUILD.currentExecutableDirectory, directory, true);

        if (SHUI_UFileExists(directoryPath) != SHUFileType_Directory)
        {
            SHUI_UMakeDirectoryRecursive(directoryPath);
        }
    }

    // its settings, such as its flags, are new or changed, so every file compiles again
    bool settingsChanged = false;

#ifdef SHUC_ENABLE_INCREMENTAL
    // a module compiled for the first time has no settings to change
    bool cached = SHUI_UFileExists(SHUI_CModuleStateFile(SHUILD.MODULE.name)) == SHUFileType_Regular;

    if (SHUI_CModuleStateDirty(SHUILD.MODULE.name))
    {
        SHU_CacheClearModule(SHUILD.MODULE.name);
        SHUI_CModuleStateUpdate(SHUILD.MODULE.name);
        settingsChanged = cached;
    }
#endif

    SHUI_MAddLinkedIncludes();

    if (module != SHUModuleType_LibraryStatic)
    {
        SHUI_MExpandLinks();
    }

    switch (module)
    {
    case SHUModuleType_Executable:
        SHUI_MCompileExecutable(directoryPath);
        break;
    case SHUModuleType_LibraryStatic:
        SHUI_MCompileLibraryStatic(directoryPath);
        break;
    case SHUModuleType_LibraryDynamic:
        SHUI_MCompileLibraryDynamic(directoryPath);
        break;
    default:
        SHUI_Fail(SHUResult_Err, "module type %d is not known.", (int)module);
        break;
    }

    if (SHUILD.MODULE.copyDynamicLinks && module != SHUModuleType_LibraryStatic)
    {
        SHUI_MCopyDynamicLinks(directoryPath);
    }

    if (module != SHUModuleType_Executable)
    {
        SHUI_MRecordLibrary(module == SHUModuleType_LibraryStatic);
    }

#ifndef SHUC_NO_MODULE_LOG
    // one line for the module: what it compiled and made, or that it was up to date
    if (SHUILD.MODULE.output == NULL)
    {
        SHUI_Log("%s (%s): up to date", SHUILD.MODULE.name, SHUModuleType_GetString(module));
    }
    else
    {
        SHUI_Log("%s (%s): compiled %zu file%s, %s %s%s",
                 SHUILD.MODULE.name,
                 SHUModuleType_GetString(module),
                 SHUILD.MODULE.compiledCount,
                 SHUILD.MODULE.compiledCount == 1 ? "" : "s",
                 module == SHUModuleType_LibraryStatic ? "packed" : "linked",
                 SHUI_SShort(SHUILD.MODULE.output),
                 settingsChanged ? " (settings changed)" : "");
    }
#else
    (void)settingsChanged;
#endif

    // the next module starts with new lists, as a library's record keeps these
    SHUILD.MODULE = (__typeof__(SHUILD.MODULE)){0};
}

static void SHUI_MAddLibraryDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    char *path = SHUI_SPath(SHUILD.currentExecutableDirectory, directory, true);

    if (SHUI_UFileExists(path) != SHUFileType_Directory)
    {
        SHUI_Fail(SHUResult_ErrNotFound, "library directory '%s' does not exist.", SHUI_SShort(path));
    }

    SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, path);
}

void SHUI_ModuleAddLibraryDirectory(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_MAddLibraryDirectory);
}

static void SHUI_MLinkLibrary(const char *library)
{
    SHU_AssertNullPointer(library);

    SHUI_SLAdd(&SHUILD.MODULE.links, SHUI_Format("%s", library));
}

void SHUI_ModuleLinkLibrary(const char *library, ...)
{
    SHU_AssertNullPointer(library);
    SHUI_EACH_ARGUMENT(library, SHUI_MLinkLibrary);
}

void SHU_ModuleCopyDynamicLinks(void)
{
    SHUILD.MODULE.copyDynamicLinks = true;
}

#pragma endregion Module

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
