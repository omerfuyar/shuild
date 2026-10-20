// You can define various macros to configure Shuild before including this file.
// define SHU_IMPLEMENTATION in one file to include the implementation.
// define SHUC_ENABLE_INCREMENTAL to enable incremental builds.
// define SHUC_NO_MODULE_LOG to leave out the line that each module logs when it compiles.
// define SHUC_LOG_COMMANDS to log each command that runs. Otherwise a command is logged only when it fails.
// define SHUC_NO_RUN_ERROR to disable termination on run error.
// define SHUC_MAX_JOB_COUNT 1 to compile one file at a time instead of as many as there are processors.
// define SHUC_MAX_<...> <limit> to customize limits.

// todo add macro helpers like module(...){...} for easy module begin and compile, like shujsn, shuarg or clay.

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

/// @brief A system that a compiler compiles for, or that shuild runs on.
typedef enum SHUPlatform
{
    SHUPlatform_Unknown = 0,
    SHUPlatform_Windows = 1,
    SHUPlatform_Linux = 2,
    SHUPlatform_MacOS = 3,
} SHUPlatform;

// the preprocessor cannot read enums, so SHUM_HOST_PLATFORM is the enum's number, and #if checks the host with SHUM_HOST_WINDOWS, SHUM_HOST_LINUX and SHUM_HOST_MACOS, each 1 or 0
#if defined(_WIN32)
#define SHUM_HOST_WINDOWS 1
#define SHUM_HOST_LINUX 0
#define SHUM_HOST_MACOS 0
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 1
#elif defined(__linux__)
#define SHUM_HOST_WINDOWS 0
#define SHUM_HOST_LINUX 1
#define SHUM_HOST_MACOS 0
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 2
#elif defined(__APPLE__) && defined(__MACH__)
#define SHUM_HOST_WINDOWS 0
#define SHUM_HOST_LINUX 0
#define SHUM_HOST_MACOS 1
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 3
#else
#define SHUM_HOST_WINDOWS 0
#define SHUM_HOST_LINUX 0
#define SHUM_HOST_MACOS 0
/// @brief The system shuild runs on, a SHUPlatform. (eg. if (SHUM_HOST_PLATFORM == SHUPlatform_Windows))
#define SHUM_HOST_PLATFORM 0
#endif

/// @brief Get the name of the given platform.
#define SHUPlatform_GetString(platform) (platform == SHUPlatform_Linux     ? "Linux"   \
                                         : platform == SHUPlatform_Windows ? "Windows" \
                                         : platform == SHUPlatform_MacOS   ? "MacOS"   \
                                                                           : "Unknown")

/// @brief Either the given platform is the host's or not. It reads an enum, so it does not work in #if; use SHUM_HOST_<...> there.
#define SHUM_PLATFORM_IS_HOST(platform) (SHUM_HOST_PLATFORM == (platform))

#pragma endregion Platform Detection

#pragma region Compiler Detection

/// @brief A family of compilers.
typedef enum SHUCompiler
{
    SHUCompiler_Unknown = 0,
    SHUCompiler_Clang = 1,
    SHUCompiler_GCC = 2,
} SHUCompiler;

#if defined(__clang__)
/// @brief The family of the compiler that compiles this file, a SHUCompiler.
#define SHUM_HOST_COMPILER 1
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
/// @brief The family of the compiler that compiles this file, a SHUCompiler.
#define SHUM_HOST_COMPILER 2
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
/// @brief The family of the compiler that compiles this file, a SHUCompiler.
#define SHUM_HOST_COMPILER 0
/// @brief Version of the host compiler.
#define SHUM_HOST_COMPILER_VERSION 0
#endif

/// @brief Get the name of the given compiler.
#define SHUCompiler_GetString(compiler) (compiler == SHUCompiler_Clang ? "Clang" \
                                         : compiler == SHUCompiler_GCC ? "GCC"   \
                                                                       : "Unknown")

/// @brief Get the command of the given compiler.
#define SHUCompiler_GetCommand(compiler) (compiler == SHUCompiler_Clang ? "clang" \
                                          : compiler == SHUCompiler_GCC ? "gcc"   \
                                                                        : "Unknown")

/// @brief Either the given compiler is the host compiler or not.
#define SHUM_COMPILER_IS_HOST(compiler) (SHUM_HOST_COMPILER == (compiler))

#pragma endregion Compiler Detection

#pragma region Configurations and Constants

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
#define SHUM_COLOR_DIM(string) "\x1b[2m" string SHUM_COLOR_RESET

// the colours of the parts of log lines; shuild's own lines use them, and a build script's lines with SHU_UtilLog can too (eg. "built " SHUM_LOG_NAME("%s"))
#define SHUM_LOG_NAME(string) SHUM_COLOR_MAGENTA(string)  // a module, a library or a project
#define SHUM_LOG_PATH(string) SHUM_COLOR_CYAN(string)     // a file or a directory
#define SHUM_LOG_COMMAND(string) SHUM_COLOR_DIM(string)   // a command line
#define SHUM_LOG_VALUE(string) SHUM_COLOR_BOLD(string)    // a setting's value, such as a build type or a compiler

#if SHUM_HOST_WINDOWS
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

/// @brief A compiler that SHU_CompilerDetect found.
typedef struct SHUCompilerInfo
{
    const char *command; // the name it runs by, as found on PATH (eg. gcc-14, x86_64-w64-mingw32-clang)
    SHUCompiler identifier; // its family
    SHUPlatform target;     // the system it compiles for
    const char *machine; // the system it compiles for, as it names it (eg. x86_64-linux-gnu, aarch64-w64-mingw32), or "" if it does not tell
    u32 version;         // major * 10000 + minor * 100 + patch, as SHUM_HOST_COMPILER_VERSION
    bool sanitizers;     // it compiles and links a program with -fsanitize=address,undefined
} SHUCompilerInfo;

/// @brief Function that SHU_UtilListDirectory calls for each entry.
/// @param path Path of the entry, relative to current executable. Directories end with a separator. (eg. src/utils/)
/// @param type Type of the entry.
/// @param data Data given to SHU_UtilListDirectory.
typedef void (*SHUListFunction)(const char *path, SHUFileType type, void *data);

#define SHUModuleType_GetString(module) (module == SHUModuleType_Executable       ? "Executable" \
                                         : module == SHUModuleType_LibraryStatic  ? "Static"     \
                                         : module == SHUModuleType_LibraryDynamic ? "Dynamic"    \
                                                                                  : "Unknown")

/// @brief The type of a module as log lines show it, in its colour: green for executables, blue for static libraries and yellow for dynamic ones.
#define SHUModuleType_GetLogString(module) (module == SHUModuleType_Executable       ? SHUM_COLOR_GREEN("Executable") \
                                            : module == SHUModuleType_LibraryStatic  ? SHUM_COLOR_BLUE("Static")      \
                                            : module == SHUModuleType_LibraryDynamic ? SHUM_COLOR_YELLOW("Dynamic")   \
                                                                                     : "Unknown")

#pragma region Utility

///!!! This function is not meant to be used directly. Use SHU_UtilAutomate macro instead. !!!
void SHUI_UAutomate(int argc, char **argv, const char *sourceName);

/// @brief Enables autonomously rebuilding the build script when the source or header is edited. It works only if the build system is one script. Run after configuring the compiler.
/// @param argc Argument count from main function.
/// @param argv Argument array from main function.
#define SHU_UtilAutomate(argc, argv) SHUI_UAutomate(argc, argv, __FILE__)

/// @brief Logs a line as shuild logs its own: "[shuild]" then the message. The SHUM_LOG_ macros colour its parts as shuild's are. (eg. "built " SHUM_LOG_NAME("%s"))
/// @param format Format of the line, as printf takes it.
void SHU_UtilLog(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Logs a warning as shuild logs its own.
/// @param format Format of the warning, as printf takes it.
void SHU_UtilWarn(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Logs an error as shuild logs its own, and ends the build with the code unless it is 0.
/// @param code Exit code of the build, or 0 to go on.
/// @param format Format of the error, as printf takes it.
void SHU_UtilFail(i32 code, const char *format, ...) __attribute__((format(printf, 2, 3)));

/// @brief Formats a string, as printf does, into new memory.
/// @param format Format of the string. (eg. "%sbin/", directory)
/// @return The new string. Free it with free.
char *SHU_UtilFormat(const char *format, ...) __attribute__((format(printf, 1, 2)));

/// @brief Internal command runner function.
/// @param command Command to run with the shell, through system. (eg. clang example.c -o example) Modules run the compiler without a shell.
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
i32 SHU_UtilRun(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a command like SHU_UtilRun, but its failure does not stop the build, even without SHUC_NO_RUN_ERROR. Use it for a command that may fail.
/// @param command Command to run with the shell, through system. (eg. ./tests --quick)
/// @return Exit code of the command.
i32 SHU_UtilRunTry(const char *commandFormat, ...) __attribute__((format(printf, 1, 2)));

/// @brief Runs a command like SHU_UtilRun, with its output and errors written to a log file in place of the terminal. When the command fails, the end of the log is shown.
/// @param log Log file to write, relative to current executable. Its directory is created if it doesn't exist. (eg. .shu/cmake.log)
/// @param command Command to run with the shell, through system. (eg. cmake --build build/)
/// @return Exit code of the command. SHUC_NO_RUN_ERROR should be defined to access this value.
i32 SHU_UtilRunLogged(const char *log, const char *commandFormat, ...) __attribute__((format(printf, 2, 3)));

/// @brief Builds another build script and runs it in its own directory, as for a project inside this one. The script is compiled with the configured compiler and SHUILD_BUILD.
/// @param script Build script to compile, relative to current executable. (eg. plugins/shuild.c)
/// @param program Program to compile it into, relative to current executable, without .exe. (eg. plugins/shuild)
/// @param flags More flags for the compiler, such as the script's include directories, or an empty string. (eg. -Idependencies)
/// @param arguments Arguments for the program, or an empty string. (eg. -b release)
void SHU_UtilBuildScript(const char *script, const char *program, const char *flags, const char *arguments);

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
/// @return The type of the file, or SHUFileType_Invalid if it does not exist.
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

/// @brief Gets the file name that shuild gives a library on the system the compiler compiles for. A module links it as -l<name> on every system.
/// Linux: libname.a and libname.so. macOS: libname.a and libname.dylib. Windows, with MinGW's gcc or LLVM: libname.a, and name.dll with its import library libname.dll.a.
/// @param name Name of the library's module. (eg. math)
/// @param type SHUModuleType_LibraryStatic or SHUModuleType_LibraryDynamic.
/// @return The file name, without a directory. (eg. libmath.so) Free it with free.
char *SHU_UtilLibraryFile(const char *name, SHUModuleType type);

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

/// @brief Configures the compiler to be used for compiling modules. Must be called before any other function. See SHU_CompilerConfigureTry for easier configuration.
/// @param compiler Family of the compiler.
/// @param compilerCommand Command to invoke the compiler. (eg. clang)
void SHU_CompilerConfigure(SHUCompiler compiler, const char *compilerCommand);

/// @brief Tries to configure the compiler by checking gcc or clang substring inside the string.
/// @param compilerCommand Command to check and use to invoke the compiler. (eg. gcc).
/// If NULL or empty, the newest compiler on PATH that compiles for the host's system and processor is used, of the family that compiled shuild.c if there is one, as SHU_CompilerDetect finds it;
/// without one, the host compiler's own command. (eg. gcc-14 when gcc is gcc 13)
void SHU_CompilerConfigureTry(const char *compilerCommand);

/// @brief Finds the gcc and clang compilers on PATH, cross compilers such as x86_64-w64-mingw32-gcc included, and asks each for its version and its target.
/// A clang that goes by gcc's name, such as LLVM-MinGW's x86_64-w64-mingw32-gcc, counts as clang.
/// Each that compiles for the host's system and processor is also tried with the sanitizers, by compiling a small program. The first of each name on PATH is kept.
/// @param retCount Number of compilers found. Must not be NULL.
/// @return The compilers, sorted by name. Free them with SHU_CompilerDetectFree.
SHUCompilerInfo *SHU_CompilerDetect(usz *retCount);

/// @brief Frees the compilers that SHU_CompilerDetect found.
/// @param compilers The compilers, as SHU_CompilerDetect gave them.
/// @param count Number of compilers, as SHU_CompilerDetect gave it.
void SHU_CompilerDetectFree(SHUCompilerInfo *compilers, usz count);

///!!! This function is not meant to be used directly. Use SHU_CompilerAddFlags macro instead. !!!
void SHUI_CompilerAddFlags(const char *flags, ...);

/// @brief Adds flags to the compiler configuration.
/// @param flags Flags to add, one string or more. Each can include multiple flags separated by spaces as you want, quoted as in a shell. On Windows, a backslash escapes only a quote, so paths keep theirs. (eg. "-DFOO=31", "-Wall")
#define SHU_CompilerAddFlags(flags, ...) SHUI_CompilerAddFlags(flags, ##__VA_ARGS__, NULL)

/// @brief Clears the compiler and linker flags, and sets the compiler flags.
/// @param flags Flags to set. Can include multiple flags separated by spaces as you want.
void SHU_CompilerSetFlags(const char *flags);

/// @brief Clears the current compiler flags, and the linker flags.
void SHU_CompilerClearFlags(void);

///!!! This function is not meant to be used directly. Use SHU_CompilerAddLinkerFlags macro instead. !!!
void SHUI_CompilerAddLinkerFlags(const char *flags, ...);

/// @brief Adds flags that only linking gets, not compiling, so the compiler does not warn that they are unused.
/// @param flags Flags to add, one string or more, written as SHU_CompilerAddFlags takes them. (eg. "-Wl,--as-needed")
/// @note Executables and dynamic libraries are linked with them; SHU_CompilerClearFlags clears them.
#define SHU_CompilerAddLinkerFlags(flags, ...) SHUI_CompilerAddLinkerFlags(flags, ##__VA_ARGS__, NULL)

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

/// @brief Gets the family of the configured compiler.
/// @return Family of the compiler.
SHUCompiler SHU_CompilerGetIdentifier(void);

/// @brief Gets the system that the configured compiler compiles for, which the compiler tells: the host's, or another's for a cross compiler such as x86_64-w64-mingw32-gcc.
/// The names of executables and libraries, and how they find their dynamic libraries, follow it. Build scripts are compiled for the host.
/// @return The system it compiles for.
SHUPlatform SHU_CompilerGetTarget(void);

#pragma endregion Compiler

#pragma region Module

/// @brief Begins a new module with the given name. A module can be an executable or a library. Must be called before any other Module function.
/// @param name Name of the module. Which will be used also for output file name. (eg. myLibName, myAppName)
/// @param root Root directory of the module. Will be used to relatively point other files and directories for module. Relative to current executable. Leave it empty string or NULL to ignore. (eg. dependencies/library/)
void SHU_ModuleBegin(const char *name, const char *root);

///!!! This function is not meant to be used directly. Use SHU_ModuleAddIncludeDirectory macro instead. !!!
void SHUI_ModuleAddIncludeDirectory(const char *directory, ...);

/// @brief Adds include directories to the module.
/// @param directory Include directories to add to the current module, one or more. Relative to root directory specified in ModuleBegin (eg. "include/", "src/")
#define SHU_ModuleAddIncludeDirectory(directory, ...) SHUI_ModuleAddIncludeDirectory(directory, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleAddPublicIncludeDirectory macro instead. !!!
void SHUI_ModuleAddPublicIncludeDirectory(const char *directory, ...);

/// @brief Adds include directories to the module, and gives them to the modules that link the module, as system headers, so their warnings stay out.
/// Only the modules that link the library themselves get them, not the ones that get the library through another library.
/// @param directory Include directories of the library's interface, one or more. Relative to root directory specified in ModuleBegin (eg. "include/")
#define SHU_ModuleAddPublicIncludeDirectory(directory, ...) SHUI_ModuleAddPublicIncludeDirectory(directory, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleAddSourceFile macro instead. !!!
void SHUI_ModuleAddSourceFile(const char *file, ...);

/// @brief Adds source files to the module. Each is a single file or a directory, added with its subdirectories.
/// @param file Files or directories to add to the current module, one or more. Relative to root directory specified in ModuleBegin (eg. "main.c", "src/")
/// @note A header file is compiled as C, so a single header library can be added with the definition of its implementation. (eg. clay.h with CLAY_IMPLEMENTATION)
#define SHU_ModuleAddSourceFile(file, ...) SHUI_ModuleAddSourceFile(file, ##__VA_ARGS__, NULL)

/// @brief Internal generic module compile function for both libraries and executables.
/// @param directory Output directory of the library file without the name. Relative to current executable directory. (eg. build/)
/// @param module Current module mode. Use with SHUM_MODULE_<...> macros. (eg. SHUModuleType_LibraryStatic)
void SHU_ModuleCompile(const char *directory, SHUModuleType module);

/// @brief Adds a directory to search for the libraries that the current module links. A static library keeps it for the modules that link it, as it keeps its libraries.
/// On Linux and macOS, a directory that holds a dynamic library the module links is embedded in it, relative to the module's own directory ($ORIGIN or @loader_path),
/// so the library is found at run time, also after both are moved together. On Windows, see SHU_ModuleCopyDynamicLinks.
/// @param directory Directories to search for libraries, one or more. Relative to current executable directory. (eg. "build/arc/")
#define SHU_ModuleAddLibraryDirectory(directory, ...) SHUI_ModuleAddLibraryDirectory(directory, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleAddLibraryDirectory macro instead. !!!
void SHUI_ModuleAddLibraryDirectory(const char *directory, ...);

/// @brief Links a library to the current module. An executable or a dynamic library is linked with it.
/// A static library cannot be linked, so it keeps the library: a module that links the static library later gets the library too, after it, with its directories.
/// @param library Libraries to link with the module, one or more, in order. Shouldn't include any path, use `SHU_ModuleAddLibraryDirectory` to search inside. (eg. "shapes", "numbers")
#define SHU_ModuleLinkLibrary(library, ...) SHUI_ModuleLinkLibrary(library, ##__VA_ARGS__, NULL)

///!!! This function is not meant to be used directly. Use SHU_ModuleLinkLibrary macro instead. !!!
void SHUI_ModuleLinkLibrary(const char *library, ...);

/// @brief Copies the dynamic libraries that the current module links into its output directory when it compiles, so they are found beside it.
/// Windows needs this, as a program finds its DLLs beside itself or on PATH, not in the directories it was linked with. A copy that has the content already is left as is.
/// Only the module's own links are copied, with those that its static libraries bring, not the ones that its dynamic libraries link.
void SHU_ModuleCopyDynamicLinks(void);

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

#if SHUM_HOST_WINDOWS
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

#if SHUM_HOST_MACOS
#include <mach-o/dyld.h>
#endif

#pragma region Internals

// calls function with each string argument of a variadic function, from first until the NULL that its macro adds
#define SHUI_EACH_ARGUMENT(first, function)                                                           \
    do                                                                                                \
    {                                                                                                 \
        va_list args;                                                                                 \
        va_start(args, first);                                                                        \
        for (const char *argument = (first); argument != NULL; argument = va_arg(args, const char *)) \
        {                                                                                             \
            function(argument);                                                                       \
        }                                                                                             \
        va_end(args);                                                                                 \
    } while (0)

#ifdef SHUC_ENABLE_INCREMENTAL
typedef u64 SHUI_Hash;
#endif

// a string list owns its strings, and frees them with itself

typedef struct SHUI_StringList
{
    usz count;
    usz capacity;
    char **data;
} SHUI_StringList;

/// @brief A string that grows as characters are added, for strings made one character at a time.
typedef struct SHUI_Builder
{
    usz length;
    usz capacity;
    char *data;
} SHUI_Builder;

/// @brief A library and what a module that links it gets: its public include directories, and for a static library, the libraries it links.
typedef struct SHUI_Library
{
    char *name;
    SHUI_StringList links;
    SHUI_StringList linkDirectories;
    SHUI_StringList includeDirectories;
} SHUI_Library;

#ifdef SHUC_ENABLE_INCREMENTAL
static bool SHUI_CDependencyDirty(const char *dependencyFile, const char *objectFile);
#endif

static struct
{
    char *currentExecutableDirectory;

#ifdef SHUC_ENABLE_INCREMENTAL
    char *cacheDirectory;
#endif

    struct
    {
        SHUCompiler identifier;
        SHUPlatform target; // the platform it compiles for
        char *command;
        SHUI_StringList flags;
        SHUI_StringList linkerFlags;
    } COMPILER;

    struct
    {
        i64 processes[SHUC_MAX_JOB_COUNT];
        char *commands[SHUC_MAX_JOB_COUNT]; // shown when the job fails
        usz count;
        usz limit;
        i32 failure;
    } JOBS;

    struct
    {
        char *name;
        char *root;
        SHUI_StringList includeDirectories;
        SHUI_StringList sourceFiles;
        SHUI_StringList links;
        SHUI_StringList linkDirectories;
        SHUI_StringList publicIncludeDirectories; // given to the modules that link it
        SHUI_StringList linkedIncludeDirectories; // the public include directories of the libraries it links
        bool copyDynamicLinks;
        usz compiledCount; // for the module's line in the log
        char *output;      // the file it linked or packed, or NULL when it was up to date
    } MODULE;

    // the libraries compiled so far, with what the modules that link them get
    struct
    {
        usz count;
        usz capacity;
        SHUI_Library *data;
    } LIBRARIES;
} SHUILD = {0};

static void *SHUI_Allocate(usz size)
{
    void *memory = malloc(size);
    SHU_Assert(memory != NULL, "Internal: Memory allocation failed for size '%zu'.", size);

    return memory;
}

static void *SHUI_Reallocate(void *memory, usz size)
{
    void *grown = realloc(memory, size);
    SHU_Assert(grown != NULL, "Internal: Memory allocation failed for size '%zu'.", size);

    return grown;
}

static usz SHUI_GrowCapacity(usz capacity)
{
    return capacity == 0 ? SHUC_ARRAY_INITIAL_COUNT : (usz)((float)capacity * SHUC_ARRAY_RESIZE_FACTOR);
}

static char *SHUI_VFormat(const char *format, va_list args)
{
    va_list copy;
    va_copy(copy, args);
    i32 length = vsnprintf(NULL, 0, format, copy);
    va_end(copy);

    SHU_Assert(length >= 0, "Internal: Formatting '%s' failed.", format);

    char *string = (char *)SHUI_Allocate((usz)length + 1);
    vsnprintf(string, (usz)length + 1, format, args);

    return string;
}

static char *SHUI_Copy(const char *string)
{
    usz length = (usz)strlen(string);
    char *copy = (char *)SHUI_Allocate(length + 1);
    memcpy(copy, string, length + 1);

    return copy;
}

// shuild's own messages are one short line each, with paths from the build script's directory
static void SHUI_LogLine(const char *kind, const char *format, va_list args)
{
    fprintf(SHU_LOG_STREAM, SHUM_COLOR_BOLD("[shuild]") " %s", kind);
    vfprintf(SHU_LOG_STREAM, format, args);
    fputc('\n', SHU_LOG_STREAM);
}

char *SHU_UtilFormat(const char *format, ...)
{
    SHU_AssertNullPointer(format);

    va_list args;
    va_start(args, format);
    char *string = SHUI_VFormat(format, args);
    va_end(args);

    return string;
}

void SHU_UtilLog(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine("", format, args);
    va_end(args);
}

void SHU_UtilWarn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_YELLOW("warning: "), format, args);
    va_end(args);
}

void SHU_UtilFail(i32 code, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    SHUI_LogLine(SHUM_COLOR_RED("error: "), format, args);
    va_end(args);

    if (code != 0)
    {
        exit(code);
    }
}

/// @brief A path from the build script's directory, for logs.
static const char *SHUI_PShort(const char *path)
{
    usz length = SHUILD.currentExecutableDirectory == NULL ? 0 : (usz)strlen(SHUILD.currentExecutableDirectory);

    return length != 0 && strncmp(path, SHUILD.currentExecutableDirectory, length) == 0 ? path + length : path;
}

static void SHUI_BAppendChar(SHUI_Builder *builder, char character)
{
    if (builder->length + 1 >= builder->capacity)
    {
        usz capacity = SHUI_GrowCapacity(builder->capacity);
        builder->data = (char *)SHUI_Reallocate(builder->data, capacity);
        builder->capacity = capacity;
    }

    builder->data[builder->length++] = character;
    builder->data[builder->length] = '\0';
}

static void SHUI_BAppend(SHUI_Builder *builder, const char *string)
{
    for (const char *c = string; *c != '\0'; c++)
    {
        SHUI_BAppendChar(builder, *c);
    }
}

// the string is the caller's, and the builder starts a new one
static char *SHUI_BTake(SHUI_Builder *builder)
{
    char *string = builder->data == NULL ? SHUI_Copy("") : builder->data;
    *builder = (SHUI_Builder){0};

    return string;
}

static bool SHUI_SEndsWithC(const char *string, const char *suffix)
{
    usz stringLength = (usz)strlen(string);
    usz suffixLength = (usz)strlen(suffix);

    return stringLength >= suffixLength && strcmp(string + stringLength - suffixLength, suffix) == 0;
}

static bool SHUI_PIsSeparator(char character)
{
    return character == '/' || character == SHUM_PATH_SEPARATOR;
}

static void SHUI_PNormalizePath(char *string)
{
#if SHUM_HOST_WINDOWS
    for (char *c = string; *c != '\0'; c++)
    {
        if (*c == '/')
        {
            *c = '\\';
        }
    }
#else
    (void)string;
#endif
}

/// @brief Joins a base path and a path. A directory ends with a separator. On Windows, the separators are backslashes.
static char *SHUI_PPath(const char *base, const char *path, bool directory)
{
    usz baseLength = (usz)strlen(base);
    usz pathLength = (usz)strlen(path);
    const char *last = pathLength != 0 ? path + pathLength - 1 : baseLength != 0 ? base + baseLength - 1 : NULL;
    bool separator = directory && (last == NULL || !SHUI_PIsSeparator(*last));

    char *joined = SHU_UtilFormat("%s%s%s", base, path, separator ? SHUM_PATH_SEPARATOR_STR : "");
    SHUI_PNormalizePath(joined);

    return joined;
}

/// @brief The directory of a path, with its separator at the end, or an empty string.
static char *SHUI_PDirectory(const char *path)
{
    usz length = (usz)strlen(path);

    while (length > 0 && !SHUI_PIsSeparator(path[length - 1]))
    {
        length--;
    }

    return SHU_UtilFormat("%.*s", (int)length, path);
}

static void SHUI_SLAdd(SHUI_StringList *list, char *string);
static void SHUI_SLFree(SHUI_StringList *list);

/// @brief A path without . and .. segments, so two paths to a directory can be compared. (eg. /a/b/../c/ is /a/c/)
static char *SHUI_PClean(const char *path)
{
    SHUI_StringList segments = {0};
    const char *start = path;

    for (const char *c = path;; c++)
    {
        if (*c != '\0' && !SHUI_PIsSeparator(*c))
        {
            continue;
        }

        char *segment = SHU_UtilFormat("%.*s", (int)(c - start), start);

        if (strcmp(segment, "..") == 0 && segments.count > 0 && strcmp(segments.data[segments.count - 1], "..") != 0)
        {
            free(segments.data[--segments.count]);
            free(segment);
        }
        else if (segment[0] != '\0' && strcmp(segment, ".") != 0)
        {
            SHUI_SLAdd(&segments, segment);
        }
        else
        {
            free(segment);
        }

        if (*c == '\0')
        {
            break;
        }

        start = c + 1;
    }

    SHUI_Builder clean = {0};

    if (SHUI_PIsSeparator(path[0]))
    {
        SHUI_BAppendChar(&clean, SHUM_PATH_SEPARATOR);
    }

    for (usz i = 0; i < segments.count; i++)
    {
        SHUI_BAppend(&clean, segments.data[i]);

        if (i + 1 < segments.count || (path[0] != '\0' && SHUI_PIsSeparator(path[strlen(path) - 1])))
        {
            SHUI_BAppendChar(&clean, SHUM_PATH_SEPARATOR);
        }
    }

    SHUI_SLFree(&segments);

    return SHUI_BTake(&clean);
}

/// @brief The path from one directory to another, both ending with a separator. (eg. from /a/bin/ to /a/lib/ is ../lib/)
static char *SHUI_PRelative(const char *fromPath, const char *toPath)
{
    char *from = SHUI_PClean(fromPath);
    char *to = SHUI_PClean(toPath);

    usz common = 0;

    for (usz i = 0; from[i] != '\0' && from[i] == to[i]; i++)
    {
        if (SHUI_PIsSeparator(from[i]))
        {
            common = i + 1;
        }
    }

    SHUI_Builder relative = {0};

    for (const char *c = from + common; *c != '\0'; c++)
    {
        if (SHUI_PIsSeparator(*c))
        {
            SHUI_BAppend(&relative, ".." SHUM_PATH_SEPARATOR_STR);
        }
    }

    SHUI_BAppend(&relative, to + common);

    free(from);
    free(to);

    return SHUI_BTake(&relative);
}

static void SHUI_SLAdd(SHUI_StringList *list, char *string)
{
    if (list->count >= list->capacity)
    {
        usz capacity = SHUI_GrowCapacity(list->capacity);
        list->data = (char **)SHUI_Reallocate(list->data, sizeof(char *) * capacity);
        list->capacity = capacity;
    }

    list->data[list->count++] = string;
}

// a list given to another owner is emptied, so it is not freed twice
static SHUI_StringList SHUI_SLTake(SHUI_StringList *list)
{
    SHUI_StringList taken = *list;
    *list = (SHUI_StringList){0};

    return taken;
}

static void SHUI_SLFree(SHUI_StringList *list)
{
    for (usz i = 0; i < list->count; i++)
    {
        free(list->data[i]);
    }

    free(list->data);
    *list = (SHUI_StringList){0};
}

static bool SHUI_SLContains(const SHUI_StringList *list, const char *string)
{
    for (usz i = 0; i < list->count; i++)
    {
        if (strcmp(list->data[i], string) == 0)
        {
            return true;
        }
    }

    return false;
}

static void SHUI_CAddArgument(SHUI_StringList *command, const char *argument)
{
    SHUI_SLAdd(command, SHUI_Copy(argument));
}

// a backslash escapes the next character, as in a POSIX shell; on Windows, where paths hold backslashes, it escapes only a quote, as the C runtime's own splitting does
#if SHUM_HOST_WINDOWS
#define SHUI_C_ESCAPES(next) ((next) == '"' || (next) == '\'')
#define SHUI_C_ESCAPES_QUOTED(next) ((next) == '"')
#else
#define SHUI_C_ESCAPES(next) ((next) != '\0')
#define SHUI_C_ESCAPES_QUOTED(next) ((next) == '"' || (next) == '\\' || (next) == '$' || (next) == '`')
#endif

static void SHUI_CAddArguments(SHUI_StringList *command, const char *arguments)
{
    // splits the arguments the way a POSIX shell does: spaces separate them, quotes group them and backslashes escape
    SHUI_Builder argument = {0};
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
                SHUI_BAppendChar(&argument, *c);
            }
        }
        else if (quote == '"')
        {
            if (*c == '"')
            {
                quote = '\0';
            }
            else if (*c == '\\' && SHUI_C_ESCAPES_QUOTED(c[1]))
            {
                SHUI_BAppendChar(&argument, *++c);
            }
            else
            {
                SHUI_BAppendChar(&argument, *c);
            }
        }
        else if (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r')
        {
            if (inArgument)
            {
                SHUI_SLAdd(command, SHUI_BTake(&argument));
                inArgument = false;
            }
        }
        else if (*c == '\'' || *c == '"')
        {
            quote = *c;
            inArgument = true;
        }
        else if (*c == '\\' && SHUI_C_ESCAPES(c[1]))
        {
            SHUI_BAppendChar(&argument, *++c);
            inArgument = true;
        }
        else
        {
            SHUI_BAppendChar(&argument, *c);
            inArgument = true;
        }
    }

    SHU_Assert(quote == '\0', "Unclosed quote in arguments '%s'.", arguments);

    if (inArgument)
    {
        SHUI_SLAdd(command, SHUI_BTake(&argument));
    }

    free(argument.data);
}

static void SHUI_CAddFlags(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.COMPILER.flags.count; i++)
    {
        SHUI_CAddArguments(command, SHUILD.COMPILER.flags.data[i]);
    }
}

static void SHUI_CAddLinkerFlags(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.COMPILER.linkerFlags.count; i++)
    {
        SHUI_CAddArguments(command, SHUILD.COMPILER.linkerFlags.data[i]);
    }
}

static void SHUI_CAddIncludeDirectories(SHUI_StringList *command)
{
    for (usz i = 0; i < SHUILD.MODULE.includeDirectories.count; i++)
    {
        SHUI_SLAdd(command, SHU_UtilFormat("-I%s", SHUILD.MODULE.includeDirectories.data[i]));
    }

    // the headers of linked libraries are another module's, so their warnings stay out
    for (usz i = 0; i < SHUILD.MODULE.linkedIncludeDirectories.count; i++)
    {
        SHUI_CAddArgument(command, "-isystem");
        SHUI_CAddArgument(command, SHUILD.MODULE.linkedIncludeDirectories.data[i]);
    }
}

// build scripts run on the host, so a cross compiler leaves them to the host's own
static const char *SHUI_CScriptCompiler(void)
{
    return SHUM_PLATFORM_IS_HOST(SHUILD.COMPILER.target) ? SHUILD.COMPILER.command : SHUCompiler_GetCommand(SHUM_HOST_COMPILER);
}

// the archiver of the compiler's toolchain: llvm-ar for clang, which reads objects of any system,
// and for gcc the gcc-ar of the same prefix and version, such as x86_64-w64-mingw32-gcc-ar or gcc-ar-14
static char *SHUI_CArchiver(void)
{
    if (SHUILD.COMPILER.identifier == SHUCompiler_Clang)
    {
        return SHUI_Copy("llvm-ar");
    }

    const char *gcc = NULL;

    for (const char *found = strstr(SHUILD.COMPILER.command, "gcc"); found != NULL; found = strstr(found + 1, "gcc"))
    {
        gcc = found;
    }

    return gcc == NULL ? SHUI_Copy("ar") : SHU_UtilFormat("%.*sgcc-ar%s", (int)(gcc - SHUILD.COMPILER.command), SHUILD.COMPILER.command, gcc + 3);
}

// the first line that the compiler prints for an option, such as -dumpmachine, or an empty string
static char *SHUI_CAsk(const char *command, const char *option)
{
    char line[256] = {0};

#if SHUM_HOST_WINDOWS
    char *asked = SHU_UtilFormat("%s %s 2>NUL", command, option);
    FILE *pipe = _popen(asked, "r");
#else
    char *asked = SHU_UtilFormat("%s %s 2>/dev/null", command, option);
    FILE *pipe = popen(asked, "r");
#endif
    free(asked);

    if (pipe != NULL)
    {
        if (fgets(line, sizeof(line), pipe) == NULL)
        {
            line[0] = '\0';
        }

#if SHUM_HOST_WINDOWS
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    }

    line[strcspn(line, "\r\n")] = '\0';
    return SHUI_Copy(line);
}

// the compiler names the system it compiles for, such as x86_64-linux-gnu, x86_64-w64-mingw32 or arm64-apple-darwin23
static SHUPlatform SHUI_CTargetOf(const char *machine)
{
    if (strstr(machine, "mingw") != NULL || strstr(machine, "windows") != NULL)
    {
        return SHUPlatform_Windows;
    }

    if (strstr(machine, "apple") != NULL || strstr(machine, "darwin") != NULL)
    {
        return SHUPlatform_MacOS;
    }

    if (strstr(machine, "linux") != NULL)
    {
        return SHUPlatform_Linux;
    }

    // a compiler that does not tell compiles for the host
    return (SHUPlatform)SHUM_HOST_PLATFORM;
}

static SHUPlatform SHUI_CDetectTarget(const char *command)
{
    char *machine = SHUI_CAsk(command, "-dumpmachine");
    SHUPlatform target = SHUI_CTargetOf(machine);
    free(machine);

    return target;
}

// whether a compiler's machine names the processor that shuild runs on, so the programs it compiles run here;
// a compiler that does not tell, and a processor that is not listed, count as the host's
static bool SHUI_CRunsOnHost(const char *machine)
{
#if defined(__x86_64__) || defined(_M_X64)
    const char *processors[] = {"x86_64-", "amd64-"};
#elif defined(__aarch64__) || defined(_M_ARM64)
    const char *processors[] = {"aarch64-", "arm64-"};
#elif defined(__i386__) || defined(_M_IX86)
    const char *processors[] = {"i386-", "i486-", "i586-", "i686-"};
#elif defined(__arm__) || defined(_M_ARM)
    const char *processors[] = {"arm-", "armv"};
#else
    const char *processors[] = {""};
#endif

    if (machine[0] == '\0')
    {
        return true;
    }

    for (usz i = 0; i < sizeof(processors) / sizeof(*processors); i++)
    {
        if (strncmp(machine, processors[i], strlen(processors[i])) == 0)
        {
            return true;
        }
    }

    return false;
}

#if SHUM_HOST_WINDOWS
static char *SHUI_CQuoteArgument(const char *argument)
{
    // _spawnvp joins the arguments with spaces, so they are quoted the way the C runtime splits them back
    if (argument[0] != '\0' && strpbrk(argument, " \t\"") == NULL)
    {
        return SHUI_Copy(argument);
    }

    SHUI_Builder quoted = {0};
    SHUI_BAppendChar(&quoted, '"');

    usz backslashes = 0;

    for (const char *c = argument; *c != '\0'; c++)
    {
        if (*c == '\\')
        {
            backslashes++;
            continue;
        }

        for (usz j = 0; j < (*c == '"' ? backslashes * 2 + 1 : backslashes); j++)
        {
            SHUI_BAppendChar(&quoted, '\\');
        }

        SHUI_BAppendChar(&quoted, *c);
        backslashes = 0;
    }

    for (usz j = 0; j < backslashes * 2; j++)
    {
        SHUI_BAppendChar(&quoted, '\\');
    }

    SHUI_BAppendChar(&quoted, '"');

    return SHUI_BTake(&quoted);
}
#endif

/// @param line Gets the command as one line, for a log, to free with free, or NULL.
static i64 SHUI_CStart(const SHUI_StringList *command, char **line)
{
    SHU_Assert(command->count > 0, "Internal: Empty command.");

    // the arguments, with a NULL after the last
    char **argv = (char **)SHUI_Allocate(sizeof(char *) * (command->count + 1));

    for (usz i = 0; i < command->count; i++)
    {
#if SHUM_HOST_WINDOWS
        argv[i] = SHUI_CQuoteArgument(command->data[i]);
#else
        argv[i] = command->data[i];
#endif
    }
    argv[command->count] = NULL;

    SHUI_Builder joined = {0};

    for (usz i = 0; i < command->count; i++)
    {
        if (i != 0)
        {
            SHUI_BAppendChar(&joined, ' ');
        }

        SHUI_BAppend(&joined, argv[i]);
    }

    char *commandLine = SHUI_BTake(&joined);

#ifdef SHUC_LOG_COMMANDS
    SHU_UtilLog("$ " SHUM_LOG_COMMAND("%s"), commandLine);
#endif

    i64 process = -1;

#if SHUM_HOST_WINDOWS
    process = (i64)_spawnvp(_P_NOWAIT, argv[0], (const char *const *)argv);
#else
    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(argv[0], argv);
        SHU_UtilFail(0, SHUM_LOG_COMMAND("%s") " cannot start: %s", argv[0], strerror(errno));
        _exit(127);
    }

    process = pid > 0 ? (i64)pid : -1;
#endif

#if SHUM_HOST_WINDOWS
    for (usz i = 0; i < command->count; i++)
    {
        free(argv[i]);
    }
#endif
    free(argv);

    if (line != NULL)
    {
        *line = commandLine;
    }
    else
    {
        free(commandLine);
    }

    return process;
}

static i32 SHUI_CWait(i64 process)
{
    if (process < 0)
    {
        return -1;
    }

#if SHUM_HOST_WINDOWS
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

// a failed command is shown whole, so it can be run again by hand
static void SHUI_CReport(i32 result, bool terminateOnError, const char *line)
{
    if (result != 0)
    {
#ifdef SHUC_NO_RUN_ERROR
        (void)terminateOnError;
        SHU_UtilFail(0, "command failed with exit code %d: " SHUM_LOG_COMMAND("%s"), result, line);
#else
        SHU_UtilFail(terminateOnError ? result : 0, "command failed with exit code %d: " SHUM_LOG_COMMAND("%s"), result, line);
#endif
    }
}

static i32 SHUI_CRun(const SHUI_StringList *command, bool terminateOnError)
{
    char *line = NULL;
    i32 result = SHUI_CWait(SHUI_CStart(command, &line));
    SHUI_CReport(result, terminateOnError, line);
    free(line);

    return result;
}

static void SHUI_CWaitJob(void)
{
    // the first job that ends; on Windows, the oldest one
    usz index = 0;
    i32 result = -1;

#if SHUM_HOST_WINDOWS
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

    char *line = SHUILD.JOBS.commands[index];
    SHUILD.JOBS.count--;
    SHUILD.JOBS.processes[index] = SHUILD.JOBS.processes[SHUILD.JOBS.count];
    SHUILD.JOBS.commands[index] = SHUILD.JOBS.commands[SHUILD.JOBS.count];

    if (result != 0)
    {
        SHUI_CReport(result, false, line);

        if (SHUILD.JOBS.failure == 0)
        {
            SHUILD.JOBS.failure = result;
        }
    }

    free(line);
}

static void SHUI_CStartJob(const SHUI_StringList *command)
{
    if (SHUILD.JOBS.limit == 0)
    {
#if SHUM_HOST_WINDOWS
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

    char *line = NULL;
    i64 process = SHUI_CStart(command, &line);

    if (process < 0)
    {
        SHUI_CReport(-1, false, line);
        free(line);
        SHUILD.JOBS.failure = SHUILD.JOBS.failure == 0 ? -1 : SHUILD.JOBS.failure;
        return;
    }

    SHUILD.JOBS.processes[SHUILD.JOBS.count] = process;
    SHUILD.JOBS.commands[SHUILD.JOBS.count++] = line;
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
        SHU_UtilFail(failure, SHUM_LOG_NAME("%s") " failed to compile.", SHUILD.MODULE.name);
    }
#else
    (void)failure;
#endif
}

static SHUFileType SHUI_UFileExists(const char *path)
{
#if SHUM_HOST_WINDOWS
    DWORD attributes = GetFileAttributesA(path);

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
    if (stat(path, &stats) == 0)
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

static void SHUI_UMakeDirectory(const char *path)
{
    i32 result = 0;

#if SHUM_HOST_WINDOWS
    result = _mkdir(path);
#else
    result = mkdir(path, 0755);
#endif

    if (result != 0 && errno != EEXIST)
    {
        SHU_UtilFail(result, "directory " SHUM_LOG_PATH("%s") " cannot be made: %s", SHUI_PShort(path), strerror(errno));
    }
}

static void SHUI_UMakeDirectoryRecursive(const char *path)
{
    // each directory on the way is made, ending the path after it for a moment
    char *partial = SHUI_Copy(path);

    for (usz i = 1; partial[i] != '\0'; i++)
    {
        if (partial[i] == SHUM_PATH_SEPARATOR)
        {
            partial[i] = '\0';
            SHUI_UMakeDirectory(partial);
            partial[i] = SHUM_PATH_SEPARATOR;
        }
    }

    SHUI_UMakeDirectory(partial);
    free(partial);
}

static void SHUI_UDeleteSingleFile(const char *path)
{
    i32 result = remove(path);

    if (result != 0)
    {
        SHU_UtilFail(result, "file " SHUM_LOG_PATH("%s") " cannot be deleted: %s", SHUI_PShort(path), strerror(errno));
    }
}

#if SHUM_HOST_WINDOWS
static void SHUI_UDeleteDirectory(const char *path)
{
    i32 result = _rmdir(path);

    if (result != 0)
    {
        SHU_UtilFail(result, "directory " SHUM_LOG_PATH("%s") " cannot be deleted: %s", SHUI_PShort(path), strerror(errno));
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

static void SHUI_UDeleteRecursive(const char *path)
{
    SHUFileType fileType = SHUI_UFileExists(path);

    SHU_Assert(fileType != SHUFileType_Invalid, "File '%s' does not exist.", path);

    if (fileType == SHUFileType_Regular)
    {
        SHUI_UDeleteSingleFile(path);
        return;
    }

#if SHUM_HOST_WINDOWS
    WIN32_FIND_DATAA ffd;
    char *pattern = SHU_UtilFormat("%s\\*", path);
    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    free(pattern);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
            continue;

        char *subPath = SHU_UtilFormat("%s\\%s", path, ffd.cFileName);

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            SHUI_UDeleteRecursive(subPath);
        }
        else
        {
            SHUI_UDeleteSingleFile(subPath);
        }

        free(subPath);
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
    SHUI_UDeleteDirectory(path);
#else
    nftw(path, SHUI_UNftwCallback, 64, FTW_DEPTH | FTW_PHYS);
#endif
}

static SHUSlice SHUI_UReadFile(const char *path)
{
    FILE *fileHandle = fopen(path, "rb");

    if (fileHandle == NULL)
    {
        SHU_UtilFail(SHUResult_ErrFile, "file " SHUM_LOG_PATH("%s") " cannot be read: %s", SHUI_PShort(path), strerror(errno));
    }

    fseek(fileHandle, 0, SEEK_END);
    long fileLength = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    SHU_Assert(fileLength >= 0, "File size getting failed for '%s'.", path);

    char *buffer = (char *)SHUI_Allocate((usz)fileLength + 1);

    usz fileRead = (usz)fread(buffer, 1, (size_t)fileLength, fileHandle);
    SHU_Assert(fileRead == (usz)fileLength, "File read failed for '%s'.", path);
    buffer[fileLength] = '\0';
    fclose(fileHandle);

    return cs(buffer, (usz)fileLength);
}

static void SHUI_UWriteFile(const char *path, SHUSliceView content)
{
    SHU_Assert(content.data != NULL || content.size == 0, "Content to write to '%s' is NULL.", path);

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

    FILE *fileHandle = fopen(path, "wb");

    if (fileHandle == NULL)
    {
        SHU_UtilFail(SHUResult_ErrFile, "file " SHUM_LOG_PATH("%s") " cannot be written: %s", SHUI_PShort(path), strerror(errno));
    }

    usz fileWritten = content.size == 0 ? 0 : (usz)fwrite(content.data, 1, content.size, fileHandle);
    SHU_Assert(fileWritten == content.size, "File write failed for '%s'.", path);
    fclose(fileHandle);
}

static void SHUI_UCopySingleFile(const char *src, const char *dst)
{
    SHUSlice content = SHUI_UReadFile(src);
    SHUI_UWriteFile(dst, csv(content));
    free(content.data);

#if !SHUM_HOST_WINDOWS
    // the copy keeps the permissions, so a copied program or script still runs
    struct stat stats;

    if (stat(src, &stats) == 0 && chmod(dst, stats.st_mode & 07777) != 0)
    {
        SHU_UtilFail(SHUResult_ErrFile, "permissions of " SHUM_LOG_PATH("%s") " cannot be set: %s", SHUI_PShort(dst), strerror(errno));
    }
#endif
}

static void SHUI_UCopyRecursive(const char *src, const char *dst)
{
    SHUFileType fileType = SHUI_UFileExists(src);

    SHU_Assert(fileType != SHUFileType_Invalid, "File '%s' does not exist", src);

    if (fileType == SHUFileType_Regular)
    {
        SHUI_UCopySingleFile(src, dst);
        return;
    }

    SHUFileType destinationType = SHUI_UFileExists(dst);

    SHU_Assert(destinationType != SHUFileType_Regular, "Directory '%s' already exist as a regular file", src);

    if (destinationType == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(dst);
    }

#if SHUM_HOST_WINDOWS
    WIN32_FIND_DATAA ffd;
    char *pattern = SHU_UtilFormat("%s\\*", src);
    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    free(pattern);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHU_UtilFail(SHUResult_ErrInternal, "directory " SHUM_LOG_PATH("%s") " cannot be opened.", SHUI_PShort(src));
    }

    do
    {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
        {
            continue;
        }

        char *from = SHU_UtilFormat("%s\\%s", src, ffd.cFileName);
        char *to = SHU_UtilFormat("%s\\%s", dst, ffd.cFileName);
        SHUI_UCopyRecursive(from, to);
        free(from);
        free(to);
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(src);
    if (!dir)
    {
        SHU_UtilFail(SHUResult_ErrInternal, "directory " SHUM_LOG_PATH("%s") " cannot be opened.", SHUI_PShort(src));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char *from = SHU_UtilFormat("%s/%s", src, entry->d_name);
        char *to = SHU_UtilFormat("%s/%s", dst, entry->d_name);
        SHUI_UCopyRecursive(from, to);
        free(from);
        free(to);
    }

    closedir(dir);
#endif
}

static void SHUI_URenameFile(const char *file, const char *name)
{
    if (SHUI_UFileExists(name) != SHUFileType_Invalid)
    {
        SHUI_UDeleteRecursive(name);
    }

    i32 result = rename(file, name);

    if (result != 0)
    {
        SHU_UtilFail(result, SHUM_LOG_PATH("%s") " cannot be renamed to " SHUM_LOG_PATH("%s") ": %s", SHUI_PShort(file), SHUI_PShort(name), strerror(errno));
    }
}

static i64 SHUI_UGetFileEditTime(const char *file)
{
    // in nanoseconds, so a file edited in the same second as its object was compiled is still seen as newer
    struct stat attr;
    i32 result = stat(file, &attr);

    if (result != 0)
    {
        SHU_UtilFail(SHUResult_ErrInternal, "file " SHUM_LOG_PATH("%s") " cannot be found: %s", SHUI_PShort(file), strerror(errno));
    }

#if SHUM_HOST_LINUX
    return (i64)attr.st_mtim.tv_sec * 1000000000LL + (i64)attr.st_mtim.tv_nsec;
#elif SHUM_HOST_MACOS
    return (i64)attr.st_mtimespec.tv_sec * 1000000000LL + (i64)attr.st_mtimespec.tv_nsec;
#else
    return (i64)attr.st_mtime * 1000000000LL;
#endif
}

static bool SHUI_CDependencyDirty(const char *dependencyFile, const char *targetFile)
{
    i64 objectTime = SHUI_UGetFileEditTime(targetFile);

    SHUSlice dependencies = SHUI_UReadFile(dependencyFile);
    const char *text = (const char *)dependencies.data;
    usz length = dependencies.size;

    // the target ends at a colon followed by a space or the end of the line, so a Windows drive, as in D:\project\main.o, is part of its path
    usz offset = 0;
    while (offset < length && !(text[offset] == ':' && (offset + 1 == length || text[offset + 1] == ' ' || text[offset + 1] == '\t' || text[offset + 1] == '\r' || text[offset + 1] == '\n')))
    {
        offset++;
    }
    offset++;

    // the compiler escapes a space in a file name with a backslash, and ends a line that goes on with one
    SHUI_Builder dependentFile = {0};

    while (offset <= length)
    {
        char c = offset < length ? text[offset] : '\0';

        if (c == '\\' && offset + 1 < length && text[offset + 1] == ' ')
        {
            SHUI_BAppendChar(&dependentFile, ' ');
            offset += 2;
            continue;
        }

        if (c == '\\' && offset + 1 < length && (text[offset + 1] == '\r' || text[offset + 1] == '\n'))
        {
            offset++;
            continue;
        }

        if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\0')
        {
            if (dependentFile.length != 0)
            {
                char *file = SHUI_BTake(&dependentFile);
                bool newer = objectTime < SHUI_UGetFileEditTime(file);
                free(file);

                if (newer)
                {
                    free(dependencies.data);
                    return true;
                }
            }
        }
        else
        {
            SHUI_BAppendChar(&dependentFile, c);
        }

        offset++;
    }

    free(dependentFile.data);
    free(dependencies.data);
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

    char *executablePath = SHU_UtilFormat("%s%s", SHUILD.currentExecutableDirectory, executableFileName);
    char *sourcePath = SHU_UtilFormat("%s%s", SHUILD.currentExecutableDirectory, sourceFileName);

    i64 exeTime = SHUI_UGetFileEditTime(executablePath);
    i64 sourceTime = SHUI_UGetFileEditTime(sourcePath);

    bool rebuild = (exeTime < sourceTime);

    if (!rebuild)
    {
        char *depFileMap = SHU_UtilFormat("%s." SHUC_FILE_EXTENSION, executablePath);

        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUI_CScriptCompiler());
        SHUI_CAddArgument(&command, "-MM");
        SHUI_CAddArgument(&command, sourcePath);
        SHUI_CAddArgument(&command, "-MF");
        SHUI_CAddArgument(&command, depFileMap);
        // when the dependencies cannot be listed, the rebuild shows why
        if (SHUI_CRun(&command, false) != 0 || SHUI_CDependencyDirty(depFileMap, executablePath))
        {
            rebuild = true;
        }

        if (SHUI_UFileExists(depFileMap) == SHUFileType_Regular)
        {
            SHUI_UDeleteSingleFile(depFileMap);
        }

        SHUI_SLFree(&command);
        free(depFileMap);
    }

    if (!rebuild)
    {
        free(executablePath);
        free(sourcePath);
        return;
    }

    SHU_UtilLog("the build script changed; rebuilding it");

    char *oldExePath = SHU_UtilFormat("%s.old", executablePath);
    SHUI_URenameFile(executablePath, oldExePath);

    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUI_CScriptCompiler());
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, executablePath);
    SHUI_CAddArgument(&command, sourcePath);
    SHUI_CAddArguments(&command, SHUILD_BUILD);
    i32 result = SHUI_CRun(&command, false);
    SHUI_SLFree(&command);

    if (result == 0)
    {
        i32 spawnResult = SHU_UtilSpawnProcessSync(executablePath, argv);
        exit(spawnResult);
    }
    else
    {
        SHUI_URenameFile(oldExePath, executablePath);
        SHU_UtilFail(result, "the build script cannot be rebuilt.");
    }
}

#ifdef SHUC_ENABLE_INCREMENTAL
static SHUI_Hash SHUI_CModuleStateHash(void)
{
    SHUI_Hash hash = 14695981039346656037ULL;

#define SHUI_HASH_BYTE(byte) hash = ((hash ^ (SHUI_Hash)(byte)) * 1099511628211ULL)
#define SHUI_HASH_MIX hash ^= (hash >> 17)
#define SHUI_HASH_STRING(string)                    \
    for (const char *c = (string); *c != '\0'; c++) \
    {                                               \
        SHUI_HASH_BYTE((u8)*c);                     \
    }                                               \
    SHUI_HASH_MIX
    // the count tells an empty list from none
#define SHUI_HASH_LIST(list)                  \
    SHUI_HASH_BYTE((list).count);             \
    for (usz i = 0; i < (list).count; i++)    \
    {                                         \
        SHUI_HASH_STRING((list).data[i]);     \
    }

    SHUI_HASH_STRING(SHUILD.cacheDirectory);

    SHUI_HASH_BYTE(SHUILD.COMPILER.identifier);
    SHUI_HASH_MIX;

    SHUI_HASH_STRING(SHUILD.COMPILER.command);
    SHUI_HASH_LIST(SHUILD.COMPILER.flags);
    SHUI_HASH_LIST(SHUILD.COMPILER.linkerFlags);
    SHUI_HASH_STRING(SHUILD.currentExecutableDirectory);
    SHUI_HASH_STRING(SHUILD.MODULE.name);
    SHUI_HASH_STRING(SHUILD.MODULE.root);
    SHUI_HASH_LIST(SHUILD.MODULE.includeDirectories);
    SHUI_HASH_LIST(SHUILD.MODULE.sourceFiles);
    SHUI_HASH_LIST(SHUILD.MODULE.linkDirectories);
    SHUI_HASH_LIST(SHUILD.MODULE.links);

#undef SHUI_HASH_LIST
#undef SHUI_HASH_STRING

    return hash;
}

static char *SHUI_CModuleStateFile(const char *moduleName)
{
    return SHU_UtilFormat("%s%s%c%s.%s", SHUILD.cacheDirectory, moduleName, SHUM_PATH_SEPARATOR, moduleName, SHUC_MODULE_FILE_EXTENSION);
}

static void SHUI_CModuleStateUpdate(const char *moduleName)
{
    char *moduleCacheFile = SHUI_CModuleStateFile(moduleName);
    char *moduleCacheDirectory = SHU_UtilFormat("%s%s%c", SHUILD.cacheDirectory, moduleName, SHUM_PATH_SEPARATOR);

    SHUI_UMakeDirectoryRecursive(moduleCacheDirectory);
    free(moduleCacheDirectory);

    SHUI_Hash currentConfig = SHUI_CModuleStateHash();

    FILE *cacheFileHandle = fopen(moduleCacheFile, "w+");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile);
    fprintf(cacheFileHandle, "%llu", (unsigned long long)currentConfig);
    fclose(cacheFileHandle);
    free(moduleCacheFile);
}

static bool SHUI_CModuleStateDirty(const char *moduleName)
{
    char *moduleCacheFile = SHUI_CModuleStateFile(moduleName);

    if (SHUI_UFileExists(moduleCacheFile) != SHUFileType_Regular)
    {
        free(moduleCacheFile);
        return true;
    }

    SHUI_Hash currentConfig = SHUI_CModuleStateHash();

    char buffer[SHUC_MAX_HASH_BUFFER_SIZE] = {0};

    FILE *cacheFileHandle = fopen(moduleCacheFile, "r");
    SHU_Assert(cacheFileHandle != NULL, "File open failed for '%s'", moduleCacheFile);
    usz bufferRead = (usz)fread(buffer, 1, sizeof(buffer), cacheFileHandle);
    SHU_Assert(bufferRead < sizeof(buffer), "Buffer overflow for '%s'", moduleCacheFile);
    fclose(cacheFileHandle);
    free(moduleCacheFile);

    SHUI_Hash savedConfig = strtoull(buffer, NULL, 10);

    return currentConfig != savedConfig;
}

static bool SHUI_CUnitRequiresCompilation(const char *sourceFile, char **retObjectFile, char **retDependencyFile)
{
    // the source's path in the module, without its extension's last letter
    usz fileStartIndex = (usz)strlen(SHUILD.MODULE.root);
    int unitLength = (int)((usz)strlen(sourceFile) - fileStartIndex - 1);

    *retDependencyFile = SHU_UtilFormat("%s%s%c%.*s%s",
                                        SHUILD.cacheDirectory,
                                        SHUILD.MODULE.name,
                                        SHUM_PATH_SEPARATOR,
                                        unitLength,
                                        sourceFile + fileStartIndex,
                                        SHUC_FILE_EXTENSION);

    *retObjectFile = SHU_UtilFormat("%s%s%c%.*s%s",
                                    SHUILD.cacheDirectory,
                                    SHUILD.MODULE.name,
                                    SHUM_PATH_SEPARATOR,
                                    unitLength,
                                    sourceFile + fileStartIndex,
                                    "o");

    if (SHUI_UFileExists(*retObjectFile) == SHUFileType_Regular &&
        SHUI_UFileExists(*retDependencyFile) == SHUFileType_Regular &&
        !SHUI_CDependencyDirty(*retDependencyFile, *retObjectFile))
    {
        return false;
    }

    char *directory = SHUI_PDirectory(*retObjectFile);
    SHUI_UMakeDirectoryRecursive(directory);
    free(directory);
    return true;
}
#endif

static void SHUI_CCompileUnit(const char *sourceFile, const char *objectFile, const char *dependencyFile, const char *extraFlag)
{
    // the compiler writes the dependency file as it compiles, with the module's flags, so the headers that definitions include are in it too
    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUILD.COMPILER.command);
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, objectFile);
    SHUI_CAddArgument(&command, "-c");

    if (extraFlag != NULL)
    {
        SHUI_CAddArgument(&command, extraFlag);
    }

    // a single header library is compiled as C, with the definition that holds its implementation, instead of as a precompiled header
    if (SHUI_SEndsWithC(sourceFile, ".h"))
    {
        SHUI_CAddArgument(&command, "-x");
        SHUI_CAddArgument(&command, "c");
    }

    SHUI_CAddArgument(&command, sourceFile);
    SHUI_CAddFlags(&command);
    SHUI_CAddIncludeDirectories(&command);

    if (dependencyFile != NULL)
    {
        SHUI_CAddArgument(&command, "-MMD");
        SHUI_CAddArgument(&command, "-MF");
        SHUI_CAddArgument(&command, dependencyFile);
    }

    SHUI_CStartJob(&command);
    SHUI_SLFree(&command);
    SHUILD.MODULE.compiledCount++;
}

static void SHUI_MAddSourceDirectoryRecursive(const char *path)
{
#if SHUM_HOST_WINDOWS
    WIN32_FIND_DATAA ffd = {0};
    char *pattern = SHU_UtilFormat("%s*", path);
    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    free(pattern);
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
            char *directory = SHU_UtilFormat("%s%s\\", path, ffd.cFileName);
            SHUI_MAddSourceDirectoryRecursive(directory);
            free(directory);
        }
        else if (SHUI_SEndsWithC(ffd.cFileName, ".c"))
        {
            SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, SHU_UtilFormat("%s%s", path, ffd.cFileName));
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path);

    if (!dir)
    {
        SHU_UtilFail(SHUResult_ErrInternal, "directory " SHUM_LOG_PATH("%s") " cannot be opened.", SHUI_PShort(path));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char *entryPath = SHU_UtilFormat("%s%s", path, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0 && S_ISDIR(st.st_mode))
        {
            char *directory = SHU_UtilFormat("%s/", entryPath);
            SHUI_MAddSourceDirectoryRecursive(directory);
            free(directory);
            free(entryPath);
        }
        else if (SHUI_SEndsWithC(entry->d_name, ".c"))
        {
            SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, entryPath);
        }
        else
        {
            free(entryPath);
        }
    }

    closedir(dir);
#endif
}

static SHUI_Library *SHUI_MFindLibrary(const char *name)
{
    for (usz i = 0; i < SHUILD.LIBRARIES.count; i++)
    {
        if (strcmp(SHUILD.LIBRARIES.data[i].name, name) == 0)
        {
            return &SHUILD.LIBRARIES.data[i];
        }
    }

    return NULL;
}

// a library keeps its public include directories for the modules that link it;
// a static library cannot be linked with other libraries, so it keeps the ones it links too, and the module that links it gets them
static void SHUI_MRecordLibrary(bool keepLinks)
{
    SHUI_Library *library = SHUI_MFindLibrary(SHUILD.MODULE.name);

    if (library == NULL)
    {
        if (SHUILD.LIBRARIES.count >= SHUILD.LIBRARIES.capacity)
        {
            usz capacity = SHUI_GrowCapacity(SHUILD.LIBRARIES.capacity);
            SHUILD.LIBRARIES.data = (SHUI_Library *)SHUI_Reallocate(SHUILD.LIBRARIES.data, sizeof(SHUI_Library) * capacity);
            SHUILD.LIBRARIES.capacity = capacity;
        }

        library = &SHUILD.LIBRARIES.data[SHUILD.LIBRARIES.count++];
        *library = (SHUI_Library){.name = SHUI_Copy(SHUILD.MODULE.name)};
    }

    // a library compiled again replaces what it kept, and takes the module's lists, which the module then does not free
    SHUI_SLFree(&library->includeDirectories);
    SHUI_SLFree(&library->links);
    SHUI_SLFree(&library->linkDirectories);

    library->includeDirectories = SHUI_SLTake(&SHUILD.MODULE.publicIncludeDirectories);

    if (keepLinks)
    {
        library->links = SHUI_SLTake(&SHUILD.MODULE.links);
        library->linkDirectories = SHUI_SLTake(&SHUILD.MODULE.linkDirectories);
    }
}

// the module gets the public include directories of the libraries it links itself, but not of the libraries those link
static void SHUI_MAddLinkedIncludes(void)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        const SHUI_Library *library = SHUI_MFindLibrary(SHUILD.MODULE.links.data[i]);

        for (usz j = 0; library != NULL && j < library->includeDirectories.count; j++)
        {
            if (!SHUI_SLContains(&SHUILD.MODULE.linkedIncludeDirectories, library->includeDirectories.data[j]))
            {
                SHUI_SLAdd(&SHUILD.MODULE.linkedIncludeDirectories, SHUI_Copy(library->includeDirectories.data[j]));
            }
        }
    }
}

static void SHUI_MExpandLink(SHUI_StringList *links, const char *link, usz depth)
{
    // a library that links itself through others would expand forever
    SHU_Assert(depth < 64, "Library '%s' links itself through other libraries.", link);

    SHUI_SLAdd(links, SHUI_Copy(link));

    const SHUI_Library *library = SHUI_MFindLibrary(link);

    if (library == NULL)
    {
        return;
    }

    for (usz i = 0; i < library->linkDirectories.count; i++)
    {
        if (!SHUI_SLContains(&SHUILD.MODULE.linkDirectories, library->linkDirectories.data[i]))
        {
            SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, SHUI_Copy(library->linkDirectories.data[i]));
        }
    }

    for (usz i = 0; i < library->links.count; i++)
    {
        SHUI_MExpandLink(links, library->links.data[i], depth + 1);
    }
}

// each static library the module links brings the libraries it keeps, after it, so the linker finds what it needs in order
static void SHUI_MExpandLinks(void)
{
    SHUI_StringList links = {0};

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_MExpandLink(&links, SHUILD.MODULE.links.data[i], 0);
    }

    // a library that comes more than once stays in its last place, after every library that needs it
    SHUI_StringList reversed = {0};

    for (usz i = links.count; i > 0; i--)
    {
        if (!SHUI_SLContains(&reversed, links.data[i - 1]))
        {
            SHUI_SLAdd(&reversed, SHUI_Copy(links.data[i - 1]));
        }
    }

    SHUI_SLFree(&links);
    SHUI_SLFree(&SHUILD.MODULE.links);

    for (usz i = reversed.count; i > 0; i--)
    {
        SHUI_SLAdd(&SHUILD.MODULE.links, SHUI_Copy(reversed.data[i - 1]));
    }

    SHUI_SLFree(&reversed);
}

// the dynamic library's file where the linker finds it: on Windows, its import library, which names the DLL
static char *SHUI_MLinkedDynamicFile(const char *name)
{
    return SHUILD.COMPILER.target == SHUPlatform_Windows ? SHU_UtilFormat("lib%s.dll.a", name) : SHU_UtilLibraryFile(name, SHUModuleType_LibraryDynamic);
}

#ifdef SHUC_ENABLE_INCREMENTAL
// a module is linked again when a library it links is newer than its output
static bool SHUI_MLinksNewer(const char *outFile)
{
    i64 outTime = SHUI_UGetFileEditTime(outFile);

    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        for (usz j = 0; j < SHUILD.MODULE.links.count; j++)
        {
            char *files[] = {
                SHU_UtilLibraryFile(SHUILD.MODULE.links.data[j], SHUModuleType_LibraryStatic),
                SHUI_MLinkedDynamicFile(SHUILD.MODULE.links.data[j]),
            };
            bool newer = false;

            for (usz k = 0; k < sizeof(files) / sizeof(*files); k++)
            {
                char *libFile = SHU_UtilFormat("%s%s", SHUILD.MODULE.linkDirectories.data[i], files[k]);

                newer = newer || (SHUI_UFileExists(libFile) == SHUFileType_Regular && SHUI_UGetFileEditTime(libFile) > outTime);
                free(libFile);
                free(files[k]);
            }

            if (newer)
            {
                return true;
            }
        }
    }

    return false;
}
#endif

// a directory is searched at run time only if it holds a dynamic library that the module links
static bool SHUI_MHoldsDynamicLink(const char *directory)
{
    bool holds = false;

    for (usz i = 0; i < SHUILD.MODULE.links.count && !holds; i++)
    {
        char *file = SHU_UtilLibraryFile(SHUILD.MODULE.links.data[i], SHUModuleType_LibraryDynamic);
        char *path = SHU_UtilFormat("%s%s", directory, file);
        holds = SHUI_UFileExists(path) == SHUFileType_Regular;
        free(path);
        free(file);
    }

    return holds;
}

/// @param directory Output directory of the module, from which its run-time search paths start.
static void SHUI_MAddLinks(SHUI_StringList *command, const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.linkDirectories.count; i++)
    {
        const char *linkDirectory = SHUILD.MODULE.linkDirectories.data[i];

        SHUI_SLAdd(command, SHU_UtilFormat("-L%s", linkDirectory));

        // the path from the module's own directory, so the two can move together; Windows has none, see SHU_ModuleCopyDynamicLinks
        if (SHUILD.COMPILER.target != SHUPlatform_Windows && SHUI_MHoldsDynamicLink(linkDirectory))
        {
            char *relative = SHUI_PRelative(directory, linkDirectory);
            usz length = (usz)strlen(relative);

            SHUI_SLAdd(command, SHU_UtilFormat("-Wl,-rpath,%s%s%.*s",
                                               SHUILD.COMPILER.target == SHUPlatform_MacOS ? "@loader_path" : "$ORIGIN",
                                               length == 0 ? "" : "/",
                                               (int)(length == 0 ? 0 : length - 1),
                                               relative));
            free(relative);
        }
    }

    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        SHUI_SLAdd(command, SHU_UtilFormat("-l%s", SHUILD.MODULE.links.data[i]));
    }
}

// the dynamic libraries the module links go beside it, from the first directory that holds each
static void SHUI_MCopyDynamicLinks(const char *directory)
{
    for (usz i = 0; i < SHUILD.MODULE.links.count; i++)
    {
        char *file = SHU_UtilLibraryFile(SHUILD.MODULE.links.data[i], SHUModuleType_LibraryDynamic);

        for (usz j = 0; j < SHUILD.MODULE.linkDirectories.count; j++)
        {
            char *library = SHU_UtilFormat("%s%s", SHUILD.MODULE.linkDirectories.data[j], file);
            bool found = SHUI_UFileExists(library) == SHUFileType_Regular;

            if (found)
            {
                char *from = SHUI_PClean(SHUILD.MODULE.linkDirectories.data[j]);
                char *to = SHUI_PClean(directory);

                if (strcmp(from, to) != 0)
                {
                    char *copy = SHU_UtilFormat("%s%s", directory, file);
                    SHUI_UCopySingleFile(library, copy);
                    free(copy);
                }

                free(from);
                free(to);
            }

            free(library);

            if (found)
            {
                break;
            }
        }

        free(file);
    }
}

static void SHUI_MCompileExecutable(const char *directory)
{
    SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, SHUI_Copy(SHUILD.currentExecutableDirectory));

    bool skipExePacking = true;

    SHUI_StringList inputFiles = {0};
    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *objectFile = NULL;
        char *dependencyFile = NULL;

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, objectFile, dependencyFile, NULL);

            skipExePacking = false;
        }

        free(dependencyFile);
        SHUI_SLAdd(&inputFiles, objectFile);
#else
        skipExePacking = false;
        SHUILD.MODULE.compiledCount++;

        SHUI_SLAdd(&inputFiles, SHUI_Copy(sourceFile));
#endif
    }

    SHUI_CWaitJobs();

    char *outFile = SHU_UtilFormat("%s%s%s",
                                   directory,
                                   SHUILD.MODULE.name,
                                   SHUILD.COMPILER.target == SHUPlatform_Windows ? ".exe" : "");

#ifdef SHUC_ENABLE_INCREMENTAL
    if (SHUI_UFileExists(outFile) != SHUFileType_Regular || SHUI_MLinksNewer(outFile))
    {
        skipExePacking = false;
    }
#endif

    if (!skipExePacking)
    {
        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command);
        SHUI_CAddArgument(&command, "-o");
        SHUI_CAddArgument(&command, outFile);
        SHUI_CAddIncludeDirectories(&command);

        for (usz i = 0; i < inputFiles.count; i++)
        {
            SHUI_CAddArgument(&command, inputFiles.data[i]);
        }

        SHUI_MAddLinks(&command, directory);

        SHUI_CAddFlags(&command);
        SHUI_CAddLinkerFlags(&command);
        SHUI_CRun(&command, true);
        SHUI_SLFree(&command);
        SHUILD.MODULE.output = outFile;
    }
    else
    {
        free(outFile);
    }

    SHUI_SLFree(&inputFiles);
}

static void SHUI_MCompileLibraryStatic(const char *directory)
{
    SHUI_StringList objFiles = {0};

    bool skipLibPacking = true;

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        char *objectFile = NULL;
        char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *dependencyFile = NULL;

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, objectFile, dependencyFile, NULL);

            skipLibPacking = false;
        }

        free(dependencyFile);
#else
        skipLibPacking = false;

        objectFile = SHU_UtilFormat("%.*so", (int)(strlen(sourceFile) - 1), sourceFile);

        SHUI_CCompileUnit(sourceFile, objectFile, NULL, NULL);
#endif

        SHUI_SLAdd(&objFiles, objectFile);
    }

    SHUI_CWaitJobs();

    char *libraryName = SHU_UtilLibraryFile(SHUILD.MODULE.name, SHUModuleType_LibraryStatic);
    char *libraryFile = SHU_UtilFormat("%s%s", directory, libraryName);
    free(libraryName);

    if (SHUI_UFileExists(libraryFile) != SHUFileType_Regular)
    {
        skipLibPacking = false;
    }

    if (!skipLibPacking)
    {
        // ar adds to an archive that exists, so the archive is made again, without the objects of sources that are gone
        if (SHUI_UFileExists(libraryFile) == SHUFileType_Regular)
        {
            SHUI_UDeleteSingleFile(libraryFile);
        }

        SHUI_StringList command = {0};
        SHUI_SLAdd(&command, SHUI_CArchiver());
        SHUI_CAddArgument(&command, "rcs");
        SHUI_CAddArgument(&command, libraryFile);

        for (usz i = 0; i < objFiles.count; i++)
        {
            SHUI_CAddArgument(&command, objFiles.data[i]);
        }

        SHUI_CRun(&command, true);
        SHUI_SLFree(&command);
        SHUILD.MODULE.output = libraryFile;
    }
    else
    {
        free(libraryFile);
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (usz i = 0; i < objFiles.count; i++)
    {
        SHUI_UDeleteSingleFile(objFiles.data[i]);
    }
#endif

    SHUI_SLFree(&objFiles);
}

static void SHUI_MCompileLibraryDynamic(const char *directory)
{
    SHUI_StringList objFiles = {0};

    bool skipLibPacking = true;

    // code for a DLL needs no position-independent flag, and some compilers refuse it
    const char *positionIndependent = SHUILD.COMPILER.target == SHUPlatform_Windows ? NULL : "-fPIC";

    for (usz i = 0; i < SHUILD.MODULE.sourceFiles.count; i++)
    {
        char *objectFile = NULL;
        char *sourceFile = SHUILD.MODULE.sourceFiles.data[i];

#ifdef SHUC_ENABLE_INCREMENTAL
        char *dependencyFile = NULL;

        if (SHUI_CUnitRequiresCompilation(sourceFile, &objectFile, &dependencyFile))
        {
            SHUI_CCompileUnit(sourceFile, objectFile, dependencyFile, positionIndependent);

            skipLibPacking = false;
        }

        free(dependencyFile);
#else
        skipLibPacking = false;

        objectFile = SHU_UtilFormat("%.*so", (int)(strlen(sourceFile) - 1), sourceFile);

        SHUI_CCompileUnit(sourceFile, objectFile, NULL, positionIndependent);
#endif

        SHUI_SLAdd(&objFiles, objectFile);
    }

    SHUI_CWaitJobs();

    char *libraryName = SHU_UtilLibraryFile(SHUILD.MODULE.name, SHUModuleType_LibraryDynamic);
    char *libraryFile = SHU_UtilFormat("%s%s", directory, libraryName);
    free(libraryName);

    if (SHUI_UFileExists(libraryFile) != SHUFileType_Regular)
    {
        skipLibPacking = false;
    }
#ifdef SHUC_ENABLE_INCREMENTAL
    else if (SHUI_MLinksNewer(libraryFile))
    {
        skipLibPacking = false;
    }
#endif

    if (!skipLibPacking)
    {
        SHUI_StringList command = {0};
        SHUI_CAddArguments(&command, SHUILD.COMPILER.command);
        SHUI_CAddArgument(&command, "-shared");
        SHUI_CAddArgument(&command, "-o");
        SHUI_CAddArgument(&command, libraryFile);

        // a DLL is linked through its import library, which -l finds as lib<name>.dll.a
        if (SHUILD.COMPILER.target == SHUPlatform_Windows)
        {
            char *importLibrary = SHUI_MLinkedDynamicFile(SHUILD.MODULE.name);
            SHUI_SLAdd(&command, SHU_UtilFormat("-Wl,--out-implib,%s%s", directory, importLibrary));
            free(importLibrary);
        }

        for (usz i = 0; i < objFiles.count; i++)
        {
            SHUI_CAddArgument(&command, objFiles.data[i]);
        }

        SHUI_MAddLinks(&command, directory);
        SHUI_CAddLinkerFlags(&command);
        SHUI_CRun(&command, true);
        SHUI_SLFree(&command);
        SHUILD.MODULE.output = libraryFile;
    }
    else
    {
        free(libraryFile);
    }

#ifndef SHUC_ENABLE_INCREMENTAL
    for (usz i = 0; i < objFiles.count; i++)
    {
        SHUI_UDeleteSingleFile(objFiles.data[i]);
    }
#endif

    SHUI_SLFree(&objFiles);
}

#pragma endregion Internals

#pragma region Utility

static i32 SHUI_URunCommand(bool stopOnFailure, const char *command)
{
#ifdef SHUC_LOG_COMMANDS
    SHU_UtilLog("$ " SHUM_LOG_COMMAND("%s"), command);
#endif

    i32 result = system(command);

#if !SHUM_HOST_WINDOWS
    // system returns the wait status, not the exit code
    result = result == -1 ? -1 : WIFEXITED(result) ? WEXITSTATUS(result) : -1;
#endif

    if (result != 0 && !stopOnFailure)
    {
        SHU_UtilWarn("command failed with exit code %d: " SHUM_LOG_COMMAND("%s"), result, command);
    }
    else
    {
        SHUI_CReport(result, true, command);
    }

    return result;
}

i32 SHU_UtilRun(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    i32 result = SHUI_URunCommand(true, command);
    free(command);

    return result;
}

i32 SHU_UtilRunTry(const char *commandFormat, ...)
{
    SHU_AssertNullPointer(commandFormat);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    i32 result = SHUI_URunCommand(false, command);
    free(command);

    return result;
}

i32 SHU_UtilRunLogged(const char *log, const char *commandFormat, ...)
{
    SHU_AssertNullPointer(log);
    SHU_AssertNullPointer(commandFormat);

    // the path gets the system's separators, so its directory can be made on Windows too
    char *logPath = SHUI_PPath(SHUILD.currentExecutableDirectory, log, false);

    // the log's directory is made first, as the shell does not make it
    char *logDirectory = SHUI_PDirectory(logPath);
    SHUI_UMakeDirectoryRecursive(logDirectory);
    free(logDirectory);

    va_list args;
    va_start(args, commandFormat);
    char *command = SHUI_VFormat(commandFormat, args);
    va_end(args);

    // both POSIX shells and cmd.exe send the output and the errors to the file this way
    char *logged = SHU_UtilFormat("%s > \"%s\" 2>&1", command, logPath);
    i32 result = SHUI_URunCommand(false, logged);
    free(logged);

    if (result != 0)
    {
        // the end of the log tells why it failed
        SHUSlice text = SHUI_UReadFile(logPath);
        const char *start = (const char *)text.data + text.size;

        for (usz lines = 0; start > (const char *)text.data && lines <= 20; start--)
        {
            lines += start[-1] == '\n';
        }

        fprintf(SHU_LOG_STREAM, "%s\n", start);
        free(text.data);

#ifdef SHUC_NO_RUN_ERROR
        SHU_UtilFail(0, "command failed with exit code %d; " SHUM_LOG_PATH("%s") " has its output: " SHUM_LOG_COMMAND("%s"), result, SHUI_PShort(logPath), command);
#else
        SHU_UtilFail(result, "command failed with exit code %d; " SHUM_LOG_PATH("%s") " has its output: " SHUM_LOG_COMMAND("%s"), result, SHUI_PShort(logPath), command);
#endif
    }

    free(command);
    free(logPath);

    return result;
}

void SHU_UtilBuildScript(const char *script, const char *program, const char *flags, const char *arguments)
{
    SHU_AssertNullPointer(script);
    SHU_AssertNullPointer(program);
    SHU_AssertNullPointer(flags);
    SHU_AssertNullPointer(arguments);

    char *programFile = SHU_UtilFormat("%s%s", program, SHUM_HOST_WINDOWS ? ".exe" : "");
    char *scriptPath = SHUI_PPath(SHUILD.currentExecutableDirectory, script, false);
    char *programPath = SHUI_PPath(SHUILD.currentExecutableDirectory, programFile, false);
    free(programFile);

    SHUI_StringList command = {0};
    SHUI_CAddArguments(&command, SHUI_CScriptCompiler());
    SHUI_CAddArgument(&command, "-o");
    SHUI_CAddArgument(&command, programPath);
    SHUI_CAddArgument(&command, scriptPath);
    SHUI_CAddArguments(&command, SHUILD_BUILD);
    SHUI_CAddArguments(&command, flags);
    SHUI_CRun(&command, true);
    SHUI_SLFree(&command);

    // it runs in its own directory, as it would if it were run there by hand, and the build goes on here after it
    char *directory = SHUI_PDirectory(programPath);
    char *run = SHU_UtilFormat("\"%s\" %s", programPath, arguments);

#if SHUM_HOST_WINDOWS
    char *previous = _getcwd(NULL, 0);
    SHU_Assert(previous != NULL && _chdir(directory) == 0, "Cannot run '%s' in its directory.", programPath);
    SHUI_URunCommand(true, run);
    SHU_Assert(_chdir(previous) == 0, "Cannot go back to '%s'.", previous);
#else
    char *previous = getcwd(NULL, 0);
    SHU_Assert(previous != NULL && chdir(directory) == 0, "Cannot run '%s' in its directory.", programPath);
    SHUI_URunCommand(true, run);
    SHU_Assert(chdir(previous) == 0, "Cannot go back to '%s'.", previous);
#endif

    free(previous);
    free(run);
    free(directory);
    free(programPath);
    free(scriptPath);
}

i32 SHU_UtilSpawnProcessSync(const char *executable, char *const *argv)
{
    i32 result = 0;

#ifdef SHUC_LOG_COMMANDS
    SHU_UtilLog("$ " SHUM_LOG_COMMAND("%s"), executable);
#endif

#if SHUM_HOST_WINDOWS
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

    SHUI_CReport(result, true, executable);

    return result;
}

const char *SHU_UtilGetExecutablePath(void)
{
    return SHUILD.currentExecutableDirectory;
}

SHUFileType SHU_UtilFileExists(const char *file)
{
    SHU_AssertNullPointer(file);

    char *path = SHUI_PPath(SHUILD.currentExecutableDirectory, file, false);
    SHUFileType type = SHUI_UFileExists(path);
    free(path);

    return type;
}

void SHU_UtilCreateDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    char *directoryPath = SHUI_PPath(SHUILD.currentExecutableDirectory, directory, true);

    if (SHUI_UFileExists(directoryPath) == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(directoryPath);
    }

    free(directoryPath);
}

void SHU_UtilDeleteFile(const char *file)
{
    SHU_AssertNullPointer(file);

    char *path = SHUI_PPath(SHUILD.currentExecutableDirectory, file, false);
    SHUI_UDeleteRecursive(path);
    free(path);
}

void SHU_UtilCopyFile(const char *file, const char *directory)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(directory);

    char *directoryPath = SHUI_PPath(SHUILD.currentExecutableDirectory, directory, false);
    char *filePath = SHUI_PPath(SHUILD.currentExecutableDirectory, file, false);

    if (SHUI_UFileExists(directoryPath) == SHUFileType_Invalid)
    {
        SHUI_UMakeDirectoryRecursive(directoryPath);
    }

    // a file goes into the directory under its own name, and a directory's contents go into it
    if (SHUI_UFileExists(filePath) == SHUFileType_Regular)
    {
        const char *name = file + strlen(file);

        while (name > file && !SHUI_PIsSeparator(name[-1]))
        {
            name--;
        }

        char *into = SHUI_PPath(directoryPath, "", true);
        free(directoryPath);
        directoryPath = SHUI_PPath(into, name, false);
        free(into);
    }

    SHUI_UCopyRecursive(filePath, directoryPath);
    free(directoryPath);
    free(filePath);
}

void SHU_UtilRenameFile(const char *file, const char *name)
{
    SHU_AssertNullPointer(file);
    SHU_AssertNullPointer(name);

    char *from = SHUI_PPath(SHUILD.currentExecutableDirectory, file, false);
    char *to = SHUI_PPath(SHUILD.currentExecutableDirectory, name, false);
    SHUI_URenameFile(from, to);
    free(from);
    free(to);
}

i64 SHU_GetFileEditTime(const char *file)
{
    SHU_AssertNullPointer(file);

    char *path = SHUI_PPath(SHUILD.currentExecutableDirectory, file, false);
    i64 time = SHUI_UGetFileEditTime(path) / 1000000000LL;
    free(path);

    return time;
}

static int SHUI_SCompare(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}

static void SHUI_UListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    char *path = SHU_UtilFormat("%s%s", SHUILD.currentExecutableDirectory, directory);

    SHUI_StringList names = {0};

#if SHUM_HOST_WINDOWS
    WIN32_FIND_DATAA ffd = {0};
    char *pattern = SHU_UtilFormat("%s*", path);
    HANDLE hFind = FindFirstFileA(pattern, &ffd);
    free(pattern);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SHU_UtilFail(SHUResult_ErrNotFound, "directory " SHUM_LOG_PATH("%s") " to list does not exist.", SHUI_PShort(path));
    }

    do
    {
        if (ffd.cFileName[0] != '.')
        {
            SHUI_SLAdd(&names, SHUI_Copy(ffd.cFileName));
        }
    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);
#else
    DIR *dir = opendir(path);

    if (!dir)
    {
        SHU_UtilFail(SHUResult_ErrNotFound, "directory " SHUM_LOG_PATH("%s") " to list does not exist.", SHUI_PShort(path));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            SHUI_SLAdd(&names, SHUI_Copy(entry->d_name));
        }
    }

    closedir(dir);
#endif

    if (names.count > 1)
    {
        qsort(names.data, names.count, sizeof(char *), SHUI_SCompare);
    }

    for (usz i = 0; i < names.count; i++)
    {
        char *fullPath = SHU_UtilFormat("%s%s", path, names.data[i]);
        SHUFileType type = SHUI_UFileExists(fullPath);
        free(fullPath);
        char *entryPath = SHU_UtilFormat("%s%s%s", directory, names.data[i], type == SHUFileType_Directory ? SHUM_PATH_SEPARATOR_STR : "");

        function(entryPath, type, data);

        if (type == SHUFileType_Directory && recursive)
        {
            SHUI_UListDirectory(entryPath, recursive, function, data);
        }

        free(entryPath);
    }

    SHUI_SLFree(&names);
    free(path);
}

void SHU_UtilListDirectory(const char *directory, bool recursive, SHUListFunction function, void *data)
{
    SHU_AssertNullPointer(directory);
    SHU_AssertNullPointer(function);

    // the executable's own directory is listed with an empty path
    char *path = SHUI_PPath("", directory, directory[0] != '\0');
    SHUI_UListDirectory(path, recursive, function, data);
    free(path);
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

    char *path = SHU_UtilFormat("%s%s", SHUILD.currentExecutableDirectory, file);
    SHUSlice content = SHUI_UReadFile(path);
    free(path);

    return content;
}

void SHU_UtilWriteFile(const char *file, SHUSliceView content)
{
    SHU_AssertNullPointer(file);

    char *path = SHU_UtilFormat("%s%s", SHUILD.currentExecutableDirectory, file);
    SHUI_UWriteFile(path, content);
    free(path);
}

char *SHU_UtilLibraryFile(const char *name, SHUModuleType type)
{
    SHU_AssertNullPointer(name);
    SHU_Assert(type == SHUModuleType_LibraryStatic || type == SHUModuleType_LibraryDynamic, "Module type '%s' is not a library.", SHUModuleType_GetString(type));

    if (type == SHUModuleType_LibraryStatic)
    {
        return SHU_UtilFormat("lib%s.a", name);
    }

    switch (SHUILD.COMPILER.target)
    {
    case SHUPlatform_Windows:
        return SHU_UtilFormat("%s.dll", name);
    case SHUPlatform_MacOS:
        return SHU_UtilFormat("lib%s.dylib", name);
    default:
        return SHU_UtilFormat("lib%s.so", name);
    }
}

#pragma endregion Utility

#ifdef SHUC_ENABLE_INCREMENTAL
#pragma region Cache

void SHU_CacheConfigure(const char *cacheDirectory)
{
    SHU_AssertNullPointer(cacheDirectory);

    free(SHUILD.cacheDirectory);
    SHUILD.cacheDirectory = SHUI_PPath(SHUILD.currentExecutableDirectory, cacheDirectory, true);

    SHUI_UMakeDirectoryRecursive(SHUILD.cacheDirectory);
}

void SHU_CacheClearModule(const char *moduleName)
{
    SHU_Assert(SHUILD.cacheDirectory != NULL, "Cache directory is not configured.");

    char *moduleCacheDirectory = SHU_UtilFormat("%s%s", SHUILD.cacheDirectory, moduleName);

    if (SHUI_UFileExists(moduleCacheDirectory) != SHUFileType_Invalid)
    {
        SHUI_UDeleteRecursive(moduleCacheDirectory);
    }

    SHUI_UMakeDirectoryRecursive(moduleCacheDirectory);
    free(moduleCacheDirectory);
}

void SHU_CacheClearAll(void)
{
    SHU_Assert(SHUILD.cacheDirectory != NULL, "Cache directory is not configured.");

    SHUI_UDeleteRecursive(SHUILD.cacheDirectory);
    SHUI_UMakeDirectoryRecursive(SHUILD.cacheDirectory);
}

#pragma endregion Cache

#endif // SHUC_ENABLE_INCREMENTAL

#pragma region Compiler

static char *SHUI_CExecutableDirectory(void)
{
    // the buffer grows until the whole path fits
    char *path = NULL;
    usz length = 0;

#if SHUM_HOST_WINDOWS
    for (DWORD size = 256;; size *= 2)
    {
        path = (char *)SHUI_Reallocate(path, size);
        length = (usz)GetModuleFileNameA(NULL, (LPSTR)path, size);

        if (length < size)
        {
            break;
        }
    }
#elif SHUM_HOST_MACOS
    u32 size = 0;
    _NSGetExecutablePath(NULL, &size);
    path = (char *)SHUI_Allocate(size);
    _NSGetExecutablePath(path, &size);
    length = (usz)strlen(path);
#else
    for (usz size = 256;; size *= 2)
    {
        path = (char *)SHUI_Reallocate(path, size);
        ssize_t read = readlink("/proc/self/exe", path, size);
        SHU_Assert(read >= 0, "Internal: The executable's path cannot be read.");

        if ((usz)read < size)
        {
            length = (usz)read;
            break;
        }
    }
#endif

    while (length > 0 && path[length - 1] != SHUM_PATH_SEPARATOR)
    {
        length--;
    }
    path[length] = '\0';

    return path;
}

// a compiler's name on PATH is gcc or clang, maybe with a version (gcc-14) and the target's triple before it (x86_64-w64-mingw32-gcc), which has two dashes or more;
// other tools, such as gcc-ar, clang-format or c99-gcc, are not compilers to pick
static SHUCompiler SHUI_CNameCompiler(const char *name)
{
    const char *families[] = {"gcc", "clang"};
    const SHUCompiler identifiers[] = {SHUCompiler_GCC, SHUCompiler_Clang};

    for (usz i = 0; i < sizeof(families) / sizeof(*families); i++)
    {
        for (const char *found = strstr(name, families[i]); found != NULL; found = strstr(found + 1, families[i]))
        {
            usz dashes = 0;

            for (const char *c = name; c < found; c++)
            {
                dashes += *c == '-';
            }

            bool prefixed = found == name || (found[-1] == '-' && dashes >= 2);
            const char *rest = found + strlen(families[i]);
            bool versioned = rest[0] == '\0' || (rest[0] == '-' && rest[1] != '\0' && strspn(rest + 1, "0123456789.") == strlen(rest + 1));

            if (prefixed && versioned)
            {
                return identifiers[i];
            }
        }
    }

    return SHUCompiler_Unknown;
}

// "14.2.0" is 140200, and "14" is 140000
static u32 SHUI_CParseVersion(const char *text)
{
    u32 parts[3] = {0};
    sscanf(text, "%u.%u.%u", &parts[0], &parts[1], &parts[2]);
    return parts[0] * 10000 + parts[1] * 100 + parts[2];
}

// the sanitizers need their libraries, which a compiler may not have, so a small program is compiled and linked with them
static bool SHUI_CHasSanitizers(const char *command)
{
#if SHUM_HOST_WINDOWS
    (void)command;
    return false; // MinGW has no sanitizers
#else
    char *test = SHU_UtilFormat("printf 'int main(void){return 0;}' | %s -x c - -fsanitize=address,undefined -o /dev/null >/dev/null 2>&1", command);
    bool works = system(test) == 0;
    free(test);

    return works;
#endif
}

// the gcc and clang compilers on PATH, the first of each name, sorted by name; with sanitizers, each that compiles for the host's system and processor is tried with them
static SHUCompilerInfo *SHUI_CFind(usz *retCount, bool sanitizers)
{
    SHUI_StringList names = {0};
    const char *path = getenv("PATH");

#if SHUM_HOST_WINDOWS
    const char separator = ';';
#else
    const char separator = ':';
#endif

    while (path != NULL && *path != '\0')
    {
        const char *end = strchr(path, separator);
        usz length = end == NULL ? strlen(path) : (usz)(end - path);
        char *directory = SHU_UtilFormat("%.*s", (int)length, path);
        path = end == NULL ? NULL : end + 1;

#if SHUM_HOST_WINDOWS
        WIN32_FIND_DATAA ffd = {0};
        char *pattern = SHU_UtilFormat("%s\\*.exe", directory);
        HANDLE hFind = length == 0 ? INVALID_HANDLE_VALUE : FindFirstFileA(pattern, &ffd);
        free(pattern);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            free(directory);
            continue;
        }

        do
        {
            char *name = SHU_UtilFormat("%.*s", (int)(strlen(ffd.cFileName) - 4), ffd.cFileName);
#else
        DIR *dir = length == 0 ? NULL : opendir(directory);

        if (dir == NULL)
        {
            free(directory);
            continue;
        }

        for (struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir))
        {
            char *name = SHUI_Copy(entry->d_name);
            char *file = SHU_UtilFormat("%s/%s", directory, name);
            bool runs = access(file, X_OK) == 0;
            free(file);

            if (!runs)
            {
                free(name);
                continue;
            }
#endif
            bool skip = SHUI_CNameCompiler(name) == SHUCompiler_Unknown;

            for (usz i = 0; i < names.count && !skip; i++)
            {
                skip = strcmp(names.data[i], name) == 0;
            }

            if (skip)
            {
                free(name);
            }
            else
            {
                SHUI_SLAdd(&names, name);
            }
#if SHUM_HOST_WINDOWS
        } while (FindNextFileA(hFind, &ffd));

        FindClose(hFind);
#else
        }

        closedir(dir);
#endif
        free(directory);
    }

    if (names.count > 1)
    {
        qsort(names.data, names.count, sizeof(char *), SHUI_SCompare);
    }

    SHUCompilerInfo *compilers = calloc(names.count + 1, sizeof(SHUCompilerInfo));
    SHU_AssertNullPointer(compilers);

    for (usz i = 0; i < names.count; i++)
    {
        char *machine = SHUI_CAsk(names.data[i], "-dumpmachine");

        compilers[i].command = names.data[i];
        compilers[i].identifier = SHUI_CNameCompiler(names.data[i]);
        compilers[i].machine = machine;
        compilers[i].target = SHUI_CTargetOf(machine);

        // some clang compilers go by gcc's name too, such as LLVM-MinGW's x86_64-w64-mingw32-gcc and macOS's gcc
        if (compilers[i].identifier == SHUCompiler_GCC)
        {
            char *about = SHUI_CAsk(names.data[i], "--version");
            compilers[i].identifier = strstr(about, "clang") != NULL ? SHUCompiler_Clang : SHUCompiler_GCC;
            free(about);
        }

        // gcc's -dumpversion may give only the major version, and clang knows no -dumpfullversion
        char *version = SHUI_CAsk(names.data[i], "-dumpfullversion");

        if (version[0] == '\0')
        {
            free(version);
            version = SHUI_CAsk(names.data[i], "-dumpversion");
        }

        compilers[i].version = SHUI_CParseVersion(version);
        compilers[i].sanitizers = sanitizers && compilers[i].target == SHUM_HOST_PLATFORM && SHUI_CRunsOnHost(machine) && SHUI_CHasSanitizers(names.data[i]);
        free(version);
    }

    // the compilers own the names now, so only the list's array is freed
    free(names.data);

    *retCount = names.count;
    return compilers;
}

void SHU_CompilerDetectFree(SHUCompilerInfo *compilers, usz count)
{
    for (usz i = 0; compilers != NULL && i < count; i++)
    {
        free((char *)compilers[i].command);
        free((char *)compilers[i].machine);
    }

    free(compilers);
}

// the newest compiler that compiles for the host's system and processor, of the host compiler's family if one is found; a shorter name wins a tie, so gcc is kept over x86_64-linux-gnu-gcc
static const SHUCompilerInfo *SHUI_CPick(const SHUCompilerInfo *compilers, usz count)
{
    const SHUCompilerInfo *best = NULL;

    for (usz i = 0; i < count; i++)
    {
        const SHUCompilerInfo *compiler = &compilers[i];

        if (compiler->target != SHUM_HOST_PLATFORM || !SHUI_CRunsOnHost(compiler->machine) || compiler->version == 0)
        {
            continue;
        }

        if (best == NULL)
        {
            best = compiler;
            continue;
        }

        bool family = compiler->identifier == SHUM_HOST_COMPILER;
        bool bestFamily = best->identifier == SHUM_HOST_COMPILER;

        if (family != bestFamily)
        {
            best = family ? compiler : best;
        }
        else if (compiler->version != best->version)
        {
            best = compiler->version > best->version ? compiler : best;
        }
        else if (strlen(compiler->command) < strlen(best->command))
        {
            best = compiler;
        }
    }

    return best;
}

void SHU_CompilerConfigure(SHUCompiler compiler, const char *compilerCommand)
{
    SHU_AssertNullPointer(compilerCommand);

    free(SHUILD.COMPILER.command);
    SHUILD.COMPILER.identifier = compiler;
    SHUILD.COMPILER.command = SHUI_Copy(compilerCommand);
    SHUILD.COMPILER.target = SHUI_CDetectTarget(compilerCommand);

    if (SHUILD.currentExecutableDirectory == NULL)
    {
        SHUILD.currentExecutableDirectory = SHUI_CExecutableDirectory();

#ifdef SHUC_ENABLE_INCREMENTAL
        SHU_CacheConfigure(SHUC_DEFAULT_CACHE_DIRECTORY);
#endif
    }
}

void SHU_CompilerConfigureTry(const char *compilerCommand)
{
    if (compilerCommand == NULL || strlen(compilerCommand) == 0)
    {
        usz count = 0;
        SHUCompilerInfo *compilers = SHUI_CFind(&count, false);
        const SHUCompilerInfo *picked = SHUI_CPick(compilers, count);

        if (picked == NULL)
        {
            SHU_CompilerConfigure((SHUCompiler)SHUM_HOST_COMPILER, SHUCompiler_GetCommand(SHUM_HOST_COMPILER));
        }
        else
        {
            SHU_CompilerConfigure(picked->identifier, picked->command);
        }

        SHU_CompilerDetectFree(compilers, count);
    }
    else if (strstr(compilerCommand, "clang") != 0)
    {
        SHU_CompilerConfigure(SHUCompiler_Clang, compilerCommand);
    }
    else if (strstr(compilerCommand, "gcc") != 0)
    {
        SHU_CompilerConfigure(SHUCompiler_GCC, compilerCommand);
    }
    else
    {
        SHU_UtilFail(SHUResult_Err, "compiler " SHUM_LOG_VALUE("%s") " is not known; configure it with SHU_CompilerConfigure.", compilerCommand);
    }
}

SHUCompilerInfo *SHU_CompilerDetect(usz *retCount)
{
    SHU_AssertNullPointer(retCount);

    return SHUI_CFind(retCount, true);
}

static void SHUI_CAddFlag(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHUI_SLAdd(&SHUILD.COMPILER.flags, SHUI_Copy(flags));
}

void SHUI_CompilerAddFlags(const char *flags, ...)
{
    SHU_AssertNullPointer(flags);
    SHUI_EACH_ARGUMENT(flags, SHUI_CAddFlag);
}

void SHU_CompilerSetFlags(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHU_CompilerClearFlags();
    SHUI_CAddFlag(flags);
}

void SHU_CompilerClearFlags(void)
{
    SHUI_SLFree(&SHUILD.COMPILER.flags);
    SHUI_SLFree(&SHUILD.COMPILER.linkerFlags);
}

static void SHUI_CAddLinkerFlag(const char *flags)
{
    SHU_AssertNullPointer(flags);

    SHUI_SLAdd(&SHUILD.COMPILER.linkerFlags, SHUI_Copy(flags));
}

void SHUI_CompilerAddLinkerFlags(const char *flags, ...)
{
    SHU_AssertNullPointer(flags);
    SHUI_EACH_ARGUMENT(flags, SHUI_CAddLinkerFlag);
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
                               SHUILD.COMPILER.flags.data[i]);

        if (written < 0 || (usz)written >= buffer.size - bufferIndex)
        {
            SHU_UtilWarn("the buffer is too small for the compiler flags, so they are cut.");
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
        const char *value = va_arg(args, const char *);

#if SHUM_HOST_WINDOWS
        SHUI_SLAdd(&SHUILD.COMPILER.flags, value == NULL ? SHU_UtilFormat("-D%s", macros) : SHU_UtilFormat("-D%s=\"\"%s\"\"", macros, value));
#else
        SHUI_SLAdd(&SHUILD.COMPILER.flags, value == NULL ? SHU_UtilFormat("-D%s", macros) : SHU_UtilFormat("-D%s='%s'", macros, value));
#endif

        macros = va_arg(args, const char *);
    }

    va_end(args);
}

SHUCompiler SHU_CompilerGetIdentifier(void)
{
    return SHUILD.COMPILER.identifier;
}

SHUPlatform SHU_CompilerGetTarget(void)
{
    return SHUILD.COMPILER.target;
}

#pragma endregion Compiler

#pragma region Module

void SHU_ModuleBegin(const char *name, const char *root)
{
    SHU_AssertNullPointer(name);

    SHUILD.MODULE.name = SHUI_Copy(name);
    SHUILD.MODULE.root = root != NULL && strlen(root) != 0 ? SHUI_PPath(SHUILD.currentExecutableDirectory, root, true) : SHUI_Copy(SHUILD.currentExecutableDirectory);
}

static void SHUI_MAddIncludeDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    SHUI_SLAdd(&SHUILD.MODULE.includeDirectories, SHUI_PPath(SHUILD.MODULE.root, directory, true));
}

void SHUI_ModuleAddIncludeDirectory(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_MAddIncludeDirectory);
}

static void SHUI_MAddPublicIncludeDirectory(const char *directory)
{
    SHUI_MAddIncludeDirectory(directory);
    SHUI_SLAdd(&SHUILD.MODULE.publicIncludeDirectories, SHUI_Copy(SHUILD.MODULE.includeDirectories.data[SHUILD.MODULE.includeDirectories.count - 1]));
}

void SHUI_ModuleAddPublicIncludeDirectory(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_MAddPublicIncludeDirectory);
}

static void SHUI_MAddSourceFile(const char *file)
{
    SHU_AssertNullPointer(file);

    char *path = SHUI_PPath(SHUILD.MODULE.root, file, false);

    SHUFileType fileType = SHUI_UFileExists(path);
    if (fileType == SHUFileType_Directory)
    {
        char *directory = SHUI_PPath(path, "", true);
        SHUI_MAddSourceDirectoryRecursive(directory);
        free(directory);
        free(path);
    }
    else if (fileType == SHUFileType_Regular)
    {
        SHUI_SLAdd(&SHUILD.MODULE.sourceFiles, path);
    }
    else
    {
        SHU_UtilFail(SHUResult_ErrNotFound, "source " SHUM_LOG_PATH("%s") " does not exist.", SHUI_PShort(path));
    }
}

void SHUI_ModuleAddSourceFile(const char *file, ...)
{
    SHU_AssertNullPointer(file);
    SHUI_EACH_ARGUMENT(file, SHUI_MAddSourceFile);
}

void SHU_ModuleCompile(const char *directory, SHUModuleType module)
{
    char *directoryPath = SHUI_PPath(SHUILD.currentExecutableDirectory, directory != NULL ? directory : "", directory != NULL && strlen(directory) != 0);

    if (directory != NULL && strlen(directory) != 0)
    {
        if (SHUI_UFileExists(directoryPath) != SHUFileType_Directory)
        {
            SHUI_UMakeDirectoryRecursive(directoryPath);
        }
    }

    // its settings, such as its flags, are new or changed, so every file compiles again
    bool settingsChanged = false;

#ifdef SHUC_ENABLE_INCREMENTAL
    // a module compiled for the first time has no settings to change
    char *stateFile = SHUI_CModuleStateFile(SHUILD.MODULE.name);
    bool cached = SHUI_UFileExists(stateFile) == SHUFileType_Regular;
    free(stateFile);

    if (SHUI_CModuleStateDirty(SHUILD.MODULE.name))
    {
        SHU_CacheClearModule(SHUILD.MODULE.name);
        SHUI_CModuleStateUpdate(SHUILD.MODULE.name);
        settingsChanged = cached;
    }
#endif

    SHUI_MAddLinkedIncludes();

    if (module != SHUModuleType_LibraryStatic)
    {
        SHUI_MExpandLinks();
    }

    switch (module)
    {
    case SHUModuleType_Executable:
        SHUI_MCompileExecutable(directoryPath);
        break;
    case SHUModuleType_LibraryStatic:
        SHUI_MCompileLibraryStatic(directoryPath);
        break;
    case SHUModuleType_LibraryDynamic:
        SHUI_MCompileLibraryDynamic(directoryPath);
        break;
    default:
        SHU_UtilFail(SHUResult_Err, "module type %d is not known.", (int)module);
        break;
    }

    if (SHUILD.MODULE.copyDynamicLinks && module != SHUModuleType_LibraryStatic)
    {
        SHUI_MCopyDynamicLinks(directoryPath);
    }

    if (module != SHUModuleType_Executable)
    {
        SHUI_MRecordLibrary(module == SHUModuleType_LibraryStatic);
    }

#ifndef SHUC_NO_MODULE_LOG
    // one line for the module: what it compiled and made, or that it was up to date
    if (SHUILD.MODULE.output == NULL)
    {
        SHU_UtilLog(SHUM_LOG_NAME("%s") " (%s): " SHUM_COLOR_DIM("up to date"), SHUILD.MODULE.name, SHUModuleType_GetLogString(module));
    }
    else
    {
        SHU_UtilLog(SHUM_LOG_NAME("%s") " (%s): compiled %zu file%s, %s " SHUM_LOG_PATH("%s") SHUM_COLOR_DIM("%s"),
                    SHUILD.MODULE.name,
                    SHUModuleType_GetLogString(module),
                    SHUILD.MODULE.compiledCount,
                    SHUILD.MODULE.compiledCount == 1 ? "" : "s",
                    module == SHUModuleType_LibraryStatic ? "packed" : "linked",
                    SHUI_PShort(SHUILD.MODULE.output),
                    settingsChanged ? " (settings changed)" : "");
    }
#else
    (void)settingsChanged;
#endif

    // the next module starts new; a library's record took the lists it keeps
    free(directoryPath);
    free(SHUILD.MODULE.name);
    free(SHUILD.MODULE.root);
    free(SHUILD.MODULE.output);
    SHUI_SLFree(&SHUILD.MODULE.includeDirectories);
    SHUI_SLFree(&SHUILD.MODULE.sourceFiles);
    SHUI_SLFree(&SHUILD.MODULE.links);
    SHUI_SLFree(&SHUILD.MODULE.linkDirectories);
    SHUI_SLFree(&SHUILD.MODULE.publicIncludeDirectories);
    SHUI_SLFree(&SHUILD.MODULE.linkedIncludeDirectories);
    SHUILD.MODULE = (__typeof__(SHUILD.MODULE)){0};
}

static void SHUI_MAddLibraryDirectory(const char *directory)
{
    SHU_AssertNullPointer(directory);

    char *path = SHUI_PPath(SHUILD.currentExecutableDirectory, directory, true);

    if (SHUI_UFileExists(path) != SHUFileType_Directory)
    {
        SHU_UtilFail(SHUResult_ErrNotFound, "library directory " SHUM_LOG_PATH("%s") " does not exist.", SHUI_PShort(path));
    }

    SHUI_SLAdd(&SHUILD.MODULE.linkDirectories, path);
}

void SHUI_ModuleAddLibraryDirectory(const char *directory, ...)
{
    SHU_AssertNullPointer(directory);
    SHUI_EACH_ARGUMENT(directory, SHUI_MAddLibraryDirectory);
}

static void SHUI_MLinkLibrary(const char *library)
{
    SHU_AssertNullPointer(library);

    SHUI_SLAdd(&SHUILD.MODULE.links, SHUI_Copy(library));
}

void SHUI_ModuleLinkLibrary(const char *library, ...)
{
    SHU_AssertNullPointer(library);
    SHUI_EACH_ARGUMENT(library, SHUI_MLinkLibrary);
}

void SHU_ModuleCopyDynamicLinks(void)
{
    SHUILD.MODULE.copyDynamicLinks = true;
}

#pragma endregion Module

#endif // SHU_IMPLEMENTATION

#pragma endregion Definitions
