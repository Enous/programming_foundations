cmake_minimum_required(VERSION 3.26)
project(20 C)

set(CMAKE_C_STANDARD 11)

include_directories(../libs/data_structures/matrix
        ../libs/data_structures/string)

add_library(data_structures ../libs/data_structures/matrix/matrix.c
        ../libs/data_structures/string/string_.c
        problems.c
        problems.h)

add_executable(20 main.c
        problems.c
        problems.h)

target_link_libraries(20 data_structures)