cmake_minimum_required(VERSION 3.14)

project(example.out)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.3 
)

FetchContent_MakeAvailable(SDL2)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.c)
target_link_libraries(${PROJECT_NAME} SDL2)