# Shuild
Shuild (SHU buILD) is a portable, cross platform project builder library.

It uses the [SHU](https://github.com/omerfuyar/shu) system. By defining `SHU`, you can tell the library where to find `shu.h`.

Goal is to create a system that is easy to use without leaving the development environment of C. A system that does not require any new syntax or concept to learn. Similar to the build system of Zig. 

Be aware that Shuild is still in early development phase. Expect breaking changes and incomplete features.

Thanks to people who come up with the name of this project and encourage me to improve it:
[bedwen](https://github.com/bedwen)
[ETCKK](https://github.com/ETCKK)

## Setup

To use Shuild, simply download the `shuild.h` file and include it in your project. You can just place the header and your build source file (like `shuild.c`) together in your project directory. It is recommended to place the executable `shuild` at the top of the project tree because most path related operations are relative to current executable directory.

## How to use

After having your header file, create a C file (like `shuild.c`) and include the `shuild.h` header. Then, use the provided API to define your build targets and configurations. If you choose it to implement here, this source file will be compiled and executed to generate the necessary build files. (I really would like to say that you can use TCC to run it directly but probably it will have some issues. Though, you can use Automate function to make the process easier. Check example `9` to learn more.)

Single header file logic is similar to stb and miniaudio libraries. There is a macro guard to specify the file is an implementation or not. This adds flexibility to the developer to include the header in multiple files without causing redefinition errors. If they want to wrap and make this shitty library much complex with their own systems, they can do that easily.

Most of the functions are logically similar to other build systems. You can specify include directories, source directories, output directories, flags, links, and other build configurations using the provided API functions.

User should not use any `SHUI_` prefixed elements of the library. These are internal elements and not meant for public use.

User can define several configurations using macros before including the header. These configurations can be found at top of the `shuild.h`.

Currently there is only support for `gcc`-like (I can only name `clang`, additionally) compilers. User can use other compilers but in this case compiler commands should be entered manually using compiler flags. Any function starts with `_Compiler` or `_Module` (also `_Cache`, if enabled) will break in this case, `_Util` functions are fine, I guess.

Using high optimization to compile the build script is recommended for better performance.

## Example

A minimal simple shuild source file example:

``` C

#define SHU_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerTryConfigure("gcc");
    
    SHU_ModuleBegin("myApp", "");

    //... Specify include directories, source directories, targets, links etc.

    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);

    return 0;
}

```

You can see more complete examples in the `example` folder.

Every function starts with `SHU_` is documented in `shuild.h`.

I also have a [Game Framework](https://github.com/omerfuyar/Code-Romeo) and [Example Game](https://github.com/omerfuyar/Code-Juliett) projects that supports/uses this build system.
