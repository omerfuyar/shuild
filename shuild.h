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

#pragma region Shuild Include

#pragma endregion Shuild Include

#pragma region Shuild Implementation

#ifdef SHUILD_IMPLEMENTATION

#endif // SHUILD_IMPLEMENTATION

#pragma endregion Shuild Implementation