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
// define SHUC_NO_MODULE_LOG to disable module logs.
// define SHUC_NO_RUN_LOG to disable command run logs.
// define SHUC_NO_RUN_ERROR to disable termination on run error.
// define SHUC_MAX_<...> to customize various limits.
// and define other SHUC_<...> macros to customize various configurations.

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
#define SHUM_COMPILER_MSVC 3

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

#elif defined(_MSC_VER)
/// @brief Current host compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_HOST_COMPILER SHUM_COMPILER_MSVC
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION _MSC_VER
/// @brief Name of the host compiler.
#define SHUM_HOST_COMPILER_STRING "MSVC"
/// @brief Default command of the host compiler.
#define SHUM_HOST_COMPILER_COMMAND "cl"

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

#pragma region Shuild Declarations

#ifndef SHUC_MAX_COMMAND_BUFFER_SIZE
#define SHUC_MAX_COMMAND_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_MESSAGE_BUFFER_SIZE
#define SHUC_MAX_MESSAGE_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_PATH_SIZE
#define SHUC_MAX_PATH_SIZE 256
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

#define SHUM_FILE_INVALID 0
#define SHUM_FILE_REGULAR 1
#define SHUM_FILE_DIRECTORY 2

#define SHUM_MODULE_EXECUTABLE 0
#define SHUM_MODULE_LIBRARY_STATIC 1
#define SHUM_MODULE_LIBRARY_DYNAMIC 2

#define SHUM_COMPILER_OPTIMIZATION_SIZE 0
#define SHUM_COMPILER_OPTIMIZATION_LOW 1
#define SHUM_COMPILER_OPTIMIZATION_MID 2
#define SHUM_COMPILER_OPTIMIZATION_HIGH 3

#define SHUM_COMPILER_WARNING_LOW 0
#define SHUM_COMPILER_WARNING_MID 1
#define SHUM_COMPILER_WARNING_HIGH 2

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

/// @brief Checks if a file exist in the environment.
/// @param file File to check.
/// @return SHUM_FILE_<...> macro accordingly.
char SHU_FileExists(const char *file);

/// @brief Creates a directory relative to current executable if the directory doesn't exists.
/// @param directory Directory to create (eg. resources/)
void SHU_CreateRelativeDirectory(const char *directory);

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

