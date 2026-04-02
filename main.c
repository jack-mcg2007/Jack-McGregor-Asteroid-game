#include "raylib.h"

int main(void)
{   
    InitWindow(1000,600, "Asteroid game");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}   