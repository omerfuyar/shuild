/* /================================================================\ */
/* ||                                                              || */
/* ||   $$$$$$\  $$\   $$\ $$\   $$\ $$$$$$\ $$\       $$$$$$$\    || */
/* ||  $$  __$$\ $$ |  $$ |$$ |  $$ |\_$$  _|$$ |      $$  __$$\   || */
/* ||  $$ /  \__|$$ |  $$ |$$ |  $$ |  $$ |  $$ |      $$ |  $$ |  || */
/* ||  \$$$$$$\  $$$$$$$$ |$$ |  $$ |  $$ |  $$ |      $$ |  $$ |  || */
/* ||   \____$$\ $$  __$$ |$$ |  $$ |  $$ |  $$ |      $$ |  $$ |  || */
/* ||  $$\   $$ |$$ |  $$ |$$ |  $$ |  $$ |  $$ |      $$ |  $$ |  || */
/* ||  \$$$$$$  |$$ |  $$ |\$$$$$$  |$$$$$$\ $$$$$$$$\ $$$$$$$  |  || */
/* ||   \______/ \__|  \__| \______/ \______|\________|\_______/   || */
/* ||                                                              || */
/* \================================================================/ */

// You can define various macros to configure Shuild before including this file.
// define SHUILD_IMPLEMENTATION in one file to include the implementation.
// define SHUC_ENABLE_INCREMENTAL <cache directory> to enable incremental builds. Directory is relative to current executable. Use "" to use default cache directory which is ".shu/".
// define SHUC_NO_MODULE_LOG to disable module logs.
// define SHUC_NO_RUN_LOG to disable command run logs.
// define SHUC_NO_RUN_ERROR to disable termination on run error.
// define SHUC_MAX_<...> <limit> to customize limits.

#define SHUC_ENABLE_INCREMENTAL ""

#pragma once

#pragma region Platform Detection

#define SHUM_PLATFORM_UNKNOWN 0
#define SHUM_PLATFORM_WINDOWS 1
#define SHUM_PLATFORM_LINUX 2
#define SHUM_PLATFORM_MACOS 3

#if defined(_WIN32)
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_WINDOWS
/// @brief Name of the host platform.
#define SHUM_HOST_PLATFORM_STRING "WINDOWS"

#elif defined(__linux__)
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_LINUX
/// @brief Name of the host platform.
#define SHUM_HOST_PLATFORM_STRING "LINUX"

#elif defined(__APPLE__) && defined(__MACH__)
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_MACOS
/// @brief Name of the host platform.
#define SHUM_HOST_PLATFORM_STRING "MACOS"

#else
/// @brief Current host platform specifier. Use it with SHUM_HOST_PLATFORM_<...> macros.
#define SHUM_HOST_PLATFORM SHUM_PLATFORM_UNKNOWN
/// @brief Name of the host platform.
#define SHUM_HOST_PLATFORM_STRING "UNKNOWN"
#endif

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
/// @brief Name of the host compiler.
#define SHUM_HOST_COMPILER_STRING "CLANG"
/// @brief Default command of the host compiler.
#define SHUM_HOST_COMPILER_COMMAND "clang"

#elif defined(__GNUC__)
/// @brief Current host compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_HOST_COMPILER SHUM_COMPILER_GCC
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
/// @brief Name of the host compiler.
#define SHUM_HOST_COMPILER_STRING "GCC"
/// @brief Default command of the host compiler.
#define SHUM_HOST_COMPILER_COMMAND "gcc"

#else
/// @brief Current host compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_HOST_COMPILER SHUM_COMPILER_UNKNOWN
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION 0
/// @brief Name of the host compiler.
#define SHUM_HOST_COMPILER_STRING "UNKNOWN"
/// @brief Default command of the host compiler.
#define SHUM_HOST_COMPILER_COMMAND "UNKNOWN"
#endif

#define _CRT_SECURE_NO_WARNINGS

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#pragma endregion Compiler Detection

#pragma region Constants and Configurations

#ifndef SHUC_MAX_COMMAND_BUFFER_SIZE
#define SHUC_MAX_COMMAND_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_MESSAGE_BUFFER_SIZE
#define SHUC_MAX_MESSAGE_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_STRING_SIZE
#define SHUC_MAX_STRING_SIZE 256
#endif

#ifndef SHUC_MAX_COMPILER_LENGTH
#define SHUC_MAX_COMPILER_LENGTH 256
#endif

#ifndef SHUC_ARRAY_INITIAL_COUNT
#define SHUC_ARRAY_INITIAL_COUNT 16
#endif

#ifndef SHUC_ARRAY_RESIZE_FACTOR
#define SHUC_ARRAY_RESIZE_FACTOR 2.0f
#endif

#define SHUM_ERROR 1
#define SHUM_ERROR_NULL 2
#define SHUM_ERROR_INDEX 3
#define SHUM_ERROR_UNKNOWN 4
#define SHUM_ERROR_INTERNAL 5
#define SHUM_ERROR_INVALID 5
#define SHUM_ERROR_ASSERTION 6

#define SHUM_FILE_INVALID 0
#define SHUM_FILE_REGULAR 1
#define SHUM_FILE_DIRECTORY 2

#define SHUM_MODULE_EXECUTABLE 0
#define SHUM_MODULE_LIBRARY_STATIC 1
#define SHUM_MODULE_LIBRARY_DYNAMIC 2

#define SHUM_FLAGS_DEBUG "-g -Og"

#define SHUM_FLAGS_OPTIMIZATION_SIZE "-Os"
#define SHUM_FLAGS_OPTIMIZATION_LOW "-O1"
#define SHUM_FLAGS_OPTIMIZATION_MID "-O2"
#define SHUM_FLAGS_OPTIMIZATION_HIGH "-O3"

#define SHUM_FLAGS_WARNING_LOW "-Wall -Wextra"
#define SHUM_FLAGS_WARNING_MID "-Wall -Wextra -Wshadow -Wpedantic -Wconversion -Wformat=2 -fstack-protector-strong"
#define SHUM_FLAGS_WARNING_HIGH "-Wall -Wextra -Wshadow -Wpedantic -Wconversion -fstack-protector-strong -Wpointer-arith -Wcast-align -Wcast-qual -Wformat=2 -Winit-self -Wmissing-declarations -Wredundant-decls -Wsign-conversion -Wpointer-to-int-cast -Wint-to-pointer-cast"
#define SHUM_FLAGS_WARNING_ERROR " -Werror"

#define SHUM_MODULE_GET_STRING(module) (module == SHUM_MODULE_EXECUTABLE        ? "Executable"      \
                                        : module == SHUM_MODULE_LIBRARY_STATIC  ? "Static Library"  \
                                        : module == SHUM_MODULE_LIBRARY_DYNAMIC ? "Dynamic Library" \
                                                                                : "Unknown")

#define SHUM_COLOR_RESET "\x1b[0m"
#define SHUM_COLOR_RED(string) "\x1b[31m" string SHUM_COLOR_RESET
#define SHUM_COLOR_GREEN(string) "\x1b[32m" string SHUM_COLOR_RESET
#define SHUM_COLOR_YELLOW(string) "\x1b[33m" string SHUM_COLOR_RESET
#define SHUM_COLOR_BLUE(string) "\x1b[34m" string SHUM_COLOR_RESET
#define SHUM_COLOR_MAGENTA(string) "\x1b[35m" string SHUM_COLOR_RESET
#define SHUM_COLOR_CYAN(string) "\x1b[36m" string SHUM_COLOR_RESET
#define SHUM_COLOR_WHITE(string) "\x1b[37m" string SHUM_COLOR_RESET
#define SHUM_COLOR_BOLD(string) "\x1b[1m" string SHUM_COLOR_RESET

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
#define SHUM_PATH_SEPARATOR '\\'
#define SHUM_PATH_SEPARATOR_STR "\\"
#else
#define SHUM_PATH_SEPARATOR '/'
#define SHUM_PATH_SEPARATOR_STR "/"
#endif

#ifdef SHUC_ENABLE_INCREMENTAL
#define SHUM_DEFAULT_CACHE_DIRECTORY ".shu/"
#define SHUM_DEFAULT_CACHE_DATA_EXTENSION "shu"
#endif

#pragma endregion

#pragma region Shuild Declarations

#pragma region General

/// @brief Enables autonomously rebuilding the build script when edited. I think it works only if the build system is one script. Run after configuring the compiler.
/// @param argc Argument count from main function.
/// @param argv Argument array from main function.
#define SHU_Automate(argc, argv) SHU_AutomateI(argc, argv, __FILE__)

void SHU_AutomateI(int argc, char **argv, const char *sourceName);

/// @brief Internal command runner function.
/// @param command Command to run with system. (eg. clang example.c -o example)
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
int SHU_Run(const char *commandFormat, ...);

/// @brief Spawns a new process synchronously.
/// @param executable Path to executable.
/// @param argv Arguments array (NULL terminated).
/// @return Exit code of the process.
int SHU_SpawnProcess(const char *executable, char *const *argv);

/// @brief Platform-specific helper to get executable path.
/// @return Address of the executable path string. Do not free or edit it.
const char *SHU_GetExecutablePath();

#ifdef SHUC_ENABLE_INCREMENTAL
/// @brief Configures the cache directory for incremental builds.
/// @param cacheDirectory Cache directory relative to current executable.
void SHU_CacheConfigure(const char *cacheDirectory);

/// @brief Clears the cache for a module
void SHU_CacheClear(const char *moduleName);

/// @brief Clears the cache directory.
void SHU_CacheClearAll();
#endif

/// @brief Checks if a file exist in the environment.
/// @param file File to check.
/// @return SHUM_FILE_<...> macro accordingly.
char SHU_FileExists(const char *file);

/// @brief Creates a directory relative to current executable if the directory doesn't exists.
/// @param directory Directory to create (eg. resources/)
void SHU_CreateDirectory(const char *directory);

/// @brief Deletes a file or directory recursively.
/// @param file File to delete. Relative to current executable.
void SHU_DeleteFile(const char *file);

/// @brief Copies a file or directory recursively.
/// @param file File to copy, relative to current executable.
/// @param directory Directory to copy file, relative to current executable.
void SHU_CopyFile(const char *file, const char *directory);

/// @brief Renames a file.
/// @param file File to rename.
/// @param name New name of the file.
void SHU_RenameFile(const char *file, const char *name);

/// @brief Internal variadic logging function.
/// @param terminate Exit code if not 0.
/// @param header Header of the log.
/// @param format Formatted message of the log.
/// @param ... Variadic arguments for the formatted message.
void SHU_Log(int terminate, const char *header, const char *format, ...);

#define LogFormat "%s:%d:%s : "

#define SHU_LogInfo(format, ...)                                                                             \
    do                                                                                                       \
    {                                                                                                        \
        SHU_Log(0, SHUM_COLOR_GREEN("INFO"), LogFormat format, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define SHU_LogWarning(format, ...)                                                                              \
    do                                                                                                           \
    {                                                                                                            \
        SHU_Log(0, SHUM_COLOR_YELLOW("WARNING"), LogFormat format, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define SHU_LogError(code, format, ...)                                                                        \
    do                                                                                                         \
    {                                                                                                          \
        SHU_Log(code, SHUM_COLOR_RED("ERROR"), LogFormat format, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define SHU_Assert(condition, format, ...)                                                                                             \
    do                                                                                                                                 \
    {                                                                                                                                  \
        if (!(condition))                                                                                                              \
        {                                                                                                                              \
            SHU_Log(SHUM_ERROR_ASSERTION, SHUM_COLOR_RED("ASSERTION"), LogFormat format, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        }                                                                                                                              \
    } while (0)

#define SHU_AssertNullPtr(ptr) SHU_Assert(ptr != NULL, "Null pointer assertion failed: " #ptr " is NULL.");

#pragma endregion General

#pragma region Compiler

/// @brief Configures the compiler to be used for compiling modules. Must be called before any other function. See SHU_CompilerTryConfigure for easier configuration.
/// @param compiler Compiler specifier. Use with SHUM_COMPILER_<...> macros.
/// @param compilerCommand Command to invoke the compiler. (eg. clang)
void SHU_CompilerConfigure(char compiler, const char *compilerCommand);

/// @brief Tries to configure the compiler by the command of it by checking regular commands. Default is the host (compiler that shuild.c compiled) compiler.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc). If NULL, uses the host compiler command.
void SHU_CompilerTryConfigure(const char *compilerCommand);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add. Can include multiple flags separated by spaces as you want. (eg. -DFOO=31)
void SHU_CompilerAddFlags(const char *flags);

/// @brief Clears and sets the compiler flags, replacing all existing ones.
/// @param flags Flags to set. Can include multiple flags separated by spaces as you want.
void SHU_CompilerSetFlags(const char *flags);

/// @brief Clears the current compiler flags.
void SHU_CompilerClearFlags();

/// @brief Gets the current configured compiler flags.
/// @param buffer Buffer to write flags.
/// @param bufferSize Size of the buffer.
/// @return Length of the flags string.
unsigned long SHU_CompilerGetFlags(char *buffer, unsigned long bufferSize);

#pragma endregion Compiler

#pragma region Module

/// @brief Begins a new module with the given name. A module can be an executable or a library.
/// @param name Name of the module. Which will be used also for output file name. (eg. myLibName, myAppName)
void SHU_ModuleBegin(const char *name);

/// @brief Adds include directories to the module. Max count is defined as `SHUC_ARRAY_INITIAL_COUNT`.
/// @param directory Include directory to add to the current module. (eg. include/)
void SHU_ModuleAddIncludeDirectory(const char *directory);

/// @brief Adds source directories to the module. Works recursively. Max source file count is defined as `SHUC_MAX_SOURCE_FILE_COUNT`.
/// @param directory Source directory to add to the current module. (eg. src/)
void SHU_ModuleAddSourceDirectory(const char *directory);

/// @brief Adds source files to the module. Max count is defined as `SHUC_ARRAY_INITIAL_COUNT`.
/// @param file Single file to add to the current module. (eg. source.c)
void SHU_ModuleAddSourceFile(const char *file);

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name (eg. build/)
/// @param module Current module mode. Use with SHUM_MODULE_<...> macros. (eg. SHUM_MODULE_LIBRARY_STATIC)
void SHU_ModuleCompile(const char *directory, char module);

/// @brief Sets the library search directory for current executable. Practical only if the current module is an executable.
/// @param directory Directory to search for libraries. (eg. build/arc/)
void SHU_ModuleAddLibraryDirectory(const char *directory);

/// @brief Links an executable to the current executable. Practical only if the current module is an executable.
/// @param library Library to link with executable. (eg. myLibName)
void SHU_ModuleLinkLibrary(const char *library);

#pragma endregion Module

#pragma endregion Shuild Declarations

#pragma region Shuild Implementations

#ifdef SHUILD_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
#include <windows.h>
#include <process.h>
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <sys/wait.h>
#endif

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_MACOS
#include <mach-o/dyld.h>
#endif

#pragma region Internals

typedef unsigned int SHUI_Size;

typedef struct SHUI_String
{
    SHUI_Size length;
    char data[SHUC_MAX_STRING_SIZE];
} SHUI_String;

typedef struct SHUI_StringList
{
    SHUI_Size count;
    SHUI_Size capacity;
    SHUI_String *data;
} SHUI_StringList;

static struct
{
    SHUI_String currentExecutableDirectory;

#ifdef SHUC_ENABLE_INCREMENTAL
    SHUI_String cacheDirectory;
#endif

    struct
    {
        char identifier;
        SHUI_String command;
        SHUI_StringList flags;
    } COMPILER;

    struct
    {
        SHUI_String name;
        SHUI_StringList includeDirectories;
        SHUI_StringList sourceFiles;

        struct
        {
            SHUI_StringList links;
            SHUI_StringList linkDirectories;
        } EXECUTABLE;
    } MODULE;
} SHUI = {0};

#define SHUI_SZero(string) memset(&string, 0, sizeof(SHUI_String));

static void SHUI_SAppend(SHUI_String *string, const SHUI_String *stringToAppend)
{
    SHU_Assert(string->length + stringToAppend->length < SHUC_MAX_STRING_SIZE, "Appending string length '%u' to '%u' exceeds maximum path size '%d'.", stringToAppend->length, string->length, SHUC_MAX_STRING_SIZE - 1);

    memcpy(string->data + string->length, stringToAppend->data, stringToAppend->length);
    string->length += stringToAppend->length;
    string->data[string->length] = '\0';
}

static void SHUI_SAppendC(SHUI_String *string, const char *stringToAppend)
{
    SHUI_Size stringLength = (SHUI_Size)strlen(stringToAppend);

    SHU_Assert(string->length + stringLength < SHUC_MAX_STRING_SIZE, "Appending string length '%u' to '%u' exceeds maximum path size '%d'.", stringLength, string->length, SHUC_MAX_STRING_SIZE - 1);

    memcpy(string->data + string->length, stringToAppend, stringLength);
    string->length += stringLength;
    string->data[string->length] = '\0';
}

static void SHUI_SFormat(SHUI_String *string, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    string->length = (SHUI_Size)vsnprintf(string->data, SHUC_MAX_STRING_SIZE, format, args);
    va_end(args);
}

static void SHUI_SReplaceChar(SHUI_String *string, char find, char replace)
{
    for (SHUI_Size i = 0; i < string->length; i++)
    {
        if (string->data[i] == find)
        {
            string->data[i] = replace;
        }
    }
}

static SHUI_StringList SHUI_SLCreate(SHUI_Size capacity)
{
    SHUI_StringList list = {0};
    list.data = (SHUI_String *)malloc(sizeof(SHUI_String) * capacity);
    list.count = 0;
    list.capacity = capacity;

    if (list.data == NULL)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Internal: Memory allocation failed for size '%zu'.", sizeof(SHUI_String) * capacity);
    }

    return list;
}

static void SHUI_SLDestroy(SHUI_StringList *list)
{
    free(list->data);
    list->count = 0;
    list->capacity = 0;
    list->data = NULL;
}

static void SHUI_SLResize(SHUI_StringList *list, SHUI_Size newCapacity)
{
    if (newCapacity == list->capacity)
    {
        return;
    }

    list->data = (SHUI_String *)realloc(list->data, sizeof(SHUI_String) * newCapacity);
    list->capacity = newCapacity;

    if (list->data == NULL)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Internal: Memory reallocation failed for size '%zu'.", sizeof(SHUI_String) * newCapacity);
    }
}

static void SHUI_SLAdd(SHUI_StringList *list, const SHUI_String *string)
{
    if (list->data == NULL)
    {
        *list = SHUI_SLCreate(SHUC_ARRAY_INITIAL_COUNT);
    }
    else if (list->count >= list->capacity)
    {
        SHUI_SLResize(list, (SHUI_Size)((float)list->capacity * SHUC_ARRAY_RESIZE_FACTOR));
    }

    list->data[list->count++] = *string;
}

static void SHUI_MakeDirectory(const SHUI_String *path)
{
    int result = 0;

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    result = _mkdir(path->data);
#else
    result = mkdir(path->data, 0755);
#endif

    if (result != 0 && errno != EEXIST)
    {
        SHU_LogError(result, "Internal: Directory creation failed for '%s'", path->data);
    }
}

static void SHUI_MakeDirectoryRecursive(const SHUI_String *path)
{
    for (SHUI_Size i = 1; i < path->length; i++)
    {
        if (path->data[i] == SHUM_PATH_SEPARATOR)
        {
            SHUI_String tempPath = *path;

            tempPath.length = i;
            tempPath.data[tempPath.length] = '\0';

            SHUI_MakeDirectory(&tempPath);
        }
    }

    SHUI_MakeDirectory(path);
}

static void SHUI_DeleteSingleFile(const SHUI_String *path)
{
    int result = remove(path->data);

    if (result != 0)
    {
        SHU_LogError(result, "Internal: File deletion failed for '%s'", path->data);
    }
}

static void SHUI_DeleteDirectory(const SHUI_String *path)
{
    int result = 0;

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    result = _rmdir(path->data);
#else
    result = rmdir(path->data);
#endif

    if (result != 0)
    {
        SHU_LogError(result, "Internal: Directory deletion failed for '%s'.", path->data);
    }
}

#if SHUM_HOST_PLATFORM != SHUM_PLATFORM_WINDOWS
static int SHUI_NftwCallback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
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

static char SHUI_FileExists(const SHUI_String *path)
{
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    DWORD attributes = GetFileAttributesA(path->data);

    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        return SHUM_FILE_INVALID;
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return SHUM_FILE_DIRECTORY;
    }

    return SHUM_FILE_REGULAR;
#else
    struct stat stats;
    if (stat(path->data, &stats) == 0)
    {
        if (S_ISDIR(stats.st_mode))
        {
            return SHUM_FILE_DIRECTORY;
        }
        return SHUM_FILE_REGULAR;
    }
    return SHUM_FILE_INVALID;
#endif
}

static void SHUI_DeleteRecursive(const SHUI_String *path)
{
    char fileType = SHUI_FileExists(path);

    SHU_Assert(fileType != SHUM_FILE_INVALID, "File '%s' does not exist.", path->data);

    if (fileType == SHUM_FILE_REGULAR)
    {
        SHUI_DeleteSingleFile(path);
        return;
    }

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
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

        char subPath[SHUC_MAX_STRING_SIZE] = {0};
        snprintf(subPath, sizeof(subPath), "%s\\%s", path->data, ffd.cFileName);

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            SHUI_DeleteRecursive(subPath);
        }
        else
        {
            SHUI_DeleteSingleFile(subPath);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
    SHUI_DeleteDirectory(path);
#else
    nftw(path->data, SHUI_NftwCallback, 64, FTW_DEPTH | FTW_PHYS);
#endif
}

static void SHUI_CopySingleFile(const SHUI_String *src, const SHUI_String *dst)
{
    FILE *srcFile = fopen(src->data, "rb");
    SHU_Assert(srcFile != NULL, "File open failed for '%s'", src->data);

    FILE *dstFile = fopen(dst->data, "wb");
    SHU_Assert(dstFile != NULL, "File open failed for '%s'", dst->data);

    char buffer[4096] = {0};
    SHUI_Size bytesRead;
    while ((bytesRead = (SHUI_Size)fread(buffer, 1, sizeof(buffer), srcFile)) > 0)
    {
        fwrite(buffer, 1, bytesRead, dstFile);
    }

    fclose(srcFile);
    fclose(dstFile);
}

static void SHUI_CopyRecursive(const SHUI_String *src, const SHUI_String *dst)
{
    char fileType = SHUI_FileExists(src);

    SHU_Assert(fileType != SHUM_FILE_INVALID, "File '%s' does not exist", src->data);

    if (fileType == SHUM_FILE_REGULAR)
    {
        SHUI_CopySingleFile(src, dst);
        return;
    }

    char destinationType = SHUI_FileExists(dst);

    SHU_Assert(destinationType != SHUM_FILE_REGULAR, "Directory '%s' already exist as a regular file", src->data);

    if (destinationType == SHUM_FILE_INVALID)
    {
        SHUI_MakeDirectoryRecursive(dst);
    }

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    WIN32_FIND_DATAA ffd;
    char pattern[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s\\*", src->data);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Internal: Directory open failed for '%s'.", src->data);
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

        SHUI_CopyRecursive(&srcPath, &dstPath);
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(src->data);
    if (!dir)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Internal: Directory open failed for '%s'.", src->data);
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

        SHUI_CopyRecursive(&srcPath, &dstPath);
    }

    closedir(dir);
#endif
}

static void SHUI_RenameFile(const SHUI_String *file, const SHUI_String *name)
{
    if (SHUI_FileExists(name) != SHUM_FILE_INVALID)
    {
        SHUI_DeleteRecursive(name);
    }

    int result = rename(file->data, name->data);

    if (result != 0)
    {
        SHU_LogError(result, "Internal: File rename failed from '%s' to '%s'.", file->data, name->data);
    }
}

static void SHUI_AddSourceDirectoryRecursive(const SHUI_String *path)
{
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
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
            SHUI_AddSourceDirectoryRecursive(&subDir);
        }
        else if (strstr(ffd.cFileName, ".c") != NULL)
        {
            SHUI_String newFile = *path;
            SHUI_SAppendC(&newFile, ffd.cFileName);
            SHUI_SLAdd((SHUI_StringList *)&SHUI.MODULE.sourceFiles, &newFile);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path->data);

    if (!dir)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Internal: Directory open failed for '%s'.", path->data);
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
            SHUI_AddSourceDirectoryRecursive(&subDir);
        }
        else if (strstr(entry->d_name, ".c") != NULL)
        {
            SHUI_String newFile = *path;
            SHUI_SAppendC(&newFile, entry->d_name);
            SHUI_SLAdd((SHUI_StringList *)&SHUI.MODULE.sourceFiles, &newFile);
        }
    }

    closedir(dir);
#endif
}

