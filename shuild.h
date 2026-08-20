// You can define various macros to configure Shuild before including this file.
// define SHU_IMPLEMENTATION in one file to include the implementation.
// define SHUC_ENABLE_INCREMENTAL to enable incremental builds.
// define SHUC_NO_MODULE_LOG to disable module logs.
// define SHUC_NO_RUN_LOG to disable command run logs.
// define SHUC_NO_RUN_ERROR to disable termination on run error.
// define SHUC_LOG_FORMAT and SHUC_LOG_FORMAT_VALUES to change log formatting.
// define SHUC_MAX_<...> <limit> to customize limits.

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
/// @param command Command to run with system. (eg. clang example.c -o example)
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
i32 SHU_UtilRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

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

/// @brief Copies a file or directory recursively.
/// @param file File to copy, relative to current executable.
/// @param directory Directory to copy file, relative to current executable.
void SHU_UtilCopyFile(const char *file, const char *directory);

/// @brief Renames a file.
/// @param file File to rename.
/// @param name New name of the file.
void SHU_UtilRenameFile(const char *file, const char *name);

/// @brief Gets the edit time of a file.
/// @param file File to get time of edit.
/// @return Timestamp of the file if found.
i64 SHU_GetFileEditTime(const char *file);

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

/// @brief Tries to configure the compiler by the command of it by checking regular commands. Default is the host (compiler that shuild.c compiled) compiler.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc). If NULL, uses the host compiler command default.
void SHU_CompilerTryConfigure(const char *compilerCommand);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add. Can include multiple flags separated by spaces as you want. (eg. -DFOO=31)
void SHU_CompilerAddFlags(const char *flags);

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
void SHU_ModuleAddSourceFile(const char *file);

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name. Relative to current executable directory. (eg. build/)
/// @param module Current module mode. Use with SHUM_MODULE_<...> macros. (eg. SHUModuleType_LibraryStatic)
void SHU_ModuleCompile(const char *directory, SHUModuleType module);

/// @brief Sets the library search directory for current executable. Practical only if the current module is an executable.
/// @param directory Directory to search for libraries. Relative to current executable directory.  (eg. build/arc/)
void SHU_ModuleAddLibraryDirectory(const char *directory);

/// @brief Links an executable to the current executable. Practical only if the current module is an executable.
/// @param library Library to link with executable. Shouldn't include any path, use `SHU_ModuleAddLibraryDirectory` to search inside. (eg. myLibName)
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
        SHUI_String name;
        SHUI_String root;
        SHUI_StringList includeDirectories;
        SHUI_StringList sourceFiles;

        struct
        {
            SHUI_StringList links;
            SHUI_StringList linkDirectories;
        } EXECUTABLE;
    } MODULE;
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

