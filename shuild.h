// You can define various macros to configure Shuild before including this file.
// define SHU_IMPLEMENTATION in one file to include the implementation.
// define SHUC_ENABLE_INCREMENTAL to enable incremental builds.
// define SHUC_NO_MODULE_LOG to disable module logs.
// define SHUC_NO_RUN_LOG to disable command run logs.
// define SHUC_NO_RUN_ERROR to disable termination on run error.
// define SHUC_MAX_JOB_COUNT 1 to compile one file at a time instead of as many as there are processors.
// define SHUC_LOG_FORMAT and SHUC_LOG_FORMAT_VALUES to change log formatting.
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

#ifndef SHUC_MAX_COMMAND_BUFFER_SIZE
#define SHUC_MAX_COMMAND_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_MESSAGE_BUFFER_SIZE
#define SHUC_MAX_MESSAGE_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_STRING_SIZE
#define SHUC_MAX_STRING_SIZE 256
#endif

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

/// @brief Internal command runner function.
/// @param command Command to run with the shell, through system. (eg. clang example.c -o example) Modules run the compiler without a shell.
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
i32 SHU_UtilRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a command like SHU_UtilRun, but its failure does not stop the build, even without SHUC_NO_RUN_ERROR. Use it for a command that may fail.
/// @param command Command to run with the shell, through system. (eg. ./tests --quick)
/// @return Exit code of the command.
i32 SHU_UtilTryRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

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
/// @return Slice of the file's contents, followed by a terminating zero that the size does not count. Free its data with free.
SHUSlice SHU_UtilReadFile(const char *file);

/// @brief Writes a file, replacing it if it exists. A file that has the content already is left as is, so its edit time stays and what includes it does not compile again.
/// @param file File to write, relative to current executable.
/// @param content Content to write.
void SHU_UtilWriteFile(const char *file, SHUSliceView content);

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

/// @brief Tries to configure the compiler by checking gcc or clang substring inside the string. Default is the host (compiler that shuild.c compiled) compiler.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc). If NULL, uses the host compiler command default.
void SHU_CompilerTryConfigure(const char *compilerCommand);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add. Can include multiple flags separated by spaces as you want, quoted as in a shell. (eg. -DFOO=31)
void SHU_CompilerAddFlags(const char *flags);
// todo make it a macro

/// @brief Clears and sets the compiler flags, replacing all existing ones.
/// @param flags Flags to set. Can include multiple flags separated by spaces as you want.
void SHU_CompilerSetFlags(const char *flags);

/// @brief Clears the current compiler flags.
void SHU_CompilerClearFlags(void);

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

#pragma endregion Compiler

#pragma region Module

/// @brief Begins a new module with the given name. A module can be an executable or a library. Must be called before any other Module function.
/// @param name Name of the module. Which will be used also for output file name. (eg. myLibName, myAppName)
/// @param root Root directory of the module. Will be used to relatively point other files and directories for module. Relative to current executable. Leave it empty string or NULL to ignore. (eg. dependencies/library/)
void SHU_ModuleBegin(const char *name, const char *root);

/// @brief Adds include directories to the module.
/// @param directory Include directory to add to the current module. Relative to root directory specified in ModuleBegin (eg. include/)
void SHU_ModuleAddIncludeDirectory(const char *directory);

/// @brief Adds source files to the module. Single file or recursive directory.
/// @param file Single file to add to the current module. Relative to root directory specified in ModuleBegin (eg. source.c)
/// @note A header file is compiled as C, so a single header library can be added with the definition of its implementation. (eg. clay.h with CLAY_IMPLEMENTATION)
void SHU_ModuleAddSourceFile(const char *file);

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name. Relative to current executable directory. (eg. build/)
/// @param module Current module mode. Use with SHUM_MODULE_<...> macros. (eg. SHUModuleType_LibraryStatic)
void SHU_ModuleCompile(const char *directory, SHUModuleType module);

/// @brief Adds a directory to search for the libraries that the current module links. A static library keeps it for the modules that link it, as it keeps its libraries.
/// A directory that holds a dynamic library the module links is embedded in it, to find the library at run time.
/// @param directory Directory to search for libraries. Relative to current executable directory.  (eg. build/arc/)
void SHU_ModuleAddLibraryDirectory(const char *directory);

/// @brief Links a library to the current module. An executable or a dynamic library is linked with it.
/// A static library cannot be linked, so it keeps the library: a module that links the static library later gets the library too, after it, with its directories.
/// @param library Library to link with the module. Shouldn't include any path, use `SHU_ModuleAddLibraryDirectory` to search inside. (eg. myLibName)
void SHU_ModuleLinkLibrary(const char *library);

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

#ifdef SHUC_ENABLE_INCREMENTAL
typedef u64 SHUI_Hash;
#endif

typedef struct SHUI_String
{
    usz length;
    char data[SHUC_MAX_STRING_SIZE];
} SHUI_String;

typedef struct SHUI_StringList
{
    usz count;
    usz capacity;
    SHUI_String *data;
} SHUI_StringList;

/// @brief A static library and the libraries it links, which a module that links it gets too.
typedef struct SHUI_Library
{
    SHUI_String name;
    SHUI_StringList links;
    SHUI_StringList linkDirectories;
} SHUI_Library;

#ifdef SHUC_ENABLE_INCREMENTAL
static bool SHUI_CDependencyDirty(const SHUI_String *dependencyFile, const SHUI_String *objectFile);
#endif

static struct
{
    SHUI_String currentExecutableDirectory;

#ifdef SHUC_ENABLE_INCREMENTAL
    SHUI_String cacheDirectory;
#endif

    struct
    {
        u8 identifier;
        SHUI_String command;
        SHUI_StringList flags;
    } COMPILER;

    struct
    {
        i64 processes[SHUC_MAX_JOB_COUNT];
        usz count;
        usz limit;
        i32 failure;
    } JOBS;

    struct
    {
        SHUI_String name;
        SHUI_String root;
        SHUI_StringList includeDirectories;
        SHUI_StringList sourceFiles;
        SHUI_StringList links;
        SHUI_StringList linkDirectories;
    } MODULE;

    // the static libraries compiled so far, with the libraries they link
    struct
    {
        usz count;
        usz capacity;
        SHUI_Library *data;
    } LIBRARIES;
} SHUILD = {0};

#define SHUI_SZero(string) memset(&string, 0, sizeof(SHUI_String));

/*
static void SHUI_SAppend(SHUI_String *string, const SHUI_String *stringToAppend)
{
    SHU_Assert(string->length + stringToAppend->length < SHUC_MAX_STRING_SIZE, "Appending string length '%u' to '%u' exceeds maximum path size '%d'.", stringToAppend->length, string->length, SHUC_MAX_STRING_SIZE - 1);

    memcpy(string->data + string->length, stringToAppend->data, stringToAppend->length);
    string->length += stringToAppend->length;
    string->data[string->length] = '\0';
}
*/

static void SHUI_SAppendC(SHUI_String *string, const char *stringToAppend)
{
    usz stringLength = (usz)strlen(stringToAppend);

    SHU_Assert(string->length + stringLength < SHUC_MAX_STRING_SIZE, "Appending string length '%zu' to '%zu' exceeds maximum path size '%d'.", stringLength, string->length, SHUC_MAX_STRING_SIZE - 1);

    memcpy(string->data + string->length, stringToAppend, stringLength);
    string->length += stringLength;
    string->data[string->length] = '\0';
}

static void SHUI_SAppendChar(SHUI_String *string, char character)
{
    SHU_Assert(string->length + 1 < SHUC_MAX_STRING_SIZE, "Appending a character to '%zu' exceeds maximum path size '%d'.", string->length, SHUC_MAX_STRING_SIZE - 1);

    string->data[string->length++] = character;
    string->data[string->length] = '\0';
}

static bool SHUI_SEndsWithC(const char *string, const char *suffix)
{
    usz stringLength = (usz)strlen(string);
    usz suffixLength = (usz)strlen(suffix);

    return stringLength >= suffixLength && strcmp(string + stringLength - suffixLength, suffix) == 0;
}

static void SHUI_SFormat(SHUI_String *string, const char *format, ...) __attribute__((format(printf, 2, 3)));
static void SHUI_SFormat(SHUI_String *string, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    i32 length = vsnprintf(string->data, SHUC_MAX_STRING_SIZE, format, args);
    va_end(args);

    SHU_Assert(length >= 0 && length < SHUC_MAX_STRING_SIZE, "Formatted string length '%d' exceeds maximum path size '%d'.", length, SHUC_MAX_STRING_SIZE - 1);

    string->length = (usz)length;
}

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
static void SHUI_SNormalizePath(SHUI_String *string)
{
    for (usz i = 0; i < string->length; i++)
    {
        if (string->data[i] == '/')
        {
            string->data[i] = '\\';
        }
    }
}
#endif

