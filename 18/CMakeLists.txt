cmake_minimum_required(VERSION 3.26)
project(18 C)

set(CMAKE_C_STANDARD 11)

include_directories(../libs/data_structures/string)

add_library(data_structures ../libs/data_structures/string/string_.c)

add_executable(18 main.c)

target_link_libraries(18 data_structures)