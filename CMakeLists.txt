cmake_minimum_required(VERSION 4.1)
project(SLImage C)

set(CMAKE_C_STANDARD 11)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

add_executable(SLImage
        src/main.c
        src/write.c
        src/read.c
        src/display.c)

target_link_libraries(SLImage ${X11_LIBRARIES} m)