#define SHU_LogInfo(format, ...)                                     \
    do                                                               \
    {                                                                \
        SHU_Log(0, SHUM_COLOR_GREEN("INFO"), format, ##__VA_ARGS__); \
    } while (0)

#define SHU_LogWarning(format, ...)                                      \
    do                                                                   \
    {                                                                    \
        SHU_Log(0, SHUM_COLOR_YELLOW("WARNING"), format, ##__VA_ARGS__); \
    } while (0)

#define SHU_LogError(code, format, ...)                                \
    do                                                                 \
    {                                                                  \
        SHU_Log(code, SHUM_COLOR_RED("ERROR"), format, ##__VA_ARGS__); \
    } while (0)

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

/// @brief Adds debug flags to the compiler configuration. Automatically selects flags for current compiler.
void SHU_CompilerDebug();

/// @brief Adds optimization flags to the compiler configuration. Automatically selects flags for current compiler.
/// @param optimizationLevel Level of optimizations to add. use SHUM_COMPILER_OPTIMIZATION_<...> flags to configure.
void SHU_CompilerOptimization(char optimizationLevel);

/// @brief Adds warning flags to the compiler configuration. Automatically selects flags for current compiler.
/// @param warningLevel Level of warnings to add. use SHUM_COMPILER_WARNING_<...> flags to configure.
/// @param treatAsError If true, treats all warnings as errors.
void SHU_CompilerWarning(char warningLevel, char treatAsError);

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

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
#define SHUI_PATH_SEPARATOR '\\'
#define SHUI_PATH_SEPARATOR_STR "\\"
#else
#define SHUI_PATH_SEPARATOR '/'
#define SHUI_PATH_SEPARATOR_STR "/"
#endif

// todo add clean build

#pragma region Internals

typedef struct SHUI_String
{
    char *data;
    size_t length;
} SHUI_String;

typedef struct SHUI_StringList
{
    SHUI_String *data;
    size_t count;
    size_t capacity;
} SHUI_StringList;

static struct
{
    struct
    {
        char data[SHUC_MAX_PATH_SIZE];
        size_t length;
    } currentExecutableDirectory;

    struct
    {
        char identifier;
        struct
        {
            char data[SHUC_MAX_COMPILER_LENGTH];
            size_t length;
        } command;
        SHUI_StringList flags;
    } COMPILER;

    struct
    {
        SHUI_String name;
        SHUI_StringList includeDirectories;
        SHUI_StringList sourceFiles;

        struct
        {
            SHUI_StringList linkDirectories;
            SHUI_StringList links;
        } EXECUTABLE;
    } MODULE;
} SHUI = {0};

/// @brief Creates a heap string from a string for internal usage.
/// @param string Null terminated string.
/// @return Created heap string.
static SHUI_String SHUI_SCreate(const char *string)
{
    const size_t stringLength = strlen(string);
    SHUI_String createdString = {0};

    createdString.length = stringLength;
    createdString.data = (char *)malloc(createdString.length + 1);

    if (createdString.data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Internal: Memory allocation failed in SHUI_SCreate.");
    }

    memcpy(createdString.data, string, createdString.length);

    createdString.data[createdString.length] = '\0';

    return createdString;
}

/// @brief Destroys a string by freeing and zeroing its memory.
/// @param string String to destroy.
static void SHUI_SDestroy(SHUI_String *string)
{
    if (string->data != NULL)
    {
        free(string->data);
    }

    string->data = NULL;
    string->length = 0;
}

/// @brief Replaces all occurrences of find with replace in a string.
/// @param string String to edit.
/// @param find Character to find and replace.
/// @param replace Character to replace with.
static void SHUI_SReplaceChar(SHUI_String *string, char find, char replace)
{
    for (size_t i = 0; i < string->length; i++)
    {
        if (string->data[i] == find)
        {
            string->data[i] = replace;
        }
    }
}

/// @brief Appends a null terminated string to a SHUI_String.
/// @param string String to append to.
/// @param appendString String to append.
/// @return Final string. Same with the string parameter by value.
static SHUI_String SHUI_SAppend(SHUI_String *string, const char *appendString)
{
    size_t appendLength = strlen(appendString);

    if (appendLength == 0)
    {
        return *string;
    }

    string->data = (char *)realloc(string->data, string->length + appendLength + 1);

    if (string->data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Internal: Memory reallocation failed in SHUI_SAppend.");
    }

    memcpy(string->data + string->length, appendString, appendLength);
    string->data[string->length + appendLength] = '\0';
    string->length += appendLength;

    return *string;
}

static SHUI_StringList SHUI_SLCreate(size_t capacity)
{
    SHUI_StringList list = {0};
    list.data = (SHUI_String *)malloc(sizeof(SHUI_String) * capacity);
    list.count = 0;
    list.capacity = capacity;

    if (list.data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Internal: Memory allocation failed in SHUI_SLCreate.");
    }

    return list;
}

static void SHUI_SLDestroy(SHUI_StringList *list)
{
    for (size_t i = 0; i < list->count; i++)
    {
        SHUI_SDestroy(&list->data[i]);
    }

    list->count = 0;

    if (list->data != NULL)
    {
        free(list->data);
    }

    list->data = NULL;
}

/// @brief Add string to the string list.
/// @param list List to add string to
/// @param data String to add.
static void SHUI_SLAdd(SHUI_StringList *list, SHUI_String string)
{
    if (list->data == NULL)
    {
        *list = SHUI_SLCreate(SHUC_ARRAY_INITIAL_COUNT);
    }
    else if (list->count >= list->capacity)
    {
        size_t newCapacity = (size_t)((float)list->capacity * SHUC_ARRAY_RESIZE_FACTOR);

        list->data = (SHUI_String *)realloc(list->data, sizeof(SHUI_String) * newCapacity);

        if (list->data == NULL)
        {
            SHU_LogError(SHUM_ERROR_NULL, "Internal: Memory reallocation failed in SHUI_SLAdd.");
        }

        list->capacity = newCapacity;
    }

    list->data[list->count] = string;

    list->count++;
}

/// @brief Platform-specific helper to create a directory.
/// @param path Directory path to create.
/// @return 0 on success, non-zero on failure.
static int SHUI_MakeDirectory(const char *path)
{
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    return _mkdir(path);
#else
    return mkdir(path, 0755);
#endif
}

/// @brief Creates directories recursively (like mkdir -p).
/// @param path Full path to create.
static void SHUI_MakeDirectoryRecursive(const char *path)
{
    char tempBuffer[SHUC_MAX_PATH_SIZE] = {0};
    size_t len = strlen(path);
    if (len >= sizeof(tempBuffer))
        return;

    memcpy(tempBuffer, path, len + 1);

    for (size_t i = 1; i < len; i++)
    {
        if (tempBuffer[i] == SHUI_PATH_SEPARATOR || tempBuffer[i] == '/' || tempBuffer[i] == '\\')
        {
            char saved = tempBuffer[i];
            tempBuffer[i] = '\0';
            SHUI_MakeDirectory(tempBuffer);
            tempBuffer[i] = saved;
        }
    }
    SHUI_MakeDirectory(tempBuffer);
}

/// @brief Platform-specific helper to delete a single file.
/// @param path File path to delete.
/// @return 0 on success.
static int SHUI_DeleteSingleFile(const char *path)
{
    return remove(path);
}

/// @brief Platform-specific helper to delete a directory.
/// @param path Directory path to delete.
/// @return 0 on success.
static int SHUI_DeleteDirectory(const char *path)
{
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    return _rmdir(path);
#else
    return rmdir(path);
#endif
}

#if SHUM_HOST_PLATFORM != SHUM_PLATFORM_WINDOWS
static int SHUI_NftwCallback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    (void)sb;
    (void)ftwbuf;
    if (typeflag == FTW_D || typeflag == FTW_DP)
        return rmdir(fpath);
    return remove(fpath);
}
#endif

/// @brief Deletes a file or directory recursively.
/// @param path Path to delete.
static void SHUI_DeleteRecursive(const char *path)
{
    char fileType = SHU_FileExists(path);
    if (fileType == SHUM_FILE_INVALID)
        return;

    if (fileType == SHUM_FILE_REGULAR)
    {
        SHUI_DeleteSingleFile(path);
        return;
    }

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    WIN32_FIND_DATAA ffd;
    char pattern[SHUC_MAX_PATH_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s\\*", path);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        char subPath[SHUC_MAX_PATH_SIZE] = {0};
        snprintf(subPath, sizeof(subPath), "%s\\%s", path, ffd.cFileName);

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            SHUI_DeleteRecursive(subPath);
        else
            SHUI_DeleteSingleFile(subPath);
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
    SHUI_DeleteDirectory(path);
#else
    nftw(path, SHUI_NftwCallback, 64, FTW_DEPTH | FTW_PHYS);
#endif
}

/// @brief Copies a single file.
/// @param src Source file path.
/// @param dst Destination file path.
static void SHUI_CopySingleFile(const char *src, const char *dst)
{
    FILE *srcFile = fopen(src, "rb");
    if (!srcFile)
        return;

    FILE *dstFile = fopen(dst, "wb");
    if (!dstFile)
    {
        fclose(srcFile);
        return;
    }

    char buffer[4096] = {0};
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0)
    {
        fwrite(buffer, 1, bytesRead, dstFile);
    }

    fclose(srcFile);
    fclose(dstFile);
}

/// @brief Copies a file or directory recursively.
/// @param src Source path.
/// @param dst Destination path.
static void SHUI_CopyRecursive(const char *src, const char *dst)
{
    char fileType = SHU_FileExists(src);
    if (fileType == SHUM_FILE_INVALID)
        return;

    if (fileType == SHUM_FILE_REGULAR)
    {
        SHUI_CopySingleFile(src, dst);
        return;
    }

    SHUI_MakeDirectoryRecursive(dst);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    WIN32_FIND_DATAA ffd;
    char pattern[SHUC_MAX_PATH_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s\\*", src);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        char srcPath[SHUC_MAX_PATH_SIZE] = {0};
        char dstPath[SHUC_MAX_PATH_SIZE] = {0};
        snprintf(srcPath, sizeof(srcPath), "%s\\%s", src, ffd.cFileName);
        snprintf(dstPath, sizeof(dstPath), "%s\\%s", dst, ffd.cFileName);

        SHUI_CopyRecursive(srcPath, dstPath);
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(src);
    if (!dir)
        return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char srcPath[SHUC_MAX_PATH_SIZE] = {0};
        char dstPath[SHUC_MAX_PATH_SIZE] = {0};
        snprintf(srcPath, sizeof(srcPath), "%s/%s", src, entry->d_name);
        snprintf(dstPath, sizeof(dstPath), "%s/%s", dst, entry->d_name);

        SHUI_CopyRecursive(srcPath, dstPath);
    }

    closedir(dir);
#endif
}

/// @brief Internal helper to traverse directory and add source files.
/// @param basePath Base path for the directory.
/// @param relativePath Relative path from base.
static void SHUI_AddSourceDirectoryRecursive(const char *basePath, const char *relativePath)
{
    char fullPath[SHUC_MAX_PATH_SIZE] = {0};
    snprintf(fullPath, sizeof(fullPath), "%s%s", basePath, relativePath);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    WIN32_FIND_DATAA ffd = {0};
    char pattern[SHUC_MAX_PATH_SIZE] = {0};
    snprintf(pattern, sizeof(pattern), "%s*", fullPath);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            char subDir[SHUC_MAX_PATH_SIZE] = {0};
            snprintf(subDir, sizeof(subDir), "%s%s\\", relativePath, ffd.cFileName);
            SHUI_AddSourceDirectoryRecursive(basePath, subDir);
        }
        else if (strstr(ffd.cFileName, ".c") != NULL)
        {
            SHUI_String newFile = SHUI_SCreate(fullPath);
            SHUI_SAppend(&newFile, ffd.cFileName);
            SHUI_SLAdd((SHUI_StringList *)&SHUI.MODULE.sourceFiles, newFile);
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(fullPath);
    if (!dir)
        return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char entryPath[SHUC_MAX_PATH_SIZE] = {0};
        snprintf(entryPath, sizeof(entryPath), "%s%s", fullPath, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0 && S_ISDIR(st.st_mode))
        {
            char subDir[SHUC_MAX_PATH_SIZE] = {0};
            snprintf(subDir, sizeof(subDir), "%s%s/", relativePath, entry->d_name);
            SHUI_AddSourceDirectoryRecursive(basePath, subDir);
        }
        else if (strstr(entry->d_name, ".c") != NULL)
        {
            SHUI_String newFile = SHUI_SCreate(fullPath);
            SHUI_SAppend(&newFile, entry->d_name);

            SHUI_SLAdd((SHUI_StringList *)&SHUI.MODULE.sourceFiles, newFile);
        }
    }

    closedir(dir);
#endif
}

/// @brief Compile the current module as an executable.
/// @param directory Relative output directory of the library file. (eg. build/lib/)
static void SHUI_CompileExecutable(SHUI_String directory)
{
    char includeBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t includeBufferIndex = 0;
    for (size_t i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        includeBufferIndex += snprintf(includeBuffer + includeBufferIndex,
                                       sizeof(includeBuffer) - includeBufferIndex,
                                       "%s%s ",
                                       SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/I" : "-I",
                                       SHUI.MODULE.includeDirectories.data[i].data);
    }

    char sourceBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t sourceBufferIndex = 0;
    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        sourceBufferIndex += snprintf(sourceBuffer + sourceBufferIndex,
                                      sizeof(sourceBuffer) - sourceBufferIndex,
                                      "%s ",
                                      SHUI.MODULE.sourceFiles.data[i].data);
    }

    char linkDirectoryBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t linkDirectoryBufferIndex = 0;
    for (size_t i = 0; i < SHUI.MODULE.EXECUTABLE.linkDirectories.count; i++)
    {
        linkDirectoryBufferIndex += snprintf(linkDirectoryBuffer + linkDirectoryBufferIndex,
                                             sizeof(linkDirectoryBuffer) - linkDirectoryBufferIndex,
                                             "%s%s %s%s ",
                                             SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/LIBPATH:" : "-L",
                                             SHUI.MODULE.EXECUTABLE.linkDirectories.data[i].data,
                                             SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "" : "-Wl,-rpath,",
                                             SHUI.MODULE.EXECUTABLE.linkDirectories.data[i].data);
    }

    char linkBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t linkBufferIndex = 0;
    for (size_t i = 0; i < SHUI.MODULE.EXECUTABLE.links.count; i++)
    {
        linkBufferIndex += snprintf(linkBuffer + linkBufferIndex,
                                    sizeof(linkBuffer) - linkBufferIndex,
                                    "%s%s ",
                                    SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "" : "-l",
                                    SHUI.MODULE.EXECUTABLE.links.data[i].data);
    }

    char flagBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t flagBufferIndex = 0;
    for (size_t i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        flagBufferIndex += snprintf(flagBuffer + flagBufferIndex,
                                    sizeof(flagBuffer) - flagBufferIndex,
                                    "%s ",
                                    SHUI.COMPILER.flags.data[i].data);
    }

    SHU_Run("%s %s %s %s %s %s %s%s%s%s",
            SHUI.COMPILER.command.data,
            includeBuffer,
            sourceBuffer,
            linkDirectoryBuffer,
            linkBuffer,
            flagBuffer,
            SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fe:" : "-o",
            directory.data,
            SHUI.MODULE.name.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".exe" : "");
}

/// @brief Compile the current module as a static library.
/// @param directory Relative output directory of the library file. (eg. build/lib/)
static void SHUI_CompileLibraryStatic(SHUI_String directory)
{
    // commands for flags
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        commandBufferIndex += snprintf(commandBuffer + commandBufferIndex,
                                       sizeof(commandBuffer) - commandBufferIndex,
                                       "%s ",
                                       SHUI.COMPILER.flags.data[i].data);
    }

    for (size_t i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        commandBufferIndex += snprintf(commandBuffer + commandBufferIndex,
                                       sizeof(commandBuffer) - commandBufferIndex,
                                       "%s%s ",
                                       SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/I" : "-I",
                                       SHUI.MODULE.includeDirectories.data[i].data);
    }

    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        SHU_Run("%s %s %s %s %.*s%s %s",
                SHUI.COMPILER.command.data,
                SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/c" : "-c",
                SHUI.MODULE.sourceFiles.data[i].data,
                SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fo:" : "-o",
                SHUI.MODULE.sourceFiles.data[i].length - 1,
                SHUI.MODULE.sourceFiles.data[i].data,
                SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o",
                commandBuffer);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        commandBufferIndex += snprintf(commandBuffer + commandBufferIndex,
                                       sizeof(commandBuffer) - commandBufferIndex,
                                       "%.*s%s ",
                                       (int)SHUI.MODULE.sourceFiles.data[i].length - 1,
                                       SHUI.MODULE.sourceFiles.data[i].data,
                                       SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o");
    }

    SHU_Run("%s %s%s%s%s%s %s",
            SHUI.COMPILER.identifier == SHUM_COMPILER_CLANG ? "llvm-ar"
            : SHUI.COMPILER.identifier == SHUM_COMPILER_GCC ? "ar"
                                                            : "lib.exe",
            SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/OUT:" : "rcs ", directory.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "" : "lib",
            SHUI.MODULE.name.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".lib" : ".a",
            commandBuffer);

    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        char objPath[SHUC_MAX_PATH_SIZE] = {0};
        snprintf(objPath, sizeof(objPath), "%.*s%s",
                 (int)SHUI.MODULE.sourceFiles.data[i].length - 1,
                 SHUI.MODULE.sourceFiles.data[i].data,
                 SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o");
        SHUI_DeleteSingleFile(objPath);
    }
}

/// @brief Compile the current module as a dynamic library.
/// @param directory Full output directory of the executable file. (eg. C:/[...]/build/bin/)
static void SHUI_CompileLibraryDynamic(SHUI_String directory)
{
    // commands for flags
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        commandBufferIndex += snprintf(commandBuffer + commandBufferIndex,
                                       sizeof(commandBuffer) - commandBufferIndex,
                                       "%s ",
                                       SHUI.COMPILER.flags.data[i].data);
    }

    for (size_t i = 0; i < SHUI.MODULE.includeDirectories.count; i++)
    {
        commandBufferIndex += snprintf(commandBuffer + commandBufferIndex,
                                       sizeof(commandBuffer) - commandBufferIndex,
                                       "%s%s ",
                                       SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/I" : "-I",
                                       SHUI.MODULE.includeDirectories.data[i].data);
    }

    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        SHU_Run("%s %s %s %s %.*s%s %s",
                SHUI.COMPILER.command.data,
                SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/c" : "-c -fPIC",
                SHUI.MODULE.sourceFiles.data[i].data,
                SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fo:" : "-o",
                SHUI.MODULE.sourceFiles.data[i].length - 1,
                SHUI.MODULE.sourceFiles.data[i].data,
                SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o",
                commandBuffer);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        commandBufferIndex += snprintf(commandBuffer + commandBufferIndex,
                                       sizeof(commandBuffer) - commandBufferIndex,
                                       "%.*s%s ",
                                       (int)SHUI.MODULE.sourceFiles.data[i].length - 1,
                                       SHUI.MODULE.sourceFiles.data[i].data,
                                       SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o");
    }

    SHU_Run("%s %s %s %s%s%s%s %s",
            SHUI.COMPILER.command.data,
            SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/LD" : "-shared",
            SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fe:" : "-o",
            directory.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "" : "lib",
            SHUI.MODULE.name.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".dll" : ".so",
            commandBuffer);

    // Delete object files
    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        char objPath[SHUC_MAX_PATH_SIZE] = {0};
        snprintf(objPath, sizeof(objPath), "%.*s%s",
                 (int)SHUI.MODULE.sourceFiles.data[i].length - 1,
                 SHUI.MODULE.sourceFiles.data[i].data,
                 SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o");
        SHUI_DeleteSingleFile(objPath);
    }
}

#pragma endregion Internals

#pragma region General

void SHU_AutomateI(int argc, char **argv, const char *sourceName)
{
    if (argc < 1 || argv == NULL || sourceName == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_Automate.");
    }

    size_t exeNameIndex = strlen(argv[0]) - 1;

    while (exeNameIndex > 0 && argv[0][exeNameIndex - 1] != SHUI_PATH_SEPARATOR && argv[0][exeNameIndex - 1] != '/' && argv[0][exeNameIndex - 1] != '\\')
    {
        exeNameIndex--;
    }

    size_t srcNameIndex = strlen(sourceName) - 1;

    while (srcNameIndex > 0 && sourceName[srcNameIndex - 1] != SHUI_PATH_SEPARATOR && sourceName[srcNameIndex - 1] != '/' && sourceName[srcNameIndex - 1] != '\\')
    {
        srcNameIndex--;
    }

    const char *exeName = argv[0] + exeNameIndex;
    const char *srcName = sourceName + srcNameIndex;

    struct stat attr;
    time_t exeTime = stat(exeName, &attr) == 0 ? attr.st_mtime : 0;
    time_t srcTime = stat(srcName, &attr) == 0 ? attr.st_mtime : 0;

    if (exeTime >= srcTime)
    {
        return;
    }

    SHU_LogInfo(SHUM_COLOR_MAGENTA("Build source has changed, rebuilding..."));

    char oldExeName[SHUC_MAX_PATH_SIZE] = {0};
    snprintf(oldExeName, sizeof(oldExeName), "%s.old", exeName);
    SHU_RenameFile(exeName, oldExeName);

    SHU_Run("%s %s %s %s%s",
            SHUI.COMPILER.command.data,
            srcName,
            SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/O2" : "-O3",
            SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fe:" : "-o",
            exeName);

    SHU_SpawnProcess(exeName, argv);
}

int SHU_Run(const char *commandFormat, ...)
{
    if (commandFormat == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_Run.");
    }

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

char SHU_FileExists(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_FileExists.");
    }

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    DWORD attributes = GetFileAttributesA(file);

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
    if (stat(file, &stats) == 0)
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

void SHU_CreateRelativeDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_CreateRelativeDirectory.");
    }

    SHUI_String directoryStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);
    SHUI_SAppend(&directoryStr, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&directoryStr, '/', '\\');
#endif

    SHUI_MakeDirectoryRecursive(directoryStr.data);
    SHUI_SDestroy(&directoryStr);
}

void SHU_DeleteFile(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_DeleteFile.");
    }

    if (strlen(file) == 0)
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Empty string passed to SHU_DeleteFile.");
    }

    SHUI_String fileStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);

    SHUI_SAppend(&fileStr, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&fileStr, '/', '\\');
#endif

    SHUI_DeleteRecursive(fileStr.data);
    SHUI_SDestroy(&fileStr);
}

void SHU_CopyFile(const char *file, const char *directory)
{
    if (file == NULL || directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_CopyFile.");
    }

    if (strlen(directory) == 0 || strlen(file) == 0)
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Empty string passed to SHU_CopyFile.");
    }

    SHU_CreateRelativeDirectory(directory);

    SHUI_String directoryStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);
    SHUI_String fileStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);

    SHUI_SAppend(&directoryStr, directory);
    SHUI_SAppend(&fileStr, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&directoryStr, '/', '\\');
    SHUI_SReplaceChar(&fileStr, '/', '\\');
#endif

    SHUI_CopyRecursive(fileStr.data, directoryStr.data);

    SHUI_SDestroy(&directoryStr);
    SHUI_SDestroy(&fileStr);
}

void SHU_RenameFile(const char *file, const char *name)
{
    if (file == NULL || name == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_RenameFile.");
    }

    if (strlen(name) == 0 || strlen(file) == 0)
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Empty string passed to SHU_RenameFile.");
    }

    SHUI_String fileStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);
    SHUI_String nameStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);

    SHUI_SAppend(&fileStr, file);
    SHUI_SAppend(&nameStr, name);

    SHU_DeleteFile(name);

    if (rename(fileStr.data, nameStr.data) != 0)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Failed to rename file '%s' to '%s'.", file, name);
    }

    SHUI_SDestroy(&fileStr);
    SHUI_SDestroy(&nameStr);
}

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    if (header == NULL || format == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_Log.");
    }

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
    if (compilerCommand == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_CompilerConfigure.");
    }

    SHUI.COMPILER.identifier = compiler;
    strncpy(SHUI.COMPILER.command.data, compilerCommand, SHUC_MAX_COMPILER_LENGTH - 1);

    if (SHUI.currentExecutableDirectory.length == 0)
    {
        char pathBuffer[SHUC_MAX_PATH_SIZE] = {0};
        size_t pathLength = 0;

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
        pathLength = GetModuleFileNameA(NULL, (LPSTR)pathBuffer, (DWORD)sizeof(pathBuffer));
#elif SHUM_HOST_PLATFORM == SHUM_PLATFORM_MACOS
        uint32_t size = (uint32_t)sizeof(pathBuffer);
        _NSGetExecutablePath(pathBuffer, &size);
        pathLength = strlen(pathBuffer);
#else
        pathLength = readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer));
