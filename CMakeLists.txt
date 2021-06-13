cmake_minimum_required(VERSION 3.12)
project(raytracing)

set(
    SRC_RAYTRACING
    src/AABB_cube.cpp
    src/img.cpp
    src/img_io.cpp
    src/material.cpp
    src/plane.cpp
    src/ray.cpp
    src/scene.cpp
    src/sphere.cpp
    src/triangle.cpp
    src/utils.cpp
    src/vector3.cpp
)

include_directories(
    src/
)

set(CMAKE_CXX_STANDARD 17)

set(OPT_FLAGS, "-Ofast")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(raytracing)
target_sources(raytracing PRIVATE "src/main.cpp" ${SRC_RAYTRACING})

target_compile_options(raytracing PRIVATE -Wall -Wextra)