static void SHUI_SFormat(SHUI_String *string, const char *format, ...) __attribute__((format(printf, 2, 3)));
static void SHUI_SFormat(SHUI_String *string, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    string->length = (usz)vsnprintf(string->data, SHUC_MAX_STRING_SIZE, format, args);
    va_end(args);
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

    if (list.data == NULL)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: Memory allocation failed for size '%zu'.", sizeof(SHUI_String) * capacity);
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

static void SHUI_SLResize(SHUI_StringList *list, usz newCapacity)
{
    if (newCapacity == list->capacity)
    {
        return;
    }

    list->data = (SHUI_String *)realloc(list->data, sizeof(SHUI_String) * newCapacity);
    list->capacity = newCapacity;

    if (list->data == NULL)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: Memory reallocation failed for size '%zu'.", sizeof(SHUI_String) * newCapacity);
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
        SHUI_SLResize(list, (usz)((float)list->capacity * SHUC_ARRAY_RESIZE_FACTOR));
    }

    list->data[list->count++] = *string;
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

static void SHUI_UCopySingleFile(const SHUI_String *src, const SHUI_String *dst)
{
    FILE *srcFile = fopen(src->data, "rb");
    SHU_Assert(srcFile != NULL, "File open failed for '%s'", src->data);

    FILE *dstFile = fopen(dst->data, "wb");
    SHU_Assert(dstFile != NULL, "File open failed for '%s'", dst->data);

    char buffer[4096] = {0};
    usz bytesRead;
    while ((bytesRead = (usz)fread(buffer, 1, sizeof(buffer), srcFile)) > 0)
    {
        fwrite(buffer, 1, bytesRead, dstFile);
    }

    fclose(srcFile);
    fclose(dstFile);
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

static time_t SHUI_UGetFileEditTime(const SHUI_String *file)
{
    struct stat attr;
    i32 result = stat(file->data, &attr);

    if (result != 0)
    {
        SHU_LogError(SHUResult_ErrInternal, "Internal: File attribute getting failed for '%s'.", file->data);
    }

    return attr.st_mtime;
}

static bool SHUI_CDependencyDirty(const SHUI_String *dependencyFile, const SHUI_String *targetFile)
{
    time_t objectTime = SHUI_UGetFileEditTime(targetFile);

    FILE *depFHandle = fopen(dependencyFile->data, "rb");
    SHU_Assert(depFHandle != NULL, "File open failed for '%s'", dependencyFile->data);

    fseek(depFHandle, 0, SEEK_END);
    usz depFLength = (usz)ftell(depFHandle);
    fseek(depFHandle, 0, SEEK_SET);

    char *depFBuffer = (char *)malloc((size_t)depFLength + 1);
    SHU_Assert(depFBuffer != NULL, "Internal: Memory allocation failed for size '%zu'.", (size_t)depFLength + 1);

    SHU_Assert(fread(depFBuffer, 1, (size_t)depFLength, depFHandle) == depFLength, "Buffer overflow for '%s'", dependencyFile->data);
    depFBuffer[depFLength] = '\0';
    fclose(depFHandle);

    usz depFOffset = 0;
    while (depFOffset < depFLength && depFBuffer[depFOffset] != ':')
    {
        depFOffset++;
    }
    depFOffset++;

    usz fileStartIndex = 0;

    while (depFOffset < depFLength)
    {
        char c = depFBuffer[depFOffset];

        if (c == '\\' &&
            depFOffset + 1 < depFLength &&
            (depFBuffer[depFOffset + 1] == '\r' ||
             depFBuffer[depFOffset + 1] == '\n'))
        {
            depFOffset++;

            while (depFOffset < depFLength &&
                   (depFBuffer[depFOffset] == '\r' ||
                    depFBuffer[depFOffset] == '\n'))
            {
                depFOffset++;
            }

            continue;
        }

        if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
        {
            if (fileStartIndex != 0)
            {
                SHUI_String dependentFile = {0};
                SHUI_SFormat(&dependentFile, "%.*s", (int)(depFOffset - fileStartIndex), depFBuffer + fileStartIndex);

                time_t dependentTime = SHUI_UGetFileEditTime(&dependentFile);

                if (objectTime < dependentTime)
                {
                    free(depFBuffer);
                    return true;
                }

                fileStartIndex = 0;
            }
        }
        else if (fileStartIndex == 0)
        {
            fileStartIndex = depFOffset;
        }

        depFOffset++;
    }

    if (fileStartIndex != 0)
    {
        SHUI_String dependentFile = {0};
        SHUI_SFormat(&dependentFile, "%.*s", (int)(depFOffset - fileStartIndex), depFBuffer + fileStartIndex);

        time_t dependentTime = SHUI_UGetFileEditTime(&dependentFile);

        if (objectTime < dependentTime)
        {
            free(depFBuffer);
            return true;
        }
    }

    free(depFBuffer);
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

    SHUI_String executablePath = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&executablePath, executableFileName);

    SHUI_String sourcePath = SHUILD.currentExecutableDirectory;
    SHUI_SAppendC(&sourcePath, sourceFileName);

    time_t exeTime = SHUI_UGetFileEditTime(&executablePath);
    time_t sourceTime = SHUI_UGetFileEditTime(&sourcePath);

    bool rebuild = (exeTime < sourceTime);

    if (!rebuild)
    {
        SHUI_String depFileMap = SHUILD.currentExecutableDirectory;
        SHUI_SAppendC(&depFileMap, executableFileName);
        SHUI_SAppendC(&depFileMap, "." SHUC_FILE_EXTENSION);

        SHU_UtilRun("%s -MM %s -MF %s",
                    SHUILD.COMPILER.command.data,
                    sourcePath.data,
                    depFileMap.data);

        if (SHUI_CDependencyDirty(&depFileMap, &executablePath))
        {
            rebuild = true;
        }

        SHUI_UDeleteSingleFile(&depFileMap);
    }

    if (!rebuild)
    {
        return;
    }

    SHU_LogInfo(SHUM_COLOR_MAGENTA("Build source or dependencies have changed, rebuilding..."));

    SHUI_String oldExePath = executablePath;
    SHUI_SAppendC(&oldExePath, ".old");
    SHUI_URenameFile(&executablePath, &oldExePath);

    i32 result = SHU_UtilRun("%s -o %s %s" SHUILD_BUILD,
                             SHUILD.COMPILER.command.data,
                             executablePath.data,
                             sourcePath.data);

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

    SHUI_HASH_BYTE(SHUILD.MODULE.EXECUTABLE.linkDirectories.count);
    for (usz i = 0; i < SHUILD.MODULE.EXECUTABLE.linkDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.EXECUTABLE.linkDirectories.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.MODULE.EXECUTABLE.linkDirectories.data[i].data[j]);
        }
        SHUI_HASH_MIX;
    }

    SHUI_HASH_BYTE(SHUILD.MODULE.EXECUTABLE.links.count);
    for (usz i = 0; i < SHUILD.MODULE.EXECUTABLE.links.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.EXECUTABLE.links.data[i].length; j++)
        {
            SHUI_HASH_BYTE(SHUILD.MODULE.EXECUTABLE.links.data[i].data[j]);
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
    fprintf(cacheFileHandle, "%llu", currentConfig);
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
    SHU_Assert(fread(buffer, 1, sizeof(buffer), cacheFileHandle) < sizeof(buffer), "Buffer overflow for '%s'", moduleCacheFile.data);
    fclose(cacheFileHandle);

    SHUI_Hash savedConfig = strtoull(buffer, NULL, 10);

    return currentConfig != savedConfig;
}

