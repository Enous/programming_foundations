cmake_minimum_required(VERSION 3.26)
project(20 C)

set(CMAKE_C_STANDARD 11)

include_directories(../libs/data_structures/matrix)

add_library(data_structures ../libs/data_structures/matrix/matrix.c
        problems.c
        problems.h)

add_executable(20 main.c
        problems.c
        problems.h
        problem9.c
        problem10.c
)

target_link_libraries(20 data_structures)