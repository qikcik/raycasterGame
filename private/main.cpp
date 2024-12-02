#include "raylib.h"

int main(void)
{
    constexpr struct
    {
        int width = 720;
        int height = 480;
    } screen;

    InitWindow(screen.width, screen.height, "game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color(33,33,33));

        DrawPixel(120, 120, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}