cmake_minimum_required(VERSION 3.15)
project(gal_engine_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB ENGINE_HEADERS engine/*.hpp)
file(GLOB ENGINE_SOURCES engine/*.cpp)

add_executable(gal_engine_demo
    main.cpp
    ${ENGINE_HEADERS}
    ${ENGINE_SOURCES}
)

# For Visual Studio users, make sure source files show up
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_HEADERS} ${ENGINE_SOURCES} main.cpp)
