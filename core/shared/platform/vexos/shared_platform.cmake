# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# Copyright (C) 2020 TU Bergakademie Freiberg Karl Fessel
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

message(STATUS "Building for VEXos")

set (PLATFORM_SHARED_DIR ${CMAKE_CURRENT_LIST_DIR})

add_definitions(-DBH_PLATFORM_VEXOS)

include_directories(${PLATFORM_SHARED_DIR})
include_directories(${PLATFORM_SHARED_DIR}/../include)

# include (${CMAKE_CURRENT_LIST_DIR}/../common/math/platform_api_math.cmake)

set (PLATFORM_SHARED_SOURCE
        "${PLATFORM_SHARED_DIR}/vexos_platform.c"
        "${PLATFORM_SHARED_DIR}/cache.S"
        ${PLATFORM_COMMON_MATH_SOURCE}
)
message(STATUS "PLATFORM_SHARED_DIR = ${PLATFORM_SHARED_DIR}")
message(STATUS "source_all = ${source_all}")
message(STATUS "PLATFORM_SHARED_SOURCE = ${PLATFORM_SHARED_SOURCE}")

