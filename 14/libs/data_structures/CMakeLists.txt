cmake_minimum_required(VERSION 3.26)
project(14 C)

set(CMAKE_C_STANDARD 11)

add_library(data_structures
        vector/vector.c,
        vector/vector.h
)
