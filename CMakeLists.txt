cmake_minimum_required(VERSION 3.28)
project(xeom C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  bin)

set(CMAKE_C_STANDARD 11)

set(XEOM_COMPILE_WITH_SDL false)
set(XEOM_RENDER_SAMPLES 99)

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
        math/utility.c
        mm/array.h
        mm/array.c
        core/scene.h
        core/camera.h
        core/rt.h
        core/rt.c
        core/scene.c
        shader/shader.h
        shader/shaders/binary.c
        shader/callback.h
        shader/shaders/normal.c
        math/ray.c
        shader/shaders/metal.c
        shader/nothing.c
        shader/shaders/diffuse.c
        core/pr.h
        core/pr.c
)

# Link with the math library
target_link_libraries(xeom m)

if (XEOM_COMPILE_WITH_SDL)
    add_compile_definitions(XEOM_USE_GUI)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(xeom ${SDL2_LIBRARIES})
endif ()

add_compile_definitions(XEOM_RENDER_SAMPLES=${XEOM_RENDER_SAMPLES})