#endif

        while (pathLength > 0 && pathBuffer[pathLength - 1] != SHUI_PATH_SEPARATOR && pathBuffer[pathLength - 1] != '/' && pathBuffer[pathLength - 1] != '\\')
        {
            pathBuffer[--pathLength] = '\0';
        }
        pathLength++;

        strncpy(SHUI.currentExecutableDirectory.data, pathBuffer, SHUC_MAX_PATH_SIZE - 1);
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
    else if (strcmp(compilerCommand, "cl") == 0 || strcmp(compilerCommand, "msvc") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_MSVC, compilerCommand);
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Unknown compiler command '%s'. Use " SHUM_COLOR_BLUE("SHU_CompilerConfigure") " to configure it manually.", compilerCommand);
    }
}

void SHU_CompilerAddFlags(const char *flags)
{
    if (flags == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_CompilerAddFlags.");
    }

    if (strlen(flags) != 0)
    {
        SHUI_SLAdd(&SHUI.COMPILER.flags, SHUI_SCreate(flags));
    }
}

void SHU_CompilerSetFlags(const char *flags)
{
    if (flags == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_CompilerSetFlags.");
    }

    SHU_CompilerClearFlags();

    SHU_CompilerAddFlags(flags);
}

void SHU_CompilerClearFlags()
{
    SHUI_SLDestroy(&SHUI.COMPILER.flags);
}

void SHU_CompilerDebug()
{
    if (SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC)
    {
        SHU_CompilerAddFlags("/Zi /Od");
    }
    else if (SHUI.COMPILER.identifier == SHUM_COMPILER_GCC || SHUI.COMPILER.identifier == SHUM_COMPILER_CLANG)
    {
        SHU_CompilerAddFlags("-g -Og");
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Compiler not configured. Configure the compiler first.");
    }
}

void SHU_CompilerOptimization(char optimizationLevel)
{
    if (SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC)
    {
        switch (optimizationLevel)
        {
        case SHUM_COMPILER_OPTIMIZATION_SIZE:
            SHU_CompilerAddFlags("/O1");
            break;
        case SHUM_COMPILER_OPTIMIZATION_LOW:
            SHU_CompilerAddFlags("/O2");
            break;
        case SHUM_COMPILER_OPTIMIZATION_MID:
            SHU_CompilerAddFlags("/Ox");
            break;
        case SHUM_COMPILER_OPTIMIZATION_HIGH:
            SHU_CompilerAddFlags("/Oxiy");
            break;
        default:
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid optimization level passed to SHU_CompilerOptimization.");
            break;
        }
    }
    else if (SHUI.COMPILER.identifier == SHUM_COMPILER_GCC || SHUI.COMPILER.identifier == SHUM_COMPILER_CLANG)
    {
        switch (optimizationLevel)
        {
        case SHUM_COMPILER_OPTIMIZATION_SIZE:
            SHU_CompilerAddFlags("-Os");
            break;
        case SHUM_COMPILER_OPTIMIZATION_LOW:
            SHU_CompilerAddFlags("-O1");
            break;
        case SHUM_COMPILER_OPTIMIZATION_MID:
            SHU_CompilerAddFlags("-O2");
            break;
        case SHUM_COMPILER_OPTIMIZATION_HIGH:
            SHU_CompilerAddFlags("-O3");
            break;
        default:
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid optimization level passed to SHU_CompilerOptimization.");
            break;
        }
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Compiler not configured. Configure the compiler first.");
    }
}

void SHU_CompilerWarning(char warningLevel, char treatAsError)
{
    if (SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC)
    {
        switch (warningLevel)
        {
        case SHUM_COMPILER_WARNING_LOW:
            SHU_CompilerAddFlags("/W1");
            break;
        case SHUM_COMPILER_WARNING_MID:
            SHU_CompilerAddFlags("/W3");
            break;
        case SHUM_COMPILER_WARNING_HIGH:
            // SHU_CompilerAddFlags("/Wall /GS");
            SHU_CompilerAddFlags("/W4 /WX-");
            break;
        default:
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid warning level passed to SHU_CompilerWarning.");
            break;
        }

        if (treatAsError)
        {
            SHU_CompilerAddFlags("/WX");
        }
    }
    else if (SHUI.COMPILER.identifier == SHUM_COMPILER_GCC || SHUI.COMPILER.identifier == SHUM_COMPILER_CLANG)
    {
        switch (warningLevel)
        {
        case SHUM_COMPILER_WARNING_LOW:
            SHU_CompilerAddFlags("-Wall -Wextra");
            break;
        case SHUM_COMPILER_WARNING_MID:
            SHU_CompilerAddFlags("-Wall -Wextra -Wshadow -Wpedantic -Wconversion -Wformat=2 -fstack-protector-strong");
            break;
        case SHUM_COMPILER_WARNING_HIGH:
            SHU_CompilerAddFlags("-Wall -Wextra -Wshadow -Wpedantic -Wconversion -Wnull-dereference -fstack-protector-strong -Wpointer-arith -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wsign-conversion -Wundef -Wpointer-to-int-cast -Wint-to-pointer-cast");
            break;
        default:
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid warning level passed to SHU_CompilerWarning.");
            break;
        }

        if (treatAsError)
        {
            SHU_CompilerAddFlags("-Werror");
        }
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Compiler not configured. Configure the compiler first.");
    }
}

unsigned long SHU_CompilerGetFlags(char *buffer, unsigned long bufferSize)
{
    unsigned long bufferIndex = 0;

    for (size_t i = 0; i < SHUI.COMPILER.flags.count; i++)
    {
        if (bufferIndex > bufferSize - 2)
        {
            SHU_LogWarning("Buffer too small for compiler flags. Output truncated.");
            break;
        }

        bufferIndex += snprintf(buffer + bufferIndex,
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
    if (name == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_ModuleBegin.");
    }

    if (SHUI.MODULE.name.data != NULL)
    {
        SHUI_SDestroy(&SHUI.MODULE.name);
    }

    SHUI.MODULE.name = SHUI_SCreate(name);
}

void SHU_ModuleAddIncludeDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_ModuleAddIncludeDirectory.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI.currentExecutableDirectory.data);
    SHUI_SAppend(&correctedDirectory, directory);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_SLAdd(&SHUI.MODULE.includeDirectories, correctedDirectory);
}

void SHU_ModuleAddSourceFile(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_ModuleAddSourceFile.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI.currentExecutableDirectory.data);
    SHUI_SAppend(&correctedDirectory, file);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_SLAdd((SHUI_StringList *)&SHUI.MODULE.sourceFiles, correctedDirectory);
}

void SHU_ModuleAddSourceDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_ModuleAddSourceDirectory.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(directory);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_AddSourceDirectoryRecursive(SHUI.currentExecutableDirectory.data, correctedDirectory.data);
    SHUI_SDestroy(&correctedDirectory);
}

void SHU_ModuleCompile(const char *directory, char module)
{
#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("Starting to compile %s " SHUM_COLOR_MAGENTA("'%s'") "...", SHUM_MODULE_GET_STRING(module), SHUI.MODULE.name.data);
#endif

    SHUI_String directoryStr = SHUI_SCreate(SHUI.currentExecutableDirectory.data);

    if (directory != NULL && strlen(directory) != 0)
    {
        SHU_CreateRelativeDirectory(directory);
        SHUI_SAppend(&directoryStr, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
        SHUI_SReplaceChar(&directoryStr, '/', '\\');
#endif
    }

    switch (module)
    {
    case SHUM_MODULE_EXECUTABLE:
        SHUI_CompileExecutable(directoryStr);
        break;
    case SHUM_MODULE_LIBRARY_STATIC:
        SHUI_CompileLibraryStatic(directoryStr);
        break;
    case SHUM_MODULE_LIBRARY_DYNAMIC:
        SHUI_CompileLibraryDynamic(directoryStr);
        break;
    default:
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid module type passed to SHU_ModuleCompile.");
        break;
    }

    if (directoryStr.data != NULL)
    {
        SHUI_SDestroy(&directoryStr);
    }

    if (module == SHUM_MODULE_EXECUTABLE)
    {
        SHUI_SLDestroy(&SHUI.MODULE.EXECUTABLE.linkDirectories);
        SHUI_SLDestroy(&SHUI.MODULE.EXECUTABLE.links);
    }

    SHUI_SLDestroy(&SHUI.MODULE.includeDirectories);
    SHUI_SLDestroy((SHUI_StringList *)&SHUI.MODULE.sourceFiles);

#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("%s " SHUM_COLOR_MAGENTA("'%s'") " successfully compiled.", SHUM_MODULE_GET_STRING(module), SHUI.MODULE.name.data);
#endif

    SHUI_SDestroy(&SHUI.MODULE.name);
}

void SHU_ModuleAddLibraryDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_ModuleAddLibraryDirectory.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI.currentExecutableDirectory.data);
    SHUI_SAppend(&correctedDirectory, directory);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplaceChar(&correctedDirectory, '/', '\\');
#endif

    SHUI_SLAdd(&SHUI.MODULE.EXECUTABLE.linkDirectories, correctedDirectory);
}

void SHU_ModuleLinkLibrary(const char *library)
{
    if (library == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed to SHU_ModuleLinkLibrary.");
    }

    SHUI_SLAdd(&SHUI.MODULE.EXECUTABLE.links, SHUI_SCreate(library));
}

#pragma endregion Module

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations
