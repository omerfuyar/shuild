// Define these before including shuild.h:
// SHU_IMPLEMENTATION in one file, to include the implementation.
// SHUC_ENABLE_INCREMENTAL to compile only what changed.
// SHUC_NO_MODULE_LOG to log no line for each module.
// SHUC_COMPILE_DATABASE to write compile_commands.json beside the build script, which clangd and clang-tidy read.
// SHUC_LOG_COMMANDS to log every command, not only failed ones.
// SHUC_MAX_JOB_COUNT <count> to compile at most that many files at once. (eg. 1)
// SHUC_ARRAY_INITIAL_COUNT <count> to set the first capacity of shuild's lists.

#pragma once

#ifndef SHU_HEADER
#ifdef SHU
#include SHU
#else
#include "../shu/shu.h"
#endif
#endif

/// @brief The flags that build scripts compile with.
#define SHUILD_BUILD "-O3 -Wno-format-truncation"

#pragma region Platform Detection

/// @brief A system that a compiler compiles for, or that shuild runs on.
typedef enum SHUPlatform
{
    SHUPlatform_Unknown = 0,
    SHUPlatform_Windows = 1,
    SHUPlatform_Linux = 2,
    SHUPlatform_MacOS = 3,
} SHUPlatform;

// the preprocessor cannot read enums, so SHUM_HOST_PLATFORM is the enum's number, and #if checks the host with SHUM_HOST_WINDOWS, SHUM_HOST_LINUX and SHUM_HOST_MACOS, each 1 or 0
#if defined(_WIN32)
#define SHUM_HOST_WINDOWS 1
#define SHUM_HOST_LINUX 0
#define SHUM_HOST_MACOS 0
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 1
#elif defined(__linux__)
#define SHUM_HOST_WINDOWS 0
#define SHUM_HOST_LINUX 1
#define SHUM_HOST_MACOS 0
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 2
#elif defined(__APPLE__) && defined(__MACH__)
#define SHUM_HOST_WINDOWS 0
#define SHUM_HOST_LINUX 0
#define SHUM_HOST_MACOS 1
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 3
#else
#define SHUM_HOST_WINDOWS 0
#define SHUM_HOST_LINUX 0
#define SHUM_HOST_MACOS 0
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 0
#endif

/// @brief Get the name of the given platform.
#define SHUPlatform_GetString(platform) (platform == SHUPlatform_Linux     ? "Linux"   \
                                         : platform == SHUPlatform_Windows ? "Windows" \
                                         : platform == SHUPlatform_MacOS   ? "MacOS"   \
                                                                           : "Unknown")

/// @brief Either the given platform is the host's or not. It reads an enum, so it does not work in #if; use SHUM_HOST_<...> there.
#define SHUM_PLATFORM_IS_HOST(platform) (SHUM_HOST_PLATFORM == (platform))

#pragma endregion Platform Detection

#pragma region Compiler Detection

/// @brief A family of compilers.
typedef enum SHUCompiler
{
    SHUCompiler_Unknown = 0,
    SHUCompiler_Clang = 1,
    SHUCompiler_GCC = 2,
} SHUCompiler;

#if defined(__clang__)
/// @brief The family of the compiler that compiles this file, a SHUCompiler.
#define SHUM_HOST_COMPILER 1
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
/// @brief The family of the compiler that compiles this file, a SHUCompiler.
#define SHUM_HOST_COMPILER 2
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
/// @brief The family of the compiler that compiles this file, a SHUCompiler.
#define SHUM_HOST_COMPILER 0
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION 0
#endif

/// @brief Get the name of the given compiler.
#define SHUCompiler_GetString(compiler) (compiler == SHUCompiler_Clang ? "Clang" \
                                         : compiler == SHUCompiler_GCC ? "GCC"   \
                                                                       : "Unknown")

/// @brief Get the command of the given compiler.
#define SHUCompiler_GetCommand(compiler) (compiler == SHUCompiler_Clang ? "clang" \
                                          : compiler == SHUCompiler_GCC ? "gcc"   \
                                                                        : "Unknown")

#pragma endregion Compiler Detection

#pragma region Configurations and Constants

#ifndef SHUC_ARRAY_INITIAL_COUNT
#define SHUC_ARRAY_INITIAL_COUNT 16
#endif

#ifndef SHUC_MAX_JOB_COUNT
#define SHUC_MAX_JOB_COUNT 64
#endif

#ifdef SHUC_ENABLE_INCREMENTAL
#define SHUC_DEFAULT_CACHE_DIRECTORY ".shu/"
#endif

// each is one string of flags, one argument of SHU_CompilerAddFlags (eg. SHU_CompilerAddFlags(SHUM_FLAGS_DEBUG, SHUM_FLAGS_OPTIMIZATION_DEBUG))
#define SHUM_FLAGS_DEBUG "-g"

#define SHUM_FLAGS_OPTIMIZATION_DEBUG "-Og"
#define SHUM_FLAGS_OPTIMIZATION_SIZE "-Os"
#define SHUM_FLAGS_OPTIMIZATION_LOW "-O1"
#define SHUM_FLAGS_OPTIMIZATION_MID "-O2"
#define SHUM_FLAGS_OPTIMIZATION_HIGH "-O3"

#define SHUM_FLAGS_WARNING_LOW "-Wall -Wextra"
#define SHUM_FLAGS_WARNING_MID "-Wall -Wextra -Wshadow -Wpedantic -Wconversion -Wformat=2 -fstack-protector-strong"
#define SHUM_FLAGS_WARNING_HIGH "-Wall -Wextra -Wshadow -Wpedantic -Wconversion -fstack-protector-strong -Wpointer-arith -Wcast-align -Wcast-qual -Wformat=2 -Winit-self -Wmissing-declarations -Wredundant-decls -Wsign-conversion -Wpointer-to-int-cast -Wint-to-pointer-cast"
#define SHUM_FLAGS_WARNING_ERROR "-Werror"

#define SHUM_FLAGS_STANDARD_C89 "-std=c89"
#define SHUM_FLAGS_STANDARD_C99 "-std=c99"
#define SHUM_FLAGS_STANDARD_C11 "-std=c11"
#define SHUM_FLAGS_STANDARD_C17 "-std=c17"
#define SHUM_FLAGS_STANDARD_C23 "-std=c23"
#define SHUM_FLAGS_STANDARD_C2Y "-std=c2y"
#define SHUM_FLAGS_STANDARD_C2X "-std=c2x"

#define SHUM_COLOR_RESET "\x1b[0m"
#define SHUM_COLOR_RED(string) "\x1b[31m" string SHUM_COLOR_RESET
#define SHUM_COLOR_GREEN(string) "\x1b[32m" string SHUM_COLOR_RESET
#define SHUM_COLOR_YELLOW(string) "\x1b[33m" string SHUM_COLOR_RESET
#define SHUM_COLOR_BLUE(string) "\x1b[34m" string SHUM_COLOR_RESET
#define SHUM_COLOR_MAGENTA(string) "\x1b[35m" string SHUM_COLOR_RESET
#define SHUM_COLOR_CYAN(string) "\x1b[36m" string SHUM_COLOR_RESET
#define SHUM_COLOR_WHITE(string) "\x1b[37m" string SHUM_COLOR_RESET
#define SHUM_COLOR_BOLD(string) "\x1b[1m" string SHUM_COLOR_RESET
#define SHUM_COLOR_DIM(string) "\x1b[2m" string SHUM_COLOR_RESET

// the colours of the parts of log lines; shuild's own lines use them, and a build script's lines with SHU_UtilLog can too (eg. "built " SHUM_LOG_NAME("%s"))
#define SHUM_LOG_NAME(string) SHUM_COLOR_MAGENTA(string)  // a module, a library or a project
#define SHUM_LOG_PATH(string) SHUM_COLOR_CYAN(string)     // a file or a directory
#define SHUM_LOG_COMMAND(string) SHUM_COLOR_DIM(string)   // a command line
#define SHUM_LOG_VALUE(string) SHUM_COLOR_BOLD(string)    // a setting's value, such as a build type or a compiler

#if SHUM_HOST_WINDOWS
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
    SHUFileType_Invalid, // missing
    SHUFileType_Regular,
    SHUFileType_Directory,
} SHUFileType;

typedef enum SHUModuleType
{
    SHUModuleType_Executable,
    SHUModuleType_LibraryStatic,
    SHUModuleType_LibraryDynamic,
} SHUModuleType;

/// @brief Get the name of the given file type.
#define SHUFileType_GetString(type) (type == SHUFileType_Regular     ? "Regular"   \
                                     : type == SHUFileType_Directory ? "Directory" \
                                                                     : "Invalid")

/// @brief Get the name of the given module type.
#define SHUModuleType_GetString(type) (type == SHUModuleType_Executable       ? "Executable"      \
                                       : type == SHUModuleType_LibraryStatic  ? "Static Library"  \
                                       : type == SHUModuleType_LibraryDynamic ? "Dynamic Library" \
                                                                              : "Unknown")

/// @brief Get the name of the given module type as log lines show it, in its colour.
#define SHUModuleType_GetLogString(type) (type == SHUModuleType_Executable       ? SHUM_COLOR_GREEN("Executable") \
                                          : type == SHUModuleType_LibraryStatic  ? SHUM_COLOR_BLUE("Static")      \
                                          : type == SHUModuleType_LibraryDynamic ? SHUM_COLOR_YELLOW("Dynamic")   \
                                                                                 : "Unknown")

/// @brief A compiler that SHU_CompilerDetect found.
typedef struct SHUCompilerInfo
{
    const char *command; // as found on PATH (eg. gcc-14, x86_64-w64-mingw32-clang)
    SHUCompiler family;
    SHUPlatform target;  // the system it compiles for
    const char *machine; // its target as it names it (eg. x86_64-linux-gnu), or ""
    u32 version;         // major * 10000 + minor * 100 + patch
    bool sanitizers;     // it can build with -fsanitize=address,undefined
} SHUCompilerInfo;

/// @brief Called by SHU_UtilListDirectory for each entry. A directory's path ends with a separator. (eg. src/utils/)
typedef void (*SHUListFunction)(const char *path, SHUFileType type, void *data);

// every path that shuild takes is relative to the build script's directory, unless it says otherwise

#pragma region Shuild

/// @brief Sets shuild up with the newest compiler on PATH for this system. Call it first. To choose the compiler, call SHU_CompilerConfigureTry or SHU_CompilerConfigure instead.
#define SHU_InitializeShuild() SHU_CompilerConfigureTry(NULL)

/// @brief Compiles another build script with the configured compiler and SHUILD_BUILD, and runs it in its own directory.
/// @param script The build script. (eg. plugins/shuild.c)
/// @param program The program to compile it into, without .exe. (eg. plugins/shuild)
/// @param flags More compiler flags, or "". (eg. -Idependencies)
/// @param arguments Arguments for the program, or "". (eg. -b release)
void SHU_Shuild(const char *script, const char *program, const char *flags, const char *arguments);

///!!! Use SHU_UtilAutomate. !!!
void SHUI_UtilAutomate(int argc, char **argv, const char *sourceFile);

/// @brief Rebuilds and reruns the build script when its source or shuild changed. Call it after configuring the compiler.
#define SHU_UtilAutomate(argc, argv) SHUI_UtilAutomate(argc, argv, __FILE__)

#pragma endregion Shuild

#pragma region Utility

