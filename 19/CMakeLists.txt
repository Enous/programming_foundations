cmake_minimum_required(VERSION 3.26)
project(19 C)

set(CMAKE_C_STANDARD 11)

include_directories(../libs/data_structures/matrix
        ../libs/data_structures/string)

add_library(data_structures ../libs/data_structures/matrix/matrix.c
        ../libs/data_structures/string/string_.c)

add_executable(19 main.c
        problems.h
        problems.c)

target_link_libraries(19 data_structures)