cmake_minimum_required(VERSION 3.21)

option(ArgsBlade_BUILD_TEST "Build the ArgsBlade test" ON)
set(Tgt ArgsBlade CACHE STRING "target name")

project(ArgsBlade VERSION 0.1)

# …Ë÷√ƒ£øÈŒª÷√
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(src)

if (ArgsBlade_BUILD_TEST)
    enable_testing()
    add_subdirectory(tests)
endif ()