static SHUI_StringList SHUI_SLCreate(usz capacity)
{
    SHUI_StringList list = {0};
    list.data = (SHUI_String *)malloc(sizeof(SHUI_String) * capacity);
    list.count = 0;
    list.capacity = capacity;

    SHU_Assert(list.data != NULL, "Internal: Memory allocation failed for size '%zu'.", sizeof(SHUI_String) * capacity);

    return list;
}

static void SHUI_SLDestroy(SHUI_StringList *list)
{
    free(list->data);
    list->count = 0;
    list->capacity = 0;
    list->data = NULL;
}

static void SHUI_SLResize(SHUI_StringList *list, usz newCapacity)
{
    if (newCapacity == list->capacity)
    {
        return;
    }

    list->data = (SHUI_String *)realloc(list->data, sizeof(SHUI_String) * newCapacity);
    list->capacity = newCapacity;

    SHU_Assert(list->data != NULL, "Internal: Memory reallocation failed for size '%zu'.", sizeof(SHUI_String) * newCapacity);
}

static void SHUI_SLAdd(SHUI_StringList *list, const SHUI_String *string)
{
    if (list->data == NULL)
    {
        *list = SHUI_SLCreate(SHUC_ARRAY_INITIAL_COUNT);
    }
    else if (list->count >= list->capacity)
    {
        SHUI_SLResize(list, list->capacity == 0 ? SHUC_ARRAY_INITIAL_COUNT : (usz)((float)list->capacity * SHUC_ARRAY_RESIZE_FACTOR));
    }

    list->data[list->count++] = *string;
}

static bool SHUI_SLContains(const SHUI_StringList *list, const SHUI_String *string)
{
    for (usz i = 0; i < list->count; i++)
    {
        if (strcmp(list->data[i].data, string->data) == 0)
        {
            return true;
        }
    }

    return false;
}

static void SHUI_CAddArgument(SHUI_StringList *command, const char *argument)
{
    SHUI_String argumentStr = {0};
    SHUI_SAppendC(&argumentStr, argument);
    SHUI_SLAdd(command, &argumentStr);
}

static void SHUI_CAddArguments(SHUI_StringList *command, const char *arguments)
{
    // splits the arguments the way a POSIX shell does: spaces separate them, quotes group them and backslashes escape
    SHUI_String argument = {0};
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
                SHUI_SAppendChar(&argument, *c);
            }
        }
        else if (quote == '"')
        {
            if (*c == '"')
            {
                quote = '\0';
            }
            else if (*c == '\\' && (c[1] == '"' || c[1] == '\\' || c[1] == '$' || c[1] == '`'))
            {
                SHUI_SAppendChar(&argument, *++c);
            }
            else
            {
                SHUI_SAppendChar(&argument, *c);
            }
        }
        else if (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r')
        {
            if (inArgument)
            {
                SHUI_SLAdd(command, &argument);
                SHUI_SZero(argument);
                inArgument = false;
            }
        }
        else if (*c == '\'' || *c == '"')
        {
            quote = *c;
            inArgument = true;
        }
        else if (*c == '\\' && c[1] != '\0')
        {
            SHUI_SAppendChar(&argument, *++c);
            inArgument = true;
        }
        else
        {
            SHUI_SAppendChar(&argument, *c);
            inArgument = true;
        }
    }

    SHU_Assert(quote == '\0', "Unclosed quote in arguments '%s'.", arguments);

    if (inArgument)
    {
        SHUI_SLAdd(command, &argument);
    }
}

static void SHUI_CAddFlags(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        SHUI_CAddArguments(command, SHUILD.COMPILER.flags.data[i].data);
    }
}

static void SHUI_CAddIncludeDirectories(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        SHUI_String include = {0};
        SHUI_SFormat(&include, "-I%s", SHUILD.MODULE.includeDirectories.data[i].data);
        SHUI_SLAdd(command, &include);
    }
}

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
static void SHUI_CQuoteArgument(SHUI_String *quoted, const SHUI_String *argument)
{
    // _spawnvp joins the arguments with spaces, so they are quoted the way the C runtime splits them back
    if (argument->length != 0 && strpbrk(argument->data, " \t\"") == NULL)
    {
        *quoted = *argument;
        return;
    }

    SHUI_SZero(*quoted);
    SHUI_SAppendChar(quoted, '"');

    usz backslashes = 0;

    for (usz i = 0; i < argument->length; i++)
    {
        if (argument->data[i] == '\\')
        {
            backslashes++;
            continue;
        }

        for (usz j = 0; j < (argument->data[i] == '"' ? backslashes * 2 + 1 : backslashes); j++)
        {
            SHUI_SAppendChar(quoted, '\\');
        }

        SHUI_SAppendChar(quoted, argument->data[i]);
        backslashes = 0;
    }

    for (usz j = 0; j < backslashes * 2; j++)
    {
        SHUI_SAppendChar(quoted, '\\');
    }

    SHUI_SAppendChar(quoted, '"');
}
#endif

static i64 SHUI_CStart(const SHUI_StringList *command)
{
    SHU_Assert(command->count > 0, "Internal: Empty command.");

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    SHUI_StringList arguments = SHUI_SLCreate(command->count);

    for (usz i = 0; i < command->count; i++)
    {
        SHUI_String quoted = {0};
        SHUI_CQuoteArgument(&quoted, &command->data[i]);
        SHUI_SLAdd(&arguments, &quoted);
    }
#else
    const SHUI_StringList arguments = *command;
#endif

#ifndef SHUC_NO_RUN_LOG
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz commandBufferIndex = 0;

    for (usz i = 0; i < arguments.count && commandBufferIndex + 1 < sizeof(commandBuffer); i++)
    {
        i32 written = snprintf(commandBuffer + commandBufferIndex,
                               sizeof(commandBuffer) - commandBufferIndex,
                               i == 0 ? "%s" : " %s",
                               arguments.data[i].data);

        commandBufferIndex = written < 0 ? sizeof(commandBuffer) : commandBufferIndex + (usz)written;
    }

    SHU_LogInfo("Executing command : " SHUM_COLOR_CYAN("'%s'"), commandBuffer);
#endif

    char **argv = (char **)malloc(sizeof(char *) * (arguments.count + 1));
    SHU_Assert(argv != NULL, "Internal: Memory allocation failed for size '%zu'.", sizeof(char *) * (arguments.count + 1));

    for (usz i = 0; i < arguments.count; i++)
    {
        argv[i] = arguments.data[i].data;
    }
    argv[arguments.count] = NULL;

    i64 process = -1;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    process = (i64)_spawnvp(_P_NOWAIT, argv[0], (const char *const *)argv);
#else
    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(argv[0], argv);
        SHU_LogError(0, "Starting " SHUM_COLOR_CYAN("'%s'") " failed : %s.", argv[0], strerror(errno));
        _exit(127);
    }

    process = pid > 0 ? (i64)pid : -1;
#endif

    free(argv);

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    SHUI_SLDestroy(&arguments);
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

static void SHUI_CReport(i32 result, bool terminateOnError)
{
    if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        (void)terminateOnError;
        SHU_LogError(0, "Command failed with exit code %d.", result);
#else
        SHU_LogError(terminateOnError ? result : 0, "Command failed with exit code %d. Define SHUC_NO_RUN_ERROR to avoid fast failing.", result);
#endif
    }
}

static i32 SHUI_CRun(const SHUI_StringList *command, bool terminateOnError)
{
    i32 result = SHUI_CWait(SHUI_CStart(command));
    SHUI_CReport(result, terminateOnError);

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

    SHUILD.JOBS.processes[index] = SHUILD.JOBS.processes[--SHUILD.JOBS.count];

    if (result != 0)
    {
        SHUI_CReport(result, false);

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

    i64 process = SHUI_CStart(command);

    if (process < 0)
    {
        SHUI_CReport(-1, false);
        SHUILD.JOBS.failure = SHUILD.JOBS.failure == 0 ? -1 : SHUILD.JOBS.failure;
        return;
    }

    SHUILD.JOBS.processes[SHUILD.JOBS.count++] = process;
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
        SHU_LogError(failure, "Compiling failed with exit code %d. Define SHUC_NO_RUN_ERROR to avoid fast failing.", failure);
    }
#else
    (void)failure;
#endif
}

static SHUFileType SHUI_UFileExists(const SHUI_String *path)
{
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    DWORD attributes = GetFileAttributesA(path->data);

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
    if (stat(path->data, &stats) == 0)
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

static void SHUI_UMakeDirectory(const SHUI_String *path)
{
    i32 result = 0;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    result = _mkdir(path->data);
#else
    result = mkdir(path->data, 0755);
#endif

    if (result != 0 && errno != EEXIST)
    {
        SHU_LogError(result, "Internal: Directory creation failed for '%s'", path->data);
    }
}

static void SHUI_UMakeDirectoryRecursive(const SHUI_String *path)
{
    for (usz i = 1; i < path->length; i++)
    {
        if (path->data[i] == SHUM_PATH_SEPARATOR)
        {
            SHUI_String tempPath = *path;

            tempPath.length = i;
            tempPath.data[tempPath.length] = '\0';

            SHUI_UMakeDirectory(&tempPath);
        }
    }

    SHUI_UMakeDirectory(path);
}

static void SHUI_UDeleteSingleFile(const SHUI_String *path)
{
    i32 result = remove(path->data);

    if (result != 0)
    {
        SHU_LogError(result, "Internal: File deletion failed for '%s'", path->data);
    }
}

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
static void SHUI_UDeleteDirectory(const SHUI_String *path)
{
    i32 result = 0;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    result = _rmdir(path->data);
#else
    result = rmdir(path->data);
#endif

    if (result != 0)
    {
        SHU_LogError(result, "Internal: Directory deletion failed for '%s'.", path->data);
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

static void SHUI_UDeleteRecursive(const SHUI_String *path)
{
    SHUFileType fileType = SHUI_UFileExists(path);

    SHU_Assert(fileType != SHUFileType_Invalid, "File '%s' does not exist.", path->data);

    if (fileType == SHUFileType_Regular)
    {
        SHUI_UDeleteSingleFile(path);
        return;
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd;
    char pattern[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s\\*", path->data);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        SHUI_String subPath = {0};
        subPath.length = (usz)snprintf(subPath.data, SHUC_MAX_STRING_SIZE, "%s\\%s", path->data, ffd.cFileName);

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            SHUI_UDeleteRecursive(&subPath);
        }
        else
        {
            SHUI_UDeleteSingleFile(&subPath);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
    SHUI_UDeleteDirectory(path);
#else
    nftw(path->data, SHUI_UNftwCallback, 64, FTW_DEPTH | FTW_PHYS);
#endif
}

static SHUSlice SHUI_UReadFile(const SHUI_String *path)
{
    FILE *fileHandle = fopen(path->data, "rb");

    if (fileHandle == NULL)
    {
        SHU_LogError(SHUResult_ErrFile, "File '%s' to read cannot be opened.", path->data);
    }

    fseek(fileHandle, 0, SEEK_END);
    long fileLength = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    SHU_Assert(fileLength >= 0, "File size getting failed for '%s'.", path->data);

    char *buffer = (char *)malloc((size_t)fileLength + 1);
    SHU_Assert(buffer != NULL, "Internal: Memory allocation failed for size '%zu'.", (size_t)fileLength + 1);

    usz fileRead = (usz)fread(buffer, 1, (size_t)fileLength, fileHandle);
    SHU_Assert(fileRead == (usz)fileLength, "File read failed for '%s'.", path->data);
    buffer[fileLength] = '\0';
    fclose(fileHandle);

    return cs(buffer, (usz)fileLength);
}

static void SHUI_UWriteFile(const SHUI_String *path, SHUSliceView content)
{
    SHU_Assert(content.data != NULL || content.size == 0, "Content to write to '%s' is NULL.", path->data);

    // a file that has the content already is left as is, so its edit time stays and what includes it does not compile again
    if (SHUI_UFileExists(path) == SHUFileType_Regular)
    {
        SHUSlice old = SHUI_UReadFile(path);
        bool same = old.size == content.size && (content.size == 0 || memcmp(old.data, content.data, content.size) == 0);
        free(old.data);

        if (same)
        {
            return;
        }
    }

    FILE *fileHandle = fopen(path->data, "wb");

    if (fileHandle == NULL)
    {
        SHU_LogError(SHUResult_ErrFile, "File '%s' to write cannot be opened.", path->data);
    }

    usz fileWritten = content.size == 0 ? 0 : (usz)fwrite(content.data, 1, content.size, fileHandle);
    SHU_Assert(fileWritten == content.size, "File write failed for '%s'.", path->data);
    fclose(fileHandle);
}

static void SHUI_UCopySingleFile(const SHUI_String *src, const SHUI_String *dst)
{
    SHUSlice content = SHUI_UReadFile(src);
    SHUI_UWriteFile(dst, csv(content));
    free(content.data);

#if !SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    // the copy keeps the permissions, so a copied program or script still runs
    struct stat stats;

    if (stat(src->data, &stats) == 0 && chmod(dst->data, stats.st_mode & 07777) != 0)
    {
        SHU_LogError(SHUResult_ErrFile, "Internal: Permission setting failed for '%s'.", dst->data);
    }
#endif
}

static void SHUI_UCopyRecursive(const SHUI_String *src, const SHUI_String *dst)
{
    SHUFileType fileType = SHUI_UFileExists(src);

    SHU_Assert(fileType != SHUFileType_Invalid, "File '%s' does not exist", src->data);

    if (fileType == SHUFileType_Regular)
    {
        SHUI_UCopySingleFile(src, dst);
        return;
    }

    SHUFileType destinationType = SHUI_UFileExists(dst);

    SHU_Assert(destinationType != SHUFileType_Regular, "Directory '%s' already exist as a regular file", src->data);

    if (destinationType == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(dst);
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd;
    char pattern[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s\\*", src->data);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: Directory open failed for '%s'.", src->data);
    }

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
        {
            continue;
        }

        SHUI_String srcPath = {0};
        SHUI_String dstPath = {0};
        SHUI_SFormat(&srcPath, "%s\\%s", src->data, ffd.cFileName);
        SHUI_SFormat(&dstPath, "%s\\%s", dst->data, ffd.cFileName);

        SHUI_UCopyRecursive(&srcPath, &dstPath);
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(src->data);
    if (!dir)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: Directory open failed for '%s'.", src->data);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        SHUI_String srcPath = {0};
        SHUI_String dstPath = {0};
        SHUI_SFormat(&srcPath, "%s/%s", src->data, entry->d_name);
        SHUI_SFormat(&dstPath, "%s/%s", dst->data, entry->d_name);

        SHUI_UCopyRecursive(&srcPath, &dstPath);
    }

    closedir(dir);
#endif
}

static void SHUI_URenameFile(const SHUI_String *file, const SHUI_String *name)
{
    if (SHUI_UFileExists(name) != SHUFileType_Invalid)
    {
        SHUI_UDeleteRecursive(name);
    }

    i32 result = rename(file->data, name->data);

    if (result != 0)
    {
        SHU_LogError(result, "Internal: File rename failed from '%s' to '%s'.", file->data, name->data);
    }
}

static i64 SHUI_UGetFileEditTime(const SHUI_String *file)
{
    // in nanoseconds, so a file edited in the same second as its object was compiled is still seen as newer
    struct stat attr;
    i32 result = stat(file->data, &attr);

    if (result != 0)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: File attribute getting failed for '%s'.", file->data);
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_LINUX)
    return (i64)attr.st_mtim.tv_sec * 1000000000LL + (i64)attr.st_mtim.tv_nsec;
#elif SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_MACOS)
    return (i64)attr.st_mtimespec.tv_sec * 1000000000LL + (i64)attr.st_mtimespec.tv_nsec;
#else
    return (i64)attr.st_mtime * 1000000000LL;
#endif
}

static bool SHUI_CDependencyDirty(const SHUI_String *dependencyFile, const SHUI_String *targetFile)
{
    i64 objectTime = SHUI_UGetFileEditTime(targetFile);

    FILE *depFHandle = fopen(dependencyFile->data, "rb");
    SHU_Assert(depFHandle != NULL, "File open failed for '%s'", dependencyFile->data);

    fseek(depFHandle, 0, SEEK_END);
    usz depFLength = (usz)ftell(depFHandle);
    fseek(depFHandle, 0, SEEK_SET);

    char *depFBuffer = (char *)malloc((size_t)depFLength + 1);
    SHU_Assert(depFBuffer != NULL, "Internal: Memory allocation failed for size '%zu'.", (size_t)depFLength + 1);

    usz depFRead = (usz)fread(depFBuffer, 1, (size_t)depFLength, depFHandle);
    SHU_Assert(depFRead == depFLength, "Buffer overflow for '%s'", dependencyFile->data);
    depFBuffer[depFLength] = '\0';
    fclose(depFHandle);

    usz depFOffset = 0;
    while (depFOffset < depFLength && depFBuffer[depFOffset] != ':')
    {
        depFOffset++;
    }
    depFOffset++;

    // the compiler escapes a space in a file name with a backslash, and ends a line that goes on with one
    SHUI_String dependentFile = {0};
    bool dirty = false;

    while (depFOffset <= depFLength && !dirty)
    {
        char c = depFOffset < depFLength ? depFBuffer[depFOffset] : '\0';

        if (c == '\\' && depFOffset + 1 < depFLength && depFBuffer[depFOffset + 1] == ' ')
        {
            SHUI_SAppendChar(&dependentFile, ' ');
            depFOffset += 2;
            continue;
        }

        if (c == '\\' && depFOffset + 1 < depFLength && (depFBuffer[depFOffset + 1] == '\r' || depFBuffer[depFOffset + 1] == '\n'))
        {
            depFOffset++;
            continue;
        }

        if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\0')
        {
            if (dependentFile.length != 0)
            {
                dirty = objectTime < SHUI_UGetFileEditTime(&dependentFile);
                SHUI_SZero(dependentFile);
            }
        }
        else
        {
            SHUI_SAppendChar(&dependentFile, c);
        }

        depFOffset++;
    }

    free(depFBuffer);
    return dirty;
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

    SHUI_String executablePath = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&executablePath, executableFileName);

    SHUI_String sourcePath = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&sourcePath, sourceFileName);

    i64 exeTime = SHUI_UGetFileEditTime(&executablePath);
    i64 sourceTime = SHUI_UGetFileEditTime(&sourcePath);

    bool rebuild = (exeTime < sourceTime);

    if (!rebuild)
    {
        SHUI_String depFileMap = SHUILD.currentExecutableDirectory;
        SHUI_SAppendC(&depFileMap, executableFileName);
        SHUI_SAppendC(&depFileMap, "." SHUC_FILE_EXTENSION);

        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command.data);
        SHUI_CAddArgument(&command, "-MM");
        SHUI_CAddArgument(&command, sourcePath.data);
        SHUI_CAddArgument(&command, "-MF");
        SHUI_CAddArgument(&command, depFileMap.data);
        // when the dependencies cannot be listed, the rebuild shows why
        if (SHUI_CRun(&command, false) != 0 || SHUI_CDependencyDirty(&depFileMap, &executablePath))
        {
            rebuild = true;
        }
        SHUI_SLDestroy(&command);

        if (SHUI_UFileExists(&depFileMap) == SHUFileType_Regular)
        {
            SHUI_UDeleteSingleFile(&depFileMap);
        }
    }

    if (!rebuild)
    {
        return;
    }

    SHU_LogInfo(SHUM_COLOR_MAGENTA("Build source or dependencies have changed, rebuilding..."));

    SHUI_String oldExePath = executablePath;
    SHUI_SAppendC(&oldExePath, ".old");
    SHUI_URenameFile(&executablePath, &oldExePath);

    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUILD.COMPILER.command.data);
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, executablePath.data);
    SHUI_CAddArgument(&command, sourcePath.data);
    SHUI_CAddArguments(&command, SHUILD_BUILD);
    i32 result = SHUI_CRun(&command, false);
    SHUI_SLDestroy(&command);

    if (result == 0)
    {
        i32 spawnResult = SHU_UtilSpawnProcessSync(executablePath.data, argv);
        exit(spawnResult);
    }
    else
    {
        SHUI_URenameFile(&oldExePath, &executablePath);
        SHU_LogError(result, "Failed to rebuild build script.");
    }
}