#ifdef SHUC_ENABLE_INCREMENTAL
static size_t SHUI_CacheHashState()
{
    size_t hash = 5381;

    hash = ((hash << 5) + hash) + (size_t)SHUI.COMPILER.identifier;

    // Hash Compiler Command
    for (SHUI_Size i = 0; i < SHUI.COMPILER.command.length; i++)
    {
        hash = ((hash << 5) + hash) + (size_t)SHUI.COMPILER.command.data[i];
    }

    for (SHUI_Size i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        for (SHUI_Size j = 0; j < SHUI.COMPILER.flags.data[i].length; j++)
        {
            hash = ((hash << 5) + hash) + (size_t)SHUI.COMPILER.flags.data[i].data[j];
        }
    }

    for (SHUI_Size i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        for (SHUI_Size j = 0; j < SHUI.MODULE.includeDirectories.data[i].length; j++)
        {
            hash = ((hash << 5) + hash) + (size_t)SHUI.MODULE.includeDirectories.data[i].data[j];
        }
    }

    for (SHUI_Size i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        for (SHUI_Size j = 0; j < SHUI.MODULE.sourceFiles.data[i].length; j++)
        {
            hash = ((hash << 5) + hash) + (size_t)SHUI.MODULE.sourceFiles.data[i].data[j];
        }
    }

    for (SHUI_Size i = 0; i < SHUI.MODULE.EXECUTABLE.linkDirectories.count; i++)
    {
        for (SHUI_Size j = 0; j < SHUI.MODULE.EXECUTABLE.linkDirectories.data[i].length; j++)
        {
            hash = ((hash << 5) + hash) + (size_t)SHUI.MODULE.EXECUTABLE.linkDirectories.data[i].data[j];
        }
    }

    for (SHUI_Size i = 0; i < SHUI.MODULE.EXECUTABLE.links.count; i++)
    {
        for (SHUI_Size j = 0; j < SHUI.MODULE.EXECUTABLE.links.data[i].length; j++)
        {
            hash = ((hash << 5) + hash) + (size_t)SHUI.MODULE.EXECUTABLE.links.data[i].data[j];
        }
    }

    return hash;
}

static void SHUI_ModuleCacheUpdate(const SHUI_String *moduleName)
{
    SHUI_String moduleCacheFile = {0};
    SHUI_SFormat(&moduleCacheFile, "%s%s%c%s.%s", SHUI.cacheDirectory.data, moduleName->data, SHUM_PATH_SEPARATOR, moduleName->data, SHUM_DEFAULT_CACHE_DATA_EXTENSION);

    size_t currentConfig = SHUI_CacheHashState();

    FILE *cacheFileHandle = fopen(moduleCacheFile.data, "w+");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile.data);
    fprintf(cacheFileHandle, "%zu", currentConfig);
    fclose(cacheFileHandle);
}

static char SHUI_ModuleCacheRequiresCleanup(const SHUI_String *moduleName)
{
    SHUI_String moduleCacheFile = {0};
    SHUI_SFormat(&moduleCacheFile, "%s%s%c%s.%s", SHUI.cacheDirectory.data, moduleName->data, SHUM_PATH_SEPARATOR, moduleName->data, SHUM_DEFAULT_CACHE_DATA_EXTENSION);

    if (SHUI_FileExists(&moduleCacheFile) != SHUM_FILE_REGULAR)
    {
        return 1;
    }

    size_t currentConfig = SHUI_CacheHashState();

    FILE *cacheFileHandle = fopen(moduleCacheFile.data, "r");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile.data);
    char buffer[32] = {0};
    fread(buffer, 1, sizeof(buffer), cacheFileHandle);
    size_t savedConfig = strtoll(buffer, NULL, 10);
    fclose(cacheFileHandle);

    return currentConfig != savedConfig;
}

