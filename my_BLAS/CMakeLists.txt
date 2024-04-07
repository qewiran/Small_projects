cmake_minimum_required(VERSION 3.22)
project(BLAS)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

add_executable(blas PRIVATE)
target_include_directories(blas headers)
add_subdirectory(src)

