cmake_minimum_required(VERSION 3.26)
project("14" C)

set(CMAKE_C_STANDARD 11)

add_executable("14" main.c
        ../libs/data_structures/vector/vector.h
        ../libs/data_structures/vector/vector.c
        ../libs/data_structures/vector/vectorVoid.h)

add_subdirectory(../libs)
target_link_libraries("14" data_structures)
