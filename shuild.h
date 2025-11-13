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

#pragma once

#pragma region Platform Detection

#define SHUM_PLATFORM_UNKNOWN 0
#define SHUM_PLATFORM_WINDOWS 1
#define SHUM_PLATFORM_LINUX 2
#define SHUM_PLATFORM_MACOS 3

#if defined(_WIN32)
/// @brief Current platform specifier. Use it with SHUM_PLATFORM_<...> macros.
#define SHUM_PLATFORM SHUM_PLATFORM_WINDOWS
/// @brief Current platform name string.
#define SHUM_PLATFORM_STRING "WINDOWS"

#elif defined(__linux__)
/// @brief Current platform specifier. Use it with SHUM_PLATFORM_<...> macros.
#define SHUM_PLATFORM SHUM_PLATFORM_LINUX
/// @brief Platform name string.
#define SHUM_PLATFORM_STRING "LINUX"

#elif defined(__APPLE__) && defined(__MACH__)
/// @brief Current platform specifier. Use it with SHUM_PLATFORM_<...> macros.
#define SHUM_PLATFORM SHUM_PLATFORM_MACOS
/// @brief Platform name string.
#define SHUM_PLATFORM_STRING "MACOS"

#else
/// @brief Current platform specifier. Use it with SHUM_PLATFORM_<...> macros.
#define SHUM_PLATFORM SHUM_PLATFORM_UNKNOWN
/// @brief Platform name string.
#define SHUM_PLATFORM_STRING "UNKNOWN"
#endif

#if SHUM_PLATFORM == SHUM_PLATFORM_LINUX || SHUM_PLATFORM == SHUM_PLATFORM_MACOS
/// @brief Current platform is Unix-like.
#define SHUM_PLATFORM_UNIX 1

#define SHUM_PATH_DELIMETER_CHAR '/'
#define SHUM_PATH_DELIMETER_STR "/"
#else
/// @brief Current platform is not a Unix-like.
#define SHUM_PLATFORM_UNIX 0

#define SHUM_PATH_DELIMETER_CHAR '\\'
#define SHUM_PATH_DELIMETER_STR "\\"
#endif // Platform Detection

#pragma endregion Platform Detection

#pragma region Compiler Detection

#define SHUM_COMPILER_UNKNOWN 0
#define SHUM_COMPILER_CLANG 1
#define SHUM_COMPILER_GCC 2
#define SHUM_COMPILER_MSVC 3
#define SHUM_COMPILER_CLANGCL 4

#if defined(__clang__) && defined(_MSC_VER)
/// @brief Current compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_COMPILER SHUM_COMPILER_CLANGCL
/// @brief Compiler version number.
#define SHUM_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
/// @brief Compiler name string.
#define SHUM_COMPILER_STRING "CLANG-CL"

#elif defined(__clang__)

/// @brief Current compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_COMPILER SHUM_COMPILER_CLANG
/// @brief Compiler version number.
#define SHUM_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
/// @brief Compiler name string.
#define SHUM_COMPILER_STRING "CLANG"

#elif defined(_MSC_VER)

/// @brief Current compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_COMPILER SHUM_COMPILER_MSVC
/// @brief Compiler version number.
#define SHUM_COMPILER_VERSION _MSC_VER
/// @brief Compiler name string.
#define SHUM_COMPILER_STRING "MSVC"

#elif defined(__GNUC__)
/// @brief Current compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_COMPILER SHUM_COMPILER_GCC
/// @brief Compiler version number.
#define SHUM_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
/// @brief Compiler name string.
#define SHUM_COMPILER_STRING "GCC"

#else
/// @brief Current compiler specifier. Use it with SHUM_COMPILER_<...> macros.
#define SHUM_COMPILER SHUM_COMPILER_UNKNOWN
/// @brief Compiler version number.
#define SHUM_COMPILER_VERSION 0
/// @brief Compiler name string.
#define SHUM_COMPILER_STRING "UNKNOWN"
#endif // Compiler Detection

#pragma endregion Compiler Detection

#pragma region Shuild Declarations

#ifndef SHUM_MAX_STRING_ARRAY_COUNT
#define SHUM_MAX_STRING_ARRAY_COUNT 16
#endif

#ifndef SHUM_MAX_SOURCE_FILE_COUNT
#define SHUM_MAX_SOURCE_FILE_COUNT 256
#endif

#ifndef SHUM_MAX_COMMAND_BUFFER_SIZE
#define SHUM_MAX_COMMAND_BUFFER_SIZE 4096
#endif

#ifndef SHUM_MAX_MESSAGE_BUFFER_SIZE
#define SHUM_MAX_MESSAGE_BUFFER_SIZE 4096
#endif

#ifndef SHUM_MAX_PATH_SIZE
#define SHUM_MAX_PATH_SIZE 256
#endif

#define SHUM_ERROR 1
#define SHUM_ERROR_NULL 2
#define SHUM_ERROR_INDEX 3
#define SHUM_ERROR_UNKNOWN 4
#define SHUM_ERROR_INTERNAL 5

#define SHUM_MODULE_EXECUTABLE 0
#define SHUM_MODULE_LIBRARY_STATIC 1
#define SHUM_MODULE_LIBRARY_DYNAMIC 2

#define SHUM_COLOR_RED(string) "\x1b[31m" string "\x1b[0m"
#define SHUM_COLOR_GREEN(string) "\x1b[32m" string "\x1b[0m"
#define SHUM_COLOR_YELLOW(string) "\x1b[33m" string "\x1b[0m"
#define SHUM_COLOR_BLUE(string) "\x1b[34m" string "\x1b[0m"

#pragma region General

/// @brief Internal command runner function.
/// @param command Command to run with system. (eg. clang example.c -o example)
void SHU_Run(const char *commandFormat, ...);

/// @brief Creates a directory relative to current executable if the directory doesn't exists.
/// @param directory Directory to create (eg. resources/)
void SHU_CreateRelativeDirectory(const char *directory);

/// @brief Deletes a file.
/// @param file File to delete. Relative to current executable.
void SHU_DeleteFile(const char *file);

/// @brief Copies a file.
/// @param file File to copy, relative to current executable.
/// @param directory Directory to copy file, relative to current executable.
void SHU_CopyFile(const char *file, const char *directory);

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

/// @brief Configures the compiler to be used for compiling modules.
/// @param compiler Compiler specifier. Use with SHUM_COMPILER_<...> macros.
/// @param compilerCommand Command to invoke the compiler. (eg. clang)
void SHU_CompilerConfigure(char compiler, const char *compilerCommand);

/// @brief Tries to configure the compiler by the command of it by checking regular commands.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc)
void SHU_CompilerTryConfigure(const char *compilerCommand);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add. Can include multiple flags separated by spaces as you want. (eg. -DFOO=31)
void SHU_CompilerAddFlags(const char *flags);

/// @brief Clears and sets the compiler flags, replacing all existing ones.
/// @param flags Flags to set. Can include multiple flags separated by spaces as you want.
void SHU_CompilerSetFlags(const char *flags);

#pragma endregion Compiler

#pragma region Module

/// @brief Begins a new module with the given name. A module can be an executable or a library.
/// @param name Name of the module. Which will be used also for output file name. (eg. myLibName, myAppName)
void SHU_ModuleBegin(const char *name);

/// @brief Adds include directories to the module. Max count is defined as `SHUM_MAX_STRING_ARRAY_COUNT`.
/// @param directory Include directory to add to the current module. (eg. include/)
void SHU_ModuleAddIncludeDirectory(const char *directory);

/// @brief Adds source directories to the module. Max count is defined as `SHUM_MAX_STRING_ARRAY_COUNT`.
/// @param directory Source directory to add to the current module. (eg. src/)
void SHU_ModuleAddSourceDirectory(const char *directory);

/// @brief Adds source files to the module. Max count is defined as `SHUM_MAX_STRING_ARRAY_COUNT`.
/// @param file Single file to add to the current module. (eg. source.c)
void SHU_ModuleAddSourcefile(const char *file);

// todo make static and dynamic configuration

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name (eg. build/)
/// @param module Current module mode. Use with SHUM_MODULE_<...> macros. (eg. SHUM_MODULE_LIBRARY_STATIC)
void SHU_ModuleCompile(const char *directory, char module);

/// @brief Sets the library search directory for current executable. Practical only if the current module is an executable.
/// @param directory Directory to search for libraries. (eg. build/arc/)
void SHU_ModuleSetLibraryDirectory(const char *directory);

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

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
#include <windows.h>
#elif SHUM_PLATFORM == SHUM_PLATFORM_LINUX
#include <unistd.h>
#elif SHUM_PLATFORM == SHUM_PLATFORM_MACOS
#include <mach-o/dyld.h>
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
    SHUI_String data[SHUM_MAX_STRING_ARRAY_COUNT];
} SHUI_StringList;

typedef struct SHUI_StringListSource
{
    size_t count;
    SHUI_String data[SHUM_MAX_SOURCE_FILE_COUNT];
} SHUI_StringListSource;

static SHUI_String SHUI_CURRENT_EXECUTABLE_DIRECTORY = {0};

static char SHUI_COMPILER = SHUM_COMPILER_UNKNOWN;
static SHUI_String SHUI_COMPILER_COMMAND = {0};
static SHUI_StringList SHUI_COMPILER_FLAGS = {0};

static SHUI_String SHUI_MODULE_NAME = {0};
static SHUI_StringList SHUI_MODULE_INCLUDE_DIRECTORIES = {0};
static SHUI_StringListSource SHUI_MODULE_SOURCE_FILES = {0};

static SHUI_String SHUI_EXECUTABLE_LINK_DIRECTORY = {0};
static SHUI_StringList SHUI_EXECUTABLE_LINKS = {0};

// todo add build targets

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
static void SHUI_SLAdd(SHUI_StringList *list, SHUI_String string)
{
    if (list == NULL || string.data == NULL || string.data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string list add.");
    }

    if (list->count >= SHUM_MAX_STRING_ARRAY_COUNT)
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

/// @brief Gets the current executable directory and sets it to SHUI_CURRENT_EXECUTABLE_DIRECTORY.
/// @return Current executable directory string.
static SHUI_String SHUI_GetCurrentExecutableDirectory()
{
    if (SHUI_CURRENT_EXECUTABLE_DIRECTORY.data == NULL)
    {
        char pathBuffer[SHUM_MAX_PATH_SIZE] = {0};

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
        GetModuleFileName(NULL, pathBuffer, sizeof(pathBuffer));
#elif SHUM_PLATFORM == SHUM_PLATFORM_UNIX
        readlink("/proc/self/exe", buffer, sizeof(buffer));
#endif

        size_t pathLength = strlen(pathBuffer);

        while (pathBuffer[--pathLength] != SHUM_PATH_DELIMETER_CHAR)
        {
            pathBuffer[pathLength] = '\0';
        }
        pathLength++;

        SHUI_CURRENT_EXECUTABLE_DIRECTORY = SHUI_SCreate(pathBuffer);
    }

    return SHUI_CURRENT_EXECUTABLE_DIRECTORY;
}

static void SHUI_CompileExecutable(SHUI_String directory)
{
    // todo cross compiler commands support

    char includeBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t includeBufferIndex = 0;
    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(includeBuffer + includeBufferIndex, sizeof(includeBuffer) - includeBufferIndex, "-I%s ", SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        includeBufferIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    char sourceBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t sourceBufferIndex = 0;
    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(sourceBuffer + sourceBufferIndex, sizeof(sourceBuffer) - sourceBufferIndex, "%s ", SHUI_MODULE_SOURCE_FILES.data[i].data);
        sourceBufferIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    char linkBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t linkBufferIndex = 0;
    for (size_t i = 0; i < SHUI_EXECUTABLE_LINKS.count; i++)
    {
        snprintf(linkBuffer + linkBufferIndex, sizeof(linkBuffer) - linkBufferIndex, "-l%s ", SHUI_EXECUTABLE_LINKS.data[i].data);
        linkBufferIndex += SHUI_EXECUTABLE_LINKS.data[i].length + 3;
    }

    char flagBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t flagBufferIndex = 0;
    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(flagBuffer + flagBufferIndex, sizeof(flagBuffer) - flagBufferIndex, "%s ", SHUI_COMPILER_FLAGS.data[i].data);
        flagBufferIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    SHU_Run("%s %s %s %s%s %s %s -o%s%s%s",
            SHUI_COMPILER_COMMAND.data,
            includeBuffer,
            sourceBuffer,
            SHUI_EXECUTABLE_LINK_DIRECTORY.data == NULL ? "" : "-L",
            SHUI_EXECUTABLE_LINK_DIRECTORY.data == NULL ? "" : SHUI_EXECUTABLE_LINK_DIRECTORY.data,
            linkBuffer,
            flagBuffer,
            directory.data,
            SHUI_MODULE_NAME.data,
            SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".exe" : "");

    SHU_LogInfo("Executable '%s' successfully compiled.", SHUI_MODULE_NAME.data);
}

static void SHUI_CompileLibraryStatic(SHUI_String directory)
{
    // commands for flags
    char commandBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex, sizeof(commandBufferIndex) - commandBufferIndex, "%s ", SHUI_COMPILER_FLAGS.data[i].data);
        commandBufferIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex, sizeof(commandBuffer) - commandBufferIndex, "-I%s ", SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        commandBufferIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    // todo .o file directory

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        SHU_Run("%s -c %s -o %.*so %s",
                SHUI_COMPILER_COMMAND.data,
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                commandBuffer);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));
    commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex, sizeof(commandBuffer) - commandBufferIndex, "%.*so ", (int)SHUI_MODULE_SOURCE_FILES.data[i].length - 1, SHUI_MODULE_SOURCE_FILES.data[i].data);
        commandBufferIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    SHU_Run("llvm-ar rcs %s%s%s %s", directory.data, SHUI_MODULE_NAME.data, SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".lib" : ".a", commandBuffer);

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("del /F /Q %s", commandBuffer);
#elif SHUM_PLATFORM_UNIX
    SHU_Run("rm -rf %s", commandBuffer);
#endif

    SHU_LogInfo("Static Library '%s' successfully compiled.", SHUI_MODULE_NAME.data);
}

static void SHUI_CompileLibraryDynamic(SHUI_String directory)
{
    // commands for flags
    char commandBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};
    size_t commandBufferIndex = 0;

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex, sizeof(commandBufferIndex) - commandBufferIndex, "%s ", SHUI_COMPILER_FLAGS.data[i].data);
        commandBufferIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex, sizeof(commandBuffer) - commandBufferIndex, "-I%s ", SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        commandBufferIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        SHU_Run("%s -c -fPIC %s -o %.*so %s",
                SHUI_COMPILER_COMMAND.data,
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                SHUI_MODULE_SOURCE_FILES.data[i].length - 1,
                SHUI_MODULE_SOURCE_FILES.data[i].data,
                commandBuffer);
    }

    // commands for objects
    memset(commandBuffer, 0, sizeof(commandBuffer));

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(commandBuffer + commandBufferIndex, sizeof(commandBuffer) - commandBufferIndex, "%.*so ", (int)SHUI_MODULE_SOURCE_FILES.data[i].length - 1, SHUI_MODULE_SOURCE_FILES.data[i].data);
        commandBufferIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    SHU_Run("%s -shared -o %s%s%s %s", SHUI_COMPILER_COMMAND.data, directory.data, SHUI_MODULE_NAME.data, SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS ? ".dll" : ".so", commandBuffer);

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("del /F /Q %s", commandBuffer);
#elif SHUM_PLATFORM_UNIX
    SHU_Run("rm -rf %s", commandBuffer);
#endif

    SHU_LogInfo("Dynamic Library '%s' successfully compiled.", SHUI_MODULE_NAME.data);
}

#pragma endregion Internals

#pragma region General

void SHU_Run(const char *commandFormat, ...)
{
    if (commandFormat == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to run.");
    }

    char commandBuffer[SHUM_MAX_COMMAND_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, commandFormat);
    vsnprintf(commandBuffer, sizeof(commandBuffer), commandFormat, args);
    va_end(args);

    SHU_LogInfo("Executing command : '%s'", commandBuffer);

    int result = system(commandBuffer);

    if (result != 0)
    {
        SHU_LogError(result, "Last executed command failed with exit code %d.", result);
    }
}

void SHU_CreateRelativeDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to create directory.");
    }

    SHUI_String directoryStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    if (strlen(directory) == 0)
    {
        return;
    }

    SHUI_SAppend(&directoryStr, directory);

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&directoryStr, '/', '\\');
    SHU_Run("if not exist %s mkdir %s", directoryStr.data, directoryStr.data);
#elif SHUM_PLATFORM_UNIX
    SHU_Run("mkdir -p %s" directoryStr.data);
#endif

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

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHU_Run("del /F /Q %s", fileStr.data);
#elif SHUM_PLATFORM_UNIX
    SHU_Run("rm -rf %s", fileStr.data);
#endif

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

    SHUI_String directoryStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_String fileStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    SHUI_SAppend(&directoryStr, directory);
    SHUI_SAppend(&fileStr, file);

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&directoryStr, '/', '\\');
    SHUI_SReplace(&fileStr, '/', '\\');
    SHU_Run("copy /Y %s %s", fileStr.data, directoryStr.data);
#elif SHUM_PLATFORM_UNIX
    SHU_Run("cp -r %s %s", fileStr.data, directoryStr.data);
#endif

    SHUI_SDestroy(&directoryStr);
    SHUI_SDestroy(&fileStr);
}

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    if (header == NULL || format == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to log.");
    }

    char messageBuffer[SHUM_MAX_MESSAGE_BUFFER_SIZE] = {0};

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

    if (strcmp(compilerCommand, "clang") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_CLANG, compilerCommand);
    }
    else if (strcmp(compilerCommand, "gcc") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_GCC, compilerCommand);
    }
    else if (strcmp(compilerCommand, "cl") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_MSVC, compilerCommand);
    }
    else if (strcmp(compilerCommand, "clang-cl") == 0)
    {
        SHU_CompilerConfigure(SHUM_COMPILER_CLANGCL, compilerCommand);
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
        SHUI_SLAdd(&SHUI_COMPILER_FLAGS, SHUI_SCreate(flags));
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
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif
    SHUI_SLAdd(&SHUI_MODULE_INCLUDE_DIRECTORIES, correctedDirectory);
}

void SHU_ModuleAddSourcefile(const char *file)
{
    if (file == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module add source file");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&correctedDirectory, file);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif
    SHUI_SLAdd((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES, correctedDirectory);
}

void SHU_ModuleAddSourceDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module add source directory.");
    }

    SHUI_String correctedDirectory = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&correctedDirectory, directory);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&correctedDirectory, '/', '\\');
#endif

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    WIN32_FIND_DATAA ffd = {0};
    char pattern[SHUM_MAX_PATH_SIZE] = {0};

    snprintf(pattern, sizeof(pattern), "%s*.c", correctedDirectory.data);
    HANDLE hFind = FindFirstFileA(pattern, &ffd);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Error value returned from internal file search API.");
    }

    do
    {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            SHUI_String newFile = SHUI_SCreate(correctedDirectory.data);
            SHUI_SAppend(&newFile, ffd.cFileName);
            SHUI_SLAdd((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES, newFile);
        }
    } while (FindNextFileA(hFind, &ffd));
    FindClose(hFind);

#else // todo cross platform
    DIR *searchDirectory = opendir(correctedDirectory.data);

    if (searchDirectory == NULL)
    {
        SHU_LogError(SHUM_ERROR_INTERNAL, "Error value returned from internal file search API.");
    }

    struct dirent *entry;
    while ((entry = readdir(searchDirectory)) != NULL)
    {
        if (strstr(entry->d_name, ".c") != NULL)
        {
            SHUI_String newFile = SHUI_SCreate(correctedDirectory.data);
            SHUI_SAppend(&newFile, entry->d_name);
            SHUI_SLAdd(&SHUI_MODULE_SOURCE_FILES, newFile);
        }
    }
    closedir(searchDirectory);
#endif

    SHUI_SDestroy(&correctedDirectory);
}

void SHU_ModuleCompile(const char *directory, char module)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module compile.");
    }

    SHU_CreateRelativeDirectory(directory);

    SHUI_String directoryStr = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);

    if (strlen(directory) != 0)
    {
        SHUI_SAppend(&directoryStr, directory);

#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
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
        SHUI_SDestroy(&SHUI_EXECUTABLE_LINK_DIRECTORY);
        SHUI_SLClear(&SHUI_EXECUTABLE_LINKS);
    }

    SHUI_SLClear(&SHUI_MODULE_INCLUDE_DIRECTORIES);
    SHUI_SLClear((SHUI_StringList *)&SHUI_MODULE_SOURCE_FILES);

    SHUI_SDestroy(&SHUI_MODULE_NAME);
}

// todo maybe add linking tree for libraries and executables

void SHU_ModuleSetLibraryDirectory(const char *directory)
{
    if (directory == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module set library directory.");
    }

    if (SHUI_EXECUTABLE_LINK_DIRECTORY.data != NULL)
    {
        SHUI_SDestroy(&SHUI_EXECUTABLE_LINK_DIRECTORY);
    }

    SHUI_EXECUTABLE_LINK_DIRECTORY = SHUI_SCreate(SHUI_GetCurrentExecutableDirectory().data);
    SHUI_SAppend(&SHUI_EXECUTABLE_LINK_DIRECTORY, directory);
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
    SHUI_SReplace(&SHUI_EXECUTABLE_LINK_DIRECTORY, '/', '\\');
#endif
}

void SHU_ModuleLinkLibrary(const char *library)
{
    if (library == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to module link library.");
    }

    SHUI_SLAdd(&SHUI_EXECUTABLE_LINKS, SHUI_SCreate(library));
}

#pragma endregion Module

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations