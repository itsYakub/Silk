cmake_minimum_required(VERSION 3.14)

project(example.out)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0 
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.c)
target_link_libraries(${PROJECT_NAME} raylib)