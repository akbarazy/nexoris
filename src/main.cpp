#include <raylib.h>

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Nexoris");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawText("Hello World", 500, 300, 50, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}