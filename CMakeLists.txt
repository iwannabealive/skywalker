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

target_compile_definitions(gal_engine_demo PRIVATE PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_command(TARGET gal_engine_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts
            $<TARGET_FILE_DIR:gal_engine_demo>/scripts)

# For Visual Studio users, make sure source files show up
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_HEADERS} ${ENGINE_SOURCES} main.cpp)
