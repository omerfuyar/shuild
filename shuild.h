#pragma once

#pragma region Platform Detection

#define SHU_PLATFORM_WINDOWS 0
#define SHU_PLATFORM_LINUX 1
#define SHU_PLATFORM_MACOS 2

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
#pragma error("Unsupported platform.")
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

#define SHU_COMPILER_CLANG 0
#define SHU_COMPILER_GCC 1
#define SHU_COMPILER_MSVC 2
#define SHU_COMPILER_CLANGCL 3

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

#pragma error("Unsupported compiler.")

#endif // Compiler Detection

#pragma endregion Compiler Detection

#pragma region Shuild Declarations

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

#pragma region Configuration

/// @brief
/// @param directory
void SHU_IncludeAddDirectory(const char *directory);

/// @brief
/// @param file
void SHU_SourceAddfile(const char *file);

/// @brief
/// @param directory
void SHU_SourceAddDirectory(const char *directory);

#pragma endregion Configuration

#pragma region Library

/// @brief
/// @param name
void SHU_LibraryBegin(const char *name);

/// @brief
/// @param directory
void SHU_LibraryCompile(const char *directory);

#pragma endregion Library

#pragma region Executable

/// @brief
/// @param name
void SHU_ExecutableBegin(const char *name);

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

#define SHUI_MESSAGE_BUFFER_SIZE 512

#define SHUI_COLOR_GREEN(string) "\x1b[32m" string "\x1b[0m"
#define SHUI_COLOR_YELLOW(string) "\x1b[33m" string "\x1b[0m"
#define SHUI_COLOR_RED(string) "\x1b[31m" string "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static char *SHUI_COMPILER_COMMAND = NULL;
static char *SHUI_COMPILER_FLAGS = NULL;

/// @brief Internal variadic logging function.
/// @param terminate Exit code if not 0.
/// @param header Header of the log.
/// @param format Formatted message of the log.
static void SHUI_Log(int terminate, const char *header, const char *format, ...)
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

#define SHUI_LogInfo(format, ...)                                     \
    do                                                                \
    {                                                                 \
        SHUI_Log(0, SHUI_COLOR_GREEN("INFO"), format, ##__VA_ARGS__); \
    } while (0)

#define SHUI_LogWarning(format, ...)                                      \
    do                                                                    \
    {                                                                     \
        SHUI_Log(0, SHUI_COLOR_YELLOW("WARNING"), format, ##__VA_ARGS__); \
    } while (0)

#define SHUI_LogError(code, format, ...)                                \
    do                                                                  \
    {                                                                   \
        SHUI_Log(code, SHUI_COLOR_RED("ERROR"), format, ##__VA_ARGS__); \
    } while (0)

/// @brief Internal command runner function.
/// @param command Command to run with system.
static void SHUI_Run(const char *command)
{
    SHU_LogInfo("'%s'", command);

    int result = system(command);

    if (result != 0)
    {
        SHU_LogError(result, "Last executed command failed");
    }
}

#pragma region Compiler

void SHU_CompilerConfigure(const char *compilerCommand)
{
}

void SHU_CompilerAddFlags(const char *flags)
{
}

void SHU_CompilerSetFlags(const char *flags)
{
}

#pragma endregion Compiler

#pragma region Configuration

void SHU_IncludeAddDirectory(const char *directory)
{
}

void SHU_SourceAddfile(const char *file)
{
}

void SHU_SourceAddDirectory(const char *directory)
{
}

#pragma endregion Configuration

#pragma region Library

void SHU_LibraryBegin(const char *name)
{
}

void SHU_LibraryCompile(const char *directory)
{
}

#pragma endregion Library

#pragma region Executable

void SHU_ExecutableBegin(const char *name)
{
}

void SHU_ExecutableLink(const char *library)
{
}

void SHU_ExecutableCompile(const char *directory)
{
}

#pragma endregion Executable

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations