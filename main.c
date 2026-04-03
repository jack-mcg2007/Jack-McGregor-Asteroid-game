#include "raylib.h"

float shipX = 300;
float shipY = 300;


int main(void)
{   
    InitWindow(600,600, "Asteroid game");
    while (!WindowShouldClose())
    {   
        if(IsKeyDown(KEY_A)) shipX -= 0.1;
        if(IsKeyDown(KEY_D)) shipX += 0.1;
        if(IsKeyDown(KEY_W)) shipY -= 0.1;
        if(IsKeyDown(KEY_S)) shipY += 0.1;
        if(shipX<0) shipX = 0;
        if(shipX>600) shipX = 600;
        if(shipY<0) shipY = 0;
        if(shipY>600) shipY = 600;


        BeginDrawing();
        ClearBackground(BLACK);
        DrawTriangle((Vector2){shipX + 20, shipY - 70}, (Vector2){shipX, shipY - 100}, (Vector2){shipX - 20, shipY - 70}, RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}    