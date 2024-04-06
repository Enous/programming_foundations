cmake_minimum_required(VERSION 3.26)
project(17 C)

set(CMAKE_C_STANDARD 11)
include_directories(../libs/data_structures/string
        ../17/problems)

add_library(data_structures ../libs/data_structures/string/string_.c)

add_executable(17 main.c
        problems/2-3.c
        problems/problems.h
        problems/4.c)

target_link_libraries(17 data_structures)
