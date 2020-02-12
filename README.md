# Cross-compiling for Raspberry Pi on Windows

## Prerequisite:
1. Pre-built GNU toolchain ([https://gnutoolchains.com/raspberry/](https://gnutoolchains.com/raspberry/)).
2. Visual Studio Code.
3. CMake.

## Steps:
1. Download and install GNU Toolchain.
2. Install all the external libraries that are needed on the Pi itself.
3. Follow [Updating Sysroot for Raspberry PI Cross-Toolchain](https://gnutoolchains.com/raspberry/tutorial/sysroot) guide to synchronize the `Sysroot` folder on our host machine (Windows machine) and the Pi.
4. Create `Toolchain-RaspberryPi.cmake` file with the content:
```
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER
D:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gcc.exe)
SET(CMAKE_CXX_COMPILER
D:/SysGCC/raspberry/bin/arm-linux-gnueabihf-g++.exe)
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH
D:/SysGCC/raspberry/arm-linux-gnueabihf/sysroot/)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

This file will instruct Cmake to build the project with installed GNU Toolchain. Replace `D:/SysGCC/raspberry` with your installation of the toolchain.

5. Place the `Toolchain-RaspberryPi.cmake` where it's easy to reference to. I personally just put it right into the GNU toolchain folder, `D:/SysGCC/raspberry/Toolchain-RaspberryPi.cmake`.
6. Create new CMake project with VSCode and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) plugin.
7. Open `Edit User-Local CMake Kits` from VSCode command palette.
8. Add the GNU Toolchain into `cmake-tools-kits.json`:
```
  {
    "name": "GCC for arm-linux-gnueabihf 8.3.0",
    "compilers": {
      "C": "D:\\SysGCC\\raspberry\\bin\\arm-linux-gnueabihf-gcc.exe",
      "CXX": "D:\\SysGCC\\raspberry\\bin\\arm-linux-gnueabihf-g++.exe"
    },
    "toolchainFile": "D:\\SysGCC\\raspberry\\Toolchain-RaspberryPi.cmake"
  },
```
9. Select the kit and build the project.

## Notes:
1. [Using VS and VS Code for Embedded C/C++ Development - Marc Goodner, Microsoft](https://www.youtube.com/watch?v=IrSUDGx_6kI).
2. [CrossCompileExtension](https://github.com/robotdad/CrossCompileExtension).