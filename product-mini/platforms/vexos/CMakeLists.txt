# VEXos WAMR build config
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
# Variables used:
# - GCC_ARM_TOOLCHAIN: should point to a ARM Embedded Toolchain install containing `bin/`, `lib/`, `arm-none-eabi/`, etc.

cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set (CMAKE_VERBOSE_MAKEFILE OFF) # Switch to ON for debugging

# This cross-compile setup is based off the one in https://stackoverflow.com/a/55610399

LIST(APPEND CMAKE_PROGRAM_PATH ${GCC_ARM_TOOLCHAIN}/bin)

# Specify the cross compiler
# The target triple needs to match the prefix of the binutils exactly
# (e.g. CMake looks for arm-none-eabi-ar)
set(CLANG_TARGET_TRIPLE arm-none-eabi)
set(GCC_ARM_TOOLCHAIN_PREFIX ${CLANG_TARGET_TRIPLE})
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${CLANG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${CLANG_TARGET_TRIPLE})
set(CMAKE_ASM_COMPILER clang)
set(CMAKE_ASM_COMPILER_TARGET ${CLANG_TARGET_TRIPLE})

# Don't run the linker on compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Specify compiler flags
# Partially pulled from VEXcode's build system
set(ARCH_FLAGS "-march=armv7-a -mcpu=cortex-a9 -mfpu=neon-fp16 -mfloat-abi=hard -funwind-tables -nostdlib")
set(CMAKE_C_FLAGS "-Wall ${ARCH_FLAGS}" CACHE STRING "Common flags for C compiler")
set(CMAKE_CXX_FLAGS "-Wall -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffunction-sections -fdata-sections ${ARCH_FLAGS}" CACHE STRING "Common flags for C++ compiler")
set(CMAKE_ASM_FLAGS "-Wall ${ARCH_FLAGS}" CACHE STRING "Common flags for assembler")

# This project doesn't make an executable but it'd probably need something like this if it did.
#set(LINKER_SCRIPT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/v5.ld)
#set(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -Wl,--gc-sections,-T${LINKER_SCRIPT_PATH} --specs=nano.specs --specs=nosys.specs" CACHE STRING "")

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

# C/C++ toolchain
set(GCC_ARM_SYSROOT "${GCC_ARM_TOOLCHAIN}/${GCC_ARM_TOOLCHAIN_PREFIX}")
set(CMAKE_SYSROOT ${GCC_ARM_SYSROOT})
set(CMAKE_FIND_ROOT_PATH ${GCC_ARM_SYSROOT})

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(iwasm)

enable_language (ASM)

set (WAMR_BUILD_PLATFORM "vexos")

# Build as ARMV7 by default, change to "AARCH64[sub]", "ARM[sub]", "THUMB[sub]", "MIPS" or "XTENSA"
# if we want to support arm, thumb, mips or xtensa

if (NOT DEFINED WAMR_BUILD_TARGET)
    set (WAMR_BUILD_TARGET "ARMV7")
endif ()

if (NOT DEFINED WAMR_BUILD_INTERP)
    # Enable Interpreter by default
    set (WAMR_BUILD_INTERP 0)
endif ()

if (NOT DEFINED WAMR_BUILD_AOT)
    # Enable AOT by default.
    set (WAMR_BUILD_AOT 1)
endif ()

if (NOT DEFINED WAMR_BUILD_LIBC_BUILTIN)
    # Enable libc builtin support by default
    set (WAMR_BUILD_LIBC_BUILTIN 1)
endif ()

if (NOT DEFINED WAMR_BUILD_LIBC_WASI)
    # Disable libc wasi support by default
    set (WAMR_BUILD_LIBC_WASI 0)
endif ()

if (NOT DEFINED WAMR_ROOT_DIR)
    set (WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
endif ()

## Override the global heap size to make it bigger
#if (NOT DEFINED  WAMR_BUILD_GLOBAL_HEAP_SIZE)
#    add_compile_definitions (WASM_GLOBAL_HEAP_SIZE=20970000) # 20 Mb
#endif ()


include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)

add_library( wamr ${WAMR_RUNTIME_LIB_SOURCE})

set_version_info (wamr)