static void SHUI_CDependencyUpdate(const SHUI_String *sourceFile, const SHUI_String *dependencyFile)
{
    char includeBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz includeBufferIndex = 0;
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        includeBufferIndex += (usz)snprintf(includeBuffer + includeBufferIndex,
                                            sizeof(includeBuffer) - includeBufferIndex,
                                            "-I%s ",
                                            SHUILD.MODULE.includeDirectories.data[i].data);
    }

    SHU_UtilRun("%s -MM %s -MF %s %s",
                SHUILD.COMPILER.command.data,
                sourceFile->data,
                dependencyFile->data,
                includeBuffer);
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
        else if (strncmp(ffd.cFileName + strlen(ffd.cFileName) - 2, ".c", 2) == 0)
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
        else if (strncmp(entry->d_name + strlen(entry->d_name) - 2, ".c", 2) == 0)
        {
            SHUI_String newFile = *path;
            SHUI_SAppendC(&newFile, entry->d_name);
            SHUI_SLAdd((SHUI_StringList *)&SHUILD.MODULE.sourceFiles, &newFile);
        }
    }

    closedir(dir);
#endif
}

static void SHUI_MCompileExecutable(const SHUI_String *directory)
{
    SHUI_SLAdd(&SHUILD.MODULE.EXECUTABLE.linkDirectories, &SHUILD.currentExecutableDirectory);

    char includeBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz includeBufferIndex = 0;
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        includeBufferIndex += (usz)snprintf(includeBuffer + includeBufferIndex,
                                            sizeof(includeBuffer) - includeBufferIndex,
                                            "-I%s ",
                                            SHUILD.MODULE.includeDirectories.data[i].data);
    }

    char linkDirectoryBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz linkDirectoryBufferIndex = 0;
    for (usz i = 0; i < SHUILD.MODULE.EXECUTABLE.linkDirectories.count; i++)
    {
        linkDirectoryBufferIndex += (usz)snprintf(linkDirectoryBuffer + linkDirectoryBufferIndex,
                                                  sizeof(linkDirectoryBuffer) - linkDirectoryBufferIndex,
                                                  "-L%s -Wl%s,%s ",
                                                  SHUILD.MODULE.EXECUTABLE.linkDirectories.data[i].data,
                                                  SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : ",-rpath",
                                                  SHUILD.MODULE.EXECUTABLE.linkDirectories.data[i].data);
    }

    char linkBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz linkBufferIndex = 0;
    for (usz i = 0; i < SHUILD.MODULE.EXECUTABLE.links.count; i++)
    {
        linkBufferIndex += (usz)snprintf(linkBuffer + linkBufferIndex,
                                         sizeof(linkBuffer) - linkBufferIndex,
                                         "-l%s ",
                                         SHUILD.MODULE.EXECUTABLE.links.data[i].data);
    }

    char flagBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz flagBufferIndex = 0;
    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        flagBufferIndex += (usz)snprintf(flagBuffer + flagBufferIndex,
                                         sizeof(flagBuffer) - flagBufferIndex,
                                         "%s ",
                                         SHUILD.COMPILER.flags.data[i].data);
    }

    bool skipExePacking = true;

    char sourceBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz sourceBufferIndex = 0;
    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        const SHUI_String *sourceFile = &SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String objectFile = {0};
        SHUI_String dependencyFile = {0};

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHU_UtilRun("%s -o %s -c %s %s %s",
                        SHUILD.COMPILER.command.data,
                        objectFile.data,
                        sourceFile->data,
                        flagBuffer,
                        includeBuffer);

            SHUI_CDependencyUpdate(sourceFile, &dependencyFile);

            skipExePacking = false;
        }

        sourceBufferIndex += (usz)snprintf(sourceBuffer + sourceBufferIndex,
                                           sizeof(sourceBuffer) - sourceBufferIndex,
                                           "%s ",
                                           objectFile.data);