/// @brief Logs a line as shuild does. The SHUM_LOG_ macros colour its parts. (eg. "built " SHUM_LOG_NAME("%s"))
void SHU_UtilLog(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Logs a warning.
void SHU_UtilWarn(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Logs an error and ends the build.
void SHU_UtilFail(const char *format, ...) __attribute__((noreturn, format(printf, 1, 2)));

/// @brief Formats a string as printf does. Free it with free.
char *SHU_UtilFormat(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a shell command. The build ends if it fails.
void SHU_UtilRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a shell command. A failure is only a warning.
/// @return The command's exit code.
i32 SHU_UtilRunTry(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a shell command with its output in a log file. If it fails, the end of the log is shown and the build ends.
/// @param log The log file. (eg. .shu/cmake.log)
void SHU_UtilRunLogged(const char *log, const char *commandFormat, ...) __attribute__((format(printf, 2, 3)));

/// @brief Gets the build script's directory, with a separator at its end. Do not free it.
const char *SHU_UtilGetScriptDirectory(void);

/// @brief Gets a path's full path, with the system's separators, as a command takes it. Free it with free.
char *SHU_UtilGetPath(const char *path);

/// @brief Gets a file's type: SHUFileType_Invalid if it does not exist.
SHUFileType SHU_UtilFileExists(const char *file);

/// @brief Creates a directory and its parents, if they do not exist.
void SHU_UtilCreateDirectory(const char *directory);

/// @brief Deletes a file, or a directory with what it holds, if it exists.
void SHU_UtilDeleteFile(const char *file);

/// @brief Copies a file, or a directory's contents, into a directory. A copy with the same content is left as is, so it does not compile again.
void SHU_UtilCopyFile(const char *file, const char *directory);

/// @brief Calls a function for each entry of a directory, sorted by name, without the ones that start with a dot.
/// @param directory The directory, or "" for the build script's. (eg. src/)
/// @param recursive Lists subdirectories too, each after its own entry.
/// @param data Given to the function. Can be NULL.
void SHU_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data);

/// @brief Checks a string against a pattern, where '*' matches any characters and '?' one. (eg. "*.c")
bool SHU_UtilMatch(const char *string, const char *pattern);

/// @brief Reads a whole file, with a zero after it that the size does not count. Free its data with free.
SHUSlice SHU_UtilReadFile(const char *file);

/// @brief Writes a file. A file with the same content is left as is, so it does not compile again.
void SHU_UtilWriteFile(const char *file, SHUSliceView content);

/// @brief Gets the file a library compiles into, on the compiler's target. (eg. libmath.a, libmath.so, libmath.dll.a) Free it with free.
/// @param type SHUModuleType_LibraryStatic or SHUModuleType_LibraryDynamic.
char *SHU_UtilLibraryFile(const char *name, SHUModuleType type);

#pragma endregion Utility

#ifdef SHUC_ENABLE_INCREMENTAL

#pragma region Cache

/// @brief Sets the cache directory of incremental builds. It is .shu/ by default.
void SHU_CacheConfigure(const char *cacheDirectory);

#pragma endregion Cache

#endif

#pragma region Compiler

/// @brief Sets the compiler. Call it first, or SHU_InitializeShuild or SHU_CompilerConfigureTry instead.
/// @param command The compiler's command. (eg. clang)
void SHU_CompilerConfigure(SHUCompiler family, const char *command);

/// @brief Sets the compiler, and asks it for its family.
/// @param command The compiler's command, or NULL for the newest compiler on PATH that compiles for this system. (eg. gcc)
void SHU_CompilerConfigureTry(const char *command);

/// @brief Finds the gcc and clang compilers on PATH, cross compilers included, with their family, version and target.
/// @param retCount The number of compilers found.
/// @return The compilers, sorted by name. Do not free them.
SHUCompilerInfo *SHU_CompilerDetect(usz *retCount);

///!!! Use SHU_CompilerAddFlags. !!!
void SHUI_CompilerAddFlags(const char *flags, ...);

/// @brief Adds compiler flags: one string or more, each with flags quoted as in a shell. (eg. "-DFOO=31", "-Wall")
#define SHU_CompilerAddFlags(flags, ...) SHUI_CompilerAddFlags(flags, ##__VA_ARGS__, NULL)

/// @brief Clears the compiler flags and the linker flags.
void SHU_CompilerClearFlags(void);

///!!! Use SHU_CompilerAddLinkerFlags. !!!
void SHUI_CompilerAddLinkerFlags(const char *flags, ...);

/// @brief Adds flags that only linking gets. (eg. "-Wl,--as-needed")
#define SHU_CompilerAddLinkerFlags(flags, ...) SHUI_CompilerAddLinkerFlags(flags, ##__VA_ARGS__, NULL)

///!!! Use SHU_CompilerAddDefinitions. !!!
void SHUI_CompilerAddDefinitions(const char *name, ...);

/// @brief Defines macros, as names and values in pairs; a NULL value defines a macro without one. (eg. "DEBUG", NULL, "SIZE", "31")
#define SHU_CompilerAddDefinitions(name, ...) SHUI_CompilerAddDefinitions(name, ##__VA_ARGS__, NULL)

/// @brief Gets the configured compiler's family.
SHUCompiler SHU_CompilerGetFamily(void);

/// @brief Gets the system the configured compiler compiles for.
SHUPlatform SHU_CompilerGetTarget(void);

/// @brief Gets the command of a tool of the compiler, with the compiler's prefix and version. (eg. g++-14 for gcc-14) Free it with free.
/// @param gccTool The tool's name for gcc. (eg. g++, gcc-ar)
/// @param clangTool The tool's name for clang. (eg. clang++, llvm-ar)
char *SHU_CompilerGetTool(const char *gccTool, const char *clangTool);

#pragma endregion Compiler

#pragma region Module

///!!! Use SHU_Module. !!!
void SHUI_ModuleBegin(const char *name, const char *root);

///!!! Use SHU_Module. !!!
void SHUI_ModuleCompile(SHUModuleType type, const char *directory);

/// @brief Compiles a module when its block ends. The other Module functions go in the block. A break or return out of the block leaves it uncompiled.
/// (eg. SHU_Module("app", NULL, SHUModuleType_Executable, "build/") { SHU_ModuleAddSourceFiles("src/"); })
/// @param name The module's name, which names its file.
/// @param root The directory its files are relative to, or NULL for the build script's.
/// @param directory The directory to compile it into, or NULL for the build script's.
#define SHU_Module(name, root, type, directory) \
    for (int shuiModuleDone = (SHUI_ModuleBegin(name, root), 0); !shuiModuleDone; shuiModuleDone = 1, SHUI_ModuleCompile(type, directory))

///!!! Use SHU_ModuleAddIncludeDirectories. !!!
void SHUI_ModuleAddIncludeDirectories(const char *directory, ...);

/// @brief Adds include directories, relative to the module's root. (eg. "include/")
#define SHU_ModuleAddIncludeDirectories(directory, ...) SHUI_ModuleAddIncludeDirectories(directory, ##__VA_ARGS__, NULL)

///!!! Use SHU_ModuleAddPublicIncludeDirectories. !!!
void SHUI_ModuleAddPublicIncludeDirectories(const char *directory, ...);

/// @brief Adds include directories, relative to the module's root, that the modules linking this library get too, as system headers.
#define SHU_ModuleAddPublicIncludeDirectories(directory, ...) SHUI_ModuleAddPublicIncludeDirectories(directory, ##__VA_ARGS__, NULL)

///!!! Use SHU_ModuleAddSourceFiles. !!!
void SHUI_ModuleAddSourceFiles(const char *file, ...);

/// @brief Adds source files, or directories with all they hold, relative to the module's root. A header compiles as C. (eg. "main.c", "src/")
#define SHU_ModuleAddSourceFiles(file, ...) SHUI_ModuleAddSourceFiles(file, ##__VA_ARGS__, NULL)

///!!! Use SHU_ModuleAddLibraryDirectories. !!!
void SHUI_ModuleAddLibraryDirectories(const char *directory, ...);

/// @brief Adds directories to find linked libraries in. On Linux and macOS, the module finds its dynamic libraries there at run time too. (eg. "build/lib/")
#define SHU_ModuleAddLibraryDirectories(directory, ...) SHUI_ModuleAddLibraryDirectories(directory, ##__VA_ARGS__, NULL)

///!!! Use SHU_ModuleLinkLibraries. !!!
void SHUI_ModuleLinkLibraries(const char *library, ...);

/// @brief Links libraries by name, in order. A static library passes them on to the modules that link it. (eg. "math")
#define SHU_ModuleLinkLibraries(library, ...) SHUI_ModuleLinkLibraries(library, ##__VA_ARGS__, NULL)

/// @brief Copies the module's dynamic libraries beside it, as Windows finds them there.
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
#include <signal.h>

#if SHUM_HOST_WINDOWS
#include <windows.h>
#include <process.h>
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#endif

#if SHUM_HOST_MACOS
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

// a failed command is shown whole, so it can be run again by hand
#define SHUI_COMMAND_FAILED "command failed with exit code %d: " SHUM_LOG_COMMAND("%s")

// a string list owns its strings
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
/// @brief How a module's settings compare with the ones it was compiled with last.
typedef enum SHUI_SettingsState
{
    SHUI_SettingsState_New,
    SHUI_SettingsState_Changed,
    SHUI_SettingsState_Same,
} SHUI_SettingsState;
#endif

static struct
{
    char *scriptDirectory; // found the first time it is needed

#ifdef SHUC_ENABLE_INCREMENTAL
    char *cacheDirectory;
#endif

    struct
    {
        SHUCompiler family;
        SHUPlatform target; // the platform it compiles for
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
        bool failed;
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
    } MODULE;

    // the libraries compiled so far, with what the modules that link them get
    struct
    {
        usz count;
        usz capacity;
        SHUI_Library *data;
    } LIBRARIES;

#ifndef SHUC_ENABLE_INCREMENTAL
    SHUI_StringList temporaryObjects; // the objects beside their sources, which are deleted after linking, or when the build fails before it
#endif

#if defined(SHUC_COMPILE_DATABASE) && !defined(SHUC_ENABLE_INCREMENTAL)
    SHUI_StringList databaseEntries; // the compile commands of every module so far, as JSON objects; with incremental builds, each module keeps its own in the cache
#endif
} SHUILD = {0};

#pragma region Basics

static void *SHUI_Allocate(usz size)
{
    void *memory = malloc(size);
    SHU_Assert(memory != NULL, "Internal: Memory allocation failed for size '%zu'.", size);

    return memory;
}

static void *SHUI_Reallocate(void *memory, usz size)
{
    void *grown = realloc(memory, size);
    SHU_Assert(grown != NULL, "Internal: Memory allocation failed for size '%zu'.", size);

    return grown;
}

static usz SHUI_GrowCapacity(usz capacity)
{
    return capacity == 0 ? SHUC_ARRAY_INITIAL_COUNT : capacity * 2;
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

static char *SHUI_Copy(const char *string)
{
    usz length = (usz)strlen(string);
    char *copy = (char *)SHUI_Allocate(length + 1);
    memcpy(copy, string, length + 1);

    return copy;
}

static bool SHUI_EndsWith(const char *string, const char *suffix)
{
    usz stringLength = (usz)strlen(string);
    usz suffixLength = (usz)strlen(suffix);

    return stringLength >= suffixLength && strcmp(string + stringLength - suffixLength, suffix) == 0;
}

static int SHUI_CompareStrings(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}

// shuild's own messages are one short line each, with paths from the build script's directory
static void SHUI_LogLine(const char *prefix, const char *format, va_list args)
{
    fprintf(SHU_LOG_STREAM, SHUM_COLOR_BOLD("[shuild]") " %s", prefix);
    vfprintf(SHU_LOG_STREAM, format, args);
    fputc('\n', SHU_LOG_STREAM);
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

void SHU_UtilLog(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine("", format, args);
    va_end(args);
}

void SHU_UtilWarn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_YELLOW("warning: "), format, args);
    va_end(args);
}

// an error that does not end the build by itself, such as one of several jobs that fail
static __attribute__((format(printf, 1, 2))) void SHUI_LogError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_RED("error: "), format, args);
    va_end(args);
}

void SHU_UtilFail(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_RED("error: "), format, args);
    va_end(args);

    exit(EXIT_FAILURE);
}

#pragma endregion Basics

#pragma region Builder

static void SHUI_BuilderAppendChar(SHUI_Builder *builder, char character)
{
    if (builder->length + 1 >= builder->capacity)
    {
        usz capacity = SHUI_GrowCapacity(builder->capacity);
        builder->data = (char *)SHUI_Reallocate(builder->data, capacity);
        builder->capacity = capacity;
    }

    builder->data[builder->length++] = character;
    builder->data[builder->length] = '\0';
}

static void SHUI_BuilderAppend(SHUI_Builder *builder, const char *string)
{
    for (const char *c = string; *c != '\0'; c++)
    {
        SHUI_BuilderAppendChar(builder, *c);
    }
}

// the string is the caller's, and the builder starts a new one
static char *SHUI_BuilderTake(SHUI_Builder *builder)
{
    char *string = builder->data == NULL ? SHUI_Copy("") : builder->data;
    *builder = (SHUI_Builder){0};

    return string;
}

#pragma endregion Builder

#pragma region List

static void SHUI_ListAdd(SHUI_StringList *list, char *string)
{
    if (list->count >= list->capacity)
    {
        usz capacity = SHUI_GrowCapacity(list->capacity);
        list->data = (char **)SHUI_Reallocate(list->data, sizeof(char *) * capacity);
        list->capacity = capacity;
    }

    list->data[list->count++] = string;
}

static void SHUI_ListFree(SHUI_StringList *list)
{
    for (usz i = 0; i < list->count; i++)
    {
        free(list->data[i]);
    }

    free(list->data);
    *list = (SHUI_StringList){0};
}

static bool SHUI_ListContains(const SHUI_StringList *list, const char *string)
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

static void SHUI_ListSort(SHUI_StringList *list)
{
    qsort(list->data, list->count, sizeof(char *), SHUI_CompareStrings);
}

#pragma endregion List

#pragma region Path

static bool SHUI_PathIsSeparator(char character)
{
    return character == '/' || character == SHUM_PATH_SEPARATOR;
}

static void SHUI_PathUseSystemSeparators(char *path)
{
#if SHUM_HOST_WINDOWS
    for (char *c = path; *c != '\0'; c++)
    {
        if (*c == '/')
        {
            *c = '\\';
        }
    }
#else
    (void)path;
#endif
}

static char *SHUI_PathProgramDirectory(void)
{
    // the buffer grows until the whole path fits
    char *path = NULL;
    usz length = 0;

#if SHUM_HOST_WINDOWS
    for (DWORD size = 256;; size *= 2)
    {
        path = (char *)SHUI_Reallocate(path, size);
        length = (usz)GetModuleFileNameA(NULL, (LPSTR)path, size);

        if (length < size)
        {
            break;
        }
    }
#elif SHUM_HOST_MACOS
    u32 size = 0;
    _NSGetExecutablePath(NULL, &size);
    path = (char *)SHUI_Allocate(size);
    _NSGetExecutablePath(path, &size);
    length = (usz)strlen(path);
#else
    for (usz size = 256;; size *= 2)
    {
        path = (char *)SHUI_Reallocate(path, size);
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

// the directory of the program that the build script is compiled into, where the paths that shuild takes start
static const char *SHUI_PathScriptDirectory(void)
{
    if (SHUILD.scriptDirectory == NULL)
    {
        SHUILD.scriptDirectory = SHUI_PathProgramDirectory();
    }

    return SHUILD.scriptDirectory;
}

/// @brief Joins a directory and a path in it, with a separator between them. On Windows, the separators are backslashes. (eg. build and bin/app is build/bin/app)
static char *SHUI_PathJoin(const char *directory, const char *path)
{
    usz length = (usz)strlen(directory);
    bool separator = length != 0 && path[0] != '\0' && !SHUI_PathIsSeparator(directory[length - 1]);

    char *joined = SHU_UtilFormat("%s%s%s", directory, separator ? "/" : "", path);
    SHUI_PathUseSystemSeparators(joined);

    return joined;
}

/// @brief Joins a directory and a directory in it, as SHUI_PathJoin does, with a separator at the end unless the path is empty.
static char *SHUI_PathJoinDirectory(const char *directory, const char *path)
{
    char *joined = SHUI_PathJoin(directory, path);
    usz length = (usz)strlen(joined);

    if (length == 0 || SHUI_PathIsSeparator(joined[length - 1]))
    {
        return joined;
    }

    return SHU_UtilFormat("%s" SHUM_PATH_SEPARATOR_STR, joined);
}

static char *SHUI_PathFromScript(const char *path)
{
    return SHUI_PathJoin(SHUI_PathScriptDirectory(), path);
}

// a path from the build script's directory, for logs
static const char *SHUI_PathForLog(const char *path)
{
    const char *directory = SHUI_PathScriptDirectory();
    usz length = (usz)strlen(directory);

    return strncmp(path, directory, length) == 0 ? path + length : path;
}

/// @brief The directory of a path, with its separator at the end, or an empty string.
static char *SHUI_PathDirectory(const char *path)
{
    usz length = (usz)strlen(path);

    while (length > 0 && !SHUI_PathIsSeparator(path[length - 1]))
    {
        length--;
    }

    return SHU_UtilFormat("%.*s", (int)length, path);
}

/// @brief The name of the file at the end of a path. (eg. src/main.c is main.c)
static const char *SHUI_PathFileName(const char *path)
{
    const char *name = path + strlen(path);

    while (name > path && !SHUI_PathIsSeparator(name[-1]))
    {
        name--;
    }

    return name;
}

/// @brief A path without . and .. segments, so two paths to a directory can be compared. (eg. /a/b/../c/ is /a/c/)
static char *SHUI_PathClean(const char *path)
{
    SHUI_StringList segments = {0};
    const char *start = path;

    for (const char *c = path;; c++)
    {
        if (*c != '\0' && !SHUI_PathIsSeparator(*c))
        {
            continue;
        }

        char *segment = SHU_UtilFormat("%.*s", (int)(c - start), start);

        if (strcmp(segment, "..") == 0 && segments.count > 0 && strcmp(segments.data[segments.count - 1], "..") != 0)
        {
            segments.count--;
        }
        else if (segment[0] != '\0' && strcmp(segment, ".") != 0)
        {
            SHUI_ListAdd(&segments, segment);
        }

        if (*c == '\0')
        {
            break;
        }

        start = c + 1;
    }

    SHUI_Builder clean = {0};

    if (SHUI_PathIsSeparator(path[0]))
    {
        SHUI_BuilderAppendChar(&clean, SHUM_PATH_SEPARATOR);
    }

    for (usz i = 0; i < segments.count; i++)
    {
        SHUI_BuilderAppend(&clean, segments.data[i]);

        if (i + 1 < segments.count || (path[0] != '\0' && SHUI_PathIsSeparator(path[strlen(path) - 1])))
        {
            SHUI_BuilderAppendChar(&clean, SHUM_PATH_SEPARATOR);
        }
    }

    return SHUI_BuilderTake(&clean);
}

/// @brief The path from one directory to another, both ending with a separator. (eg. from /a/bin/ to /a/lib/ is ../lib/)
static char *SHUI_PathRelative(const char *fromDirectory, const char *toDirectory)
{
    char *from = SHUI_PathClean(fromDirectory);
    char *to = SHUI_PathClean(toDirectory);

    usz common = 0;

    for (usz i = 0; from[i] != '\0' && from[i] == to[i]; i++)
    {
        if (SHUI_PathIsSeparator(from[i]))
        {
            common = i + 1;
        }
    }

    SHUI_Builder relative = {0};

    for (const char *c = from + common; *c != '\0'; c++)
    {
        if (SHUI_PathIsSeparator(*c))
        {
            SHUI_BuilderAppend(&relative, ".." SHUM_PATH_SEPARATOR_STR);
        }
    }

    SHUI_BuilderAppend(&relative, to + common);

    return SHUI_BuilderTake(&relative);
}

#pragma endregion Path

#pragma region File

static SHUFileType SHUI_FileGetType(const char *path)
{
#if SHUM_HOST_WINDOWS
    DWORD attributes = GetFileAttributesA(path);

    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        return SHUFileType_Invalid;
    }

    return attributes & FILE_ATTRIBUTE_DIRECTORY ? SHUFileType_Directory : SHUFileType_Regular;
#else
    struct stat stats;

    if (stat(path, &stats) != 0)
    {
        return SHUFileType_Invalid;
    }

    return S_ISDIR(stats.st_mode) ? SHUFileType_Directory : SHUFileType_Regular;
#endif
}

// a directory, with each directory on its way
static void SHUI_FileMakeDirectories(const char *path)
{
    if (SHUI_FileGetType(path) == SHUFileType_Directory)
    {
        return;
    }

    // each directory on the way is made, ending the path after it for a moment
    char *partial = SHUI_Copy(path);
    usz length = (usz)strlen(partial);

    for (usz i = 1; i <= length; i++)
    {
        char separator = partial[i];

        if (separator != '\0' && !SHUI_PathIsSeparator(separator))
        {
            continue;
        }

        partial[i] = '\0';

#if SHUM_HOST_WINDOWS
        i32 result = _mkdir(partial);
#else
        i32 result = mkdir(partial, 0755);
#endif

        if (result != 0 && errno != EEXIST)
        {
            SHU_UtilFail("directory " SHUM_LOG_PATH("%s") " cannot be made: %s", SHUI_PathForLog(partial), strerror(errno));
        }

        partial[i] = separator;
    }

    free(partial);
}

// the names in a directory, sorted, without . and ..
static SHUI_StringList SHUI_FileListNames(const char *directory)
{
    SHUI_StringList names = {0};

#if SHUM_HOST_WINDOWS
    WIN32_FIND_DATAA found = {0};
    HANDLE search = FindFirstFileA(SHUI_PathJoin(directory, "*"), &found);

    if (search == INVALID_HANDLE_VALUE)
    {
        SHU_UtilFail("directory " SHUM_LOG_PATH("%s") " cannot be opened.", SHUI_PathForLog(directory));
    }

    do
    {
        if (strcmp(found.cFileName, ".") != 0 && strcmp(found.cFileName, "..") != 0)
        {
            SHUI_ListAdd(&names, SHUI_Copy(found.cFileName));
        }
    } while (FindNextFileA(search, &found));

    FindClose(search);
#else
    DIR *opened = opendir(directory);

    if (opened == NULL)
    {
        SHU_UtilFail("directory " SHUM_LOG_PATH("%s") " cannot be opened.", SHUI_PathForLog(directory));
    }

    for (struct dirent *entry = readdir(opened); entry != NULL; entry = readdir(opened))
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            SHUI_ListAdd(&names, SHUI_Copy(entry->d_name));
        }
    }

    closedir(opened);
#endif

    SHUI_ListSort(&names);

    return names;
}

// a file, or a directory with what it holds
static void SHUI_FileDelete(const char *path)
{
#if SHUM_HOST_WINDOWS
    bool directory = SHUI_FileGetType(path) == SHUFileType_Directory;
#else
    // a link is deleted itself, not what it points to
    struct stat stats;
    bool directory = lstat(path, &stats) == 0 && S_ISDIR(stats.st_mode);
#endif

    if (directory)
    {
        SHUI_StringList names = SHUI_FileListNames(path);

        for (usz i = 0; i < names.count; i++)
        {
            SHUI_FileDelete(SHUI_PathJoin(path, names.data[i]));
        }

        SHUI_ListFree(&names);
    }

#if SHUM_HOST_WINDOWS
    i32 result = directory ? _rmdir(path) : remove(path);
#else
    i32 result = directory ? rmdir(path) : remove(path);
#endif

    if (result != 0)
    {
        SHU_UtilFail(SHUM_LOG_PATH("%s") " cannot be deleted: %s", SHUI_PathForLog(path), strerror(errno));
    }
}

static SHUSlice SHUI_FileRead(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (file == NULL)
    {
        SHU_UtilFail("file " SHUM_LOG_PATH("%s") " cannot be read: %s", SHUI_PathForLog(path), strerror(errno));
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    SHU_Assert(length >= 0, "File size getting failed for '%s'.", path);

    char *content = (char *)SHUI_Allocate((usz)length + 1);

    usz read = (usz)fread(content, 1, (size_t)length, file);
    SHU_Assert(read == (usz)length, "File read failed for '%s'.", path);
    content[length] = '\0';
    fclose(file);

    return cs(content, (usz)length);
}

static void SHUI_FileWrite(const char *path, SHUSliceView content)
{
    SHU_Assert(content.data != NULL || content.size == 0, "Content to write to '%s' is NULL.", path);

    // a file that has the content already is left as is, so its edit time stays and what includes it does not compile again
    if (SHUI_FileGetType(path) == SHUFileType_Regular)
    {
        SHUSlice old = SHUI_FileRead(path);
        bool same = old.size == content.size && (content.size == 0 || memcmp(old.data, content.data, content.size) == 0);
        free(old.data);

        if (same)
        {
            return;
        }
    }

    FILE *file = fopen(path, "wb");

    if (file == NULL)
    {
        SHU_UtilFail("file " SHUM_LOG_PATH("%s") " cannot be written: %s", SHUI_PathForLog(path), strerror(errno));
    }

    usz written = content.size == 0 ? 0 : (usz)fwrite(content.data, 1, content.size, file);
    SHU_Assert(written == content.size, "File write failed for '%s'.", path);
    fclose(file);
}

// a file, or a directory with what it holds
static void SHUI_FileCopy(const char *from, const char *to)
{
    if (SHUI_FileGetType(from) == SHUFileType_Directory)
    {
        SHUI_FileMakeDirectories(to);
        SHUI_StringList names = SHUI_FileListNames(from);

        for (usz i = 0; i < names.count; i++)
        {
            SHUI_FileCopy(SHUI_PathJoin(from, names.data[i]), SHUI_PathJoin(to, names.data[i]));
        }

        SHUI_ListFree(&names);
        return;
    }

    SHUSlice content = SHUI_FileRead(from);
    SHUI_FileWrite(to, csv(content));
    free(content.data);

#if !SHUM_HOST_WINDOWS
    // the copy keeps the permissions, so a copied program or script still runs
    struct stat stats;

    if (stat(from, &stats) == 0 && chmod(to, stats.st_mode & 07777) != 0)
    {
        SHU_UtilFail("permissions of " SHUM_LOG_PATH("%s") " cannot be set: %s", SHUI_PathForLog(to), strerror(errno));
    }
#endif
}

static void SHUI_FileRename(const char *from, const char *to)
{
    if (SHUI_FileGetType(to) != SHUFileType_Invalid)
    {
        SHUI_FileDelete(to);
    }

    if (rename(from, to) != 0)
    {
        SHU_UtilFail(SHUM_LOG_PATH("%s") " cannot be renamed to " SHUM_LOG_PATH("%s") ": %s", SHUI_PathForLog(from), SHUI_PathForLog(to), strerror(errno));
    }
}

// in nanoseconds, so a file edited in the same second as its object was compiled is still seen as newer
static i64 SHUI_FileGetEditTime(const char *path)
{
#if SHUM_HOST_WINDOWS
    // stat gives whole seconds on Windows; this gives the time in units of 100 nanoseconds
    WIN32_FILE_ATTRIBUTE_DATA attributes;

    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attributes))
    {
        SHU_UtilFail("file " SHUM_LOG_PATH("%s") " cannot be found.", SHUI_PathForLog(path));
    }

    return (i64)(((u64)attributes.ftLastWriteTime.dwHighDateTime << 32) | (u64)attributes.ftLastWriteTime.dwLowDateTime) * 100LL;
#else
    struct stat stats;

    if (stat(path, &stats) != 0)
    {
        SHU_UtilFail("file " SHUM_LOG_PATH("%s") " cannot be found: %s", SHUI_PathForLog(path), strerror(errno));
    }

#if SHUM_HOST_LINUX
    return (i64)stats.st_mtim.tv_sec * 1000000000LL + (i64)stats.st_mtim.tv_nsec;
#elif SHUM_HOST_MACOS
    return (i64)stats.st_mtimespec.tv_sec * 1000000000LL + (i64)stats.st_mtimespec.tv_nsec;
#else
    return (i64)stats.st_mtime * 1000000000LL;
#endif
#endif
}

// whether a file that a dependency file, as the compiler writes it, lists for a target is newer than the target
static bool SHUI_FileHasNewerDependency(const char *dependencyFile, const char *targetFile)
{
    i64 targetTime = SHUI_FileGetEditTime(targetFile);

    SHUSlice dependencies = SHUI_FileRead(dependencyFile);
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
    SHUI_Builder dependency = {0};

    for (; offset <= length; offset++)
    {
        char c = offset < length ? text[offset] : '\0';

        if (c == '\\' && offset + 1 < length && text[offset + 1] == ' ')
        {
            SHUI_BuilderAppendChar(&dependency, ' ');
            offset++;
        }
        else if (c == '\\' && offset + 1 < length && (text[offset + 1] == '\r' || text[offset + 1] == '\n'))
        {
            continue;
        }
        else if (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != '\0')
        {
            SHUI_BuilderAppendChar(&dependency, c);
        }
        else if (dependency.length != 0)
        {
            // a file that is gone, such as a header that moved, counts as newer
            if (SHUI_FileGetType(dependency.data) == SHUFileType_Invalid || SHUI_FileGetEditTime(dependency.data) > targetTime)
            {
                free(dependencies.data);
                return true;
            }

            // the builder is used again for the next file
            dependency.length = 0;
        }
    }

    free(dependencies.data);
    return false;
}

