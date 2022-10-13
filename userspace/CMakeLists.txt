cmake_minimum_required(VERSION 3.4)
project(ecen427)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_C_FLAGS_RELEASE "-O3")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

if (TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-12" REQUIRED)
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=modernize-*,bugprone-*,clang-analyzer-*,cppcoreguidelines-*,google-*,misc-*,portability-*,-google-readability-braces-around-statements,-cppcoreguidelines-macro-usage,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-cppcoreguidelines-avoid-non-const-global-variables")

else() 
    if (NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "armv7l")
        message(WARNING "Building on non-PYNQ board.  Cross-compiling will be attempted (this is experimental).")

        SET(CMAKE_SYSTEM_PROCESSOR armv7)
        SET(CMAKE_CROSSCOMPILING 1)
        set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
        set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
        add_compile_options("-march=armv7-a")
        add_compile_options("-mfpu=vfpv3")
        add_compile_options("-mfloat-abi=hard")
        add_link_options("-march=armv7-a")
        add_link_options("-mfpu=vfpv3")
        add_link_options("-mfloat-abi=hard")
        add_link_options("-mhard-float")
    endif()
endif()

include_directories(.)
include_directories(drivers)

add_subdirectory(drivers)
add_subdirectory(apps)
