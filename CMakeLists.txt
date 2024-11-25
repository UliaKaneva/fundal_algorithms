cmake_minimum_required(VERSION 3.22)
project(Lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(laba2.7 "Laba 2/task7/laba2-7.c"
        "Laba 2/task7/2-7.c"
        "Laba 2/task7/2-7.h")
target_link_libraries(laba2.7 m)
add_executable(laba2.2 "Laba 2/task2/laba2-2.c"
        "Laba 2/task2/2-2.h"
        "Laba 2/task2/2-2.c")
target_link_libraries(laba2.2 m)
add_executable(laba2.1 "Laba 2/task1/laba2-1.c"
        "Laba 2/task1/2-1.c"
        "Laba 2/task1/2-1.h")
add_executable(laba2.8 "Laba 2/task8/laba2-8.c"
        "Laba 2/task8/2-8.h"
        "Laba 2/task8/2-8.c"
        "Laba 2/task8/2-8.c")
add_executable(laba3.1 Laba3/task1/laba3-1.c
        Laba3/task1/3-1.h
        Laba3/task1/3-1.c)
add_executable(laba3.4 Laba3/task4/laba3-4.c
        Laba3/task4/strings.c
        Laba3/task4/strings.h
        Laba3/task4/3-4.c
        Laba3/task4/3-4.h)

add_executable(laba3.3 Laba3/task3/laba3-3.c
        Laba3/task3/3-3.c
        Laba3/task3/3-3.h
)
add_executable(laba4.1 Laba4/task1/main4-1.c
        Laba3/task4/strings.h
        Laba3/task4/strings.c
        Laba4/task1/hash_table.c
        Laba4/task1/hash_table.h
        Laba4/task1/4-1.c
        Laba4/task1/4-1.h)
target_link_libraries(laba4.1 m)