#pragma endregion File

#pragma region Command

static void SHUI_CommandAddArgument(SHUI_StringList *command, const char *argument)
{
    SHUI_ListAdd(command, SHUI_Copy(argument));
}

// a backslash escapes the next character, as in a POSIX shell; on Windows, where paths hold backslashes, it escapes only a quote, as the C runtime's own splitting does
#if SHUM_HOST_WINDOWS
#define SHUI_COMMAND_ESCAPES(next) ((next) == '"' || (next) == '\'')
#define SHUI_COMMAND_ESCAPES_QUOTED(next) ((next) == '"')
#else
#define SHUI_COMMAND_ESCAPES(next) ((next) != '\0')
#define SHUI_COMMAND_ESCAPES_QUOTED(next) ((next) == '"' || (next) == '\\' || (next) == '$' || (next) == '`')
#endif

// splits the arguments the way a POSIX shell does: spaces separate them, quotes group them and backslashes escape
static void SHUI_CommandAddArguments(SHUI_StringList *command, const char *arguments)
{
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
                SHUI_BuilderAppendChar(&argument, *c);
            }
        }
        else if (quote == '"')
        {
            if (*c == '"')
            {
                quote = '\0';
            }
            else if (*c == '\\' && SHUI_COMMAND_ESCAPES_QUOTED(c[1]))
            {
                SHUI_BuilderAppendChar(&argument, *++c);
            }
            else
            {
                SHUI_BuilderAppendChar(&argument, *c);
            }
        }
        else if (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r')
        {
            if (inArgument)
            {
                SHUI_ListAdd(command, SHUI_BuilderTake(&argument));
                inArgument = false;
            }
        }
        else if (*c == '\'' || *c == '"')
        {
            quote = *c;
            inArgument = true;
        }
        else if (*c == '\\' && SHUI_COMMAND_ESCAPES(c[1]))
        {
            SHUI_BuilderAppendChar(&argument, *++c);
            inArgument = true;
        }
        else
        {
            SHUI_BuilderAppendChar(&argument, *c);
            inArgument = true;
        }
    }

    SHU_Assert(quote == '\0', "Unclosed quote in arguments '%s'.", arguments);

    if (inArgument)
    {
        SHUI_ListAdd(command, SHUI_BuilderTake(&argument));
    }
}

// each string of flags, split into its arguments
static void SHUI_CommandAddFlags(SHUI_StringList *command, const SHUI_StringList *flags)
{
    for (usz i = 0; i < flags->count; i++)
    {
        SHUI_CommandAddArguments(command, flags->data[i]);
    }
}

// the module's include directories, and the public ones of the libraries it links
static void SHUI_CommandAddIncludeDirectories(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        SHUI_ListAdd(command, SHU_UtilFormat("-I%s", SHUILD.MODULE.includeDirectories.data[i]));
    }

    // the headers of linked libraries are another module's, so their warnings stay out
    for (usz i = 0; i < SHUILD.MODULE.linkedIncludeDirectories.count; i++)
    {
        SHUI_CommandAddArgument(command, "-isystem");
        SHUI_CommandAddArgument(command, SHUILD.MODULE.linkedIncludeDirectories.data[i]);
    }
}

#if SHUM_HOST_WINDOWS
// _spawnvp joins the arguments with spaces, so they are quoted the way the C runtime splits them back
static char *SHUI_CommandQuoteArgument(const char *argument)
{
    if (argument[0] != '\0' && strpbrk(argument, " \t\"") == NULL)
    {
        return SHUI_Copy(argument);
    }

    SHUI_Builder quoted = {0};
    SHUI_BuilderAppendChar(&quoted, '"');

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
            SHUI_BuilderAppendChar(&quoted, '\\');
        }

        SHUI_BuilderAppendChar(&quoted, *c);
        backslashes = 0;
    }

    for (usz j = 0; j < backslashes * 2; j++)
    {
        SHUI_BuilderAppendChar(&quoted, '\\');
    }

    SHUI_BuilderAppendChar(&quoted, '"');

    return SHUI_BuilderTake(&quoted);
}
#endif

// the command as one line, for logs
static char *SHUI_CommandJoin(const SHUI_StringList *command)
{
    SHUI_Builder line = {0};

    for (usz i = 0; i < command->count; i++)
    {
        if (i != 0)
        {
            SHUI_BuilderAppendChar(&line, ' ');
        }

#if SHUM_HOST_WINDOWS
        SHUI_BuilderAppend(&line, SHUI_CommandQuoteArgument(command->data[i]));
#else
        SHUI_BuilderAppend(&line, command->data[i]);
#endif
    }

    return SHUI_BuilderTake(&line);
}

// starts a command without a shell, and gives its process, or -1 when it cannot start
static i64 SHUI_CommandStart(const SHUI_StringList *command)
{
    SHU_Assert(command->count > 0, "Internal: Empty command.");

#ifdef SHUC_LOG_COMMANDS
    SHU_UtilLog("$ " SHUM_LOG_COMMAND("%s"), SHUI_CommandJoin(command));
#endif

    // the arguments, with a NULL after the last
    char **arguments = (char **)SHUI_Allocate(sizeof(char *) * (command->count + 1));

    for (usz i = 0; i < command->count; i++)
    {
#if SHUM_HOST_WINDOWS
        arguments[i] = SHUI_CommandQuoteArgument(command->data[i]);
#else
        arguments[i] = command->data[i];
#endif
    }
    arguments[command->count] = NULL;

#if SHUM_HOST_WINDOWS
    i64 process = (i64)_spawnvp(_P_NOWAIT, arguments[0], (const char *const *)arguments);

    for (usz i = 0; i < command->count; i++)
    {
        free(arguments[i]);
    }
#else
    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(arguments[0], arguments);
        SHUI_LogError(SHUM_LOG_COMMAND("%s") " cannot start: %s", arguments[0], strerror(errno));
        _exit(127);
    }

    i64 process = pid > 0 ? (i64)pid : -1;
#endif

    free(arguments);

    return process;
}

// the exit code of a process, or -1 when it did not end by itself
static i32 SHUI_CommandWait(i64 process)
{
    if (process < 0)
    {
        return -1;
    }

    int status = 0;

#if SHUM_HOST_WINDOWS
    return _cwait(&status, (intptr_t)process, _WAIT_CHILD) == -1 ? -1 : (i32)status;
#else
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

// runs a command without a shell, and gives its exit code
static i32 SHUI_CommandRun(const SHUI_StringList *command)
{
    return SHUI_CommandWait(SHUI_CommandStart(command));
}

// runs a command that the build needs, and ends the build when it fails
static void SHUI_CommandRunOrFail(const SHUI_StringList *command)
{
    i32 result = SHUI_CommandRun(command);

    if (result != 0)
    {
        SHU_UtilFail(SHUI_COMMAND_FAILED, result, SHUI_CommandJoin(command));
    }
}

// runs a command with the shell, and gives its exit code
static i32 SHUI_ShellRun(const char *command)
{
#ifdef SHUC_LOG_COMMANDS
    SHU_UtilLog("$ " SHUM_LOG_COMMAND("%s"), command);
#endif

    i32 result = system(command);

#if !SHUM_HOST_WINDOWS
    // system gives the wait status, not the exit code
    result = result == -1 ? -1 : WIFEXITED(result) ? WEXITSTATUS(result) : -1;
#endif

    return result;
}

#pragma endregion Command

#pragma region Job

// a job is a command that runs while others do; the module's files compile in jobs

static void SHUI_JobWaitOne(void)
{
    // the first job that ends
    usz index = 0;
    i32 result = -1;

#if SHUM_HOST_WINDOWS
    // Windows waits for 64 processes at most; with more jobs, it waits for the oldest one
    if (SHUILD.JOBS.count <= MAXIMUM_WAIT_OBJECTS)
    {
        HANDLE handles[MAXIMUM_WAIT_OBJECTS];

        for (usz i = 0; i < SHUILD.JOBS.count; i++)
        {
            handles[i] = (HANDLE)(intptr_t)SHUILD.JOBS.processes[i];
        }

        DWORD ended = WaitForMultipleObjects((DWORD)SHUILD.JOBS.count, handles, FALSE, INFINITE);

        if (ended < WAIT_OBJECT_0 + (DWORD)SHUILD.JOBS.count)
        {
            index = (usz)(ended - WAIT_OBJECT_0);
        }
    }

    result = SHUI_CommandWait(SHUILD.JOBS.processes[index]);
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
        SHUI_LogError(SHUI_COMMAND_FAILED, result, line);
        SHUILD.JOBS.failed = true;
    }

    free(line);
}

static void SHUI_JobStart(const SHUI_StringList *command)
{
    if (SHUILD.JOBS.limit == 0)
    {
#if SHUM_HOST_WINDOWS
        SYSTEM_INFO systemInfo = {0};
        GetSystemInfo(&systemInfo);
        usz processors = (usz)systemInfo.dwNumberOfProcessors;
#else
        long processorCount = sysconf(_SC_NPROCESSORS_ONLN);
        usz processors = processorCount > 0 ? (usz)processorCount : 1;
#endif

        SHUILD.JOBS.limit = SHUMax((usz)1, SHUMin(processors, (usz)SHUC_MAX_JOB_COUNT));
    }

    // after a failure, the jobs that run are waited for, and no new ones start
    if (SHUILD.JOBS.failed)
    {
        return;
    }

    if (SHUILD.JOBS.count >= SHUILD.JOBS.limit)
    {
        SHUI_JobWaitOne();
    }

    i64 process = SHUI_CommandStart(command);
    char *line = SHUI_CommandJoin(command);

    if (process < 0)
    {
        SHUI_LogError(SHUI_COMMAND_FAILED, -1, line);
        SHUILD.JOBS.failed = true;
        return;
    }

    SHUILD.JOBS.processes[SHUILD.JOBS.count] = process;
    SHUILD.JOBS.commands[SHUILD.JOBS.count++] = line;
}

// waits for every job, and ends the build when one failed
static void SHUI_JobWaitAll(void)
{
    while (SHUILD.JOBS.count > 0)
    {
        SHUI_JobWaitOne();
    }

    if (SHUILD.JOBS.failed)
    {
        SHU_UtilFail(SHUM_LOG_NAME("%s") " failed to compile.", SHUILD.MODULE.name);
    }
}

#pragma endregion Job

#pragma region Compiler

// the first line that a compiler prints for an option, such as -dumpmachine, or an empty string
static char *SHUI_CompilerReadLine(const char *command, const char *option)
{
    char line[256] = {0};

#if SHUM_HOST_WINDOWS
    FILE *pipe = _popen(SHU_UtilFormat("%s %s 2>NUL", command, option), "r");
#else
    FILE *pipe = popen(SHU_UtilFormat("%s %s 2>/dev/null", command, option), "r");
#endif

    if (pipe != NULL)
    {
        if (fgets(line, sizeof(line), pipe) == NULL)
        {
            line[0] = '\0';
        }

#if SHUM_HOST_WINDOWS
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    }

    line[strcspn(line, "\r\n")] = '\0';
    return SHUI_Copy(line);
}

// the compiler names the system it compiles for, such as x86_64-linux-gnu, x86_64-w64-mingw32 or arm64-apple-darwin23
static SHUPlatform SHUI_PlatformFromMachine(const char *machine)
{
    if (strstr(machine, "mingw") != NULL || strstr(machine, "windows") != NULL)
    {
        return SHUPlatform_Windows;
    }

    if (strstr(machine, "apple") != NULL || strstr(machine, "darwin") != NULL)
    {
        return SHUPlatform_MacOS;
    }

    if (strstr(machine, "linux") != NULL)
    {
        return SHUPlatform_Linux;
    }

    // a compiler that does not tell compiles for the host
    return (SHUPlatform)SHUM_HOST_PLATFORM;
}

// whether a compiler's machine names the processor that shuild runs on, so the programs it compiles run here;
// a compiler that does not tell, and a processor that is not listed, count as the host's
static bool SHUI_ProcessorIsHost(const char *machine)
{
#if defined(__x86_64__) || defined(_M_X64)
    const char *processors[] = {"x86_64-", "amd64-"};
#elif defined(__aarch64__) || defined(_M_ARM64)
    const char *processors[] = {"aarch64-", "arm64-"};
#elif defined(__i386__) || defined(_M_IX86)
    const char *processors[] = {"i386-", "i486-", "i586-", "i686-"};
#elif defined(__arm__) || defined(_M_ARM)
    const char *processors[] = {"arm-", "armv"};
#else
    const char *processors[] = {""};
#endif

    if (machine[0] == '\0')
    {
        return true;
    }

    for (usz i = 0; i < sizeof(processors) / sizeof(*processors); i++)
    {
        if (strncmp(machine, processors[i], strlen(processors[i])) == 0)
        {
            return true;
        }
    }

    return false;
}

