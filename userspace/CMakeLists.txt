cmake_minimum_required(VERSION 3.4)
project(ecen427)

set(CMAKE_BUILD_TYPE Release)

if (NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} EQUAL "armv7l")
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


include_directories(.)
include_directories(drivers)

add_subdirectory(drivers)
add_subdirectory(apps)