#else
        skipExePacking = false;

        sourceBufferIndex += (usz)snprintf(sourceBuffer + sourceBufferIndex,
                                           sizeof(sourceBuffer) - sourceBufferIndex,
                                           "%s ",
                                           sourceFile->data);
#endif
    }

    SHUI_String outFile = {0};

    SHUI_SFormat(&outFile, "%s%s%s",
                 directory->data,
                 SHUILD.MODULE.name.data,
                 SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? ".exe" : "");

    SHU_LogInfo("Compiling executable '%s'...", outFile.data);

#ifdef SHUC_ENABLE_INCREMENTAL
    if (SHUI_UFileExists(&outFile) != SHUFileType_Regular)
    {
        skipExePacking = false;
        goto out;
    }

    time_t exeTime = SHUI_UGetFileEditTime(&outFile);

    for (usz i = 0; i < SHUILD.MODULE.EXECUTABLE.linkDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.EXECUTABLE.links.count; j++)
        {
            SHUI_String libFile = {0};

            SHUI_SFormat(&libFile, "%slib%s.%s",
                         SHUILD.MODULE.EXECUTABLE.linkDirectories.data[i].data,
                         SHUILD.MODULE.EXECUTABLE.links.data[j].data,
                         SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "lib" : "a");

            if (SHUI_UFileExists(&libFile) == SHUFileType_Regular &&
                SHUI_UGetFileEditTime(&libFile) > exeTime)
            {
                skipExePacking = false;
                goto out;
            }
        }
    }
out:
#endif

    if (!skipExePacking)
    {
        SHU_UtilRun("%s -o %s %s %s %s %s %s",
                    SHUILD.COMPILER.command.data,
                    outFile.data,
                    includeBuffer,
                    sourceBuffer,
                    linkDirectoryBuffer,
                    linkBuffer,
                    flagBuffer);
    }
    else
    {
        SHU_LogInfo("Nothing to compile, skipping...");
    }
}

static void SHUI_MCompileLibraryStatic(const SHUI_String *directory)
{
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz commandBufferIndex = 0;

    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        commandBufferIndex += (usz)snprintf(commandBuffer + commandBufferIndex,
                                            sizeof(commandBuffer) - commandBufferIndex,
                                            "%s ",
                                            SHUILD.COMPILER.flags.data[i].data);
    }

    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        commandBufferIndex += (usz)snprintf(commandBuffer + commandBufferIndex,
                                            sizeof(commandBuffer) - commandBufferIndex,
                                            "-I%s ",
                                            SHUILD.MODULE.includeDirectories.data[i].data);
    }

    SHUI_StringList objFiles = SHUI_SLCreate(SHUILD.MODULE.sourceFiles.count);

    bool skipLibPacking = true;

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        SHUI_String objectFile = {0};
        const SHUI_String *sourceFile = &SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String dependencyFile = {0};

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHU_UtilRun("%s -o %s -c %s %s",
                        SHUILD.COMPILER.command.data,
                        objectFile.data,
                        sourceFile->data,
                        commandBuffer);

            SHUI_CDependencyUpdate(sourceFile, &dependencyFile);

            skipLibPacking = false;
        }
#else
        skipLibPacking = false;

        SHUI_SFormat(&objectFile, "%.*s%s", (int)(sourceFile->length - 1),
                     sourceFile->data,
                     SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "obj" : "o");

        SHU_UtilRun("%s -o %s -c %s %s",
                    SHUILD.COMPILER.command.data,
                    objectFile.data,
                    sourceFile->data,
                    commandBuffer);
#endif

        SHUI_SLAdd(&objFiles, &objectFile);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (usz i = 0; i < objFiles.count; i++)
    {
        commandBufferIndex += (usz)snprintf(commandBuffer + commandBufferIndex,
                                            sizeof(commandBuffer) - commandBufferIndex,
                                            "%s ",
                                            objFiles.data[i].data);
    }

    if (!skipLibPacking)
    {
        SHU_UtilRun("%s rcs %s%s%s.%s %s",
                    SHUILD.COMPILER.identifier == SHUM_COMPILER_CLANG ? "llvm-ar" : "ar",
                    directory->data,
                    SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : "lib",
                    SHUILD.MODULE.name.data,
                    SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "lib" : "a",
                    commandBuffer);
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
    // commands for flags
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    usz commandBufferIndex = 0;

    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        commandBufferIndex += (usz)snprintf(commandBuffer + commandBufferIndex,
                                            sizeof(commandBuffer) - commandBufferIndex,
                                            "%s ",
                                            SHUILD.COMPILER.flags.data[i].data);
    }

    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        commandBufferIndex += (usz)snprintf(commandBuffer + commandBufferIndex,
                                            sizeof(commandBuffer) - commandBufferIndex,
                                            "-I%s ",
                                            SHUILD.MODULE.includeDirectories.data[i].data);
    }

    SHUI_StringList objFiles = SHUI_SLCreate(SHUILD.MODULE.sourceFiles.count);

    bool skipLibPacking = true;

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        SHUI_String objectFile = {0};
        const SHUI_String *sourceFile = &SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        SHUI_String dependencyFile = {0};

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHU_UtilRun("%s -o %s -c -fPIC %s %s",
                        SHUILD.COMPILER.command.data,
                        objectFile.data,
                        sourceFile->data,
                        commandBuffer);

            SHUI_CDependencyUpdate(sourceFile, &dependencyFile);

            skipLibPacking = false;
        }

        SHUI_SLAdd(&objFiles, &objectFile);
#else
        skipLibPacking = false;

        SHUI_SFormat(&objectFile, "%.*s%s", (int)(sourceFile->length - 1), sourceFile->data,
                     SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "obj" : "o");

        SHU_UtilRun("%s -o %s -c -fPIC %s %s",
                    SHUILD.COMPILER.command.data,
                    objectFile.data,
                    sourceFile->data,
                    commandBuffer);

        SHUI_SLAdd(&objFiles, &objectFile);
#endif
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (usz i = 0; i < objFiles.count; i++)
    {
        commandBufferIndex += (usz)snprintf(commandBuffer + commandBufferIndex,
                                            sizeof(commandBuffer) - commandBufferIndex,
                                            "%s ",
                                            objFiles.data[i].data);
    }

    if (!skipLibPacking)
    {
        SHU_UtilRun("%s -shared -o %s%s%s.%s %s",
                    SHUILD.COMPILER.command.data,
                    directory->data,
                    SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "" : "lib",
                    SHUILD.MODULE.name.data,
                    SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS) ? "dll" : "so",
                    commandBuffer);
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

i32 SHU_UtilRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, commandFormat);
    vsnprintf(commandBuffer, sizeof(commandBuffer), commandFormat, args);
    va_end(args);

#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Executing command : " SHUM_COLOR_CYAN("'%s'"), commandBuffer);
#endif

    i32 result = system(commandBuffer);

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

    return SHUI_UGetFileEditTime(&fileStr);
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

    SHU_LogInfo("Configured cache directory at " SHUM_COLOR_CYAN("'%s'") "\n", SHUILD.cacheDirectory.data);
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

    char *chars = (char *)buffer.data;
    usz bufferIndex = 0;

    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        if (bufferIndex > buffer.size - 2)
        {
            SHU_LogWarning("Buffer too small for compiler flags. Output truncated.");
            break;
        }

        bufferIndex += (usz)snprintf(chars + bufferIndex,
                                     buffer.size - bufferIndex,
                                     "%s ",
                                     SHUILD.COMPILER.flags.data[i].data);
    }

    chars[bufferIndex] = '\0';

    return bufferIndex;
}

void SHUI_CompilerAddDefinition(const char *macros, ...)
{
    va_list args;
    va_start(args, macros);

    //! maybe redundant
    const char *currentMacro = macros;
    while (currentMacro != NULL)
    {
        SHUI_String flag = {0};

        SHUI_SAppendC(&flag, "-D");
        SHUI_SAppendC(&flag, currentMacro);
        currentMacro = va_arg(args, const char *);

        if (currentMacro != NULL)
        {
#if SHUM_PLATFORM_IS_HOST(SHUM_PLATFORM_WINDOWS)
            SHUI_SAppendC(&flag, "=\"\"");
            SHUI_SAppendC(&flag, currentMacro);
            SHUI_SAppendC(&flag, "\"\"");
#else
            SHUI_SAppendC(&flag, "='");
            SHUI_SAppendC(&flag, currentMacro);
            SHUI_SAppendC(&flag, "'");
#endif
        }
        SHUI_SLAdd(&SHUILD.COMPILER.flags, &flag);

        currentMacro = va_arg(args, const char *);
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

    if (module == SHUModuleType_Executable)
    {
        SHUI_SLDestroy(&SHUILD.MODULE.EXECUTABLE.linkDirectories);
        SHUI_SLDestroy(&SHUILD.MODULE.EXECUTABLE.links);
    }

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

    SHUI_SLAdd(&SHUILD.MODULE.EXECUTABLE.linkDirectories, &correctedDirectory);
}

void SHU_ModuleLinkLibrary(const char *library)
{
    SHU_AssertNullPointer(library);

    SHUI_String libraryStr = {0};
    SHUI_SAppendC(&libraryStr, library);

    SHUI_SLAdd(&SHUILD.MODULE.EXECUTABLE.links, &libraryStr);
}

#pragma endregion Module

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
