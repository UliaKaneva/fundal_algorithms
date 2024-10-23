cmake_minimum_required(VERSION 3.22)
project(Lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(laba7 laba2-7.c
        2-7.c
        2-7.h)
target_link_libraries(laba7 m)
add_executable(laba2 laba2-2.c
        2-2.h
        2-2.c)
target_link_libraries(laba2 m)