#ifdef SHUC_ENABLE_INCREMENTAL
static SHUI_Hash SHUI_CModuleStateHash(void)
{
    SHUI_Hash hash = 14695981039346656037ULL;

#define SHUI_HASH_BYTE(byte) hash = ((hash ^ (SHUI_Hash)(byte)) * 1099511628211ULL)
#define SHUI_HASH_MIX hash ^= (hash >> 17)

    for (usz i = 0; i < SHUILD.cacheDirectory.length; i++)
    {
        SHUI_HASH_BYTE(SHUILD.cacheDirectory.data[i]);
    }
    SHUI_HASH_MIX;

    SHUI_HASH_BYTE(SHUILD.COMPILER.identifier);
    SHUI_HASH_MIX;

    for (usz i = 0; i < SHUILD.COMPILER.command.length; i++)
    {
        SHUI_HASH_BYTE(SHUILD.COMPILER.command.data[i]);
    }
    SHUI_HASH_MIX;

    SHUI_HASH_BYTE(SHUILD.COMPILER.flags.count); // Include count to differentiate empty lists
    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        for (usz j = 0; j < SHUILD.COMPILER.flags.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.COMPILER.flags.data[i].data[j]);
        }
        SHUI_HASH_MIX;
    }

    for (usz i = 0; i < SHUILD.currentExecutableDirectory.length; i++)
    {
        SHUI_HASH_BYTE(SHUILD.currentExecutableDirectory.data[i]);
    }
    SHUI_HASH_MIX;

    for (usz i = 0; i < SHUILD.MODULE.name.length; i++)
    {
        SHUI_HASH_BYTE(SHUILD.MODULE.name.data[i]);
    }
    SHUI_HASH_MIX;

    for (usz i = 0; i < SHUILD.MODULE.root.length; i++)
    {
        SHUI_HASH_BYTE(SHUILD.MODULE.root.data[i]);
    }
    SHUI_HASH_MIX;

    SHUI_HASH_BYTE(SHUILD.MODULE.includeDirectories.count);
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.includeDirectories.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.MODULE.includeDirectories.data[i].data[j]);
        }
        SHUI_HASH_MIX;
    }

    SHUI_HASH_BYTE(SHUILD.MODULE.sourceFiles.count);
    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.sourceFiles.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.MODULE.sourceFiles.data[i].data[j]);
        }
        SHUI_HASH_MIX;
    }

    SHUI_HASH_BYTE(SHUILD.MODULE.linkDirectories.count);
    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.linkDirectories.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.MODULE.linkDirectories.data[i].data[j]);
        }
        SHUI_HASH_MIX;
    }

    SHUI_HASH_BYTE(SHUILD.MODULE.links.count);
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.links.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.MODULE.links.data[i].data[j]);
        }
        SHUI_HASH_MIX;
    }

    return hash;
}

static void SHUI_CModuleStateUpdate(const SHUI_String *moduleName)
{
    SHUI_String moduleCacheFile = {0};
    SHUI_SFormat(&moduleCacheFile, "%s%s%c%s.%s",
                 SHUILD.cacheDirectory.data,
                 moduleName->data,
                 SHUM_PATH_SEPARATOR,
                 moduleName->data,
                 SHUC_MODULE_FILE_EXTENSION);

    SHUI_String moduleCacheDir = {0};
    SHUI_SFormat(&moduleCacheDir, "%s%s%c",
                 SHUILD.cacheDirectory.data,
                 moduleName->data,
                 SHUM_PATH_SEPARATOR);

    SHUI_UMakeDirectoryRecursive(&moduleCacheDir);

    SHUI_Hash currentConfig = SHUI_CModuleStateHash();

    FILE *cacheFileHandle = fopen(moduleCacheFile.data, "w+");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile.data);
    fprintf(cacheFileHandle, "%llu", (unsigned long long)currentConfig);
    fclose(cacheFileHandle);
}

static bool SHUI_CModuleStateDirty(const SHUI_String *moduleName)
{
    SHUI_String moduleCacheFile = {0};
    SHUI_SFormat(&moduleCacheFile, "%s%s%c%s.%s",
                 SHUILD.cacheDirectory.data,
                 moduleName->data,
                 SHUM_PATH_SEPARATOR,
                 moduleName->data,
                 SHUC_MODULE_FILE_EXTENSION);

    if (SHUI_UFileExists(&moduleCacheFile) != SHUFileType_Regular)
    {
        return true;
    }

    SHUI_Hash currentConfig = SHUI_CModuleStateHash();

    char buffer[SHUC_MAX_HASH_BUFFER_SIZE] = {0};

    FILE *cacheFileHandle = fopen(moduleCacheFile.data, "r");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile.data);
    usz bufferRead = (usz)fread(buffer, 1, sizeof(buffer), cacheFileHandle);
    SHU_Assert(bufferRead < sizeof(buffer), "Buffer overflow for '%s'", moduleCacheFile.data);
    fclose(cacheFileHandle);

    SHUI_Hash savedConfig = strtoull(buffer, NULL, 10);

    return currentConfig != savedConfig;
}

static bool SHUI_CUnitRequiresCompilation(const SHUI_String *sourceFile, SHUI_String *retObjectFile, SHUI_String *retDependencyFile)
{
    usz fileStartIndex = SHUILD.MODULE.root.length;

    SHUI_SFormat(retDependencyFile, "%s%s%c%.*s%s",
                 SHUILD.cacheDirectory.data,
                 SHUILD.MODULE.name.data,
                 SHUM_PATH_SEPARATOR,
                 (int)(sourceFile->length - fileStartIndex - 1),
                 sourceFile->data + fileStartIndex,
                 SHUC_FILE_EXTENSION);

    SHUI_SFormat(retObjectFile, "%.*s%s",
                 (int)(retDependencyFile->length - 3), // - SHUC_FILE_EXTENSION length
                 retDependencyFile->data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "obj" : "o");

    if (SHUI_UFileExists(retObjectFile) != SHUFileType_Regular ||
        SHUI_UFileExists(retDependencyFile) != SHUFileType_Regular ||
        SHUI_CDependencyDirty(retDependencyFile, retObjectFile))
    {
        goto dirty;
    }

    return false;

dirty:
    {
    } // suppress warnings

    usz lastSeparatorIndex = retObjectFile->length - 1;
    while (lastSeparatorIndex > 0 && retObjectFile->data[lastSeparatorIndex] != SHUM_PATH_SEPARATOR)
    {
        lastSeparatorIndex--;
    }

    SHUI_String objectDirectory = {0};
    SHUI_SFormat(&objectDirectory, "%.*s", (int)(lastSeparatorIndex + 1), retObjectFile->data);
    SHUI_UMakeDirectoryRecursive(&objectDirectory);
    return true;
}
#endif

static void SHUI_CCompileUnit(const SHUI_String *sourceFile, const SHUI_String *objectFile, const SHUI_String *dependencyFile, const char *extraFlag)
{
    // the compiler writes the dependency file as it compiles, with the module's flags, so the headers that definitions include are in it too
    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUILD.COMPILER.command.data);
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, objectFile->data);
    SHUI_CAddArgument(&command, "-c");

    if (extraFlag != NULL)
    {
        SHUI_CAddArgument(&command, extraFlag);
    }

    // a single header library is compiled as C, with the definition that holds its implementation, instead of as a precompiled header
    if (SHUI_SEndsWithC(sourceFile->data, ".h"))
    {
        SHUI_CAddArgument(&command, "-x");
        SHUI_CAddArgument(&command, "c");
    }

    SHUI_CAddArgument(&command, sourceFile->data);
    SHUI_CAddFlags(&command);
    SHUI_CAddIncludeDirectories(&command);

    if (dependencyFile != NULL)
    {
        SHUI_CAddArgument(&command, "-MMD");
        SHUI_CAddArgument(&command, "-MF");
        SHUI_CAddArgument(&command, dependencyFile->data);
    }

    SHUI_CStartJob(&command);
    SHUI_SLDestroy(&command);
}

static void SHUI_MAddSourceDirectoryRecursive(const SHUI_String *path)
{
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd = {0};
    char pattern[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s*", path->data);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
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
            SHUI_String subDir = {0};
            SHUI_SFormat(&subDir, "%s%s\\", path->data, ffd.cFileName);
            SHUI_MAddSourceDirectoryRecursive(&subDir);
        }
        else if (SHUI_SEndsWithC(ffd.cFileName, ".c"))
        {
            SHUI_String newFile = *path;
            SHUI_SAppendC(&newFile, ffd.cFileName);
            SHUI_SLAdd((SHUI_StringList *)&SHUILD.MODULE.sourceFiles, &newFile);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path->data);

    if (!dir)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: Directory open failed for '%s'.", path->data);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char entryPath[SHUC_MAX_STRING_SIZE] = {0};
        snprintf(entryPath, sizeof(entryPath), "%s%s", path->data, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0 && S_ISDIR(st.st_mode))
        {
            SHUI_String subDir = {0};
            SHUI_SFormat(&subDir, "%s%s/", path->data, entry->d_name);
            SHUI_MAddSourceDirectoryRecursive(&subDir);
        }
        else if (SHUI_SEndsWithC(entry->d_name, ".c"))
        {
            SHUI_String newFile = *path;
            SHUI_SAppendC(&newFile, entry->d_name);
            SHUI_SLAdd((SHUI_StringList *)&SHUILD.MODULE.sourceFiles, &newFile);
        }
    }

    closedir(dir);
#endif
}

static SHUI_Library *SHUI_MFindLibrary(const SHUI_String *name)
{
    for (usz i = 0; i < SHUILD.LIBRARIES.count; i++)
    {
        if (strcmp(SHUILD.LIBRARIES.data[i].name.data, name->data) == 0)
        {
            return &SHUILD.LIBRARIES.data[i];
        }
    }

    return NULL;
}

// a static library cannot be linked with other libraries, so it keeps the ones it links, and the module that links it gets them
static void SHUI_MRecordLibrary(void)
{
    SHUI_Library *library = SHUI_MFindLibrary(&SHUILD.MODULE.name);

    if (library == NULL)
    {
        if (SHUILD.LIBRARIES.count >= SHUILD.LIBRARIES.capacity)
        {
            SHUILD.LIBRARIES.capacity = SHUILD.LIBRARIES.capacity == 0 ? SHUC_ARRAY_INITIAL_COUNT : (usz)((float)SHUILD.LIBRARIES.capacity * SHUC_ARRAY_RESIZE_FACTOR);
            SHUILD.LIBRARIES.data = (SHUI_Library *)realloc(SHUILD.LIBRARIES.data, sizeof(SHUI_Library) * SHUILD.LIBRARIES.capacity);
            SHU_Assert(SHUILD.LIBRARIES.data != NULL, "Internal: Memory reallocation failed for size '%zu'.", sizeof(SHUI_Library) * SHUILD.LIBRARIES.capacity);
        }

        library = &SHUILD.LIBRARIES.data[SHUILD.LIBRARIES.count++];
        library->name = SHUILD.MODULE.name;
    }
    else
    {
        SHUI_SLDestroy(&library->links);
        SHUI_SLDestroy(&library->linkDirectories);
    }

    // the module's lists move to the record
    library->links = SHUILD.MODULE.links;
    library->linkDirectories = SHUILD.MODULE.linkDirectories;
    SHUILD.MODULE.links = (SHUI_StringList){0};
    SHUILD.MODULE.linkDirectories = (SHUI_StringList){0};
}

static void SHUI_MExpandLink(SHUI_StringList *links, const SHUI_String *link, usz depth)
{
    // a library that links itself through others would expand forever
    SHU_Assert(depth < 64, "Library '%s' links itself through other libraries.", link->data);

    SHUI_SLAdd(links, link);

    const SHUI_Library *library = SHUI_MFindLibrary(link);

    if (library == NULL)
    {
        return;
    }

    for (usz i = 0; i < library->linkDirectories.count; i++)
    {
        if (!SHUI_SLContains(&SHUILD.MODULE.linkDirectories, &library->linkDirectories.data[i]))
        {
            SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, &library->linkDirectories.data[i]);
        }
    }

    for (usz i = 0; i < library->links.count; i++)
    {
        SHUI_MExpandLink(links, &library->links.data[i], depth + 1);
    }
}

// each static library the module links brings the libraries it keeps, after it, so the linker finds what it needs in order
static void SHUI_MExpandLinks(void)
{
    SHUI_StringList links = {0};

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_MExpandLink(&links, &SHUILD.MODULE.links.data[i], 0);
    }

    // a library that comes more than once stays in its last place, after every library that needs it
    SHUI_StringList reversed = {0};

    for (usz i = links.count; i > 0; i--)
    {
        if (!SHUI_SLContains(&reversed, &links.data[i - 1]))
        {
            SHUI_SLAdd(&reversed, &links.data[i - 1]);
        }
    }

    SHUILD.MODULE.links.count = 0;

    for (usz i = reversed.count; i > 0; i--)
    {
        SHUI_SLAdd(&SHUILD.MODULE.links, &reversed.data[i - 1]);
    }

    SHUI_SLDestroy(&links);
    SHUI_SLDestroy(&reversed);
}

#ifdef SHUC_ENABLE_INCREMENTAL
// a module is linked again when a library it links is newer than its output
static bool SHUI_MLinksNewer(const SHUI_String *outFile)
{
    i64 outTime = SHUI_UGetFileEditTime(outFile);

    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.links.count; j++)
        {
            // the names that SHUI_MCompileLibraryStatic and SHUI_MCompileLibraryDynamic give the library
            for (u8 k = 0; k < 2; k++)
            {
                SHUI_String libFile = {0};

                SHUI_SFormat(&libFile, "%s%s%s.%s",
                             SHUILD.MODULE.linkDirectories.data[i].data,
                             SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : "lib",
                             SHUILD.MODULE.links.data[j].data,
                             SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? (k == 0 ? "lib" : "dll") : (k == 0 ? "a" : "so"));

                if (SHUI_UFileExists(&libFile) == SHUFileType_Regular &&
                    SHUI_UGetFileEditTime(&libFile) > outTime)
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
static bool SHUI_MHoldsDynamicLink(const SHUI_String *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_String libFile = {0};

        SHUI_SFormat(&libFile, "%s%s%s.%s",
                     directory->data,
                     SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : "lib",
                     SHUILD.MODULE.links.data[i].data,
                     SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "dll" : "so");

        if (SHUI_UFileExists(&libFile) == SHUFileType_Regular)
        {
            return true;
        }
    }

    return false;
}

static void SHUI_MAddLinks(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        SHUI_String linkDirectory = {0};
        SHUI_SFormat(&linkDirectory, "-L%s", SHUILD.MODULE.linkDirectories.data[i].data);
        SHUI_SLAdd(command, &linkDirectory);

        if (SHUI_MHoldsDynamicLink(&SHUILD.MODULE.linkDirectories.data[i]))
        {
            SHUI_SFormat(&linkDirectory, "-Wl%s,%s",
                         SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : ",-rpath",
                         SHUILD.MODULE.linkDirectories.data[i].data);
            SHUI_SLAdd(command, &linkDirectory);
        }
    }

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_String link = {0};
        SHUI_SFormat(&link, "-l%s", SHUILD.MODULE.links.data[i].data);
        SHUI_SLAdd(command, &link);
    }
}

static void SHUI_MCompileExecutable(const SHUI_String *directory)
{
    SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, &SHUILD.currentExecutableDirectory);

    bool skipExePacking = true;

    SHUI_StringList inputFiles = {0};
    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        const SHUI_String *sourceFile = &SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String objectFile = {0};
        SHUI_String dependencyFile = {0};

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, &objectFile, &dependencyFile, NULL);

            skipExePacking = false;
        }

        SHUI_SLAdd(&inputFiles, &objectFile);
#else
        skipExePacking = false;

        SHUI_SLAdd(&inputFiles, sourceFile);
#endif
    }

    SHUI_CWaitJobs();

    SHUI_String outFile = {0};

    SHUI_SFormat(&outFile, "%s%s%s",
                 directory->data,
                 SHUILD.MODULE.name.data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? ".exe" : "");

    SHU_LogInfo("Compiling executable '%s'...", outFile.data);

#ifdef SHUC_ENABLE_INCREMENTAL
    if (SHUI_UFileExists(&outFile) != SHUFileType_Regular || SHUI_MLinksNewer(&outFile))
    {
        skipExePacking = false;
    }
#endif

    if (!skipExePacking)
    {
        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command.data);
        SHUI_CAddArgument(&command, "-o");
        SHUI_CAddArgument(&command, outFile.data);
        SHUI_CAddIncludeDirectories(&command);

        for (usz i = 0; i < inputFiles.count; i++)
        {
            SHUI_SLAdd(&command, &inputFiles.data[i]);
        }

        SHUI_MAddLinks(&command);

        SHUI_CAddFlags(&command);
        SHUI_CRun(&command, true);
        SHUI_SLDestroy(&command);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }

    SHUI_SLDestroy(&inputFiles);
}

static void SHUI_MCompileLibraryStatic(const SHUI_String *directory)
{
    SHUI_StringList objFiles = {0};

    bool skipLibPacking = true;

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        SHUI_String objectFile = {0};
        const SHUI_String *sourceFile = &SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String dependencyFile = {0};

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, &objectFile, &dependencyFile, NULL);

            skipLibPacking = false;
        }
#else
        skipLibPacking = false;

        SHUI_SFormat(&objectFile, "%.*s%s", (int)(sourceFile->length - 1),
                     sourceFile->data,
                     SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "obj" : "o");

        SHUI_CCompileUnit(sourceFile, &objectFile, NULL, NULL);
#endif

        SHUI_SLAdd(&objFiles, &objectFile);
    }

    SHUI_CWaitJobs();

    SHUI_String libraryFile = {0};
    SHUI_SFormat(&libraryFile, "%s%s%s.%s",
                 directory->data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : "lib",
                 SHUILD.MODULE.name.data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "lib" : "a");

    if (SHUI_UFileExists(&libraryFile) != SHUFileType_Regular)
    {
        skipLibPacking = false;
    }

    if (!skipLibPacking)
    {
        // ar adds to an archive that exists, so the archive is made again, without the objects of sources that are gone
        if (SHUI_UFileExists(&libraryFile) == SHUFileType_Regular)
        {
            SHUI_UDeleteSingleFile(&libraryFile);
        }

        SHUI_StringList command = {0};
        SHUI_CAddArgument(&command, SHUILD.COMPILER.identifier == SHUM_COMPILER_CLANG ? "llvm-ar" : "ar");
        SHUI_CAddArgument(&command, "rcs");
        SHUI_SLAdd(&command, &libraryFile);

        for (usz i = 0; i < objFiles.count; i++)
        {
            SHUI_SLAdd(&command, &objFiles.data[i]);
        }

        SHUI_CRun(&command, true);
        SHUI_SLDestroy(&command);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (usz i = 0; i < objFiles.count; i++)
    {
        SHUI_UDeleteSingleFile(&objFiles.data[i]);
    }
#endif

    SHUI_SLDestroy(&objFiles);
}

static void SHUI_MCompileLibraryDynamic(const SHUI_String *directory)
{
    SHUI_StringList objFiles = {0};

    bool skipLibPacking = true;

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        SHUI_String objectFile = {0};
        const SHUI_String *sourceFile = &SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String dependencyFile = {0};

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, &objectFile, &dependencyFile, "-fPIC");

            skipLibPacking = false;
        }
#else
        skipLibPacking = false;

        SHUI_SFormat(&objectFile, "%.*s%s", (int)(sourceFile->length - 1), sourceFile->data,
                     SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "obj" : "o");

        SHUI_CCompileUnit(sourceFile, &objectFile, NULL, "-fPIC");
#endif

        SHUI_SLAdd(&objFiles, &objectFile);
    }

    SHUI_CWaitJobs();

    SHUI_String libraryFile = {0};
    SHUI_SFormat(&libraryFile, "%s%s%s.%s",
                 directory->data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : "lib",
                 SHUILD.MODULE.name.data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "dll" : "so");

    if (SHUI_UFileExists(&libraryFile) != SHUFileType_Regular)
    {
        skipLibPacking = false;
    }
#ifdef SHUC_ENABLE_INCREMENTAL
    else if (SHUI_MLinksNewer(&libraryFile))
    {
        skipLibPacking = false;
    }
#endif

    if (!skipLibPacking)
    {
        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command.data);
        SHUI_CAddArgument(&command, "-shared");
        SHUI_CAddArgument(&command, "-o");
        SHUI_SLAdd(&command, &libraryFile);

        for (usz i = 0; i < objFiles.count; i++)
        {
            SHUI_SLAdd(&command, &objFiles.data[i]);
        }

        SHUI_MAddLinks(&command);
        SHUI_CRun(&command, true);
        SHUI_SLDestroy(&command);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (usz i = 0; i < objFiles.count; i++)
    {
        SHUI_UDeleteSingleFile(&objFiles.data[i]);
    }
#endif

    SHUI_SLDestroy(&objFiles);
}

#pragma endregion Internals

#pragma region Utility

static i32 SHUI_URun(bool stopOnFailure, const char *commandFormat, va_list args)
{
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    vsnprintf(commandBuffer, sizeof(commandBuffer), commandFormat, args);

#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Executing command : " SHUM_COLOR_CYAN("'%s'"), commandBuffer);
#endif

    i32 result = system(commandBuffer);

#if !SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    // system returns the wait status, not the exit code
    result = result == -1 ? -1 : WIFEXITED(result) ? WEXITSTATUS(result) : -1;
#endif

    if (result != 0 && !stopOnFailure)
    {
        SHU_LogWarning("Command failed with exit code %d.", result);
    }
    else if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        SHU_LogError(0, "Command failed with exit code %d.", result);
#else
        SHU_LogError(result, "Command failed with exit code %d. Define SHUC_NO_RUN_ERROR to avoid fast failing.", result);
#endif
    }

    return result;
}

i32 SHU_UtilRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    i32 result = SHUI_URun(true, commandFormat, args);
    va_end(args);

    return result;
}

i32 SHU_UtilTryRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    i32 result = SHUI_URun(false, commandFormat, args);
    va_end(args);

    return result;
}

i32 SHU_UtilSpawnProcessSync(const char *executable, char *const *argv)
{
    i32 result = 0;

#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Spawning process : " SHUM_COLOR_CYAN("'%s'"), executable);
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

    if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        SHU_LogError(0, "Process failed with exit code %d.", result);
#else
        SHU_LogError(result, "Process failed with exit code %d. Define SHUC_NO_RUN_ERROR to avoid fast failing.", result);
#endif
    }
    else
    {
#ifndef SHUC_NO_RUN_LOG
        SHU_LogInfo("Process " SHUM_COLOR_CYAN("'%s'") " executed successfully.", executable);
#endif
    }

    return result;
}

const char *SHU_UtilGetExecutablePath(void)
{
    return SHUILD.currentExecutableDirectory.data;
}

SHUFileType SHU_UtilFileExists(const char *file)
{
    SHU_AssertNullPointer(file);

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

    return SHUI_UFileExists(&fileStr);
}

void SHU_UtilCreateDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    SHUI_String directoryStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&directoryStr, directory);

    if (directoryStr.data[directoryStr.length - 1] != '/')
    {
        SHUI_SAppendC(&directoryStr, SHUM_PATH_SEPARATOR_STR);
    }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    else
    {
        directoryStr.data[directoryStr.length - 1] = '\\';
    }

    SHUI_SNormalizePath(&directoryStr);
#endif

    if (SHUI_UFileExists(&directoryStr) == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(&directoryStr);
    }
}

void SHU_UtilDeleteFile(const char *file)
{
    SHU_AssertNullPointer(file);

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    SHUI_SNormalizePath(&fileStr);
#endif

    SHUI_UDeleteRecursive(&fileStr);
}

void SHU_UtilCopyFile(const char *file, const char *directory)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(directory);

    SHUI_String directoryStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&directoryStr, directory);

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    SHUI_SNormalizePath(&directoryStr);
    SHUI_SNormalizePath(&fileStr);
#endif

    if (SHUI_UFileExists(&directoryStr) == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(&directoryStr);
    }

    // a file goes into the directory under its own name, and a directory's contents go into it
    if (SHUI_UFileExists(&fileStr) == SHUFileType_Regular)
    {
        const char *name = file + strlen(file);

        while (name > file && name[-1] != '/' && name[-1] != SHUM_PATH_SEPARATOR)
        {
            name--;
        }

        if (directoryStr.data[directoryStr.length - 1] != '/' && directoryStr.data[directoryStr.length - 1] != SHUM_PATH_SEPARATOR)
        {
            SHUI_SAppendC(&directoryStr, SHUM_PATH_SEPARATOR_STR);
        }

        SHUI_SAppendC(&directoryStr, name);
    }

    SHUI_UCopyRecursive(&fileStr, &directoryStr);
}

void SHU_UtilRenameFile(const char *file, const char *name)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(name);

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;
    SHUI_String nameStr = SHUILD.currentExecutableDirectory;

    SHUI_SAppendC(&fileStr, file);
    SHUI_SAppendC(&nameStr, name);

    SHUI_URenameFile(&fileStr, &nameStr);
}

i64 SHU_GetFileEditTime(const char *file)
{
    SHU_AssertNullPointer(file);

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;

    SHUI_SAppendC(&fileStr, file);

    return SHUI_UGetFileEditTime(&fileStr) / 1000000000LL;
}

static int SHUI_SCompare(const void *a, const void *b)
{
    return strcmp(((const SHUI_String *)a)->data, ((const SHUI_String *)b)->data);
}

static void SHUI_UListDirectory(const SHUI_String *directory, bool recursive, SHUListFunction function, void *data)
{
    SHUI_String path = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&path, directory->data);

    SHUI_StringList names = {0};

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    WIN32_FIND_DATAA ffd = {0};
    char pattern[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s*", path.data);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHU_LogError(SHUResult_ErrNotFound, "Directory '%s' to list does not exists.", path.data);
    }

    do
    {
        if (ffd.cFileName[0] != '.')
        {
            SHUI_String name = {0};
            SHUI_SAppendC(&name, ffd.cFileName);
            SHUI_SLAdd(&names, &name);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path.data);

    if (!dir)
    {
        SHU_LogError(SHUResult_ErrNotFound, "Directory '%s' to list does not exists.", path.data);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            SHUI_String name = {0};
            SHUI_SAppendC(&name, entry->d_name);
            SHUI_SLAdd(&names, &name);
        }
    }

    closedir(dir);
#endif

    if (names.count > 1)
    {
        qsort(names.data, names.count, sizeof(SHUI_String), SHUI_SCompare);
    }

    for (usz i = 0; i < names.count; i++)
    {
        SHUI_String entryPath = *directory;
        SHUI_SAppendC(&entryPath, names.data[i].data);

        SHUI_String fullPath = path;
        SHUI_SAppendC(&fullPath, names.data[i].data);

        SHUFileType type = SHUI_UFileExists(&fullPath);

        if (type == SHUFileType_Directory)
        {
            SHUI_SAppendC(&entryPath, SHUM_PATH_SEPARATOR_STR);
        }

        function(entryPath.data, type, data);

        if (type == SHUFileType_Directory && recursive)
        {
            SHUI_UListDirectory(&entryPath, recursive, function, data);
        }
    }

    SHUI_SLDestroy(&names);
}

void SHU_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    SHU_AssertNullPointer(directory);
    SHU_AssertNullPointer(function);

    SHUI_String directoryStr = {0};
    SHUI_SAppendC(&directoryStr, directory);

    if (directoryStr.length != 0 && directoryStr.data[directoryStr.length - 1] != '/' && directoryStr.data[directoryStr.length - 1] != SHUM_PATH_SEPARATOR)
    {
        SHUI_SAppendC(&directoryStr, SHUM_PATH_SEPARATOR_STR);
    }

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    SHUI_SNormalizePath(&directoryStr);
#endif

    SHUI_UListDirectory(&directoryStr, recursive, function, data);
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

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

    return SHUI_UReadFile(&fileStr);
}

void SHU_UtilWriteFile(const char *file, SHUSliceView content)
{
    SHU_AssertNullPointer(file);

    SHUI_String fileStr = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

    SHUI_UWriteFile(&fileStr, content);
}

#pragma endregion Utility

#ifdef SHUC_ENABLE_INCREMENTAL
#pragma region Cache

void SHU_CacheConfigure(const char *cacheDirectory)
{
    SHU_AssertNullPointer(cacheDirectory);

    SHUILD.cacheDirectory = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&SHUILD.cacheDirectory, cacheDirectory);

    if (SHUILD.cacheDirectory.data[SHUILD.cacheDirectory.length - 1] != '/')
    {
        SHUI_SAppendC(&SHUILD.cacheDirectory, SHUM_PATH_SEPARATOR_STR);
    }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    else
    {
        SHUILD.cacheDirectory.data[SHUILD.cacheDirectory.length - 1] = '\\';
    }

    SHUI_SNormalizePath(&SHUILD.cacheDirectory);
#endif

    SHUI_UMakeDirectoryRecursive(&SHUILD.cacheDirectory);

    SHU_LogInfo("Configured cache directory at " SHUM_COLOR_CYAN("'%s'"), SHUILD.cacheDirectory.data);
}

void SHU_CacheClearModule(const char *moduleName)
{
    SHU_Assert(SHUILD.cacheDirectory.length > 0, "Cache directory is not configured.");

    SHUI_String moduleCacheDirectory = SHUILD.cacheDirectory;
    SHUI_SAppendC(&moduleCacheDirectory, moduleName);

    if (SHUI_UFileExists(&moduleCacheDirectory) != SHUFileType_Invalid)
    {
        SHUI_UDeleteRecursive(&moduleCacheDirectory);
    }

    SHUI_UMakeDirectoryRecursive(&moduleCacheDirectory);
}

void SHU_CacheClearAll(void)
{
    SHU_Assert(SHUILD.cacheDirectory.length > 0, "Cache directory is not configured.");

    SHUI_UDeleteRecursive(&SHUILD.cacheDirectory);
    SHUI_UMakeDirectoryRecursive(&SHUILD.cacheDirectory);
}

#pragma endregion Cache

#endif // SHUC_ENABLE_INCREMENTAL

#pragma region Compiler

void SHU_CompilerConfigure(u8 compiler, const char *compilerCommand)
{
    SHU_AssertNullPointer(compilerCommand);

    SHUILD.COMPILER.identifier = compiler;
    SHUI_SZero(SHUILD.COMPILER.command);
    SHUI_SAppendC(&SHUILD.COMPILER.command, compilerCommand);

    if (SHUILD.currentExecutableDirectory.length == 0)
    {
        char pathBuffer[SHUC_MAX_STRING_SIZE] = {0};
        usz pathLength = 0;

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        pathLength = GetModuleFileNameA(NULL, (LPSTR)pathBuffer, (DWORD)sizeof(pathBuffer));
#elif SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_MACOS)
        u32 size = (u32)sizeof(pathBuffer);
        _NSGetExecutablePath(pathBuffer, &size);
        pathLength = (usz)strlen(pathBuffer);
#else
        pathLength = (usz)readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer));
#endif

        while (pathLength > 0 && pathBuffer[pathLength - 1] != SHUM_PATH_SEPARATOR)
        {
            pathBuffer[--pathLength] = '\0';
        }
        pathLength++;

        SHUI_SAppendC(&SHUILD.currentExecutableDirectory, pathBuffer);

#ifdef SHUC_ENABLE_INCREMENTAL
        SHU_CacheConfigure(SHUC_DEFAULT_CACHE_DIRECTORY);
#endif
    }
}

void SHU_CompilerTryConfigure(const char *compilerCommand)
{
    if (compilerCommand == NULL || strlen(compilerCommand) == 0)
    {
        SHU_CompilerConfigure(SHUM_HOST_COMPILER, SHUM_COMPILER_GET_COMMAND(SHUM_HOST_COMPILER));
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
        SHU_LogError(SHUResult_Err, "Unknown compiler command '%s'. Use " SHUM_COLOR_BLUE("SHU_CompilerConfigure") " to configure it manually.", compilerCommand);
    }
}

void SHU_CompilerAddFlags(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHUI_String Sflags = {0};
    SHUI_SAppendC(&Sflags, flags);
    SHUI_SLAdd(&SHUILD.COMPILER.flags, &Sflags);
}

void SHU_CompilerSetFlags(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHU_CompilerClearFlags();
    SHU_CompilerAddFlags(flags);
}

void SHU_CompilerClearFlags(void)
{
    if (SHUILD.COMPILER.flags.data != NULL)
    {
        SHUI_SLDestroy(&SHUILD.COMPILER.flags);
    }
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
                               SHUILD.COMPILER.flags.data[i].data);

        if (written < 0 || (usz)written >= buffer.size - bufferIndex)
        {
            SHU_LogWarning("Buffer too small for compiler flags. Output truncated.");
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
        SHUI_String flag = {0};

        SHUI_SAppendC(&flag, "-D");
        SHUI_SAppendC(&flag, macros);
        const char *value = va_arg(args, const char *);

        if (value != NULL)
        {
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
            SHUI_SAppendC(&flag, "=\"\"");
            SHUI_SAppendC(&flag, value);
            SHUI_SAppendC(&flag, "\"\"");
#else
            SHUI_SAppendC(&flag, "='");
            SHUI_SAppendC(&flag, value);
            SHUI_SAppendC(&flag, "'");
#endif
        }
        SHUI_SLAdd(&SHUILD.COMPILER.flags, &flag);

        macros = va_arg(args, const char *);
    }

    va_end(args);
}

u8 SHU_CompilerGetIdentifier(void)
{
    return SHUILD.COMPILER.identifier;
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name, const char *root)
{
    SHU_AssertNullPointer(name);

    SHUI_SZero(SHUILD.MODULE.name);
    SHUI_SAppendC(&SHUILD.MODULE.name, name);

    SHUILD.MODULE.root = SHUILD.currentExecutableDirectory;

    if (root != NULL && strlen(root) != 0)
    {
        SHUI_SAppendC(&SHUILD.MODULE.root, root);

        if (SHUILD.MODULE.root.data[SHUILD.MODULE.root.length - 1] != '/')
        {
            SHUI_SAppendC(&SHUILD.MODULE.root, SHUM_PATH_SEPARATOR_STR);
        }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        else
        {
            SHUILD.MODULE.root.data[SHUILD.MODULE.root.length - 1] = '\\';
        }
#endif
    }
}

void SHU_ModuleAddIncludeDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    SHUI_String correctedDirectory = SHUILD.MODULE.root;
    SHUI_SAppendC(&correctedDirectory, directory);

    if (correctedDirectory.data[correctedDirectory.length - 1] != '/')
    {
        SHUI_SAppendC(&correctedDirectory, SHUM_PATH_SEPARATOR_STR);
    }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    else
    {
        correctedDirectory.data[correctedDirectory.length - 1] = '\\';
    }

    SHUI_SNormalizePath(&correctedDirectory);
#endif

    SHUI_SLAdd(&SHUILD.MODULE.includeDirectories, &correctedDirectory);
}

void SHU_ModuleAddSourceFile(const char *file)
{
    SHU_AssertNullPointer(file);

    SHUI_String correctedDirectory = SHUILD.MODULE.root;
    SHUI_SAppendC(&correctedDirectory, file);

#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    SHUI_SNormalizePath(&correctedDirectory);
#endif

    SHUFileType fileType = SHUI_UFileExists(&correctedDirectory);
    if (fileType == SHUFileType_Directory)
    {
        if (correctedDirectory.data[correctedDirectory.length - 1] != SHUM_PATH_SEPARATOR)
        {
            SHUI_SAppendC(&correctedDirectory, SHUM_PATH_SEPARATOR_STR);
        }

        SHUI_MAddSourceDirectoryRecursive(&correctedDirectory);
    }
    else if (fileType == SHUFileType_Regular)
    {
        SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, &correctedDirectory);
    }
    else
    {
        SHU_LogError(SHUResult_ErrNotFound, "File '%s' to add source does not exists.", correctedDirectory.data);
    }
}

void SHU_ModuleCompile(const char *directory, SHUModuleType module)
{
#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("Starting to compile %s " SHUM_COLOR_MAGENTA("'%s'") "...", SHUModuleType_GetString(module), SHUILD.MODULE.name.data);
#endif

    SHUI_String directoryStr = SHUILD.currentExecutableDirectory;

    if (directory != NULL && strlen(directory) != 0)
    {
        SHUI_SAppendC(&directoryStr, directory);

        if (directoryStr.data[directoryStr.length - 1] != '/')
        {
            SHUI_SAppendC(&directoryStr, SHUM_PATH_SEPARATOR_STR);
        }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
        else
        {
            directoryStr.data[directoryStr.length - 1] = '\\';
        }

        SHUI_SNormalizePath(&directoryStr);
#endif

        if (SHUI_UFileExists(&directoryStr) != SHUFileType_Directory)
        {
            SHUI_UMakeDirectoryRecursive(&directoryStr);
        }
    }

#ifdef SHUC_ENABLE_INCREMENTAL
    if (SHUI_CModuleStateDirty(&SHUILD.MODULE.name))
    {
        SHU_LogInfo("Build cache not initialized or changed, Cleaning up cache for %s " SHUM_COLOR_MAGENTA("'%s'") "...", SHUModuleType_GetString(module), SHUILD.MODULE.name.data);
        SHU_CacheClearModule(SHUILD.MODULE.name.data);
        SHUI_CModuleStateUpdate(&SHUILD.MODULE.name);
    }
#endif

    if (module != SHUModuleType_LibraryStatic)
    {
        SHUI_MExpandLinks();
    }

    switch (module)
    {
    case SHUModuleType_Executable:
        SHUI_MCompileExecutable(&directoryStr);
        break;
    case SHUModuleType_LibraryStatic:
        SHUI_MCompileLibraryStatic(&directoryStr);
        break;
    case SHUModuleType_LibraryDynamic:
        SHUI_MCompileLibraryDynamic(&directoryStr);
        break;
    default:
        SHU_LogError(SHUResult_Err, "Invalid module type passed to SHU_ModuleCompile.");
        break;
    }

    if (module == SHUModuleType_LibraryStatic)
    {
        SHUI_MRecordLibrary();
    }

    SHUI_SLDestroy(&SHUILD.MODULE.linkDirectories);
    SHUI_SLDestroy(&SHUILD.MODULE.links);

    SHUI_SLDestroy(&SHUILD.MODULE.includeDirectories);
    SHUI_SLDestroy((SHUI_StringList *)&SHUILD.MODULE.sourceFiles);

#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("%s " SHUM_COLOR_MAGENTA("'%s'") " successfully compiled.\n", SHUModuleType_GetString(module), SHUILD.MODULE.name.data);
#endif

    SHUI_SZero(SHUILD.MODULE.name);
    SHUI_SZero(SHUILD.MODULE.root);
}

void SHU_ModuleAddLibraryDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    SHUI_String correctedDirectory = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&correctedDirectory, directory);

    if (correctedDirectory.data[correctedDirectory.length - 1] != '/')
    {
        SHUI_SAppendC(&correctedDirectory, SHUM_PATH_SEPARATOR_STR);
    }
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
    else
    {
        correctedDirectory.data[correctedDirectory.length - 1] = '\\';
    }

    SHUI_SNormalizePath(&correctedDirectory);
#endif

    if (SHUI_UFileExists(&correctedDirectory) != SHUFileType_Directory)
    {
        SHU_LogError(SHUResult_ErrNotFound, "File '%s' to add library directory does not exists or not a directory.", correctedDirectory.data);
    }

    SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, &correctedDirectory);
}

void SHU_ModuleLinkLibrary(const char *library)
{
    SHU_AssertNullPointer(library);

    SHUI_String libraryStr = {0};
    SHUI_SAppendC(&libraryStr, library);

    SHUI_SLAdd(&SHUILD.MODULE.links, &libraryStr);
}

#pragma endregion Module

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
