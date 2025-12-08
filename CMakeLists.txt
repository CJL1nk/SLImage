cmake_minimum_required(VERSION 4.1)
project(SLImage C)

set(CMAKE_C_STANDARD 11)

add_executable(SLImage
        src/main.c
        src/write.c
        src/read.c)
