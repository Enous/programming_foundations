cmake_minimum_required(VERSION 3.26)
project(16 C)

set(CMAKE_C_STANDARD 11)
include_directories(../libs/data_structures/matrix)

add_library(data_structures ../libs/data_structures/matrix/matrix.c
        ../libs/data_structures/vector/vector.c)

add_executable(16 main.c
        funcs.h
        funcs.c)

target_link_libraries(16 data_structures)