// a compiler's name on PATH is gcc or clang, maybe with a version (gcc-14) and the target's triple before it (x86_64-w64-mingw32-gcc), which has two dashes or more;
// other tools, such as gcc-ar, clang-format or c99-gcc, are not compilers to pick
static bool SHUI_IsCompilerName(const char *name)
{
    const char *families[] = {"gcc", "clang"};

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
                return true;
            }
        }
    }

    return false;
}

// a compiler tells its family in its version, so a clang that goes by gcc's name, such as LLVM-MinGW's x86_64-w64-mingw32-gcc or macOS's gcc, counts as clang
static SHUCompiler SHUI_CompilerFamily(const char *command)
{
    char *about = SHUI_CompilerReadLine(command, "--version");

    if (strstr(about, "clang") != NULL)
    {
        return SHUCompiler_Clang;
    }

    if (strstr(about, "gcc") != NULL || strstr(about, "GCC") != NULL)
    {
        return SHUCompiler_GCC;
    }

    return SHUCompiler_Unknown;
}

// gcc's -dumpversion may give only the major version, and clang knows no -dumpfullversion; "14.2.0" is 140200, and "14" is 140000
static u32 SHUI_CompilerVersion(const char *command)
{
    char *version = SHUI_CompilerReadLine(command, "-dumpfullversion");

    if (version[0] == '\0')
    {
        version = SHUI_CompilerReadLine(command, "-dumpversion");
    }

    u32 parts[3] = {0};
    sscanf(version, "%u.%u.%u", &parts[0], &parts[1], &parts[2]);

    return parts[0] * 10000 + parts[1] * 100 + parts[2];
}

// the sanitizers need their libraries, which a compiler may not have, so a small program is compiled and linked with them
static bool SHUI_CompilerHasSanitizers(const char *command)
{
#if SHUM_HOST_WINDOWS
    (void)command;
    return false; // MinGW has no sanitizers
#else
    return SHUI_ShellRun(SHU_UtilFormat("printf 'int main(void){return 0;}' | %s -x c - -fsanitize=address,undefined -o /dev/null >/dev/null 2>&1", command)) == 0;
#endif
}

// the commands of the gcc and clang compilers on PATH, the first of each name, sorted
static SHUI_StringList SHUI_CompilerFindOnPath(void)
{
#if SHUM_HOST_WINDOWS
    const char separator = ';';
#else
    const char separator = ':';
#endif

    SHUI_StringList commands = {0};
    const char *path = getenv("PATH");

    while (path != NULL && *path != '\0')
    {
        const char *end = strchr(path, separator);
        char *directory = SHU_UtilFormat("%.*s", (int)(end == NULL ? strlen(path) : (usz)(end - path)), path);
        path = end == NULL ? NULL : end + 1;

        if (SHUI_FileGetType(directory) != SHUFileType_Directory)
        {
            continue;
        }

        SHUI_StringList names = SHUI_FileListNames(directory);

        for (usz i = 0; i < names.count; i++)
        {
            char *name = names.data[i];

#if SHUM_HOST_WINDOWS
            // a program's name ends with .exe, which its command leaves out
            if (!SHUI_EndsWith(name, ".exe"))
            {
                continue;
            }

            name[strlen(name) - 4] = '\0';
#endif

            if (!SHUI_IsCompilerName(name) || SHUI_ListContains(&commands, name))
            {
                continue;
            }

#if !SHUM_HOST_WINDOWS
            if (access(SHUI_PathJoin(directory, name), X_OK) != 0)
            {
                continue;
            }
#endif

            SHUI_ListAdd(&commands, SHUI_Copy(name));
        }

        SHUI_ListFree(&names);
    }

    SHUI_ListSort(&commands);

    return commands;
}

// the compilers on PATH, with what each tells of itself; whether each has the sanitizers takes a compilation to know, so it is left to SHU_CompilerDetect
static SHUCompilerInfo *SHUI_CompilerDescribeAll(usz *retCount)
{
    SHUI_StringList commands = SHUI_CompilerFindOnPath();
    SHUCompilerInfo *compilers = (SHUCompilerInfo *)SHUI_Allocate(sizeof(SHUCompilerInfo) * (commands.count + 1));

    for (usz i = 0; i < commands.count; i++)
    {
        const char *command = commands.data[i];
        const char *machine = SHUI_CompilerReadLine(command, "-dumpmachine");

        compilers[i] = (SHUCompilerInfo){
            .command = command,
            .family = SHUI_CompilerFamily(command),
            .target = SHUI_PlatformFromMachine(machine),
            .machine = machine,
            .version = SHUI_CompilerVersion(command),
        };
    }

    *retCount = commands.count;
    return compilers;
}

// the newest compiler that compiles for the host's system and processor, of the host compiler's family if one is found; a shorter name wins a tie, so gcc is kept over x86_64-linux-gnu-gcc
static const SHUCompilerInfo *SHUI_CompilerPick(const SHUCompilerInfo *compilers, usz count)
{
    const SHUCompilerInfo *best = NULL;

    for (usz i = 0; i < count; i++)
    {
        const SHUCompilerInfo *compiler = &compilers[i];

        if (compiler->target != SHUM_HOST_PLATFORM || !SHUI_ProcessorIsHost(compiler->machine) || compiler->version == 0)
        {
            continue;
        }

        if (best == NULL)
        {
            best = compiler;
            continue;
        }

        bool hostFamily = compiler->family == SHUM_HOST_COMPILER;
        bool bestHostFamily = best->family == SHUM_HOST_COMPILER;

        if (hostFamily != bestHostFamily)
        {
            best = hostFamily ? compiler : best;
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

// build scripts run on the host, so a cross compiler leaves them to the host's own
static const char *SHUI_CompilerForScripts(void)
{
    return SHUM_PLATFORM_IS_HOST(SHUILD.COMPILER.target) ? SHUILD.COMPILER.command : SHUCompiler_GetCommand(SHUM_HOST_COMPILER);
}

#pragma endregion Compiler

#ifdef SHUC_ENABLE_INCREMENTAL
#pragma region Cache

static const char *SHUI_CacheDirectory(void)
{
    if (SHUILD.cacheDirectory == NULL)
    {
        SHU_CacheConfigure(SHUC_DEFAULT_CACHE_DIRECTORY);
    }

    return SHUILD.cacheDirectory;
}

// the current module's objects, dependency files and settings
static char *SHUI_CacheModuleDirectory(void)
{
    return SHUI_PathJoinDirectory(SHUI_CacheDirectory(), SHUILD.MODULE.name);
}

static void SHUI_CacheClearModule(void)
{
    char *directory = SHUI_CacheModuleDirectory();

    if (SHUI_FileGetType(directory) != SHUFileType_Invalid)
    {
        SHUI_FileDelete(directory);
    }

    SHUI_FileMakeDirectories(directory);
}

// a hash of everything that the module's files compile with
static u64 SHUI_CacheSettingsHash(void)
{
    u64 hash = 14695981039346656037ULL;

#define SHUI_HASH_BYTE(byte) hash = ((hash ^ (u64)(byte)) * 1099511628211ULL)
#define SHUI_HASH_MIX hash ^= (hash >> 17)
#define SHUI_HASH_STRING(string)                    \
    for (const char *c = (string); *c != '\0'; c++) \
    {                                               \
        SHUI_HASH_BYTE((u8)*c);                     \
    }                                               \
    SHUI_HASH_MIX
    // the count tells an empty list from none
#define SHUI_HASH_LIST(list)               \
    SHUI_HASH_BYTE((list).count);          \
    for (usz i = 0; i < (list).count; i++) \
    {                                      \
        SHUI_HASH_STRING((list).data[i]);  \
    }

    SHUI_HASH_STRING(SHUI_CacheDirectory());

    SHUI_HASH_BYTE(SHUILD.COMPILER.family);
    SHUI_HASH_MIX;

    SHUI_HASH_STRING(SHUILD.COMPILER.command);
    SHUI_HASH_LIST(SHUILD.COMPILER.flags);
    SHUI_HASH_LIST(SHUILD.COMPILER.linkerFlags);
    SHUI_HASH_STRING(SHUI_PathScriptDirectory());
    SHUI_HASH_STRING(SHUILD.MODULE.name);
    SHUI_HASH_STRING(SHUILD.MODULE.root);
    SHUI_HASH_LIST(SHUILD.MODULE.includeDirectories);
    SHUI_HASH_LIST(SHUILD.MODULE.sourceFiles);
    SHUI_HASH_LIST(SHUILD.MODULE.linkDirectories);
    SHUI_HASH_LIST(SHUILD.MODULE.links);

#undef SHUI_HASH_LIST
#undef SHUI_HASH_STRING
#undef SHUI_HASH_MIX
#undef SHUI_HASH_BYTE

    return hash;
}

static char *SHUI_CacheSettingsFile(void)
{
    return SHU_UtilFormat("%s%s.hash", SHUI_CacheModuleDirectory(), SHUILD.MODULE.name);
}

static SHUI_SettingsState SHUI_CacheCompareSettings(void)
{
    char *file = SHUI_CacheSettingsFile();

    if (SHUI_FileGetType(file) != SHUFileType_Regular)
    {
        return SHUI_SettingsState_New;
    }

    SHUSlice saved = SHUI_FileRead(file);
    bool same = strtoull((const char *)saved.data, NULL, 10) == SHUI_CacheSettingsHash();
    free(saved.data);

    return same ? SHUI_SettingsState_Same : SHUI_SettingsState_Changed;
}

static void SHUI_CacheSaveSettings(void)
{
    char *hash = SHU_UtilFormat("%llu", (unsigned long long)SHUI_CacheSettingsHash());
    SHUI_FileWrite(SHUI_CacheSettingsFile(), csv(cs(hash, strlen(hash))));
}

// a source's object or dependency file in the module's cache: its path in the module, with its extension's last letter replaced (eg. src/main.c is src/main.o)
static char *SHUI_CacheUnitFile(const char *sourceFile, const char *extension)
{
    usz rootLength = (usz)strlen(SHUILD.MODULE.root);
    int unitLength = (int)((usz)strlen(sourceFile) - rootLength - 1);

    return SHU_UtilFormat("%s%.*s%s", SHUI_CacheModuleDirectory(), unitLength, sourceFile + rootLength, extension);
}

#pragma endregion Cache
#endif // SHUC_ENABLE_INCREMENTAL

#pragma region Module

// the command that compiles a source file of the module into its object
static SHUI_StringList SHUI_ModuleCompileCommand(const char *sourceFile, const char *objectFile, const char *dependencyFile, const char *extraFlag)
{
    // the compiler writes the dependency file as it compiles, with the module's flags, so the headers that definitions include are in it too
    SHUI_StringList command = {0};
    SHUI_CommandAddArguments(&command, SHUILD.COMPILER.command);
    SHUI_CommandAddArgument(&command, "-o");
    SHUI_CommandAddArgument(&command, objectFile);
    SHUI_CommandAddArgument(&command, "-c");

    if (extraFlag != NULL)
    {
        SHUI_CommandAddArgument(&command, extraFlag);
    }

    // a single header library is compiled as C, with the definition that holds its implementation, instead of as a precompiled header
    if (SHUI_EndsWith(sourceFile, ".h"))
    {
        SHUI_CommandAddArgument(&command, "-x");
        SHUI_CommandAddArgument(&command, "c");
    }

    SHUI_CommandAddArgument(&command, sourceFile);
    SHUI_CommandAddFlags(&command, &SHUILD.COMPILER.flags);
    SHUI_CommandAddIncludeDirectories(&command);

    if (dependencyFile != NULL)
    {
        SHUI_CommandAddArgument(&command, "-MMD");
        SHUI_CommandAddArgument(&command, "-MF");
        SHUI_CommandAddArgument(&command, dependencyFile);
    }

    return command;
}

static void SHUI_ModuleCompileUnit(const SHUI_StringList *command, const char *objectFile)
{
    SHUI_FileMakeDirectories(SHUI_PathDirectory(objectFile));
    SHUI_JobStart(command);
    SHUILD.MODULE.compiledCount++;
}

#ifdef SHUC_COMPILE_DATABASE
// a string as JSON writes it, in quotes
static void SHUI_DatabaseAppendString(SHUI_Builder *text, const char *string)
{
    SHUI_BuilderAppendChar(text, '"');

    for (const char *c = string; *c != '\0'; c++)
    {
        if (*c == '"' || *c == '\\')
        {
            SHUI_BuilderAppendChar(text, '\\');
        }

        SHUI_BuilderAppendChar(text, *c);
    }

    SHUI_BuilderAppendChar(text, '"');
}

// a source file's entry of compile_commands.json: the directory its paths start from, the file, its object and the command's arguments
static char *SHUI_DatabaseEntry(const char *sourceFile, const char *objectFile, const SHUI_StringList *command)
{
    SHUI_Builder entry = {0};
    SHUI_BuilderAppend(&entry, "  {\n    \"directory\": ");
    SHUI_DatabaseAppendString(&entry, SHUI_PathScriptDirectory());
    SHUI_BuilderAppend(&entry, ",\n    \"file\": ");
    SHUI_DatabaseAppendString(&entry, sourceFile);
    SHUI_BuilderAppend(&entry, ",\n    \"output\": ");
    SHUI_DatabaseAppendString(&entry, objectFile);
    SHUI_BuilderAppend(&entry, ",\n    \"arguments\": [");

    for (usz i = 0; i < command->count; i++)
    {
        SHUI_BuilderAppend(&entry, i == 0 ? "" : ", ");
        SHUI_DatabaseAppendString(&entry, command->data[i]);
    }

    SHUI_BuilderAppend(&entry, "]\n  }");
    return SHUI_BuilderTake(&entry);
}

// entries joined into one text, with a comma between two of them
static void SHUI_DatabaseAppendEntries(SHUI_Builder *text, const SHUI_StringList *entries)
{
    for (usz i = 0; i < entries->count; i++)
    {
        SHUI_BuilderAppend(text, text->length == 0 ? "" : ",\n");
        SHUI_BuilderAppend(text, entries->data[i]);
    }
}

// writes compile_commands.json in the build script's directory: a list of entries
static void SHUI_DatabaseWriteFile(const char *entries)
{
    char *database = SHU_UtilFormat("[\n%s\n]\n", entries);
    SHUI_FileWrite(SHUI_PathFromScript("compile_commands.json"), csv(cs(database, strlen(database))));
}

#ifdef SHUC_ENABLE_INCREMENTAL
// with incremental builds, a module that the build script skips keeps its entries from an earlier build, so each module keeps its own in the cache,
// and compile_commands.json joins those of every module in the cache
static void SHUI_DatabaseWrite(const SHUI_StringList *moduleEntries)
{
    SHUI_Builder moduleText = {0};
    SHUI_DatabaseAppendEntries(&moduleText, moduleEntries);
    char *text = SHUI_BuilderTake(&moduleText);
    SHUI_FileWrite(SHU_UtilFormat("%scommands.json", SHUI_CacheModuleDirectory()), csv(cs(text, strlen(text))));
    free(text);

    SHUI_Builder entries = {0};
    SHUI_StringList modules = SHUI_FileListNames(SHUI_CacheDirectory());

    for (usz i = 0; i < modules.count; i++)
    {
        char *file = SHU_UtilFormat("%s%s" SHUM_PATH_SEPARATOR_STR "commands.json", SHUI_CacheDirectory(), modules.data[i]);

        if (SHUI_FileGetType(file) == SHUFileType_Regular)
        {
            SHUSlice saved = SHUI_FileRead(file);
            SHUI_BuilderAppend(&entries, entries.length == 0 || saved.size == 0 ? "" : ",\n");
            SHUI_BuilderAppend(&entries, (const char *)saved.data);
            free(saved.data);
        }
    }

    SHUI_ListFree(&modules);
    char *database = SHUI_BuilderTake(&entries);
    SHUI_DatabaseWriteFile(database);
    free(database);
}
#else
// without incremental builds, every module compiles each time, so compile_commands.json holds the modules of this build
static void SHUI_DatabaseWrite(const SHUI_StringList *moduleEntries)
{
    for (usz i = 0; i < moduleEntries->count; i++)
    {
        SHUI_ListAdd(&SHUILD.databaseEntries, SHUI_Copy(moduleEntries->data[i]));
    }

    SHUI_Builder entries = {0};
    SHUI_DatabaseAppendEntries(&entries, &SHUILD.databaseEntries);
    char *database = SHUI_BuilderTake(&entries);
    SHUI_DatabaseWriteFile(database);
    free(database);
}
#endif
#endif // SHUC_COMPILE_DATABASE

#ifndef SHUC_ENABLE_INCREMENTAL
// deletes the objects beside their sources; it also runs when the build ends, so a build that fails leaves none
static void SHUI_ModuleDeleteObjects(void)
{
    for (usz i = 0; i < SHUILD.temporaryObjects.count; i++)
    {
        // a file that did not compile has no object
        if (SHUI_FileGetType(SHUILD.temporaryObjects.data[i]) == SHUFileType_Regular)
        {
            SHUI_FileDelete(SHUILD.temporaryObjects.data[i]);
        }
    }

    SHUI_ListFree(&SHUILD.temporaryObjects);
}

static void SHUI_ModuleStopped(int signalNumber)
{
    // exit runs SHUI_ModuleDeleteObjects
    exit(128 + signalNumber);
}
#endif

// the module's sources compile to objects, each in a job; with incremental builds, only the ones whose files changed.
// compile_commands.json gets every source's command, also of those that did not compile again
static SHUI_StringList SHUI_ModuleCompileObjects(const char *extraFlag)
{
    SHUI_StringList objectFiles = {0};
    SHUI_StringList databaseEntries = {0};

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        const char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *objectFile = SHUI_CacheUnitFile(sourceFile, "o");
        char *dependencyFile = SHUI_CacheUnitFile(sourceFile, "d");
        SHUI_StringList command = SHUI_ModuleCompileCommand(sourceFile, objectFile, dependencyFile, extraFlag);

        if (SHUI_FileGetType(objectFile) != SHUFileType_Regular ||
            SHUI_FileGetType(dependencyFile) != SHUFileType_Regular ||
            SHUI_FileHasNewerDependency(dependencyFile, objectFile))
        {
            SHUI_ModuleCompileUnit(&command, objectFile);
        }
#else
        // the object goes beside its source, and is deleted after linking
        char *objectFile = SHU_UtilFormat("%.*so", (int)(strlen(sourceFile) - 1), sourceFile);
        static bool registered = false;

        if (!registered)
        {
            registered = true;
            atexit(SHUI_ModuleDeleteObjects);

            // a build that is stopped, with Ctrl+C for one, deletes them too
            signal(SIGINT, SHUI_ModuleStopped);
            signal(SIGTERM, SHUI_ModuleStopped);
        }

        SHUI_ListAdd(&SHUILD.temporaryObjects, SHUI_Copy(objectFile));
        SHUI_StringList command = SHUI_ModuleCompileCommand(sourceFile, objectFile, NULL, extraFlag);
        SHUI_ModuleCompileUnit(&command, objectFile);
#endif

#ifdef SHUC_COMPILE_DATABASE
        SHUI_ListAdd(&databaseEntries, SHUI_DatabaseEntry(sourceFile, objectFile, &command));
#endif

        SHUI_ListFree(&command);
        SHUI_ListAdd(&objectFiles, objectFile);
    }

    SHUI_JobWaitAll();

#ifdef SHUC_COMPILE_DATABASE
    SHUI_DatabaseWrite(&databaseEntries);
#endif

    SHUI_ListFree(&databaseEntries);

    return objectFiles;
}

// the C files in a directory and in the directories inside it
static void SHUI_ModuleAddSourceDirectory(const char *directory)
{
    SHUI_StringList names = SHUI_FileListNames(directory);

    for (usz i = 0; i < names.count; i++)
    {
        char *path = SHUI_PathJoin(directory, names.data[i]);

        if (SHUI_FileGetType(path) == SHUFileType_Directory)
        {
            SHUI_ModuleAddSourceDirectory(path);
        }
        else if (SHUI_EndsWith(path, ".c"))
        {
            SHUI_ListAdd(&SHUILD.MODULE.sourceFiles, path);
        }
    }

    SHUI_ListFree(&names);
}

static SHUI_Library *SHUI_ModuleFindLibrary(const char *name)
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
static void SHUI_ModuleRecordLibrary(SHUModuleType type)
{
    SHUI_Library *library = SHUI_ModuleFindLibrary(SHUILD.MODULE.name);

    if (library == NULL)
    {
        if (SHUILD.LIBRARIES.count >= SHUILD.LIBRARIES.capacity)
        {
            usz capacity = SHUI_GrowCapacity(SHUILD.LIBRARIES.capacity);
            SHUILD.LIBRARIES.data = (SHUI_Library *)SHUI_Reallocate(SHUILD.LIBRARIES.data, sizeof(SHUI_Library) * capacity);
            SHUILD.LIBRARIES.capacity = capacity;
        }

        library = &SHUILD.LIBRARIES.data[SHUILD.LIBRARIES.count++];
        library->name = SHUI_Copy(SHUILD.MODULE.name);
    }

    // a library compiled again replaces what it kept
    library->includeDirectories = SHUILD.MODULE.publicIncludeDirectories;
    library->links = type == SHUModuleType_LibraryStatic ? SHUILD.MODULE.links : (SHUI_StringList){0};
    library->linkDirectories = type == SHUModuleType_LibraryStatic ? SHUILD.MODULE.linkDirectories : (SHUI_StringList){0};
}

// the module gets the public include directories of the libraries it links itself, but not of the libraries those link
static void SHUI_ModuleAddLinkedIncludes(void)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        const SHUI_Library *library = SHUI_ModuleFindLibrary(SHUILD.MODULE.links.data[i]);

        for (usz j = 0; library != NULL && j < library->includeDirectories.count; j++)
        {
            if (!SHUI_ListContains(&SHUILD.MODULE.linkedIncludeDirectories, library->includeDirectories.data[j]))
            {
                SHUI_ListAdd(&SHUILD.MODULE.linkedIncludeDirectories, SHUI_Copy(library->includeDirectories.data[j]));
            }
        }
    }
}

// a link and, after it, the libraries that it keeps as a static library, with their directories
static void SHUI_ModuleExpandLink(SHUI_StringList *links, const char *link, usz depth)
{
    // a library that links itself through others would expand forever
    SHU_Assert(depth < 64, "Library '%s' links itself through other libraries.", link);

    SHUI_ListAdd(links, SHUI_Copy(link));

    const SHUI_Library *library = SHUI_ModuleFindLibrary(link);

    if (library == NULL)
    {
        return;
    }

    for (usz i = 0; i < library->linkDirectories.count; i++)
    {
        if (!SHUI_ListContains(&SHUILD.MODULE.linkDirectories, library->linkDirectories.data[i]))
        {
            SHUI_ListAdd(&SHUILD.MODULE.linkDirectories, SHUI_Copy(library->linkDirectories.data[i]));
        }
    }

    for (usz i = 0; i < library->links.count; i++)
    {
        SHUI_ModuleExpandLink(links, library->links.data[i], depth + 1);
    }
}

// each static library the module links brings the libraries it keeps, after it, so the linker finds what it needs in order
static void SHUI_ModuleExpandLinks(void)
{
    SHUI_StringList expanded = {0};

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_ModuleExpandLink(&expanded, SHUILD.MODULE.links.data[i], 0);
    }

    // a library that comes more than once stays in its last place, after every library that needs it
    SHUI_StringList lastFirst = {0};

    for (usz i = expanded.count; i > 0; i--)
    {
        if (!SHUI_ListContains(&lastFirst, expanded.data[i - 1]))
        {
            SHUI_ListAdd(&lastFirst, expanded.data[i - 1]);
        }
    }

    SHUI_ListFree(&SHUILD.MODULE.links);

    for (usz i = lastFirst.count; i > 0; i--)
    {
        SHUI_ListAdd(&SHUILD.MODULE.links, lastFirst.data[i - 1]);
    }
}

// the file that a library compiles into; on Windows, a dynamic library's is its DLL, not the import library that SHU_UtilLibraryFile gives
static char *SHUI_ModuleLibraryFile(const char *name, SHUModuleType type)
{
    if (type == SHUModuleType_LibraryStatic)
    {
        return SHU_UtilFormat("lib%s.a", name);
    }

    switch (SHUILD.COMPILER.target)
    {
    case SHUPlatform_Windows:
        return SHU_UtilFormat("%s.dll", name);
    case SHUPlatform_MacOS:
        return SHU_UtilFormat("lib%s.dylib", name);
    default:
        return SHU_UtilFormat("lib%s.so", name);
    }
}

#ifdef SHUC_ENABLE_INCREMENTAL
static bool SHUI_FileNewerThan(const char *path, i64 time)
{
    return SHUI_FileGetType(path) == SHUFileType_Regular && SHUI_FileGetEditTime(path) > time;
}

// a module is linked again when a library it links is newer than its output
static bool SHUI_ModuleLinksNewer(const char *outputFile)
{
    i64 outputTime = SHUI_FileGetEditTime(outputFile);

    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        const char *directory = SHUILD.MODULE.linkDirectories.data[i];

        for (usz j = 0; j < SHUILD.MODULE.links.count; j++)
        {
            const char *link = SHUILD.MODULE.links.data[j];

            if (SHUI_FileNewerThan(SHUI_PathJoin(directory, SHU_UtilLibraryFile(link, SHUModuleType_LibraryStatic)), outputTime) ||
                SHUI_FileNewerThan(SHUI_PathJoin(directory, SHU_UtilLibraryFile(link, SHUModuleType_LibraryDynamic)), outputTime))
            {
                return true;
            }
        }
    }

    return false;
}
#endif

// a directory is searched at run time only if it holds a dynamic library that the module links
static bool SHUI_ModuleHoldsDynamicLink(const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        if (SHUI_FileGetType(SHUI_PathJoin(directory, SHUI_ModuleLibraryFile(SHUILD.MODULE.links.data[i], SHUModuleType_LibraryDynamic))) == SHUFileType_Regular)
        {
            return true;
        }
    }

    return false;
}

/// @param directory Output directory of the module, from which its run-time search paths start.
static void SHUI_CommandAddLinks(SHUI_StringList *command, const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        const char *linkDirectory = SHUILD.MODULE.linkDirectories.data[i];

        SHUI_ListAdd(command, SHU_UtilFormat("-L%s", linkDirectory));

        // the path from the module's own directory, so the two can move together; Windows has none, see SHU_ModuleCopyDynamicLinks
        if (SHUILD.COMPILER.target != SHUPlatform_Windows && SHUI_ModuleHoldsDynamicLink(linkDirectory))
        {
            char *relative = SHUI_PathRelative(directory, linkDirectory);
            usz length = (usz)strlen(relative);

            SHUI_ListAdd(command, SHU_UtilFormat("-Wl,-rpath,%s%s%.*s",
                                                 SHUILD.COMPILER.target == SHUPlatform_MacOS ? "@loader_path" : "$ORIGIN",
                                                 length == 0 ? "" : "/",
                                                 (int)(length == 0 ? 0 : length - 1),
                                                 relative));
        }
    }

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_ListAdd(command, SHU_UtilFormat("-l%s", SHUILD.MODULE.links.data[i]));
    }
}

// the dynamic libraries the module links go beside it, from the first directory that holds each
static void SHUI_ModuleCopyDynamicLinks(const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        char *file = SHUI_ModuleLibraryFile(SHUILD.MODULE.links.data[i], SHUModuleType_LibraryDynamic);

        for (usz j = 0; j < SHUILD.MODULE.linkDirectories.count; j++)
        {
            const char *linkDirectory = SHUILD.MODULE.linkDirectories.data[j];
            char *library = SHUI_PathJoin(linkDirectory, file);

            if (SHUI_FileGetType(library) != SHUFileType_Regular)
            {
                continue;
            }

            // a library in the module's own directory is beside it already
            if (strcmp(SHUI_PathClean(linkDirectory), SHUI_PathClean(directory)) != 0)
            {
                SHUI_FileCopy(library, SHUI_PathJoin(directory, file));
            }

            break;
        }
    }
}

static char *SHUI_ModuleOutputFile(const char *directory, SHUModuleType type)
{
    if (type == SHUModuleType_Executable)
    {
        return SHU_UtilFormat("%s%s%s", directory, SHUILD.MODULE.name, SHUILD.COMPILER.target == SHUPlatform_Windows ? ".exe" : "");
    }

    return SHUI_PathJoin(directory, SHUI_ModuleLibraryFile(SHUILD.MODULE.name, type));
}

// links the objects into an executable or a dynamic library, or packs them into a static library
static void SHUI_ModuleLink(SHUModuleType type, const SHUI_StringList *objectFiles, const char *outputFile, const char *directory)
{
    SHUI_StringList command = {0};

    if (type == SHUModuleType_LibraryStatic)
    {
        // ar adds to an archive that exists, so the archive is made again, without the objects of sources that are gone
        if (SHUI_FileGetType(outputFile) == SHUFileType_Regular)
        {
            SHUI_FileDelete(outputFile);
        }

        // llvm-ar reads objects of any system, and gcc-ar of the compiler's prefix and version reads its link-time optimized objects
        SHUI_ListAdd(&command, SHU_CompilerGetTool("gcc-ar", "llvm-ar"));
        SHUI_CommandAddArgument(&command, "rcs");
        SHUI_CommandAddArgument(&command, outputFile);
    }
    else
    {
        SHUI_CommandAddArguments(&command, SHUILD.COMPILER.command);

        if (type == SHUModuleType_LibraryDynamic)
        {
            SHUI_CommandAddArgument(&command, "-shared");
        }

        SHUI_CommandAddArgument(&command, "-o");
        SHUI_CommandAddArgument(&command, outputFile);

        // a DLL is linked through its import library, which -l finds as lib<name>.dll.a
        if (type == SHUModuleType_LibraryDynamic && SHUILD.COMPILER.target == SHUPlatform_Windows)
        {
            SHUI_ListAdd(&command, SHU_UtilFormat("-Wl,--out-implib,%s%s", directory, SHU_UtilLibraryFile(SHUILD.MODULE.name, type)));
        }
    }

    for (usz i = 0; i < objectFiles->count; i++)
    {
        SHUI_CommandAddArgument(&command, objectFiles->data[i]);
    }

    if (type != SHUModuleType_LibraryStatic)
    {
        SHUI_CommandAddLinks(&command, directory);

        // an executable is linked with the compiler's flags too, as the sanitizers need
        if (type == SHUModuleType_Executable)
        {
            SHUI_CommandAddFlags(&command, &SHUILD.COMPILER.flags);
        }

        SHUI_CommandAddFlags(&command, &SHUILD.COMPILER.linkerFlags);
    }

    SHUI_CommandRunOrFail(&command);
    SHUI_ListFree(&command);
}

#pragma endregion Module

#pragma endregion Internals

#pragma region Utility

// the build script compiles again when its source, or a header it includes, is newer than its program
static bool SHUI_UtilScriptChanged(const char *program, const char *source, const char *flags)
{
    if (SHUI_FileGetType(program) != SHUFileType_Regular || SHUI_FileGetEditTime(program) < SHUI_FileGetEditTime(source))
    {
        return true;
    }

    char *dependencyFile = SHU_UtilFormat("%s.d", program);

    SHUI_StringList command = {0};
    SHUI_CommandAddArguments(&command, SHUI_CompilerForScripts());
    SHUI_CommandAddArgument(&command, "-MM");
    SHUI_CommandAddArgument(&command, source);
    SHUI_CommandAddArgument(&command, "-MF");
    SHUI_CommandAddArgument(&command, dependencyFile);
    SHUI_CommandAddArguments(&command, flags);

    // when the dependencies cannot be listed, the rebuild shows why
    bool changed = SHUI_CommandRun(&command) != 0 || SHUI_FileHasNewerDependency(dependencyFile, program);

    if (SHUI_FileGetType(dependencyFile) == SHUFileType_Regular)
    {
        SHUI_FileDelete(dependencyFile);
    }

    SHUI_ListFree(&command);

    return changed;
}

void SHUI_UtilAutomate(int argc, char **argv, const char *sourceFile)
{
    SHU_AssertNullPointer(sourceFile);
    SHU_AssertNullPointer(argv);
    SHU_Assert(argc > 0, "Invalid argument count");

    char *program = SHUI_PathFromScript(SHUI_PathFileName(argv[0]));
    char *source = SHUI_PathFromScript(SHUI_PathFileName(sourceFile));

    char *oldProgram = SHU_UtilFormat("%s.old", program);

    // the program that an earlier rebuild replaced; Windows cannot delete it while it runs, so it stays until the next run
    if (SHUI_FileGetType(oldProgram) == SHUFileType_Regular)
    {
        remove(oldProgram);
    }

    if (!SHUI_UtilScriptChanged(program, source, ""))
    {
        return;
    }

    SHU_UtilLog("the build script changed; rebuilding it");

    SHUI_FileRename(program, oldProgram);

    SHUI_StringList command = {0};
    SHUI_CommandAddArguments(&command, SHUI_CompilerForScripts());
    SHUI_CommandAddArgument(&command, "-o");
    SHUI_CommandAddArgument(&command, program);
    SHUI_CommandAddArgument(&command, source);
    SHUI_CommandAddArguments(&command, SHUILD_BUILD);
    i32 result = SHUI_CommandRun(&command);

    if (result != 0)
    {
        SHUI_FileRename(oldProgram, program);
        SHU_UtilFail("the build script cannot be rebuilt; " SHUI_COMMAND_FAILED, result, SHUI_CommandJoin(&command));
    }

#if !SHUM_HOST_WINDOWS
    remove(oldProgram);
#endif

    // the new program runs in place of this one, with the same arguments
    SHUI_StringList rerun = {0};
    SHUI_CommandAddArgument(&rerun, program);

    for (int i = 1; i < argc; i++)
    {
        SHUI_CommandAddArgument(&rerun, argv[i]);
    }

    exit(SHUI_CommandRun(&rerun));
}

void SHU_UtilRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    i32 result = SHUI_ShellRun(command);

    if (result != 0)
    {
        SHU_UtilFail(SHUI_COMMAND_FAILED, result, command);
    }

    free(command);
}

i32 SHU_UtilRunTry(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    i32 result = SHUI_ShellRun(command);

    if (result != 0)
    {
        SHU_UtilWarn(SHUI_COMMAND_FAILED, result, command);
    }

    free(command);

    return result;
}

void SHU_UtilRunLogged(const char *log, const char *commandFormat, ...)
{
    SHU_AssertNullPointer(log);
    SHU_AssertNullPointer(commandFormat);

    // the path gets the system's separators, so its directory can be made on Windows too; the shell does not make it
    char *logPath = SHUI_PathFromScript(log);
    SHUI_FileMakeDirectories(SHUI_PathDirectory(logPath));

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    // both POSIX shells and cmd.exe send the output and the errors to the file this way
    i32 result = SHUI_ShellRun(SHU_UtilFormat("%s > \"%s\" 2>&1", command, logPath));

    if (result == 0)
    {
        free(command);
        return;
    }

    // the end of the log tells why it failed
    SHUSlice text = SHUI_FileRead(logPath);
    const char *start = (const char *)text.data + text.size;

    for (usz lines = 0; start > (const char *)text.data && lines <= 20; start--)
    {
        lines += start[-1] == '\n';
    }

    fprintf(SHU_LOG_STREAM, "%s\n", start);
    SHU_UtilFail("command failed with exit code %d; " SHUM_LOG_PATH("%s") " has its output: " SHUM_LOG_COMMAND("%s"), result, SHUI_PathForLog(logPath), command);
}

void SHU_Shuild(const char *script, const char *program, const char *flags, const char *arguments)
{
    SHU_AssertNullPointer(script);
    SHU_AssertNullPointer(program);
    SHU_AssertNullPointer(flags);
    SHU_AssertNullPointer(arguments);

    char *programPath = SHUI_PathFromScript(SHU_UtilFormat("%s%s", program, SHUM_HOST_WINDOWS ? ".exe" : ""));

    // the script is named by its directory, such as plugins for plugins/shuild.c, or by its program when it is in this directory
    char *scriptDirectory = SHUI_PathDirectory(script);
    usz nameLength = strlen(scriptDirectory) > 0 ? strlen(scriptDirectory) - 1 : 0;
    char *name = nameLength > 0 ? SHU_UtilFormat("%.*s", (int)nameLength, scriptDirectory) : SHU_UtilFormat("%s", program);

    // a line sets its log apart from the lines before it
    SHU_UtilLog(SHUM_COLOR_DIM("---- ") SHUM_LOG_NAME("%s") " (" SHUM_COLOR_GREEN("Build Script") "): building " SHUM_COLOR_DIM("----"), name);

    // it compiles when its source, or a header it includes, is newer than its program
    char *scriptPath = SHUI_PathFromScript(script);
    char *allFlags = SHU_UtilFormat("%s %s", SHUILD_BUILD, flags);

    if (SHUI_UtilScriptChanged(programPath, scriptPath, allFlags))
    {
        SHUI_StringList command = {0};
        SHUI_CommandAddArguments(&command, SHUI_CompilerForScripts());
        SHUI_CommandAddArgument(&command, "-o");
        SHUI_CommandAddArgument(&command, programPath);
        SHUI_CommandAddArgument(&command, scriptPath);
        SHUI_CommandAddArguments(&command, allFlags);
        SHUI_CommandRunOrFail(&command);
        SHUI_ListFree(&command);
    }

    free(scriptPath);
    free(allFlags);

    // it runs in its own directory, as it would if it were run there by hand, and the build goes on here after it
    char *directory = SHUI_PathDirectory(programPath);

#if SHUM_HOST_WINDOWS
    char *previous = _getcwd(NULL, 0);
    SHU_Assert(previous != NULL && _chdir(directory) == 0, "Cannot run '%s' in its directory.", programPath);
    SHU_UtilRun("\"%s\" %s", programPath, arguments);
    SHU_Assert(_chdir(previous) == 0, "Cannot go back to '%s'.", previous);
#else
    char *previous = getcwd(NULL, 0);
    SHU_Assert(previous != NULL && chdir(directory) == 0, "Cannot run '%s' in its directory.", programPath);
    SHU_UtilRun("\"%s\" %s", programPath, arguments);
    SHU_Assert(chdir(previous) == 0, "Cannot go back to '%s'.", previous);
#endif

    SHU_UtilLog(SHUM_LOG_NAME("%s") " (" SHUM_COLOR_GREEN("Build Script") "): built", name);
    free(previous);
    free(scriptDirectory);
    free(name);
}

const char *SHU_UtilGetScriptDirectory(void)
{
    return SHUI_PathScriptDirectory();
}

char *SHU_UtilGetPath(const char *path)
{
    SHU_AssertNullPointer(path);

    return SHUI_PathFromScript(path);
}

SHUFileType SHU_UtilFileExists(const char *file)
{
    SHU_AssertNullPointer(file);

    return SHUI_FileGetType(SHUI_PathFromScript(file));
}

void SHU_UtilCreateDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    SHUI_FileMakeDirectories(SHUI_PathFromScript(directory));
}

void SHU_UtilDeleteFile(const char *file)
{
    SHU_AssertNullPointer(file);

    char *path = SHUI_PathFromScript(file);

    if (SHUI_FileGetType(path) != SHUFileType_Invalid)
    {
        SHUI_FileDelete(path);
    }

    free(path);
}

void SHU_UtilCopyFile(const char *file, const char *directory)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(directory);

    char *from = SHUI_PathFromScript(file);
    char *to = SHUI_PathFromScript(directory);

    // a file goes into the directory under its own name, and a directory's contents go into it
    if (SHUI_FileGetType(from) == SHUFileType_Regular)
    {
        SHUI_FileMakeDirectories(to);
        to = SHUI_PathJoin(to, SHUI_PathFileName(from));
    }

    SHUI_FileCopy(from, to);
}

static void SHUI_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    SHUI_StringList names = SHUI_FileListNames(SHUI_PathFromScript(directory));

    for (usz i = 0; i < names.count; i++)
    {
        // names that start with a dot are hidden
        if (names.data[i][0] == '.')
        {
            continue;
        }

        char *path = SHUI_PathJoin(directory, names.data[i]);
        SHUFileType type = SHUI_FileGetType(SHUI_PathFromScript(path));

        if (type == SHUFileType_Directory)
        {
            path = SHUI_PathJoinDirectory(path, "");
        }

        function(path, type, data);

        if (type == SHUFileType_Directory && recursive)
        {
            SHUI_UtilListDirectory(path, recursive, function, data);
        }
    }

    SHUI_ListFree(&names);
}

