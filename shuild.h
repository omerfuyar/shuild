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

#ifndef SHUC_MAX_STRING_ARRAY_COUNT
#define SHUC_MAX_STRING_ARRAY_COUNT 16
#endif

#ifndef SHUC_MAX_SOURCE_FILE_COUNT
#define SHUC_MAX_SOURCE_FILE_COUNT 256
#endif

#ifndef SHUC_MAX_COMMAND_BUFFER_SIZE
#define SHUC_MAX_COMMAND_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_MESSAGE_BUFFER_SIZE
#define SHUC_MAX_MESSAGE_BUFFER_SIZE 4096
#endif

#ifndef SHUC_MAX_PATH_SIZE
#define SHUC_MAX_PATH_SIZE 256
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

#define SHUM_COLOR_RED(string) "\x1b[31m" string "\x1b[0m"
#define SHUM_COLOR_GREEN(string) "\x1b[32m" string "\x1b[0m"
#define SHUM_COLOR_YELLOW(string) "\x1b[33m" string "\x1b[0m"
#define SHUM_COLOR_BLUE(string) "\x1b[34m" string "\x1b[0m"

#pragma region General

/// @brief Enables autonomously rebuilding the build script when edited. I think it works only if the build system is one script. Run after configuring the compiler.
/// @param argc Argument count from main function.
/// @param argv Argument array from main function.
#define SHU_Automate(argc, argv) SHU_AutomateI(argc, argv, __FILE__)

void SHU_AutomateI(int argc, char **argv, const char *sourceName);

/// @brief Internal command runner function.
/// @param command Command to run with system. (eg. clang example.c -o example)
void SHU_Run(const char *commandFormat, ...);

/// @brief Spawns a new process and waits for completion.
/// @param executable Path to executable.
/// @param argv Arguments array (NULL terminated).
/// @return Exit code of the process, or -1 on failure.
void SHU_SpawnProcess(const char *executable, char *const *argv);

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

/// @brief Configures the compiler to be used for compiling modules. Default is the host (compiler that shuild.c compiled) compiler.
/// @param compiler Compiler specifier. Use with SHUM_COMPILER_<...> macros.
/// @param compilerCommand Command to invoke the compiler. (eg. clang)
void SHU_CompilerConfigure(char compiler, const char *compilerCommand);

/// @brief Tries to configure the compiler by the command of it by checking regular commands. Default is the host (compiler that shuild.c compiled) compiler.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc)
void SHU_CompilerTryConfigure(const char *compilerCommand);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add. Can include multiple flags separated by spaces as you want. (eg. -DFOO=31)
void SHU_CompilerAddFlags(const char *flags);

/// @brief Clears and sets the compiler flags, replacing all existing ones.
/// @param flags Flags to set. Can include multiple flags separated by spaces as you want.
void SHU_CompilerSetFlags(const char *flags);

/// @brief Adds debug flags to the compiler configuration. Automatically selects flags for current compiler.
void SHU_CompilerDebug();

/// @brief Adds optimization flags to the compiler configuration. Automatically selects flags for current compiler.
/// @param optimizationLevel Level of optimizations to add. use SHUM_COMPILER_OPTIMIZATION_<...> flags to configure.
void SHU_CompilerOptimization(char optimizationLevel);

/// @brief Adds warning flags to the compiler configuration. Automatically selects flags for current compiler.
/// @param warningLevel Level of warnings to add. use SHUM_COMPILER_WARNING_<...> flags to configure.
/// @param treatAsError If true, treats all warnings as errors.
void SHU_CompilerWarning(char warningLevel, char treatAsError);

#pragma endregion Compiler

#pragma region Module

/// @brief Begins a new module with the given name. A module can be an executable or a library.
/// @param name Name of the module. Which will be used also for output file name. (eg. myLibName, myAppName)
void SHU_ModuleBegin(const char *name);

/// @brief Adds include directories to the module. Max count is defined as `SHUC_MAX_STRING_ARRAY_COUNT`.
/// @param directory Include directory to add to the current module. (eg. include/)
void SHU_ModuleAddIncludeDirectory(const char *directory);

/// @brief Adds source directories to the module. Works recursively. Max source file count is defined as `SHUC_MAX_SOURCE_FILE_COUNT`.
/// @param directory Source directory to add to the current module. (eg. src/)
void SHU_ModuleAddSourceDirectory(const char *directory);

/// @brief Adds source files to the module. Max count is defined as `SHUC_MAX_STRING_ARRAY_COUNT`.
/// @param file Single file to add to the current module. (eg. source.c)
void SHU_ModuleAddSourcefile(const char *file);

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

// Platform-specific path separator
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
#define SHUI_PATH_SEPARATOR '\\'
#define SHUI_PATH_SEPARATOR_STR "\\"
#else
#define SHUI_PATH_SEPARATOR '/'
#define SHUI_PATH_SEPARATOR_STR "/"
#endif

#pragma region Internals

typedef struct SHUI_String
{
    char *data;
    size_t length;
} SHUI_String;

typedef struct SHUI_StringList
{
    size_t count;
    SHUI_String data[SHUC_MAX_STRING_ARRAY_COUNT];
} SHUI_StringList;

typedef struct SHUI_StringListBig
{
    size_t count;
    SHUI_String data[SHUC_MAX_SOURCE_FILE_COUNT];
} SHUI_StringListBig;

static SHUI_String SHUI_CURRENT_EXECUTABLE_DIRECTORY = {0};

static char SHUI_COMPILER = SHUM_HOST_COMPILER;
static SHUI_String SHUI_COMPILER_COMMAND = {0};
static SHUI_StringList SHUI_COMPILER_FLAGS = {0};

static SHUI_String SHUI_MODULE_NAME = {0};
static SHUI_StringList SHUI_MODULE_INCLUDE_DIRECTORIES = {0};
static SHUI_StringListBig SHUI_MODULE_SOURCE_FILES = {0};

static SHUI_StringList SHUI_EXECUTABLE_LINK_DIRECTORIES = {0};
static SHUI_StringList SHUI_EXECUTABLE_LINKS = {0};

/// @brief Creates a heap string from a string for internal usage.
/// @param string Null terminated string.
/// @return Created heap string.
static SHUI_String SHUI_SCreate(const char *string)
{
    if (string == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string create.");
    }

    const size_t stringLength = strlen(string);

    if (stringLength == 0)
    {
        SHU_LogError(SHUM_ERROR_INDEX, "String length to create a heap copy can not be 0.");
    }

    SHUI_String createdString = {0};

    createdString.length = stringLength;
    createdString.data = (char *)malloc(createdString.length + 1);

    if (createdString.data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Malloc error while creating heap string.");
    }

    memcpy(createdString.data, string, createdString.length);

    createdString.data[createdString.length] = '\0';

    return createdString;
}

/// @brief Destroys a string by freeing and zeroing its memory.
/// @param string String to destroy.
static void SHUI_SDestroy(SHUI_String *string)
{
    if (string == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string destroy.");
    }

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
static void SHUI_SReplace(SHUI_String *string, char find, char replace)
{
    if (string == NULL || string->data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string replace.");
    }

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
    if (string == NULL || string->data == NULL || appendString == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string append.");
    }

    size_t appendLength = strlen(appendString);

    string->data = (char *)realloc(string->data, string->length + appendLength + 1);

    if (string->data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Realloc error while appending to string.");
    }

    memcpy(string->data + string->length, appendString, appendLength);
    string->data[string->length + appendLength] = '\0';
    string->length += appendLength;

    return *string;
}

/// @brief Add string to the string list.
/// @param list List to add string to
/// @param data String to add.
static void SHUI_SLAdd(SHUI_StringList *list, SHUI_String string, size_t capacity)
{
    if (list == NULL || string.data == NULL || string.data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string list add.");
    }

    if (list->count >= capacity)
    {
        SHU_LogError(SHUM_ERROR_INDEX, "String list is full. Try increasing the limit, batch inputs or use manual flags.");
    }

    list->data[list->count] = string;

    list->count++;
}

/// @brief Clears the data of the String List by freeing its memory and setting datas to null.
/// @param list List to clear.
static void SHUI_SLClear(SHUI_StringList *list)
{
    if (list == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null list pointer passed as parameter to string list clear.");
    }

    for (size_t i = 0; i < list->count; i++)
    {
        if (list->data[i].data != NULL)
        {
            SHUI_SDestroy(&list->data[i]);
        }
    }

    list->count = 0;
}

/// @brief Platform-specific helper to get executable path.
/// @param buffer Buffer to write path into.
/// @param bufferSize Size of the buffer.
/// @return Length of the path or 0 on failure.
static size_t SHUI_GetExecutablePath(char *buffer, size_t bufferSize)
{
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    return (size_t)GetModuleFileNameA(NULL, buffer, (DWORD)bufferSize);
#elif SHUM_HOST_PLATFORM == SHUM_PLATFORM_MACOS
    uint32_t size = (uint32_t)bufferSize;
    if (_NSGetExecutablePath(buffer, &size) == 0)
        return strlen(buffer);
    return 0;
#else
    ssize_t len = readlink("/proc/self/exe", buffer, bufferSize - 1);
    if (len > 0)
    {
        buffer[len] = '\0';
        return (size_t)len;
    }
    return 0;
#endif
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
    char tempBuffer[SHUC_MAX_PATH_SIZE];
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
    char pattern[SHUC_MAX_PATH_SIZE];
    snprintf(pattern, sizeof(pattern), "%s\\*", path);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        char subPath[SHUC_MAX_PATH_SIZE];
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

    char buffer[4096];
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
    char pattern[SHUC_MAX_PATH_SIZE];
    snprintf(pattern, sizeof(pattern), "%s\\*", src);

    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        char srcPath[SHUC_MAX_PATH_SIZE];
        char dstPath[SHUC_MAX_PATH_SIZE];
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

        char srcPath[SHUC_MAX_PATH_SIZE];
        char dstPath[SHUC_MAX_PATH_SIZE];
        snprintf(srcPath, sizeof(srcPath), "%s/%s", src, entry->d_name);
        snprintf(dstPath, sizeof(dstPath), "%s/%s", dst, entry->d_name);

        SHUI_CopyRecursive(srcPath, dstPath);
    }

    closedir(dir);
#endif
}

/// @brief Gets the current executable directory and sets it to SHUI_CURRENT_EXECUTABLE_DIRECTORY.
/// @return Current executable directory string.
static SHUI_String SHUI_GetCurrentExecutableDirectory()
{
    if (SHUI_CURRENT_EXECUTABLE_DIRECTORY.data == NULL)
    {
        char pathBuffer[SHUC_MAX_PATH_SIZE] = {0};
        SHUI_GetExecutablePath(pathBuffer, sizeof(pathBuffer));

        size_t pathLength = strlen(pathBuffer);

        while (pathLength > 0 && pathBuffer[pathLength - 1] != SHUI_PATH_SEPARATOR && pathBuffer[pathLength - 1] != '/' && pathBuffer[pathLength - 1] != '\\')
        {
            pathBuffer[--pathLength] = '\0';
        }
        pathLength++;

        SHUI_CURRENT_EXECUTABLE_DIRECTORY = SHUI_SCreate(pathBuffer);
    }

    return SHUI_CURRENT_EXECUTABLE_DIRECTORY;
}

/// @brief Internal helper to traverse directory and add source files.
/// @param basePath Base path for the directory.
/// @param relativePath Relative path from base.
static void SHUI_AddSourceDirectoryRecursive(const char *basePath, const char *relativePath)
{
    char fullPath[SHUC_MAX_PATH_SIZE];
    snprintf(fullPath, sizeof(fullPath), "%s%s", basePath, relativePath);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    WIN32_FIND_DATAA ffd = {0};
    char pattern[SHUC_MAX_PATH_SIZE];
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
            char subDir[SHUC_MAX_PATH_SIZE];
            snprintf(subDir, sizeof(subDir), "%s%s\\", relativePath, ffd.cFileName);
            SHUI_AddSourceDirectoryRecursive(basePath, subDir);
        }
        else if (strstr(ffd.cFileName, ".c") != NULL)
        {
            SHUI_String newFile = SHUI_SCreate(fullPath);
            SHUI_SAppend(&newFile, ffd.cFileName);
            SHUI_SLAdd((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES, newFile, SHUC_MAX_SOURCE_FILE_COUNT);
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

        char entryPath[SHUC_MAX_PATH_SIZE];
        snprintf(entryPath, sizeof(entryPath), "%s%s", fullPath, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0 && S_ISDIR(st.st_mode))
        {
            char subDir[SHUC_MAX_PATH_SIZE];
            snprintf(subDir, sizeof(subDir), "%s%s/", relativePath, entry->d_name);
            SHUI_AddSourceDirectoryRecursive(basePath, subDir);
        }
        else if (strstr(entry->d_name, ".c") != NULL)
        {
            SHUI_String newFile = SHUI_SCreate(fullPath);
            SHUI_SAppend(&newFile, entry->d_name);
            SHUI_SLAdd((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES, newFile, SHUC_MAX_SOURCE_FILE_COUNT);
        }
    }

    closedir(dir);
#endif
}

/// @brief Compile the current module as an executable.
/// @param directory Full output directory of the executable file. (eg. C:/[...]/build/bin/)
static void SHUI_CompileExecutable(SHUI_String directory)
{
    char includeBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t includeBufferIndex = 0;
    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(includeBuffer + includeBufferIndex,
                 sizeof(includeBuffer) - includeBufferIndex,
                 "%s%s ",
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/I" : "-I",
                 SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        includeBufferIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    char sourceBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t sourceBufferIndex = 0;
    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(sourceBuffer + sourceBufferIndex,
                 sizeof(sourceBuffer) - sourceBufferIndex,
                 "%s ",
                 SHUI_MODULE_SOURCE_FILES.data[i].data);
        sourceBufferIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    char linkDirectoryBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t linkDirectoryBufferIndex = 0;
    for (size_t i = 0; i < SHUI_EXECUTABLE_LINK_DIRECTORIES.count; i++)
    {
        snprintf(linkDirectoryBuffer + linkDirectoryBufferIndex,
                 sizeof(linkDirectoryBuffer) - linkDirectoryBufferIndex,
                 "%s%s ",
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/LIBPATH:" : "-L",
                 SHUI_EXECUTABLE_LINK_DIRECTORIES.data[i].data);
        linkDirectoryBufferIndex += SHUI_EXECUTABLE_LINK_DIRECTORIES.data[i].length + 1 + (SHUI_COMPILER == SHUM_COMPILER_MSVC ? 9 : 2);
    }

    char linkBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t linkBufferIndex = 0;
    for (size_t i = 0; i < SHUI_EXECUTABLE_LINKS.count; i++)
    {
        snprintf(linkBuffer + linkBufferIndex,
                 sizeof(linkBuffer) - linkBufferIndex,
                 "%s%s ",
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "" : "-l",
                 SHUI_EXECUTABLE_LINKS.data[i].data);
        linkBufferIndex += SHUI_EXECUTABLE_LINKS.data[i].length + 1 + (SHUI_COMPILER == SHUM_COMPILER_MSVC ? 0 : 2);
    }

    char flagBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t flagBufferIndex = 0;
    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(flagBuffer + flagBufferIndex,
                 sizeof(flagBuffer) - flagBufferIndex,
                 "%s ",
                 SHUI_COMPILER_FLAGS.data[i].data);
        flagBufferIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    SHU_Run("%s %s %s %s %s %s %s%s%s%s",
            SHUI_COMPILER_COMMAND.data,
            includeBuffer,
            sourceBuffer,
            linkDirectoryBuffer,
            linkBuffer,
            flagBuffer,
            SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/Fe:" : "-o",
            directory.data,
            SHUI_MODULE_NAME.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".exe" : "");
}

/// @brief Compile the current module as a static library.
/// @param directory Full output directory of the executable file. (eg. C:/[...]/build/bin/)
static void SHUI_CompileLibraryStatic(SHUI_String directory)
{
    // commands for flags
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex,
                 sizeof(commandBuffer) - commandBufferIndex,
                 "%s ",
                 SHUI_COMPILER_FLAGS.data[i].data);
        commandBufferIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex,
                 sizeof(commandBuffer) - commandBufferIndex,
                 "%s%s ",
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/I" : "-I",
                 SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        commandBufferIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        SHU_Run("%s %s %s %s %.*s%s %s",
                SHUI_COMPILER_COMMAND.data,
                SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/c" : "-c",
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/Fo:" : "-o",
                SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                SHUI_COMPILER == SHUM_COMPILER_MSVC ? "obj" : "o",
                commandBuffer);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex,
                 sizeof(commandBuffer) - commandBufferIndex,
                 "%.*s%s ",
                 (int)SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                 SHUI_MODULE_SOURCE_FILES.data[i].data,
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "obj" : "o");
        commandBufferIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + (SHUI_COMPILER == SHUM_COMPILER_MSVC ? 3 : 1);
    }

    SHU_Run("%s %s%s%s%s%s %s",
            SHUI_COMPILER == SHUM_COMPILER_CLANG ? "llvm-ar"
            : SHUI_COMPILER == SHUM_COMPILER_GCC ? "ar"
                                                 : "lib.exe",
            SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/OUT:" : "rcs ", directory.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "" : "lib",
            SHUI_MODULE_NAME.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".lib" : ".a",
            commandBuffer);

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        char objPath[SHUC_MAX_PATH_SIZE];
        snprintf(objPath, sizeof(objPath), "%.*s%s",
                 (int)SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                 SHUI_MODULE_SOURCE_FILES.data[i].data,
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "obj" : "o");
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

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex,
                 sizeof(commandBuffer) - commandBufferIndex,
                 "%s ",
                 SHUI_COMPILER_FLAGS.data[i].data);
        commandBufferIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex,
                 sizeof(commandBuffer) - commandBufferIndex,
                 "%s%s ",
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/I" : "-I",
                 SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        commandBufferIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        SHU_Run("%s %s %s %s %.*s%s %s",
                SHUI_COMPILER_COMMAND.data,
                SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/c" : "-c -fPIC",
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/Fo:" : "-o",
                SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                SHUI_COMPILER == SHUM_COMPILER_MSVC ? "obj" : "o",
                commandBuffer);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex,
                 sizeof(commandBuffer) - commandBufferIndex,
                 "%.*s%s ",
                 (int)SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                 SHUI_MODULE_SOURCE_FILES.data[i].data,
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "obj" : "o");
        commandBufferIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + (SHUI_COMPILER == SHUM_COMPILER_MSVC ? 3 : 1);
    }

    SHU_Run("%s %s %s %s%s%s %s",
            SHUI_COMPILER_COMMAND.data,
            SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/LD" : "-shared",
            SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/Fe:" : "-o",
            directory.data, SHUI_MODULE_NAME.data,
            SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".dll" : ".so",
            commandBuffer);

    // Delete object files
    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        char objPath[SHUC_MAX_PATH_SIZE];
        snprintf(objPath, sizeof(objPath), "%.*s%s",
                 (int)SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                 SHUI_MODULE_SOURCE_FILES.data[i].data,
                 SHUI_COMPILER == SHUM_COMPILER_MSVC ? "obj" : "o");
        SHUI_DeleteSingleFile(objPath);
    }
}

#pragma endregion Internals

#pragma region General

void SHU_AutomateI(int argc, char **argv, const char *sourceName)
{
    if (argc < 1 || argv == NULL || sourceName == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to automate.");
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

    SHU_LogInfo("Build source has changed, rebuilding...");

    char oldExeName[SHUC_MAX_PATH_SIZE] = {0};
    snprintf(oldExeName, sizeof(oldExeName), "%s.old", exeName);
    SHU_RenameFile(exeName, oldExeName);

    SHU_Run("%s %s %s %s%s",
            SHUI_COMPILER_COMMAND.data,
            srcName,
            SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/O2" : "-O3",
            SHUI_COMPILER == SHUM_COMPILER_MSVC ? "/Fe:" : "-o",
            exeName);

    SHU_SpawnProcess(exeName, argv);
}

void SHU_Run(const char *commandFormat, ...)
{
    if (commandFormat == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to run.");
    }

    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, commandFormat);
    vsnprintf(commandBuffer, sizeof(commandBuffer), commandFormat, args);
    va_end(args);

#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Executing command : '%s'", commandBuffer);
#endif

    int result = system(commandBuffer);

    if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        SHU_LogError(0, "Last executed command failed with exit code %d.", result);
#else
        SHU_LogError(result, "Last executed command failed with exit code %d.", result);
#endif
    }
}

void SHU_SpawnProcess(const char *executable, char *const *argv)
{
    int result = 0;

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
        SHU_LogError(0, "Last spawned process failed with exit code %d.", result);
#else
        SHU_LogError(result, "Last spawned process failed with exit code %d.", result);
#endif
    }
    else
    {
        SHU_LogInfo("Process '%s' executed successfully.", executable);
        exit(0);
    }
}

char SHU_FileExists(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to file exists.");
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
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to create directory.");
    }

    if (strlen(directory) == 0)
    {
        return;
    }

    SHUI_String directoryStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&directoryStr, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&directoryStr, '/', '\\');
#endif

    SHUI_MakeDirectoryRecursive(directoryStr.data);
    SHUI_SDestroy(&directoryStr);
}

void SHU_DeleteFile(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to delete file.");
    }

    if (strlen(file) == 0)
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Empty string passed as parameter to delete file.");
    }

    SHUI_String fileStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    SHUI_SAppend(&fileStr, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&fileStr, '/', '\\');
#endif

    SHUI_DeleteRecursive(fileStr.data);
    SHUI_SDestroy(&fileStr);
}

void SHU_CopyFile(const char *file, const char *directory)
{
    if (file == NULL || directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to copy file.");
    }

    if (strlen(directory) == 0 || strlen(file) == 0)
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Empty string passed as parameter to copy file.");
    }

    SHU_CreateRelativeDirectory(directory);

    SHUI_String directoryStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_String fileStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    SHUI_SAppend(&directoryStr, directory);
    SHUI_SAppend(&fileStr, file);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&directoryStr, '/', '\\');
    SHUI_SReplace(&fileStr, '/', '\\');
#endif

    SHUI_CopyRecursive(fileStr.data, directoryStr.data);

    SHUI_SDestroy(&directoryStr);
    SHUI_SDestroy(&fileStr);
}

void SHU_RenameFile(const char *file, const char *name)
{
    if (file == NULL || name == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to rename file.");
    }

    if (strlen(name) == 0 || strlen(file) == 0)
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Empty string passed as parameter to rename file.");
    }

    SHUI_String fileStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_String nameStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    SHUI_SAppend(&fileStr, file);
    SHUI_SAppend(&nameStr, name);

    SHU_DeleteFile(name);

    if (rename(fileStr.data, nameStr.data) != 0)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Error while renaming file '%s' to '%s'.", file, name);
    }

    SHUI_SDestroy(&fileStr);
    SHUI_SDestroy(&nameStr);
}

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    if (header == NULL || format == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to log.");
    }

    char messageBuffer[SHUC_MAX_MESSAGE_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, format);
    vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
    va_end(args);

    printf("[%s] : %s\n", header, messageBuffer);

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
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to compiler configure.");
    }

    if (SHUI_COMPILER_COMMAND.data != NULL)
    {
        SHUI_SDestroy(&SHUI_COMPILER_COMMAND);
    }

    SHUI_COMPILER = compiler;
    SHUI_COMPILER_COMMAND = SHUI_SCreate(compilerCommand);
}

void SHU_CompilerTryConfigure(const char *compilerCommand)
{
    if (compilerCommand == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to compiler try configure.");
    }

    if (strcmp(compilerCommand, "clang") == 0 || strcmp(compilerCommand, "clang-cl") == 0)
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
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Could not configure compiler with command '%s'. Try using standard commands or use the function" SHUM_COLOR_BLUE("SHU_CompilerConfigure") ".", compilerCommand);
    }
}

void SHU_CompilerAddFlags(const char *flags)
{
    if (flags == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to compiler add flags.");
    }

    if (strlen(flags) != 0)
    {
        SHUI_SLAdd(&SHUI_COMPILER_FLAGS, SHUI_SCreate(flags), SHUC_MAX_STRING_ARRAY_COUNT);
    }
}

void SHU_CompilerSetFlags(const char *flags)
{
    if (flags == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to compiler set flags.");
    }

    SHUI_SLClear(&SHUI_COMPILER_FLAGS);

    SHU_CompilerAddFlags(flags);
}

void SHU_CompilerDebug()
{
    if (SHUI_COMPILER == SHUM_COMPILER_MSVC)
    {
        SHU_CompilerAddFlags("/Zi /Od");
    }
    else if (SHUI_COMPILER == SHUM_COMPILER_GCC || SHUI_COMPILER == SHUM_COMPILER_CLANG)
    {
        SHU_CompilerAddFlags("-g -Og");
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Compiler not configured. Cannot set debug flags.");
    }
}

void SHU_CompilerOptimization(char optimizationLevel)
{
    if (SHUI_COMPILER == SHUM_COMPILER_MSVC)
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
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid optimization level passed as parameter to compiler optimization.");
            break;
        }
    }
    else if (SHUI_COMPILER == SHUM_COMPILER_GCC || SHUI_COMPILER == SHUM_COMPILER_CLANG)
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
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid optimization level passed as parameter to compiler optimization.");
            break;
        }
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Compiler not configured. Cannot set debug optimization.");
    }
}

void SHU_CompilerWarning(char warningLevel, char treatAsError)
{
    if (SHUI_COMPILER == SHUM_COMPILER_MSVC)
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
            SHU_CompilerAddFlags("/Wall /GS");
            break;
        default:
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid warning level passed as parameter to compiler optimization.");
            break;
        }

        if (treatAsError)
        {
            SHU_CompilerAddFlags("/WX");
        }
    }
    else if (SHUI_COMPILER == SHUM_COMPILER_GCC || SHUI_COMPILER == SHUM_COMPILER_CLANG)
    {
        switch (warningLevel)
        {
        case SHUM_COMPILER_WARNING_LOW:
            SHU_CompilerAddFlags("-Wall");
            break;
        case SHUM_COMPILER_WARNING_MID:
            SHU_CompilerAddFlags("-Wall -Wextra -Wshadow -Wpedantic");
            break;
        case SHUM_COMPILER_WARNING_HIGH:
            SHU_CompilerAddFlags("-Wall -Wall -Wextra -Wshadow -Wpedantic -Wconversion -Wnull-dereference -Wunused-result -fstack-protector-strong -Wpointer-arith -Wstrict-prototypes -Wmissing-prototypes Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wpointer-to-int-cast -Wint-to-pointer-cast");
            break;
        default:
            SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid warning level passed as parameter to compiler optimization.");
            break;
        }

        if (treatAsError)
        {
            SHU_CompilerAddFlags("-Werror");
        }
    }
    else
    {
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Compiler not configured. Cannot set debug optimization.");
    }
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name)
{
    if (name == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module begin.");
    }

    if (SHUI_MODULE_NAME.data != NULL)
    {
        SHUI_SDestroy(&SHUI_MODULE_NAME);
    }

    SHUI_MODULE_NAME = SHUI_SCreate(name);
}

void SHU_ModuleAddIncludeDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module add include directory");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&correctedDirectory, directory);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif
    SHUI_SLAdd(&SHUI_MODULE_INCLUDE_DIRECTORIES, correctedDirectory, SHUC_MAX_STRING_ARRAY_COUNT);
}

void SHU_ModuleAddSourcefile(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module add source file");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&correctedDirectory, file);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif
    SHUI_SLAdd((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES, correctedDirectory, SHUC_MAX_SOURCE_FILE_COUNT);
}

void SHU_ModuleAddSourceDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module add source directory.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(directory);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif

    SHUI_AddSourceDirectoryRecursive(SHUI_GetCurrentExecutableDirectory().data, correctedDirectory.data);
    SHUI_SDestroy(&correctedDirectory);
}

void SHU_ModuleCompile(const char *directory, char module)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module compile.");
    }

    if (SHUI_COMPILER_COMMAND.data == NULL)
    {
        SHUI_COMPILER_COMMAND = SHUI_SCreate(SHUM_HOST_COMPILER_COMMAND);
    }

#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("Starting to compile %s '%s'...", SHUM_MODULE_GET_STRING(module), SHUI_MODULE_NAME.data);
#endif

    SHU_CreateRelativeDirectory(directory);

    SHUI_String directoryStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    if (strlen(directory) != 0)
    {
        SHUI_SAppend(&directoryStr, directory);

#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
        SHUI_SReplace(&directoryStr, '/', '\\');
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
        SHU_LogError(SHUM_ERROR_UNKNOWN, "Invalid module passed as parameter to module compile.");
        break;
    }

    if (directoryStr.data != NULL)
    {
        SHUI_SDestroy(&directoryStr);
    }

    if (module == SHUM_MODULE_EXECUTABLE)
    {
        SHUI_SLClear(&SHUI_EXECUTABLE_LINK_DIRECTORIES);
        SHUI_SLClear(&SHUI_EXECUTABLE_LINKS);
    }

    SHUI_SLClear(&SHUI_MODULE_INCLUDE_DIRECTORIES);
    SHUI_SLClear((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES);

#ifndef SHUC_NO_MODULE_LOG
    SHU_LogInfo("%s '%s' successfully compiled.", SHUM_MODULE_GET_STRING(module), SHUI_MODULE_NAME.data);
#endif

    SHUI_SDestroy(&SHUI_MODULE_NAME);
}

void SHU_ModuleAddLibraryDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module set library directory.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&correctedDirectory, directory);
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif
    SHUI_SLAdd(&SHUI_EXECUTABLE_LINK_DIRECTORIES, correctedDirectory, SHUC_MAX_STRING_ARRAY_COUNT);
}

void SHU_ModuleLinkLibrary(const char *library)
{
    if (library == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module link library.");
    }

    SHUI_SLAdd(&SHUI_EXECUTABLE_LINKS, SHUI_SCreate(library), SHUC_MAX_STRING_ARRAY_COUNT);
}

#pragma endregion Module

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations
