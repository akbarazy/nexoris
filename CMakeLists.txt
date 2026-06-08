cmake_minimum_required(VERSION 3.15)
project(Nexoris)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(external/raylib)
add_executable(Nexoris
    src/main.cpp
    src/core/game.cpp
    src/entities/player.cpp
)
target_link_libraries(Nexoris raylib)
target_include_directories(Nexoris PRIVATE include)