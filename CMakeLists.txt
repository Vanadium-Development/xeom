cmake_minimum_required(VERSION 3.28)
project(xeom C)

set(CMAKE_C_STANDARD 11)

add_executable(xeom xeom/main.c
        image/image.h
        image/image.c
        error/error.h
        error/error.c
        preview/preview.h
        preview/preview.c
        math/shape.h
        math/vec3d.h
        math/vec3d.c
        math/ray.h
        math/shape.c
        math/utility.h
        math/utility.c)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(xeom ${SDL2_LIBRARIES})
