cmake_minimum_required(VERSION 3.20)

project(renderer)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(renderer src/main.cpp
        src/display.cpp
        src/display.h
        src/vector.h
        src/vector.cpp
        src/mesh.h
        src/mesh.cpp
        src/triangle.cpp
        src/triangle.h
        src/array.h
        src/array.cpp
)

target_link_libraries(renderer ${SDL2_LIBRARIES})