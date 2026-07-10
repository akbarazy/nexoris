#include "engine/core/window_manager.hpp"
#include "engine/core/input_manager.hpp"
#include "engine/core/asset_manager.hpp"
#include "engine/events/event_manager.hpp"
#include "engine/ecs/player_control_system.hpp"
#include "engine/ecs/movement_system.hpp"
#include "engine/ecs/collision_system.hpp"
#include "engine/ecs/render_system.hpp"
#include "engine/ecs/camera_system.hpp"
#include "game/factories/entity_factory.hpp"
#include <entt/entt.hpp>
#include <raylib.h>
#include <iostream>

using namespace nexoris::engine;
using namespace nexoris::engine::ecs;
using namespace nexoris::game;

int main()
{
    // Initialize Managers
    WindowManager windowManager;
    InputManager inputManager;
    AssetManager assetManager;
    EventManager eventManager;

    // Initialize Window
    windowManager.Init("Nexoris - Engine Foundation (ECS)");

    // Initialize ECS Registry & Systems
    entt::registry registry;
    PlayerControlSystem playerControlSystem;
    MovementSystem movementSystem;
    CollisionSystem collisionSystem;
    RenderSystem renderSystem;
    CameraSystem cameraSystem(WindowManager::RENDER_WIDTH, WindowManager::RENDER_HEIGHT);

    // Setup World (Spawn map area and obstacles from map.cpp logic)
    EntityFactory::CreateMapArea(registry, { -1000.0f, -1000.0f, 3000.0f, 3000.0f });
    EntityFactory::CreateMapObstacle(registry, { 300.0f, 200.0f, 80.0f, 80.0f });
    EntityFactory::CreateMapObstacle(registry, { 800.0f, 400.0f, 160.0f, 60.0f });
    EntityFactory::CreateMapObstacle(registry, { 500.0f, 450.0f, 60.0f, 150.0f });
    EntityFactory::CreateMapObstacle(registry, { -300.0f, -200.0f, 100.0f, 100.0f });
    EntityFactory::CreateMapObstacle(registry, { 1200.0f, -150.0f, 200.0f, 80.0f });
    EntityFactory::CreateMapObstacle(registry, { -500.0f, 800.0f, 80.0f, 200.0f });
    EntityFactory::CreateMapObstacle(registry, { 1500.0f, 1200.0f, 300.0f, 300.0f });
    EntityFactory::CreateMapObstacle(registry, { -800.0f, -800.0f, 150.0f, 150.0f });
    EntityFactory::CreateMapObstacle(registry, { 800.0f, 1600.0f, 250.0f, 100.0f });

    // Spawn Player
    EntityFactory::CreatePlayer(registry, 640.0f - 16.0f, 360.0f - 16.0f);

    // Game Loop
    while (!windowManager.ShouldClose())
    {
        float deltaTime = GetFrameTime();

        // 1. Update Managers
        windowManager.Update();
        inputManager.Update();

        // 2. ECS Systems Update
        playerControlSystem.Update(registry, inputManager);
        movementSystem.Update(registry);
        collisionSystem.Update(registry);
        cameraSystem.Update(registry, deltaTime);

        // 3. Render
        windowManager.BeginRender();
        
        windowManager.BeginCameraMode(cameraSystem.GetCamera());
        renderSystem.Update(registry);
        windowManager.EndCameraMode();

        // Draw UI overlay
        const char* titleText = "Tahap 2 & 3: ECS Player, Map & Camera Berhasil!";
        const char* subText = "Gunakan W, A, S, D untuk bergerak";
        int titleWidth = MeasureText(titleText, 30);
        int subWidth = MeasureText(subText, 20);
        DrawText(titleText, (WindowManager::RENDER_WIDTH - titleWidth) / 2, 50, 30, GREEN);
        DrawText(subText, (WindowManager::RENDER_WIDTH - subWidth) / 2, 90, 20, LIGHTGRAY);
        
        windowManager.EndRender();
    }

    return 0;
}