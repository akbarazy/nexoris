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
    src/engine/core/window_manager.cpp
    src/engine/core/input_manager.cpp
    src/engine/core/asset_manager.cpp
    src/engine/events/event_manager.cpp
    
    src/engine/ecs/player_control_system.cpp
    src/engine/ecs/movement_system.cpp
    src/engine/ecs/collision_system.cpp
    src/engine/ecs/render_system.cpp
    src/engine/ecs/camera_system.cpp
    src/game/factories/entity_factory.cpp
    
    # Old game files (disabled temporarily for architectural refactoring)
    # src/core/game.cpp
    # src/core/camera.cpp
    # src/entities/player.cpp
    # src/world/map.cpp
)

target_link_libraries(Nexoris PRIVATE raylib EnTT::EnTT)
target_include_directories(Nexoris PRIVATE include)