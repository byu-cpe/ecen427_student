cmake_minimum_required(VERSION 3.5)
project(ecen427)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_C_FLAGS_RELEASE "-O3")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

set(USERSPACE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ROOT_DIR ${USERSPACE_DIR} DIRECTORY)

if (TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-12" REQUIRED)
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=modernize-*,bugprone-*,clang-analyzer-*,cppcoreguidelines-*,google-*,misc-*,portability-*,-google-readability-braces-around-statements,-cppcoreguidelines-macro-usage,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-cppcoreguidelines-avoid-non-const-global-variables")

else() 
    if (NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "armv7l")
        message(WARNING "Building on non-PYNQ board.  Cross-compiling will be performed.")

        if (NOT EXISTS "${ROOT_DIR}/tools/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++")
            message(FATAL_ERROR "Cross-compilation ARM toolchain not found.  Please run `make g++-arm-11.2` from the root directory.")
        endif()

        SET(CMAKE_SYSTEM_PROCESSOR armv7)
        SET(CMAKE_CROSSCOMPILING 1)
        set(CMAKE_C_COMPILER "${ROOT_DIR}/tools/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc")
        set(CMAKE_CXX_COMPILER "${ROOT_DIR}/tools/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++")
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

function(deploy_to_board target_name)
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
