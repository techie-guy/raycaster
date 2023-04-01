# raycaster

A Simple Raycaster that casts rays and draws them accordingly to get a "3D Effect".

This is inspired by 3DSage's very cool video: https://youtu.be/gYRrGTC7GtA

## Build it
**If Building on Windows, you need to have a working MSYS2 Installation**

Clone this repository recursively to pull in the submodules

**To Build the Project:**

-> You will need a C Compiler: Clang, GCC or Emscripten(not yet supported)

-> pkg-config

-> Premake5

-> GLFW3

You can Download them from your package manager

After cloning the repo recursively, `cd` into it, then:
1. Generate the project files (here Makefiles) using `premake5 gmake2`
2. Use `make` to build the project
