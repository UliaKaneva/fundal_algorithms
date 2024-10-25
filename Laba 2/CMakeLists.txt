cmake_minimum_required(VERSION 3.22)
project(Lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(laba7 task7/laba2-7.c
        task7/2-7.c
        task7/2-7.h)
target_link_libraries(laba7 m)
add_executable(laba2 task2/laba2-2.c
        task2/2-2.h
        task2/2-2.c)
target_link_libraries(laba2 m)
add_executable(laba1 task1/laba2-1.c
        task1/2-1.c
        task1/2-1.h)
