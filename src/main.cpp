#include "engine/core/window_manager.hpp"
#include "engine/core/input_manager.hpp"
#include "engine/core/asset_manager.hpp"
#include "engine/events/event_manager.hpp"
#include <entt/entt.hpp>
#include <iostream>

using namespace nexoris::engine;

int main()
{
    // Initialize Managers
    WindowManager windowManager;
    InputManager inputManager;
    AssetManager assetManager;
    EventManager eventManager;

    // Initialize Window
    windowManager.Init("Nexoris - Engine Foundation (ECS)");

    // Initialize ECS Registry
    entt::registry registry;

    // Optional: Test Event Manager subscription
    eventManager.Subscribe(EventType::WindowResize, [](std::shared_ptr<EventData> data) {
        std::cout << "Event Received: Window Resize!" << std::endl;
    });

    // Game Loop
    while (!windowManager.ShouldClose())
    {
        // 1. Update Managers
        windowManager.Update();
        inputManager.Update();

        // 2. Test Input & Event
        if (inputManager.IsActionPressed(Action::Interact)) {
            std::cout << "Interact Button Pressed!" << std::endl;
            eventManager.Publish(EventType::WindowResize); // Just firing a test event
        }

        // 3. ECS Systems (Empty for now)

        // 4. Render
        windowManager.BeginRender();
        
        // Draw things to canvas here
        const char* titleText = "Tahap 1: Engine Foundation Berhasil!";
        const char* subText = "Tekan 'E' untuk menguji Input & Event Bus (Lihat Console)";
        
        int titleWidth = MeasureText(titleText, 40);
        int subWidth = MeasureText(subText, 20);

        DrawText(titleText, (WindowManager::RENDER_WIDTH - titleWidth) / 2, WindowManager::RENDER_HEIGHT / 2 - 50, 40, GREEN);
        DrawText(subText, (WindowManager::RENDER_WIDTH - subWidth) / 2, WindowManager::RENDER_HEIGHT / 2 + 10, 20, LIGHTGRAY);
        
        windowManager.EndRender();
    }

    // Cleanup (Destructors of managers will handle the rest)
    return 0;
}