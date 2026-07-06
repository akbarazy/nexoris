#pragma once
#include <raylib.h>
#include <string>

namespace nexoris {
namespace engine {

class WindowManager {
public:
    static constexpr int GAME_WIDTH = 1280;
    static constexpr int GAME_HEIGHT = 720;
    static constexpr int RENDER_WIDTH = 1920;
    static constexpr int RENDER_HEIGHT = 1080;

    WindowManager();
    ~WindowManager();

    void Init(const std::string& title);
    void Close();
    void Update();

    // Call this before drawing game world (ECS)
    void BeginRender();
    // Call this after drawing game world
    void EndRender();

    bool ShouldClose() const;
    
    // Begin 2D mode with a specific camera (can be used later when camera is decoupled)
    void BeginCameraMode(Camera2D camera);
    void EndCameraMode();

private:
    RenderTexture2D m_Canvas;
};

} // namespace engine
} // namespace nexoris
