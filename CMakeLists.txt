cmake_minimum_required(VERSION 3.15)
project(Nexoris)
set(CMAKE_CXX_STANDARD 17)

# Fetch EnTT
include(FetchContent)
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v3.12.2
)
FetchContent_MakeAvailable(entt)

add_subdirectory(external/raylib)

add_executable(Nexoris
    src/main.cpp
)

target_link_libraries(Nexoris PRIVATE raylib EnTT::EnTT)
target_include_directories(Nexoris PRIVATE include)