static void SHUI_HeaderCacheUpdate(const SHUI_String *moduleName, const SHUI_String *sourceFile)
{
    char includeBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size includeBufferIndex = 0;
    for (SHUI_Size i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        includeBufferIndex += (SHUI_Size)snprintf(includeBuffer + includeBufferIndex,
                                                  sizeof(includeBuffer) - includeBufferIndex,
                                                  "-I%s ",
                                                  SHUI.MODULE.includeDirectories.data[i].data);
    }

    SHUI_Size fileStartIndex = 0;
    while (sourceFile->data[fileStartIndex] == SHUI.currentExecutableDirectory.data[fileStartIndex])
    {
        fileStartIndex++;
    }

    SHUI_String dependencyFile = {0};
    SHUI_SFormat(&dependencyFile, "%s%s%c%.*s%s", SHUI.cacheDirectory.data, moduleName->data, SHUM_PATH_SEPARATOR, sourceFile->length - fileStartIndex - 1, sourceFile->data + fileStartIndex, SHUM_DEFAULT_CACHE_DATA_EXTENSION);

    {
        SHUI_Size lastSeparatorIndex = dependencyFile.length - 1;
        while (lastSeparatorIndex > 0 && dependencyFile.data[lastSeparatorIndex] != SHUM_PATH_SEPARATOR)
        {
            lastSeparatorIndex--;
        }

        SHUI_String objectDirectory = {0};
        SHUI_SFormat(&objectDirectory, "%.*s", lastSeparatorIndex + 1, dependencyFile.data);
        SHUI_MakeDirectoryRecursive(&objectDirectory);
    }

    SHU_Run("%s -MM %s -MF %s %s", SHUI.COMPILER.command.data, sourceFile->data, dependencyFile.data, includeBuffer);

    SHUI_String bufferFile = dependencyFile;
    SHUI_SAppendC(&bufferFile, ".tmp");

    FILE *dependencyFileHandle = fopen(dependencyFile.data, "r");
    FILE *bufferFileHandle = fopen(bufferFile.data, "w+");
    SHU_Assert(dependencyFileHandle != NULL, "File open failed for '%s'", dependencyFile.data);
    SHU_Assert(bufferFileHandle != NULL, "File open failed for '%s'", bufferFile.data);

    SHUI_String lineBuffer = {0};
    while (fgets(lineBuffer.data, SHUC_MAX_STRING_SIZE, dependencyFileHandle) != NULL)
    {
        lineBuffer.length = (SHUI_Size)strlen(lineBuffer.data);

        if (strncmp(lineBuffer.data + lineBuffer.length - 5, ".h \\\n", 5) != 0 && strncmp(lineBuffer.data + lineBuffer.length - 4, ".h \n", 4) != 0)
        {
            fputs(lineBuffer.data, bufferFileHandle);
            continue;
        }

        SHUI_Size headerPathStartIndex = 0;
        while (headerPathStartIndex < lineBuffer.length && lineBuffer.data[headerPathStartIndex] != SHUM_PATH_SEPARATOR)
        {
            headerPathStartIndex++;
        }

        SHUI_String headerFile = {0};
        SHUI_SFormat(&headerFile, "%.*s", lineBuffer.length - headerPathStartIndex - 3, lineBuffer.data + headerPathStartIndex);

        struct stat attr;
        time_t headerTime = stat(headerFile.data, &attr) == 0 ? attr.st_mtime : 0;

        fprintf(bufferFileHandle, "%lld%s", (long long)headerTime, lineBuffer.data);
    }

    fclose(bufferFileHandle);
    fclose(dependencyFileHandle);

    SHUI_DeleteSingleFile(&dependencyFile);
    SHUI_RenameFile(&bufferFile, &dependencyFile);
}

static char SHUI_RequiresCompilation(const SHUI_String *moduleName, const SHUI_String *sourceFile, SHUI_String *retObjectFile, char *headerCacheDirty)
{
    SHUI_Size fileStartIndex = 0;
    while (sourceFile->data[fileStartIndex] == SHUI.currentExecutableDirectory.data[fileStartIndex])
    {
        fileStartIndex++;
    }

    SHUI_SFormat(retObjectFile, "%s%s%c%.*so", SHUI.cacheDirectory.data, moduleName->data, SHUM_PATH_SEPARATOR, sourceFile->length - fileStartIndex - 1, sourceFile->data + fileStartIndex);

    {
        SHUI_Size lastSeparatorIndex = retObjectFile->length - 1;
        while (lastSeparatorIndex > 0 && retObjectFile->data[lastSeparatorIndex] != SHUM_PATH_SEPARATOR)
        {
            lastSeparatorIndex--;
        }

        SHUI_String objectDirectory = {0};
        SHUI_SFormat(&objectDirectory, "%.*s", lastSeparatorIndex + 1, retObjectFile->data);
        SHUI_MakeDirectoryRecursive(&objectDirectory);
    }

    // Object file existence check
    if (SHUI_FileExists(retObjectFile) != SHUM_FILE_REGULAR)
    {
        *headerCacheDirty = 1;
        return 1;
    }

    struct stat attr;
    time_t sourceTime = stat(sourceFile->data, &attr) == 0 ? attr.st_mtime : 0;
    time_t objectTime = stat(retObjectFile->data, &attr) == 0 ? attr.st_mtime : 0;

    // Object file validity check
    if (sourceTime > objectTime)
    {
        return 1;
    }

    SHUI_String dependencyFile = {0};
    SHUI_SFormat(&dependencyFile, "%s%s%c%.*s%s", SHUI.cacheDirectory.data, moduleName->data, SHUM_PATH_SEPARATOR, sourceFile->length - fileStartIndex - 1, sourceFile->data + fileStartIndex, SHUM_DEFAULT_CACHE_DATA_EXTENSION);

    // Dependency file existence check
    if (SHUI_FileExists(&dependencyFile) != SHUM_FILE_REGULAR)
    {
        *headerCacheDirty = 1;
        return 1;
    }

    FILE *dependencyFileHandle = fopen(dependencyFile.data, "r");
    SHU_Assert(dependencyFileHandle != NULL, "File open failed for '%s'", dependencyFile.data);

    SHUI_String lineBuffer = {0};
    while (fgets(lineBuffer.data, SHUC_MAX_STRING_SIZE, dependencyFileHandle) != NULL)
    {
        lineBuffer.length = (SHUI_Size)strlen(lineBuffer.data);

        if (strncmp(lineBuffer.data + lineBuffer.length - 5, ".h \\\n", 5) != 0)
        {
            continue;
        }

        SHUI_Size headerPathStartIndex = 0;
        while (headerPathStartIndex < lineBuffer.length && lineBuffer.data[headerPathStartIndex] != SHUM_PATH_SEPARATOR)
        {
            headerPathStartIndex++;
        }

        char timestampBuffer[32] = {0};
        memcpy(timestampBuffer, lineBuffer.data, headerPathStartIndex - 1);

        time_t headerCacheTime = strtoll(timestampBuffer, NULL, 10);
        SHU_Assert(headerCacheTime != 0, "Invalid header cache time parsed from dependency file '%s'.", dependencyFile.data);

        SHUI_String headerFile = {0};
        SHUI_SFormat(&headerFile, "%.*s", lineBuffer.length - headerPathStartIndex - 3, lineBuffer.data + headerPathStartIndex);

        time_t headerTime = stat(retObjectFile->data, &attr) == 0 ? attr.st_mtime : 0;

        if (headerTime > headerCacheTime)
        {
            fclose(dependencyFileHandle);
            *headerCacheDirty = 1;
            return 1;
        }
    }

    fclose(dependencyFileHandle);

    return 0;
}
#endif

