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
/// @param compilerCommand
void SHU_CompilerConfigure(const char *compilerCommand);

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

#define SHUI_ERROR_NULL 1
#define SHUI_ERROR_INDEX 2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct SHUI_String
{
    char *data;
    size_t length;
} SHUI_String;

typedef struct SHUI_StringList
{
    SHUI_String *data[SHUI_MAX_STRING_ARRAY_COUNT];
    size_t count;
} SHUI_StringList;

static SHUI_String SHUI_COMPILER_COMMAND = {0};
static SHUI_String SHUI_COMPILER_FLAGS = {0};

static SHUI_String SHUI_COMPILE_NAME = {0};
static SHUI_StringList SHUI_COMPILE_INCLUDE_DIRECTORIES = {0};
static SHUI_StringList SHUI_COMPILE_SOURCE_DIRECTORIES = {0};
static SHUI_StringList SHUI_COMPILE_SOURCE_FILES = {0};
static SHUI_StringList SHUI_COMPILE_LINKS = {0};

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

/// @brief String concatenation function. Reallocates the first string parameter.
/// @param string String to add other string to.
/// @param other Other string to add.
static void SHUI_SConcat(SHUI_String *string, SHUI_String other)
{
    if (string == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Null pointer passed as parameter to string concat.");
    }

    string->data = (char *)realloc(string->data, string->length + other.length + 1);

    if (string->data == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Realloc error while concating strings.");
    }

    memcpy(string->data + string->length, other.data, other.length);

    string->length = string->length + other.length;
    string->data[string->length] = '\0';
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

    list->data[list->count] = &string;

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
        if (list->data[i]->data != NULL)
        {
            SHUI_SDestroy(list->data[i]);
        }
    }

    list->count = 0;
}

/// @brief Internal command runner function.
/// @param command Command to run with system.
static void SHUI_Run(const char *command)
{
    if (command == NULL)
    {
        SHU_LogError(SHUI_ERROR_NULL, "Null pointer passed as parameter to run.");
    }

    SHU_LogInfo("Executing command : '%s'", command);

    int result = system(command);

    if (result != 0)
    {
        SHU_LogError(result, "Last executed command failed");
    }
}

#pragma region General

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    char messageBuffer[SHUI_MESSAGE_BUFFER_SIZE] = {0};

    va_list args;
    va_start(args, format);
    vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
    va_end(args);

    printf("[%s] : %s", header, messageBuffer);

    if (terminate != 0)
    {
        exit(terminate);
    }
}

#pragma endregion General

#pragma region Compiler

void SHU_CompilerConfigure(const char *compilerCommand)
{
    if (SHUI_COMPILER_COMMAND.data != NULL)
    {
        SHUI_SDestroy(&SHUI_COMPILER_COMMAND);
    }

    SHUI_COMPILER_COMMAND = SHUI_SCreate(compilerCommand);
}

void SHU_CompilerAddFlags(const char *flags)
{
    if (SHUI_COMPILER_FLAGS.data == NULL)
    {
        SHUI_COMPILER_FLAGS = SHUI_SCreate(flags);
    }
    else
    {
        SHUI_String tempFlags = SHUI_SCreate(flags);
        SHUI_SConcat(&SHUI_COMPILER_FLAGS, tempFlags);
        SHUI_SDestroy(&tempFlags);
    }
}

void SHU_CompilerSetFlags(const char *flags)
{
    if (SHUI_COMPILER_FLAGS.data != NULL)
    {
        SHUI_SDestroy(&SHUI_COMPILER_FLAGS);
    }

    SHUI_COMPILER_FLAGS = SHUI_SCreate(flags);
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name)
{
    if (SHUI_COMPILE_NAME.data != NULL)
    {
        SHUI_SDestroy(&SHUI_COMPILE_NAME);
    }

    SHUI_COMPILE_NAME = SHUI_SCreate(name);
}

void SHU_ModuleAddIncludeDirectory(const char *directory)
{
    SHUI_SLAdd(&SHUI_COMPILE_INCLUDE_DIRECTORIES, SHUI_SCreate(directory));
}

void SHU_ModuleAddSourcefile(const char *file)
{
    SHUI_SLAdd(&SHUI_COMPILE_SOURCE_FILES, SHUI_SCreate(file));
}

void SHU_ModuleAddSourceDirectory(const char *directory)
{
    SHUI_SLAdd(&SHUI_COMPILE_SOURCE_DIRECTORIES, SHUI_SCreate(directory));
}

#pragma endregion Module

#pragma region Library

void SHU_LibraryCompile(const char *directory)
{
    SHUI_SLClear(&SHUI_COMPILE_INCLUDE_DIRECTORIES);
    SHUI_SLClear(&SHUI_COMPILE_SOURCE_FILES);
    SHUI_SLClear(&SHUI_COMPILE_SOURCE_DIRECTORIES);

    //...
}

#pragma endregion Library

#pragma region Executable

void SHU_ExecutableLink(const char *library)
{
}

void SHU_ExecutableCompile(const char *directory)
{
    SHUI_SLClear(&SHUI_COMPILE_INCLUDE_DIRECTORIES);
    SHUI_SLClear(&SHUI_COMPILE_SOURCE_FILES);
    SHUI_SLClear(&SHUI_COMPILE_SOURCE_DIRECTORIES);
    SHUI_SLClear(&SHUI_COMPILE_LINKS);

    //...
}

#pragma endregion Executable

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations