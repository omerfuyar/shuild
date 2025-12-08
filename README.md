# Shuild

Shuild is a cross platform, simple, single header file project builder library to achieve a build system similar to Zig. The idea is to create a system that is easy to use without leaving the development environment. System does not require any new syntax or concept to learn.

Be aware that Shuild is still in early development phase. Expect breaking changes and incomplete features.

Huge thanks to people who come up with the name of this project and encourage me to improve it:
[bedwen](https://github.com/bedwen)
[ETCKK](https://github.com/ETCKK)

## Setup

To use Shuild, simply download the `shuild.h` file and include it in your project. You don't even need to add to your include paths (you still can if you want), just place the header and your build source file (like `shuild.c`) in your project directory. 

## How to use

After having your header file, create a C file (like `shuild.c`) and include the `shuild.h` header. Then, use the provided API to define your build targets and dependencies. This source file will be compiled and executed to generate the necessary build files. You can use a compiler like TCC to run the build file directly. Or compile it with your system compiler and run the resulting executable.

Single header file logic is similar to stb and miniaudio libraries. There is a macro guard to specify the file is an implementation or not. This adds flexibility to the developer to include the header in multiple files without causing redefinition errors. If they want to wrap and make this shitty library much complex with their own systems, they can do that easily.

Most of the functions are logically similar to other build systems. You can specify include directories, source directories, targets, links, and other build configurations using the provided API functions.

User should not use any `SHUI_` prefixed elements of the library. These are internal elements and not meant for public use.

User can define several configurations using macros before including the header. These configurations can be found on top of the `shuild.h`.

Currently there is only support for `clang`, `gcc` and `msvc` compilers. User can use other compilers but in this case compiler commands should be entered manually using compiler flags.

Using `-O3` for `clang` and `gcc` or `/O2` optimization for `msvc` to compile the build script is recommended for better performance.

Recently I added SHU_Automate which allows you to simply compile the build source file (`shuild.c`) once, and every time you run the executable it will check if the source file edited or not. It will automatically compile the source file again and run the new executable.

## Example

A simple build source file example:

``` C

#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(...);
    
    SHU_ModuleBegin("myApp");

    //... Specify include directories, source directories, targets, links etc.

    SHU_ModuleCompile("build/bin/", SHUM_MODULE_EXECUTABLE);

    return 0;
}

```

You can see more complete examples in the `example` folder.

I also have a [Game Framework](https://github.com/omerfuyar/Code-Romeo) and [Example Game](https://github.com/omerfuyar/Code-Juliett) projects that supports/uses this build system.
