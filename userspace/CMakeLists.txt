cmake_minimum_required(VERSION 3.5)
project(ecen427)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_C_FLAGS_RELEASE "-O3")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

# Ubuntu's gcc (used when building natively on the board) enables these by
# default at -O1+; the bare ARM cross-compiler toolchain does not. Set them
# explicitly so builds produce identical warnings/behavior on both, whether
# building natively on the board or cross-compiling.
add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_options(-Wformat -Wformat-security -fstack-protector-strong -fPIC -fPIE)
add_link_options(-fPIE -pie)

set(USERSPACE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ROOT_DIR ${USERSPACE_DIR} DIRECTORY)

if (TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-12" REQUIRED)
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=modernize-*,bugprone-*,clang-analyzer-*,cppcoreguidelines-*,google-*,misc-*,portability-*,-google-readability-braces-around-statements,-cppcoreguidelines-macro-usage,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-cppcoreguidelines-avoid-non-const-global-variables")

else() 
    if (NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "armv7l")
        message(WARNING "Building on non-PYNQ board.  Cross-compiling will be performed.")

        # Where to find the ARM cross-compiler, in order of precedence:
        #   1. -DARM_TOOLCHAIN_DIR=/path/to/toolchain on the cmake command line
        #   2. the ECEN427_ARM_TOOLCHAIN environment variable
        #   3. the copy downloaded into this repo by `make g++-arm-11.2`
        #
        # Graders should use (2), so one shared toolchain can serve every
        # student repo instead of downloading a copy into each one.
        if (NOT ARM_TOOLCHAIN_DIR)
            if (DEFINED ENV{ECEN427_ARM_TOOLCHAIN})
                set(ARM_TOOLCHAIN_DIR "$ENV{ECEN427_ARM_TOOLCHAIN}")
            else()
                set(ARM_TOOLCHAIN_DIR "${ROOT_DIR}/tools/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf")
            endif()
        endif()

        set(ARM_CC "${ARM_TOOLCHAIN_DIR}/bin/arm-none-linux-gnueabihf-gcc")
        set(ARM_CXX "${ARM_TOOLCHAIN_DIR}/bin/arm-none-linux-gnueabihf-g++")

        if (NOT EXISTS "${ARM_CXX}")
            message(FATAL_ERROR
                "Cross-compilation ARM toolchain not found at:\n"
                "    ${ARM_TOOLCHAIN_DIR}\n"
                "\n"
                "Either run `make g++-arm-11.2` from the root directory to download it,\n"
                "or point at a copy you already have:\n"
                "    export ECEN427_ARM_TOOLCHAIN=/path/to/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf")
        endif()

        message(STATUS "ARM toolchain: ${ARM_TOOLCHAIN_DIR}")

        SET(CMAKE_SYSTEM_PROCESSOR armv7)
        SET(CMAKE_CROSSCOMPILING 1)
        set(CMAKE_C_COMPILER "${ARM_CC}")
        set(CMAKE_CXX_COMPILER "${ARM_CXX}")
        add_compile_options("-march=armv7-a")
        add_compile_options("-mfpu=vfpv3")
        add_compile_options("-mfloat-abi=hard")
        add_compile_options("-Wno-abi")
        add_link_options("-march=armv7-a")
        add_link_options("-mfpu=vfpv3")
        add_link_options("-mfloat-abi=hard")
        add_link_options("-mhard-float")
    endif()
endif()

# Graders: set ECEN427_NO_DEPLOY=1 to skip copying executables to the board.
set(DEPLOY_TO_BOARD ON)
if (DEFINED ENV{ECEN427_NO_DEPLOY} AND NOT "$ENV{ECEN427_NO_DEPLOY}" STREQUAL "0")
    set(DEPLOY_TO_BOARD OFF)
endif()

function(deploy_to_board target_name)
    if (NOT DEPLOY_TO_BOARD)
        return()
    endif()
    if (NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "armv7l")
        add_custom_command(
            TARGET ${target_name}
            POST_BUILD
            COMMENT "Sending ${target_name} to PYNQ board..."
            COMMAND scp $<TARGET_FILE:${target_name}> byu@pynq:/home/byu/myrepo/cross-compiled/
        )
    endif()
endfunction()

include_directories(.)
include_directories(drivers)
include_directories(apps)
include_directories(../kernel/hdmi_ctrl)
include_directories(../kernel/audio_codec)
include_directories(../kernel/dma_desc)
include_directories(../kernel/pit)


add_subdirectory(drivers)
add_subdirectory(apps)
