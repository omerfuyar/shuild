# Shuild

Shuild is a cross platform, simple, single header file project builder library to achieve a build system similar to Zig. The idea is to create a system that is easy to use without leaving the development environment. System does not require any new syntax or concept to learn.

Be aware that Shuild is still in early development phase. Expect breaking changes and incomplete features.

## Setup

To use Shuild, simply download the `shuild.h` file and include it in your project. You don't even need to add to your include paths (you still can if you want), just place the header and your build source file (like `shuild.c`) in your project directory. Build folder will be created in the same directory as your build file.

## How to use

After having your header file, create a C file (like `shuild.c`) and include the `shuild.h` header. Then, use the provided API to define your build targets and dependencies. This source file will be compiled and executed to generate the necessary build files. You can use a compiler like TCC to run the build file directly. Or compile it with your system compiler and run the resulting executable.

Single header file logic is similar to stb and miniaudio libraries. There is a macro guard to specify the file is an implementation or not. This adds flexibility to the developer to include the header in multiple files without causing redefinition errors. If they want to wrap and make this shitty library much complex with their own systems, they can do that easily.

Most of the functions are logically similar to other build systems. You can specify include directories, source directories, targets, links, and other build configurations using the provided API functions.

## Example

A simple build source file example:

``` C

#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_Project("MyProject");

    //... Specify include directories, source directories, targets, links etc.

    SHU_Build();

    return 0;
}

```

You can see more complete examples in the `example` folder.
