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

#else
/// @brief Current platform is not a Unix-like.
#define SHUM_PLATFORM_UNIX 0
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

#ifndef SHUM_COMPILER_COMMAND_BUFFER
#define SHUM_COMPILER_COMMAND_BUFFER 4096
#endif

#ifndef SHUM_MESSAGE_BUFFER_SIZE
#define SHUM_MESSAGE_BUFFER_SIZE 512
#endif

#define SHUM_ERROR 0
#define SHUM_ERROR_NULL 1
#define SHUM_ERROR_INDEX 2
#define SHUM_ERROR_UNKNOWN 3

#define SHUM_COLOR_RED(string) "\x1b[31m" string "\x1b[0m"
#define SHUM_COLOR_GREEN(string) "\x1b[32m" string "\x1b[0m"
#define SHUM_COLOR_YELLOW(string) "\x1b[33m" string "\x1b[0m"
#define SHUM_COLOR_BLUE(string) "\x1b[34m" string "\x1b[0m"

#pragma region General

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

/// @brief Compiles the current module as a library.
/// @param directory Output directory of the library file without the name (eg. build/arc/)
void SHU_ModuleCompileLibrary(const char *directory);

/// @brief Compiles the current module as an executable.
/// @param directory Output directory of the executable file without the name (eg. build/bin/)
void SHU_ModuleCompileExecutable(const char *directory);

/// @brief Sets the library search directory for current executable. Practical only if the current module is an executable.
/// @param directory Directory to search for libraries. (eg. build/arc/)
void SHU_ModuleExecutableSetLibraryDirectory(const char *directory);

/// @brief Links an executable to the current executable. Practical only if the current module is an executable.
/// @param library Library to link with executable. (eg. myLibName)
void SHU_ModuleExecutableLinkLibrary(const char *library);

#pragma endregion Module

#pragma endregion Shuild Declarations

#pragma region Shuild Implementations

#ifdef SHUILD_IMPLEMENTATION

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
    SHUI_String data[SHUM_MAX_STRING_ARRAY_COUNT];
    size_t count;
} SHUI_StringList;

static char SHUI_COMPILER = SHUM_COMPILER_UNKNOWN;
static SHUI_String SHUI_COMPILER_COMMAND = {0};
static SHUI_StringList SHUI_COMPILER_FLAGS = {0};

static SHUI_String SHUI_MODULE_NAME = {0};
static SHUI_StringList SHUI_MODULE_INCLUDE_DIRECTORIES = {0};
static SHUI_StringList SHUI_MODULE_SOURCE_DIRECTORIES = {0};
static SHUI_StringList SHUI_MODULE_SOURCE_FILES = {0};

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
    if (string == NULL || string->data == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to string destroy.");
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

/// @brief Internal command runner function.
/// @param command Command to run with system.
static void SHUI_Run(const char *commandFormat, ...)
{
    if (commandFormat == NULL)
    {
        SHU_LogError(SHUM_ERROR_NULL, "Null pointer passed as parameter to run.");
    }

    char commandBuffer[SHUM_MESSAGE_BUFFER_SIZE] = {0};

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

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name (eg. build/)
/// @param finalCommandBuffer Buffer to write compiler command.
/// @param finalCommandBufferSize Size of the finalCommandBuffer in bytes.
/// @param isLibrary Current module is a library or not.
/// @return The index of the finalCommand to continue appending.
static size_t SHUI_ModuleBuildCompileCommand(const char *directory, char *finalCommandBuffer, size_t finalCommandBufferSize, char isLibrary)
{
    SHUI_String directoryStr = {0};

    if (strlen(directory) != 0)
    {
        directoryStr = SHUI_SCreate(directory);

        // todo targets
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
        SHUI_SReplace(&directoryStr, '/', '\\');
        SHUI_Run("if not exist %s mkdir %s", directoryStr.data, directoryStr.data);
#elif SHUM_PLATFORM_UNIX
        SHUI_Run("mkdir -p %s" directory);
#endif
    }

    size_t finalCommandIndex = 0;

    snprintf(finalCommandBuffer + finalCommandIndex, finalCommandBufferSize - finalCommandIndex, "%s %s", SHUI_COMPILER_COMMAND.data, isLibrary != 0 ? "-S " : "");
    finalCommandIndex += SHUI_COMPILER_COMMAND.length + 1;

    // todo cross compiler commands support

    for (size_t i = 0; i < SHUI_MODULE_INCLUDE_DIRECTORIES.count; i++)
    {
        snprintf(finalCommandBuffer + finalCommandIndex, finalCommandBufferSize - finalCommandIndex, "-I%s ", SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].data);
        finalCommandIndex += SHUI_MODULE_INCLUDE_DIRECTORIES.data[i].length + 3;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_DIRECTORIES.count; i++)
    {
        snprintf(finalCommandBuffer + finalCommandIndex, finalCommandBufferSize - finalCommandIndex, "%s*.c ", SHUI_MODULE_SOURCE_DIRECTORIES.data[i].data);
        finalCommandIndex += SHUI_MODULE_SOURCE_DIRECTORIES.data[i].length + 4;
    }

    for (size_t i = 0; i < SHUI_MODULE_SOURCE_FILES.count; i++)
    {
        snprintf(finalCommandBuffer + finalCommandIndex, finalCommandBufferSize - finalCommandIndex, "%s ", SHUI_MODULE_SOURCE_FILES.data[i].data);
        finalCommandIndex += SHUI_MODULE_SOURCE_FILES.data[i].length + 1;
    }

    for (size_t i = 0; i < SHUI_COMPILER_FLAGS.count; i++)
    {
        snprintf(finalCommandBuffer + finalCommandIndex, finalCommandBufferSize - finalCommandIndex, "%s ", SHUI_COMPILER_FLAGS.data[i].data);
        finalCommandIndex += SHUI_COMPILER_FLAGS.data[i].length + 1;
    }

    char *fileExtension = NULL;

    if (isLibrary != 0)
    {
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
        fileExtension = ".lib";
#else
        fileExtension = ".a";
#endif
    }
    else
    {
#if SHUM_PLATFORM == SHUM_PLATFORM_WINDOWS
        fileExtension = ".exe";
#else
        fileExtension = "";
#endif
    }

    snprintf(finalCommandBuffer + finalCommandIndex, finalCommandBufferSize - finalCommandIndex, "-o%s%s%s", directoryStr.data == NULL ? "" : directoryStr.data, SHUI_MODULE_NAME.data, fileExtension);
    finalCommandIndex += directoryStr.length + 2;

    if (directoryStr.data != NULL)
    {
        SHUI_SDestroy(&directoryStr);
    }

    SHUI_SLClear(&SHUI_MODULE_INCLUDE_DIRECTORIES);
    SHUI_SLClear(&SHUI_MODULE_SOURCE_FILES);
    SHUI_SLClear(&SHUI_MODULE_SOURCE_DIRECTORIES);

    return finalCommandIndex;
}

#pragma endregion Internals

#pragma region General

void SHU_Log(int terminate, const char *header, const char *format, ...)
{
    char messageBuffer[SHUM_MESSAGE_BUFFER_SIZE] = {0};

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
    if (strlen(flags) != 0)
    {
        SHUI_SLAdd(&SHUI_COMPILER_FLAGS, SHUI_SCreate(flags));
    }
}

void SHU_CompilerSetFlags(const char *flags)
{
    SHUI_SLClear(&SHUI_COMPILER_FLAGS);

    SHU_CompilerAddFlags(flags);
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

void SHU_ModuleCompileLibrary(const char *directory)
{
    char finalCommand[SHUM_COMPILER_COMMAND_BUFFER] = {0};

    SHUI_ModuleBuildCompileCommand(directory, finalCommand, sizeof(finalCommand), 1);

    SHUI_Run(finalCommand);

    SHU_LogInfo("Library '%s' successfully compiled.", SHUI_MODULE_NAME.data);

    SHUI_SDestroy(&SHUI_MODULE_NAME);
}

void SHU_ModuleCompileExecutable(const char *directory)
{
    char finalCommand[SHUM_COMPILER_COMMAND_BUFFER] = {0};

    size_t finalCommandIndex = SHUI_ModuleBuildCompileCommand(directory, finalCommand, sizeof(finalCommand), 0);

    snprintf(finalCommand + finalCommandIndex, sizeof(finalCommand) - finalCommandIndex, "-L%s ", SHUI_EXECUTABLE_LINK_DIRECTORY.data);
    finalCommandIndex += SHUI_EXECUTABLE_LINK_DIRECTORY.length + 3;

    for (size_t i = 0; i < SHUI_EXECUTABLE_LINKS.count; i++)
    {
        snprintf(finalCommand + finalCommandIndex, sizeof(finalCommand) - finalCommandIndex, "-l%s ", SHUI_EXECUTABLE_LINKS.data[i].data);
        finalCommandIndex += SHUI_EXECUTABLE_LINKS.data[i].length + 3;
    }

    SHUI_SDestroy(&SHUI_EXECUTABLE_LINK_DIRECTORY);
    SHUI_SLClear(&SHUI_EXECUTABLE_LINKS);

    SHUI_Run(finalCommand);

    SHU_LogInfo("Executable '%s' successfully compiled.", SHUI_MODULE_NAME.data);

    SHUI_SDestroy(&SHUI_MODULE_NAME);
}

void SHU_ModuleExecutableSetLibraryDirectory(const char *directory)
{
    if (SHUI_EXECUTABLE_LINK_DIRECTORY.data != NULL)
    {
        SHUI_SDestroy(&SHUI_EXECUTABLE_LINK_DIRECTORY);
    }

    SHUI_EXECUTABLE_LINK_DIRECTORY = SHUI_SCreate(directory);
}

void SHU_ModuleExecutableLinkLibrary(const char *library)
{
    SHUI_SLAdd(&SHUI_EXECUTABLE_LINKS, SHUI_SCreate(library));
}

#pragma endregion Module

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementations