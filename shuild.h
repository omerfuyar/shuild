#pragma once

#pragma region Platform Detection

#define SHU_PLATFORM_UNKNOWN 0
#define SHU_PLATFORM_WINDOWS 1
#define SHU_PLATFORM_LINUX 2
#define SHU_PLATFORM_MACOS 3

#if defined(_WIN32)
/// @brief Current platform specifier. Use it with SHU_PLATFORM_<...> macros.
#define SHU_PLATFORM SHU_PLATFORM_WINDOWS
/// @brief Current platform name string.
#define SHU_PLATFORM_STRING "WINDOWS"

#elif defined(__linux__)
/// @brief Current platform specifier. Use it with SHU_PLATFORM_<...> macros.
#define SHU_PLATFORM SHU_PLATFORM_LINUX
/// @brief Platform name string.
#define SHU_PLATFORM_STRING "LINUX"

#elif defined(__APPLE__) && defined(__MACH__)
/// @brief Current platform specifier. Use it with SHU_PLATFORM_<...> macros.
#define SHU_PLATFORM SHU_PLATFORM_MACOS
/// @brief Platform name string.
#define SHU_PLATFORM_STRING "MACOS"

#else
/// @brief Current platform specifier. Use it with SHU_PLATFORM_<...> macros.
#define SHU_PLATFORM SHU_PLATFORM_UNKNOWN
/// @brief Platform name string.
#define SHU_PLATFORM_STRING "UNKNOWN"
#endif

#if SHU_PLATFORM == SHU_PLATFORM_LINUX || SHU_PLATFORM == SHU_PLATFORM_MACOS
/// @brief Current platform is Unix-like.
#define SHU_PLATFORM_UNIX 1

#else
/// @brief Current platform is not a Unix-like.
#define SHU_PLATFORM_UNIX 0
#endif // Platform Detection

#pragma endregion Platform Detection

#pragma region Compiler Detection

#define SHU_COMPILER_UNKNOWN 0
#define SHU_COMPILER_CLANG 1
#define SHU_COMPILER_GCC 2
#define SHU_COMPILER_MSVC 3
#define SHU_COMPILER_CLANGCL 4

#if defined(__clang__) && defined(_MSC_VER)
/// @brief Current compiler specifier. Use it with SHU_COMPILER_<...> macros.
#define SHU_COMPILER SHU_COMPILER_CLANGCL
/// @brief Compiler version number.
#define SHU_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
/// @brief Compiler name string.
#define SHU_COMPILER_STRING "CLANG-CL"

#elif defined(__clang__)

/// @brief Current compiler specifier. Use it with SHU_COMPILER_<...> macros.
#define SHU_COMPILER SHU_COMPILER_CLANG
/// @brief Compiler version number.
#define SHU_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
/// @brief Compiler name string.
#define SHU_COMPILER_STRING "CLANG"

#elif defined(_MSC_VER)

/// @brief Current compiler specifier. Use it with SHU_COMPILER_<...> macros.
#define SHU_COMPILER SHU_COMPILER_MSVC
/// @brief Compiler version number.
#define SHU_COMPILER_VERSION _MSC_VER
/// @brief Compiler name string.
#define SHU_COMPILER_STRING "MSVC"

#elif defined(__GNUC__)
/// @brief Current compiler specifier. Use it with SHU_COMPILER_<...> macros.
#define SHU_COMPILER SHU_COMPILER_GCC
/// @brief Compiler version number.
#define SHU_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
/// @brief Compiler name string.
#define SHU_COMPILER_STRING "GCC"

#else
/// @brief Current compiler specifier. Use it with SHU_COMPILER_<...> macros.
#define SHU_COMPILER SHU_COMPILER_UNKNOWN
/// @brief Compiler version number.
#define SHU_COMPILER_VERSION 0
/// @brief Compiler name string.
#define SHU_COMPILER_STRING "UNKNOWN"
#endif // Compiler Detection

#pragma endregion Compiler Detection

#pragma region Shuild Declarations

#define SHUI_MESSAGE_BUFFER_SIZE 512

#define SHU_COLOR_GREEN(string) "\x1b[32m" string "\x1b[0m"
#define SHU_COLOR_YELLOW(string) "\x1b[33m" string "\x1b[0m"
#define SHU_COLOR_RED(string) "\x1b[31m" string "\x1b[0m"

#pragma region General

/// @brief Internal variadic logging function.
/// @param terminate Exit code if not 0.
/// @param header Header of the log.
/// @param format Formatted message of the log.
void SHU_Log(int terminate, const char *header, const char *format, ...);

#define SHU_LogInfo(format, ...)                                    \
    do                                                              \
    {                                                               \
        SHU_Log(0, SHU_COLOR_GREEN("INFO"), format, ##__VA_ARGS__); \
    } while (0)

#define SHU_LogWarning(format, ...)                                     \
    do                                                                  \
    {                                                                   \
        SHU_Log(0, SHU_COLOR_YELLOW("WARNING"), format, ##__VA_ARGS__); \
    } while (0)

#define SHU_LogError(code, format, ...)                               \
    do                                                                \
    {                                                                 \
        SHU_Log(code, SHU_COLOR_RED("ERROR"), format, ##__VA_ARGS__); \
    } while (0)

#pragma endregion General

#pragma region Compiler

/// @brief
/// @param compiler
/// @param compilerCommand
void SHU_CompilerConfigure(char compiler, const char *compilerCommand);

/// @brief
/// @param flags
void SHU_CompilerAddFlags(const char *flags);

/// @brief
/// @param flags
void SHU_CompilerSetFlags(const char *flags);

#pragma endregion Compiler

#pragma region Module

/// @brief
/// @param name
void SHU_ModuleBegin(const char *name);

/// @brief
/// @param directory
void SHU_ModuleAddIncludeDirectory(const char *directory);

/// @brief
/// @param file
void SHU_ModuleAddSourcefile(const char *file);

/// @brief
/// @param directory
void SHU_ModuleAddSourceDirectory(const char *directory);

#pragma endregion Module

#pragma region Library

/// @brief
/// @param directory
void SHU_LibraryCompile(const char *directory);

#pragma endregion Library

#pragma region Executable

/// @brief
/// @param library
void SHU_ExecutableLink(const char *library);

/// @brief
/// @param directory
void SHU_ExecutableCompile(const char *directory);

#pragma endregion Executable

#pragma endregion Shuild Declarations

#pragma region Shuild Implementations

#ifdef SHUILD_IMPLEMENTATION

#define SHUI_MAX_STRING_ARRAY_COUNT 16
#define SHUI_COMPILER_COMMAND_BUFFER 4096

#define SHUI_ERROR_NULL 1
#define SHUI_ERROR_INDEX 2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#pragma region Internals

typedef struct SHUI_String
{
    char *data;
    size_t length;
} SHUI_String;

typedef struct SHUI_StringList
{
    SHUI_String data[SHUI_MAX_STRING_ARRAY_COUNT];
    size_t count;
} SHUI_StringList;

static char SHUI_COMPILER = SHU_COMPILER_UNKNOWN;
static SHUI_String SHUI_COMPILER_COMMAND = {0};
static SHUI_StringList SHUI_COMPILER_FLAGS = {0};

static SHUI_String SHUI_MODULE_NAME = {0};
static SHUI_StringList SHUI_MODULE_INCLUDE_DIRECTORIES = {0};
static SHUI_StringList SHUI_MODULE_SOURCE_DIRECTORIES = {0};
static SHUI_StringList SHUI_MODULE_SOURCE_FILES = {0};
static SHUI_StringList SHUI_EXECUTABLE_LINKS = {0};

/// @brief Creates a heap string from a string for internal usage.
/// @param string Null terminated string.
/// @return Created heap string.
static SHUI_String SHUI_SCreate(const char *string)
{
    if (string == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Null pointer passed as parameter to string create.");
    }

    const size_t stringLength = strlen(string);

    if (stringLength == 0)
    {
        SHU_LogError(SHUI_ERROR_INDEX, "String length to create a heap copy can not be 0.");
    }

    SHUI_String createdString = {0};

    createdString.length = stringLength;
    createdString.data = (char *)malloc(createdString.length + 1);

    if (createdString.data == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Malloc error while creating heap string.");
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
        SHU_LogError(SHUI_ERROR_NULL, "Null pointer passed as parameter to string destroy.");
    }

    free(string->data);

    string->data = NULL;
    string->length = 0;
}

/// @brief Replaces all occurrences of find with replace in a string.
/// @param string String to edit.
/// @param find Character to find and replace.
/// @param replace Character to replace with.
static void SHUI_SReplace(SHUI_String *string, char find, char replace)
{
    for (size_t i = 0; i < string->length; i++)
    {
        if (string->data[i] == find)
        {
            string->data[i] = replace;
        }
    }
}

/// @brief Add string to the string list.
/// @param list List to add string to
/// @param data String to add.
static void SHUI_SLAdd(SHUI_StringList *list, SHUI_String string)
{
    if (list == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Null pointer passed as parameter to string list add.");
    }

    if (list->count >= SHUI_MAX_STRING_ARRAY_COUNT)
    {
        SHU_LogError(SHUI_ERROR_INDEX, "List is full.");
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
        SHU_LogError(SHUI_ERROR_NULL, "Null list pointer passed as parameter to string list clear.");
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

/// @brief Internal command runner function.
/// @param command Command to run with system.
static void SHUI_Run(const char *commandFormat, ...)
{
    if (commandFormat == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Null pointer passed as parameter to run.");
    }

    char commandBuffer[SHUI_MESSAGE_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, commandFormat);
    vsnprintf(commandBuffer, sizeof(commandBuffer), commandFormat, args);
    va_end(args);

    SHU_LogInfo("Executing command : '%s'", commandBuffer);

    int result = system(commandBuffer);

    if (result != 0)
    {
        SHU_LogError(result, "Last executed command failed");
    }
}

#pragma endregion Internals

#pragma region General

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    char messageBuffer[SHUI_MESSAGE_BUFFER_SIZE] = {0};

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
    if (SHUI_COMPILER_COMMAND.data != NULL)
    {
        SHUI_SDestroy(&SHUI_COMPILER_COMMAND);
    }

    SHUI_COMPILER = compiler;
    SHUI_COMPILER_COMMAND = SHUI_SCreate(compilerCommand);
}

void SHU_CompilerAddFlags(const char *flags)
{
    SHUI_SLAdd(&SHUI_COMPILER_FLAGS, SHUI_SCreate(flags));
}

void SHU_CompilerSetFlags(const char *flags)
{
    SHUI_SLClear(&SHUI_COMPILER_FLAGS);

    if (strlen(flags) != 0)
    {
        SHUI_SLAdd(&SHUI_COMPILER_FLAGS, SHUI_SCreate(flags));
    }
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name)
{
    if (SHUI_MODULE_NAME.data != NULL)
    {
        SHUI_SDestroy(&SHUI_MODULE_NAME);
    }

    SHUI_MODULE_NAME = SHUI_SCreate(name);
}

void SHU_ModuleAddIncludeDirectory(const char *directory)
{
    SHUI_SLAdd(&SHUI_MODULE_INCLUDE_DIRECTORIES, SHUI_SCreate(directory));
}

void SHU_ModuleAddSourcefile(const char *file)
{
    SHUI_SLAdd(&SHUI_MODULE_SOURCE_FILES, SHUI_SCreate(file));
}

void SHU_ModuleAddSourceDirectory(const char *directory)
{
    SHUI_SLAdd(&SHUI_MODULE_SOURCE_DIRECTORIES, SHUI_SCreate(directory));
}

#pragma endregion Module

#pragma region Library

void SHU_LibraryCompile(const char *directory)
{
    SHUI_String directoryStr = SHUI_SCreate(directory);

#if SHU_PLATFORM == SHU_PLATFORM_WINDOWS
    SHUI_SReplace(&directoryStr, '/', '\\');
    SHUI_Run("if not exist %s mkdir %s", directoryStr.data, directoryStr.data);
#elif SHU_PLATFORM_UNIX
    SHUI_Run("mkdir -p %s" directory);
#endif

    char finalCommand[SHUI_COMPILER_COMMAND_BUFFER] = {0};
    size_t compilerCommandIndex = 0;

    snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "%s ", SHUI_COMPILER_COMMAND.data);
    compilerCommandIndex += SHUI_COMPILER_COMMAND.length + 1;

    // todo cross compiler commands support

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "-I%s ", SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        compilerCommandIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_DIRECTORIES.count; i++)
    {
        // todo find files in dir
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "%s ", SHUI_MODULE_SOURCE_FILES.data[i].data);
        compilerCommandIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "%s ", SHUI_COMPILER_FLAGS.data[i].data);
        compilerCommandIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "-o%s%s ", directoryStr.data, SHUI_MODULE_NAME.data);
    compilerCommandIndex += directoryStr.length + 3;

    SHUI_SDestroy(&directoryStr);

    SHUI_Run(finalCommand);

    SHUI_SLClear(&SHUI_MODULE_INCLUDE_DIRECTORIES);
    SHUI_SLClear(&SHUI_MODULE_SOURCE_DIRECTORIES);
    SHUI_SLClear(&SHUI_MODULE_SOURCE_FILES);

    SHU_LogInfo("Library '%s' successfully compiled.", SHUI_MODULE_NAME.data);

    SHUI_SDestroy(&SHUI_MODULE_NAME);
}

#pragma endregion Library

#pragma region Executable

void SHU_ExecutableLink(const char *library)
{
    SHUI_SLAdd(&SHUI_EXECUTABLE_LINKS, SHUI_SCreate(library));
}

void SHU_ExecutableCompile(const char *directory)
{
    SHUI_String directoryStr = SHUI_SCreate(directory);

#if SHU_PLATFORM == SHU_PLATFORM_WINDOWS
    SHUI_SReplace(&directoryStr, '/', '\\');
    SHUI_Run("if not exist %s mkdir %s", directoryStr.data, directoryStr.data);
#elif SHU_PLATFORM_UNIX
    SHUI_Run("mkdir -p %s" directory);
#endif

    char finalCommand[SHUI_COMPILER_COMMAND_BUFFER] = {0};
    size_t compilerCommandIndex = 0;

    snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "%s ", SHUI_COMPILER_COMMAND.data);
    compilerCommandIndex += SHUI_COMPILER_COMMAND.length + 1;

    // todo cross compiler commands support

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "-I%s ", SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        compilerCommandIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_DIRECTORIES.count; i++)
    {
        // todo find files in dir
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "%s ", SHUI_MODULE_SOURCE_FILES.data[i].data);
        compilerCommandIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_EXECUTABLE_LINKS.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "-L%s ", SHUI_EXECUTABLE_LINKS.data[i].data);
        compilerCommandIndex += SHUI_EXECUTABLE_LINKS.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "%s ", SHUI_COMPILER_FLAGS.data[i].data);
        compilerCommandIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    snprintf(finalCommand + compilerCommandIndex, sizeof(finalCommand) - compilerCommandIndex, "-o%s%s%s ", directoryStr.data, SHUI_MODULE_NAME.data, SHU_PLATFORM == SHU_PLATFORM_WINDOWS ? ".exe" : "");
    compilerCommandIndex += directoryStr.length + 3;

    SHUI_SDestroy(&directoryStr);

    SHUI_Run(finalCommand);

    SHUI_SLClear(&SHUI_MODULE_INCLUDE_DIRECTORIES);
    SHUI_SLClear(&SHUI_MODULE_SOURCE_FILES);
    SHUI_SLClear(&SHUI_MODULE_SOURCE_DIRECTORIES);
    SHUI_SLClear(&SHUI_EXECUTABLE_LINKS);

    SHU_LogInfo("Executable '%s' successfully compiled.", SHUI_MODULE_NAME.data);

    SHUI_SDestroy(&SHUI_MODULE_NAME);
}

#pragma endregion Executable

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations