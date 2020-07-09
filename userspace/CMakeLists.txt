cmake_minimum_required(VERSION 3.4)

set(CMAKE_BUILD_TYPE Debug)

include_directories(drivers)

add_subdirectory(drivers)
add_subdirectory(apps)