static void SHUI_CompileExecutable(const SHUI_String *directory)
{
    char includeBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size includeBufferIndex = 0;
    for (SHUI_Size i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        includeBufferIndex += (SHUI_Size)snprintf(includeBuffer + includeBufferIndex,
                                                  sizeof(includeBuffer) - includeBufferIndex,
                                                  "-I%s ",
                                                  SHUI.MODULE.includeDirectories.data[i].data);
    }

    char linkDirectoryBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size linkDirectoryBufferIndex = 0;
    for (SHUI_Size i = 0; i < SHUI.MODULE.EXECUTABLE.linkDirectories.count; i++)
    {
        linkDirectoryBufferIndex += (SHUI_Size)snprintf(linkDirectoryBuffer + linkDirectoryBufferIndex,
                                                        sizeof(linkDirectoryBuffer) - linkDirectoryBufferIndex,
                                                        "-L%s -Wl,-rpath,%s ",
                                                        SHUI.MODULE.EXECUTABLE.linkDirectories.data[i].data,
                                                        SHUI.MODULE.EXECUTABLE.linkDirectories.data[i].data);
    }

    char linkBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size linkBufferIndex = 0;
    for (SHUI_Size i = 0; i < SHUI.MODULE.EXECUTABLE.links.count; i++)
    {
        linkBufferIndex += (SHUI_Size)snprintf(linkBuffer + linkBufferIndex,
                                               sizeof(linkBuffer) - linkBufferIndex,
                                               "-l%s ",
                                               SHUI.MODULE.EXECUTABLE.links.data[i].data);
    }

    char flagBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size flagBufferIndex = 0;
    for (SHUI_Size i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        flagBufferIndex += (SHUI_Size)snprintf(flagBuffer + flagBufferIndex,
                                               sizeof(flagBuffer) - flagBufferIndex,
                                               "%s ",
                                               SHUI.COMPILER.flags.data[i].data);
    }

    char skipExePacking = 1;

    char sourceBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size sourceBufferIndex = 0;
    for (SHUI_Size i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        const SHUI_String *sourceFile = &SHUI.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String objectFile = {0};

        char headerCacheDirty = 0;
        if (SHUI_RequiresCompilation(&SHUI.MODULE.name, sourceFile, &objectFile, &headerCacheDirty))
        {
            SHU_Run("%s -c %s %s %s -o%s",
                    SHUI.COMPILER.command.data,
                    sourceFile->data,
                    flagBuffer,
                    includeBuffer,
                    objectFile.data);

            if (headerCacheDirty)
            {
                SHUI_HeaderCacheUpdate(&SHUI.MODULE.name, sourceFile);
            }

            skipExePacking = 0;
        }

        sourceBufferIndex += (SHUI_Size)snprintf(sourceBuffer + sourceBufferIndex,
                                                 sizeof(sourceBuffer) - sourceBufferIndex,
                                                 "%s ",
                                                 objectFile.data);
#else
        skipExePacking = 0;

        sourceBufferIndex += (SHUI_Size)snprintf(sourceBuffer + sourceBufferIndex,
                                                 sizeof(sourceBuffer) - sourceBufferIndex,
                                                 "%s ",
                                                 sourceFile->data);
#endif
    }

    if (!skipExePacking)
    {
        SHU_Run("%s %s %s %s %s %s -o%s%s",
                SHUI.COMPILER.command.data,
                includeBuffer,
                sourceBuffer,
                linkDirectoryBuffer,
                linkBuffer,
                flagBuffer,
                directory->data,
                SHUI.MODULE.name.data);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }
}

static void SHUI_CompileLibraryStatic(const SHUI_String *directory)
{
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size commandBufferIndex = 0;

    for (SHUI_Size i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        commandBufferIndex += (SHUI_Size)snprintf(commandBuffer + commandBufferIndex,
                                                  sizeof(commandBuffer) - commandBufferIndex,
                                                  "%s ",
                                                  SHUI.COMPILER.flags.data[i].data);
    }

    for (SHUI_Size i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        commandBufferIndex += (SHUI_Size)snprintf(commandBuffer + commandBufferIndex,
                                                  sizeof(commandBuffer) - commandBufferIndex,
                                                  "-I%s ",
                                                  SHUI.MODULE.includeDirectories.data[i].data);
    }

    SHUI_StringList objFiles = SHUI_SLCreate(SHUI.MODULE.sourceFiles.count);

    char skipLibPacking = 1;

    for (SHUI_Size i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        SHUI_String objPath = {0};

#ifdef SHUC_ENABLE_INCREMENTAL
        char headerCacheDirty = 0;
        if (SHUI_RequiresCompilation(&SHUI.MODULE.name, &SHUI.MODULE.sourceFiles.data[i], &objPath, &headerCacheDirty))
        {
            SHU_Run("%s -c %s -o%s %s",
                    SHUI.COMPILER.command.data,
                    SHUI.MODULE.sourceFiles.data[i].data,
                    objPath.data,
                    commandBuffer);

            if (headerCacheDirty)
            {
                SHUI_HeaderCacheUpdate(&SHUI.MODULE.name, &SHUI.MODULE.sourceFiles.data[i]);
            }

            skipLibPacking = 0;
        }

        SHUI_SLAdd(&objFiles, &objPath);
#else
        skipLibPacking = 0;

        SHUI_SFormat(&objPath, "%.*so", SHUI.MODULE.sourceFiles.data[i].length - 1, SHUI.MODULE.sourceFiles.data[i].data);

        SHU_Run("%s -c %s -o%s %s",
                SHUI.COMPILER.command.data,
                SHUI.MODULE.sourceFiles.data[i].data,
                objPath.data,
                commandBuffer);

        SHUI_SLAdd(&objFiles, &objPath);
#endif
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (SHUI_Size i = 0; i < objFiles.count; i++)
    {
        commandBufferIndex += (SHUI_Size)snprintf(commandBuffer + commandBufferIndex,
                                                  sizeof(commandBuffer) - commandBufferIndex,
                                                  "%s ",
                                                  objFiles.data[i].data);
    }

    if (!skipLibPacking)
    {
        SHU_Run("%s rcs %slib%s.a %s",
                SHUI.COMPILER.identifier == SHUM_COMPILER_CLANG ? "llvm-ar" : "ar",
                directory->data,
                SHUI.MODULE.name.data,
                commandBuffer);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (SHUI_Size i = 0; i < objFiles.count; i++)
    {
        SHUI_DeleteSingleFile(&objFiles.data[i]);
    }
#endif

    SHUI_SLDestroy(&objFiles);
}

static void SHUI_CompileLibraryDynamic(const SHUI_String *directory)
{
    // commands for flags
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    SHUI_Size commandBufferIndex = 0;

    for (SHUI_Size i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        commandBufferIndex += (SHUI_Size)snprintf(commandBuffer + commandBufferIndex,
                                                  sizeof(commandBuffer) - commandBufferIndex,
                                                  "%s ",
                                                  SHUI.COMPILER.flags.data[i].data);
    }

    for (SHUI_Size i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        commandBufferIndex += (SHUI_Size)snprintf(commandBuffer + commandBufferIndex,
                                                  sizeof(commandBuffer) - commandBufferIndex,
                                                  "-I%s ",
                                                  SHUI.MODULE.includeDirectories.data[i].data);
    }

    SHUI_StringList objFiles = SHUI_SLCreate(SHUI.MODULE.sourceFiles.count);

    char skipLibPacking = 1;

    for (SHUI_Size i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        SHUI_String objPath = {0};

#ifdef SHUC_ENABLE_INCREMENTAL
        char headerCacheDirty = 0;
        if (SHUI_RequiresCompilation(&SHUI.MODULE.name, &SHUI.MODULE.sourceFiles.data[i], &objPath, &headerCacheDirty))
        {
            SHU_Run("%s -c -fPIC %s -o%s %s",
                    SHUI.COMPILER.command.data,
                    SHUI.MODULE.sourceFiles.data[i].data,
                    objPath.data,
                    commandBuffer);

            if (headerCacheDirty)
            {
                SHUI_HeaderCacheUpdate(&SHUI.MODULE.name, &SHUI.MODULE.sourceFiles.data[i]);
            }

            skipLibPacking = 0;
        }

        SHUI_SLAdd(&objFiles, &objPath);
#else
        skipLibPacking = 0;

        SHUI_SFormat(&objPath, "%.*so", SHUI.MODULE.sourceFiles.data[i].length - 1, SHUI.MODULE.sourceFiles.data[i].data);

        SHU_Run("%s -c -fPIC %s -o%s %s",
                SHUI.COMPILER.command.data,
                SHUI.MODULE.sourceFiles.data[i].data,
                objPath.data,
                commandBuffer);

        SHUI_SLAdd(&objFiles, &objPath);
#endif
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (SHUI_Size i = 0; i < objFiles.count; i++)
    {
        commandBufferIndex += (SHUI_Size)snprintf(commandBuffer + commandBufferIndex,
                                                  sizeof(commandBuffer) - commandBufferIndex,
                                                  "%s ",
                                                  objFiles.data[i].data);
    }

    if (!skipLibPacking)
    {
        SHU_Run("%s -shared -o%slib%s.so %s",
                SHUI.COMPILER.command.data,
                directory->data,
                SHUI.MODULE.name.data,
                commandBuffer);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (SHUI_Size i = 0; i < objFiles.count; i++)
    {
        SHUI_DeleteSingleFile(&objFiles.data[i]);
    }
#endif

    SHUI_SLDestroy(&objFiles);
}

#pragma endregion Internals

#pragma region General

void SHU_AutomateI(int argc, char **argv, const char *sourceName)
{
    SHU_AssertNullPtr(sourceName);
    SHU_AssertNullPtr(argv);
    SHU_Assert(argc > 0, "Invalid argument count");

    SHUI_Size exeNameIndex = (SHUI_Size)strlen(argv[0]) - 1;

    while (exeNameIndex > 0 && argv[0][exeNameIndex - 1] != SHUM_PATH_SEPARATOR && argv[0][exeNameIndex - 1] != '/' && argv[0][exeNameIndex - 1] != '\\')
    {
        exeNameIndex--;
    }

    SHUI_Size srcNameIndex = (SHUI_Size)strlen(sourceName) - 1;

    while (srcNameIndex > 0 && sourceName[srcNameIndex - 1] != SHUM_PATH_SEPARATOR && sourceName[srcNameIndex - 1] != '/' && sourceName[srcNameIndex - 1] != '\\')
    {
        srcNameIndex--;
    }

    const char *exeName = argv[0] + exeNameIndex;
    const char *srcName = sourceName + srcNameIndex;

    struct stat attr;
    time_t exeTime = stat(exeName, &attr) == 0 ? attr.st_mtime : 0;
    time_t sourceTime = stat(srcName, &attr) == 0 ? attr.st_mtime : 0;

    if (exeTime >= sourceTime)
    {
        return;
    }

    SHU_LogInfo(SHUM_COLOR_MAGENTA("Build source has changed, rebuilding..."));

    char oldExeName[SHUC_MAX_STRING_SIZE] = {0};
    snprintf(oldExeName, sizeof(oldExeName), "%s.old", exeName);
    SHU_RenameFile(exeName, oldExeName);

    SHU_Run("%s %s " SHUM_FLAGS_DEBUG " -o%s",
            SHUI.COMPILER.command.data,
            srcName,
            exeName);

    SHU_SpawnProcess(exeName, argv);
}

int SHU_Run(const char *commandFormat, ...)
{
    SHU_AssertNullPtr(commandFormat);

    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, commandFormat);
    vsnprintf(commandBuffer, sizeof(commandBuffer), commandFormat, args);
    va_end(args);

#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Executing command : " SHUM_COLOR_CYAN("'%s'"), commandBuffer);
#endif

    int result = system(commandBuffer);

    if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        SHU_LogError(0, "Command failed with exit code %d.", result);
#else
        SHU_LogError(result, "Command failed with exit code %d. Define SHUC_NO_RUN_ERROR to avoid fast failing.", result);
#endif
    }

    return result;
}

int SHU_SpawnProcess(const char *executable, char *const *argv)
{
    int result = 0;

#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Spawning process : " SHUM_COLOR_CYAN("'%s'"), executable);
#endif

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    result = (int)_spawnv(_P_WAIT, executable, (const char *const *)argv);
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
        waitpid(pid, &status, 0);
        result = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
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
        exit(result);
    }

    return result;
}

const char *SHU_GetExecutablePath()
{
    return SHUI.currentExecutableDirectory.data;
}

#ifdef SHUC_ENABLE_INCREMENTAL
void SHU_CacheConfigure(const char *cacheDirectory)
{
    SHU_AssertNullPtr(cacheDirectory);

    SHUI.cacheDirectory = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&SHUI.cacheDirectory, cacheDirectory);

    SHUI_MakeDirectoryRecursive(&SHUI.cacheDirectory);

    SHU_LogInfo("Configured cache directory at " SHUM_COLOR_CYAN("'%s'"), SHUI.cacheDirectory.data);
}

void SHU_CacheClearModule(const char *moduleName)
{
    SHU_Assert(SHUI.cacheDirectory.length > 0, "Cache directory is not configured.");

    SHUI_String moduleCacheDirectory = SHUI.cacheDirectory;
    SHUI_SAppendC(&moduleCacheDirectory, moduleName);

    if (SHUI_FileExists(&moduleCacheDirectory) != SHUM_FILE_INVALID)
    {
        SHUI_DeleteRecursive(&moduleCacheDirectory);
    }

    SHUI_MakeDirectoryRecursive(&moduleCacheDirectory);
}

void SHU_CacheClearAll()
{
    SHU_Assert(SHUI.cacheDirectory.length > 0, "Cache directory is not configured.");

    SHUI_DeleteRecursive(&SHUI.cacheDirectory);
    SHUI_MakeDirectoryRecursive(&SHUI.cacheDirectory);
}
#endif

char SHU_FileExists(const char *file)
{
    SHU_AssertNullPtr(file);

    SHUI_String fileStr = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

    return SHUI_FileExists(&fileStr);
}

void SHU_CreateDirectory(const char *directory)
{
    SHU_AssertNullPtr(directory);

    SHUI_String directoryStr = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&directoryStr, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&directoryStr, '/', '\\');
#endif

    if (SHUI_FileExists(&directoryStr) == SHUM_FILE_INVALID)
    {
        SHUI_MakeDirectoryRecursive(&directoryStr);
    }
}

void SHU_DeleteFile(const char *file)
{
    SHU_AssertNullPtr(file);

    SHUI_String fileStr = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&fileStr, '/', '\\');
#endif

    SHUI_DeleteRecursive(&fileStr);
}

void SHU_CopyFile(const char *file, const char *directory)
{
    SHU_AssertNullPtr(file);
    SHU_AssertNullPtr(directory);

    SHUI_String directoryStr = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&directoryStr, directory);

    SHUI_String fileStr = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&fileStr, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&directoryStr, '/', '\\');
    SHUI_SReplaceChar(&fileStr, '/', '\\');
#endif

    if (SHUI_FileExists(&directoryStr) == SHUM_FILE_INVALID)
    {
        SHUI_MakeDirectoryRecursive(&directoryStr);
    }

    SHUI_CopyRecursive(&fileStr, &directoryStr);
}

void SHU_RenameFile(const char *file, const char *name)
{
    SHU_AssertNullPtr(file);
    SHU_AssertNullPtr(name);

    SHUI_String fileStr = SHUI.currentExecutableDirectory;
    SHUI_String nameStr = SHUI.currentExecutableDirectory;

    SHUI_SAppendC(&fileStr, file);
    SHUI_SAppendC(&nameStr, name);

    SHUI_RenameFile(&fileStr, &nameStr);
}

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    SHU_AssertNullPtr(header);
    SHU_AssertNullPtr(format);

    char messageBuffer[SHUC_MAX_MESSAGE_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, format);
    vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
    va_end(args);

    printf(SHUM_COLOR_BOLD("[") "%s" SHUM_COLOR_BOLD("]") " : %s\n", header, messageBuffer);

    if (terminate != 0)
    {
        exit(terminate);
    }
}

#pragma endregion General

#pragma region Compiler

void SHU_CompilerConfigure(char compiler, const char *compilerCommand)
{
    SHU_AssertNullPtr(compilerCommand);

    SHUI.COMPILER.identifier = compiler;
    SHUI_SZero(SHUI.COMPILER.command);
    SHUI_SAppendC(&SHUI.COMPILER.command, compilerCommand);

    if (SHUI.currentExecutableDirectory.length == 0)
    {
        char pathBuffer[SHUC_MAX_STRING_SIZE] = {0};
        SHUI_Size pathLength = 0;

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
        pathLength = GetModuleFileNameA(NULL, (LPSTR)pathBuffer, (DWORD)sizeof(pathBuffer));
#elif SHUM_HOST_PLATFORM == SHUM_PLATFORM_MACOS
        uint32_t size = (uint32_t)sizeof(pathBuffer);
        _NSGetExecutablePath(pathBuffer, &size);
        pathLength = (SHUI_Size)strlen(pathBuffer);
#else
        pathLength = (SHUI_Size)readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer));
#endif

        while (pathLength > 0 && pathBuffer[pathLength - 1] != SHUM_PATH_SEPARATOR && pathBuffer[pathLength - 1] != '/' && pathBuffer[pathLength - 1] != '\\')
        {
            pathBuffer[--pathLength] = '\0';
        }
        pathLength++;

        SHUI_SAppendC(&SHUI.currentExecutableDirectory, pathBuffer);

#ifdef SHUC_ENABLE_INCREMENTAL
        SHU_CacheConfigure(SHUM_DEFAULT_CACHE_DIRECTORY);
#endif
    }
}

void SHU_CompilerTryConfigure(const char *compilerCommand)
{
    if (compilerCommand == NULL)
    {
        SHU_CompilerConfigure(SHUM_HOST_COMPILER, SHUM_HOST_COMPILER_COMMAND);
    }
    else if (strcmp(compilerCommand, "clang") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_CLANG, compilerCommand);
    }
    else if (strcmp(compilerCommand, "gcc") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_GCC, compilerCommand);
    }
    else if (strcmp(compilerCommand, "cc") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_GCC, compilerCommand);
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Unknown compiler command '%s'. Use " SHUM_COLOR_BLUE("SHU_CompilerConfigure") " to configure it manually.", compilerCommand);
    }
}

void SHU_CompilerAddFlags(const char *flags)
{
    SHU_AssertNullPtr(flags);

    SHUI_String Sflags = {0};
    SHUI_SAppendC(&Sflags, flags);
    SHUI_SLAdd(&SHUI.COMPILER.flags, &Sflags);
}

void SHU_CompilerSetFlags(const char *flags)
{
    SHU_AssertNullPtr(flags);

    SHU_CompilerClearFlags();
    SHU_CompilerAddFlags(flags);
}

void SHU_CompilerClearFlags()
{
    if (SHUI.COMPILER.flags.data != NULL)
    {
        SHUI_SLDestroy(&SHUI.COMPILER.flags);
    }
}

unsigned long SHU_CompilerGetFlags(char *buffer, unsigned long bufferSize)
{
    unsigned long bufferIndex = 0;

    for (SHUI_Size i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        if (bufferIndex > bufferSize - 2)
        {
            SHU_LogWarning("Buffer too small for compiler flags. Output truncated.");
            break;
        }

        bufferIndex += (unsigned long)snprintf(buffer + bufferIndex,
                                               bufferSize - bufferIndex,
                                               "%s ",
                                               SHUI.COMPILER.flags.data[i].data);
    }

    buffer[bufferIndex] = '\0';

    return bufferIndex;
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name)
{
    SHU_AssertNullPtr(name);

    SHUI_SZero(SHUI.MODULE.name);
    SHUI_SAppendC(&SHUI.MODULE.name, name);
}

void SHU_ModuleAddIncludeDirectory(const char *directory)
{
    SHU_AssertNullPtr(directory);

    SHUI_String correctedDirectory = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&correctedDirectory, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_SLAdd(&SHUI.MODULE.includeDirectories, &correctedDirectory);
}

void SHU_ModuleAddSourceFile(const char *file)
{
    SHU_AssertNullPtr(file);

    SHUI_String correctedDirectory = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&correctedDirectory, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_SLAdd(&SHUI.MODULE.sourceFiles, &correctedDirectory);
}

void SHU_ModuleAddSourceDirectory(const char *directory)
{
    SHU_AssertNullPtr(directory);

    SHUI_String correctedDirectory = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&correctedDirectory, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_AddSourceDirectoryRecursive(&correctedDirectory);
}

void SHU_ModuleCompile(const char *directory, char module)
{
#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("Starting to compile %s " SHUM_COLOR_MAGENTA("'%s'") "...", SHUM_MODULE_GET_STRING(module), SHUI.MODULE.name.data);
#endif

    SHUI_String directoryStr = SHUI.currentExecutableDirectory;

    if (directory != NULL && (SHUI_Size)strlen(directory) != 0)
    {
        SHUI_SAppendC(&directoryStr, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
        SHUI_SReplaceChar(&directoryStr, '/', '\\');
#endif

        if (SHUI_FileExists(&directoryStr) == SHUM_FILE_INVALID)
        {
            SHUI_MakeDirectoryRecursive(&directoryStr);
        }
    }

#ifdef SHUC_ENABLE_INCREMENTAL
    if (SHUI_ModuleCacheRequiresCleanup(&SHUI.MODULE.name))
    {
        SHU_LogInfo("Build cache not initialized or changed, Cleaning up cache for %s " SHUM_COLOR_MAGENTA("'%s'") "...", SHUM_MODULE_GET_STRING(module), SHUI.MODULE.name.data);
        SHU_CacheClearModule(SHUI.MODULE.name.data);
        SHUI_ModuleCacheUpdate(&SHUI.MODULE.name);
    }
#endif

    switch (module)
    {
    case SHUM_MODULE_EXECUTABLE:
        SHUI_CompileExecutable(&directoryStr);
        break;
    case SHUM_MODULE_LIBRARY_STATIC:
        SHUI_CompileLibraryStatic(&directoryStr);
        break;
    case SHUM_MODULE_LIBRARY_DYNAMIC:
        SHUI_CompileLibraryDynamic(&directoryStr);
        break;
    default:
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid module type passed to SHU_ModuleCompile.");
        break;
    }

    if (module == SHUM_MODULE_EXECUTABLE)
    {
        SHUI_SLDestroy(&SHUI.MODULE.EXECUTABLE.linkDirectories);
        SHUI_SLDestroy(&SHUI.MODULE.EXECUTABLE.links);
    }

    SHUI_SLDestroy(&SHUI.MODULE.includeDirectories);
    SHUI_SLDestroy((SHUI_StringList *)&SHUI.MODULE.sourceFiles);

#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("%s " SHUM_COLOR_MAGENTA("'%s'") " successfully compiled.\n", SHUM_MODULE_GET_STRING(module), SHUI.MODULE.name.data);
#endif
}

void SHU_ModuleAddLibraryDirectory(const char *directory)
{
    SHU_AssertNullPtr(directory);

    SHUI_String correctedDirectory = SHUI.currentExecutableDirectory;
    SHUI_SAppendC(&correctedDirectory, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_SLAdd(&SHUI.MODULE.EXECUTABLE.linkDirectories, &correctedDirectory);
}

void SHU_ModuleLinkLibrary(const char *library)
{
    SHU_AssertNullPtr(library);

    SHUI_String libraryStr = {0};
    SHUI_SAppendC(&libraryStr, library);

    SHUI_SLAdd(&SHUI.MODULE.EXECUTABLE.links, &libraryStr);
}

#pragma endregion Module

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations
