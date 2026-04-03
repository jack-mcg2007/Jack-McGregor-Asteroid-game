#include "raylib.h"

float shipX = 300;
float shipY = 300;

float score = 0;

int main(void)
{   
    InitWindow(600,600, "Asteroid game");
    while (!WindowShouldClose())
    {   
        if(IsKeyDown(KEY_A)) shipX -= 5;
        if(IsKeyDown(KEY_D)) shipX += 5;
        if(IsKeyDown(KEY_W)) shipY -= 5;
        if(IsKeyDown(KEY_S)) shipY += 5;
        if(shipX<20) shipX = 20;
        if(shipX>580) shipX = 580;
        if(shipY<0) shipY = 0;
        if(shipY>570) shipY = 570;

        score +=0.1;

        SetTargetFPS(60);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTriangle((Vector2){shipX + 20, shipY +15}, (Vector2){shipX, shipY - 15}, (Vector2){shipX - 20, shipY +15}, RAYWHITE);
        DrawText("Score: 0", 10,10,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}    