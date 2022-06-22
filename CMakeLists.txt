cmake_minimum_required(VERSION 3.17)
project(GameOfLife C)
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_C_STANDARD 99)

add_executable(GameOfLife main.c engine.c engine.h display.c display.h file.c file.h)

target_link_libraries(GameOfLife ${SDL2_LIBRARY}  -lmingw32 -lSDL2main -lSDL2)
