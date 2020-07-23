cmake_minimum_required(VERSION 3.4)
project(ecen427)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -pedantic -Werror)


include_directories(drivers)

add_subdirectory(drivers)
add_subdirectory(apps)