void SHU_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    SHU_AssertNullPointer(directory);
    SHU_AssertNullPointer(function);

    // the build script's own directory is listed with an empty path
    SHUI_UtilListDirectory(SHUI_PathJoinDirectory("", directory), recursive, function, data);
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

    return SHUI_FileRead(SHUI_PathFromScript(file));
}

void SHU_UtilWriteFile(const char *file, SHUSliceView content)
{
    SHU_AssertNullPointer(file);

    SHUI_FileWrite(SHUI_PathFromScript(file), content);
}

char *SHU_UtilLibraryFile(const char *name, SHUModuleType type)
{
    SHU_AssertNullPointer(name);
    SHU_Assert(type == SHUModuleType_LibraryStatic || type == SHUModuleType_LibraryDynamic, "Module type %d is not a library.", (int)type);

    // a DLL is linked through its import library
    if (type == SHUModuleType_LibraryDynamic && SHUILD.COMPILER.target == SHUPlatform_Windows)
    {
        return SHU_UtilFormat("lib%s.dll.a", name);
    }

    return SHUI_ModuleLibraryFile(name, type);
}

#pragma endregion Utility

#ifdef SHUC_ENABLE_INCREMENTAL
#pragma region Cache

void SHU_CacheConfigure(const char *cacheDirectory)
{
    SHU_AssertNullPointer(cacheDirectory);

    SHUILD.cacheDirectory = SHUI_PathJoinDirectory(SHUI_PathScriptDirectory(), cacheDirectory);
    SHUI_FileMakeDirectories(SHUILD.cacheDirectory);
}

#pragma endregion Cache
#endif // SHUC_ENABLE_INCREMENTAL

#pragma region Compiler

void SHU_CompilerConfigure(SHUCompiler family, const char *command)
{
    SHU_AssertNullPointer(command);

    SHUILD.COMPILER.family = family;
    SHUILD.COMPILER.command = SHUI_Copy(command);
    SHUILD.COMPILER.target = SHUI_PlatformFromMachine(SHUI_CompilerReadLine(command, "-dumpmachine"));
}

void SHU_CompilerConfigureTry(const char *command)
{
    if (command != NULL && command[0] != '\0')
    {
        SHUCompiler family = SHUI_CompilerFamily(command);

        if (family == SHUCompiler_Unknown)
        {
            SHU_UtilFail("compiler " SHUM_LOG_VALUE("%s") " is not known; configure it with SHU_CompilerConfigure.", command);
        }

        SHU_CompilerConfigure(family, command);
        return;
    }

    usz count = 0;
    const SHUCompilerInfo *compilers = SHUI_CompilerDescribeAll(&count);
    const SHUCompilerInfo *picked = SHUI_CompilerPick(compilers, count);

    if (picked == NULL)
    {
        SHU_CompilerConfigure((SHUCompiler)SHUM_HOST_COMPILER, SHUCompiler_GetCommand(SHUM_HOST_COMPILER));
    }
    else
    {
        SHU_CompilerConfigure(picked->family, picked->command);
    }
}

SHUCompilerInfo *SHU_CompilerDetect(usz *retCount)
{
    SHU_AssertNullPointer(retCount);

    SHUCompilerInfo *compilers = SHUI_CompilerDescribeAll(retCount);

    // only a compiler whose programs run here can be tried with the sanitizers
    for (usz i = 0; i < *retCount; i++)
    {
        SHUCompilerInfo *compiler = &compilers[i];
        compiler->sanitizers = compiler->target == SHUM_HOST_PLATFORM && SHUI_ProcessorIsHost(compiler->machine) && SHUI_CompilerHasSanitizers(compiler->command);
    }

    return compilers;
}

static void SHUI_CompilerAddFlag(const char *flag)
{
    SHUI_ListAdd(&SHUILD.COMPILER.flags, SHUI_Copy(flag));
}

void SHUI_CompilerAddFlags(const char *flags, ...)
{
    SHU_AssertNullPointer(flags);
    SHUI_EACH_ARGUMENT(flags, SHUI_CompilerAddFlag);
}

void SHU_CompilerClearFlags(void)
{
    SHUI_ListFree(&SHUILD.COMPILER.flags);
    SHUI_ListFree(&SHUILD.COMPILER.linkerFlags);
}

static void SHUI_CompilerAddLinkerFlag(const char *flag)
{
    SHUI_ListAdd(&SHUILD.COMPILER.linkerFlags, SHUI_Copy(flag));
}

void SHUI_CompilerAddLinkerFlags(const char *flags, ...)
{
    SHU_AssertNullPointer(flags);
    SHUI_EACH_ARGUMENT(flags, SHUI_CompilerAddLinkerFlag);
}

void SHUI_CompilerAddDefinitions(const char *name, ...)
{
    va_list args;
    va_start(args, name);

    // the arguments are names and values in pairs, until a NULL name
    while (name != NULL)
    {
        const char *value = va_arg(args, const char *);

        // the flags are split as a shell splits them, on every system, so the single quotes keep the value whole
        SHUI_ListAdd(&SHUILD.COMPILER.flags, value == NULL ? SHU_UtilFormat("-D%s", name) : SHU_UtilFormat("-D%s='%s'", name, value));

        name = va_arg(args, const char *);
    }

    va_end(args);
}

SHUCompiler SHU_CompilerGetFamily(void)
{
    return SHUILD.COMPILER.family;
}

SHUPlatform SHU_CompilerGetTarget(void)
{
    return SHUILD.COMPILER.target;
}

char *SHU_CompilerGetTool(const char *gccTool, const char *clangTool)
{
    SHU_AssertNullPointer(gccTool);
    SHU_AssertNullPointer(clangTool);

    bool clang = SHUILD.COMPILER.family == SHUCompiler_Clang;
    const char *family = clang ? "clang" : "gcc";
    const char *tool = clang ? clangTool : gccTool;
    const char *command = SHUILD.COMPILER.command;

    // the last one is the program's name, as a directory before it may hold the family's name too
    const char *found = NULL;

    for (const char *c = strstr(command, family); c != NULL; c = strstr(c + 1, family))
    {
        found = c;
    }

    if (found == NULL)
    {
        return SHUI_Copy(tool);
    }

    return SHU_UtilFormat("%.*s%s%s", (int)(found - command), command, tool, found + strlen(family));
}

#pragma endregion Compiler

#pragma region Module

void SHUI_ModuleBegin(const char *name, const char *root)
{
    SHU_AssertNullPointer(name);

    SHUILD.MODULE.name = SHUI_Copy(name);
    SHUILD.MODULE.root = SHUI_PathJoinDirectory(SHUI_PathScriptDirectory(), root != NULL ? root : "");
}

static void SHUI_ModuleAddIncludeDirectory(const char *directory)
{
    SHUI_ListAdd(&SHUILD.MODULE.includeDirectories, SHUI_PathJoinDirectory(SHUILD.MODULE.root, directory));
}

void SHUI_ModuleAddIncludeDirectories(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_ModuleAddIncludeDirectory);
}

static void SHUI_ModuleAddPublicIncludeDirectory(const char *directory)
{
    SHUI_ModuleAddIncludeDirectory(directory);
    SHUI_ListAdd(&SHUILD.MODULE.publicIncludeDirectories, SHUI_Copy(SHUILD.MODULE.includeDirectories.data[SHUILD.MODULE.includeDirectories.count - 1]));
}

void SHUI_ModuleAddPublicIncludeDirectories(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_ModuleAddPublicIncludeDirectory);
}

static void SHUI_ModuleAddSourceFile(const char *file)
{
    char *path = SHUI_PathJoin(SHUILD.MODULE.root, file);
    SHUFileType type = SHUI_FileGetType(path);

    if (type == SHUFileType_Directory)
    {
        SHUI_ModuleAddSourceDirectory(path);
    }
    else if (type == SHUFileType_Regular)
    {
        SHUI_ListAdd(&SHUILD.MODULE.sourceFiles, path);
    }
    else
    {
        SHU_UtilFail("source " SHUM_LOG_PATH("%s") " does not exist.", SHUI_PathForLog(path));
    }
}

void SHUI_ModuleAddSourceFiles(const char *file, ...)
{
    SHU_AssertNullPointer(file);
    SHUI_EACH_ARGUMENT(file, SHUI_ModuleAddSourceFile);
}

static void SHUI_ModuleAddLibraryDirectory(const char *directory)
{
    char *path = SHUI_PathJoinDirectory(SHUI_PathScriptDirectory(), directory);

    if (SHUI_FileGetType(path) != SHUFileType_Directory)
    {
        SHU_UtilFail("library directory " SHUM_LOG_PATH("%s") " does not exist.", SHUI_PathForLog(path));
    }

    SHUI_ListAdd(&SHUILD.MODULE.linkDirectories, path);
}

void SHUI_ModuleAddLibraryDirectories(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_ModuleAddLibraryDirectory);
}

static void SHUI_ModuleLinkLibrary(const char *library)
{
    SHUI_ListAdd(&SHUILD.MODULE.links, SHUI_Copy(library));
}

void SHUI_ModuleLinkLibraries(const char *library, ...)
{
    SHU_AssertNullPointer(library);
    SHUI_EACH_ARGUMENT(library, SHUI_ModuleLinkLibrary);
}

void SHU_ModuleCopyDynamicLinks(void)
{
    SHUILD.MODULE.copyDynamicLinks = true;
}

void SHUI_ModuleCompile(SHUModuleType type, const char *directory)
{
    SHU_Assert(type == SHUModuleType_Executable || type == SHUModuleType_LibraryStatic || type == SHUModuleType_LibraryDynamic, "Module type %d is not known.", (int)type);

    char *outputDirectory = SHUI_PathJoinDirectory(SHUI_PathScriptDirectory(), directory != NULL ? directory : "");
    SHUI_FileMakeDirectories(outputDirectory);

#ifdef SHUC_ENABLE_INCREMENTAL
    // a module whose settings, such as its flags, are new or changed compiles every file again
    SHUI_SettingsState settings = SHUI_CacheCompareSettings();

    if (settings != SHUI_SettingsState_Same)
    {
        SHUI_CacheClearModule();
        SHUI_CacheSaveSettings();
    }

    bool settingsChanged = settings == SHUI_SettingsState_Changed;
#else
    bool settingsChanged = false;
#endif

    SHUI_ModuleAddLinkedIncludes();

    if (type != SHUModuleType_LibraryStatic)
    {
        SHUI_ModuleExpandLinks();
    }

    if (type == SHUModuleType_Executable)
    {
        SHUI_ListAdd(&SHUILD.MODULE.linkDirectories, SHUI_Copy(SHUI_PathScriptDirectory()));
    }

    // code for a DLL needs no position-independent flag, and some compilers refuse it
    const char *extraFlag = type == SHUModuleType_LibraryDynamic && SHUILD.COMPILER.target != SHUPlatform_Windows ? "-fPIC" : NULL;

    SHUI_StringList objectFiles = SHUI_ModuleCompileObjects(extraFlag);
    char *outputFile = SHUI_ModuleOutputFile(outputDirectory, type);

    bool needsLink = SHUILD.MODULE.compiledCount > 0 || SHUI_FileGetType(outputFile) != SHUFileType_Regular;

#ifdef SHUC_ENABLE_INCREMENTAL
    needsLink = needsLink || (type != SHUModuleType_LibraryStatic && SHUI_ModuleLinksNewer(outputFile));
#endif

    if (needsLink)
    {
        SHUI_ModuleLink(type, &objectFiles, outputFile, outputDirectory);
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    SHUI_ModuleDeleteObjects();
#endif

    SHUI_ListFree(&objectFiles);

    if (SHUILD.MODULE.copyDynamicLinks && type != SHUModuleType_LibraryStatic)
    {
        SHUI_ModuleCopyDynamicLinks(outputDirectory);
    }

    if (type != SHUModuleType_Executable)
    {
        SHUI_ModuleRecordLibrary(type);
    }

#ifndef SHUC_NO_MODULE_LOG
    // one line for the module: what it compiled and made, or that it was up to date
    if (!needsLink)
    {
        SHU_UtilLog(SHUM_LOG_NAME("%s") " (%s): " SHUM_COLOR_DIM("up to date"), SHUILD.MODULE.name, SHUModuleType_GetLogString(type));
    }
    else
    {
        SHU_UtilLog(SHUM_LOG_NAME("%s") " (%s): compiled %zu file%s, %s " SHUM_LOG_PATH("%s") SHUM_COLOR_DIM("%s"),
                    SHUILD.MODULE.name,
                    SHUModuleType_GetLogString(type),
                    SHUILD.MODULE.compiledCount,
                    SHUILD.MODULE.compiledCount == 1 ? "" : "s",
                    type == SHUModuleType_LibraryStatic ? "packed" : "linked",
                    SHUI_PathForLog(outputFile),
                    settingsChanged ? " (settings changed)" : "");
    }
#else
    (void)settingsChanged;
#endif

    // the next module starts new; a library keeps its links and public include directories, so they are not freed
    SHUI_ListFree(&SHUILD.MODULE.includeDirectories);
    SHUI_ListFree(&SHUILD.MODULE.sourceFiles);
    SHUI_ListFree(&SHUILD.MODULE.linkedIncludeDirectories);
    SHUILD.MODULE = (__typeof__(SHUILD.MODULE)){0};
}

#pragma endregion Module

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
