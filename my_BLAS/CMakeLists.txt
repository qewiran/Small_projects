cmake_minimum_required(VERSION 3.22)
project(BLAS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic -std=c++2b)

add_executable(blas)
target_include_directories(blas PRIVATE include)
add_subdirectory(src)
