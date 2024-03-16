cmake_minimum_required(VERSION 3.26)
project("15" C)

set(CMAKE_C_STANDARD 11)
include_directories(../libs/data_structures/matrix)

add_library(data_structures ../libs/data_structures/matrix/matrix.c)

add_executable(15 main.c)

target_link_libraries(15 data_structures)