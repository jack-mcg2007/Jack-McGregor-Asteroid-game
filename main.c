#include "raylib.h"
#include <stdio.h>

float shipX = 300;
float shipY = 300;

float left;
float right;
float top;
float bottom;

char scoreString [50];
float score = 0;


struct Asteroid{
float positionX;
float positionY;
float speed;
float leftHitbox;
float rightHitbox;
float topHitbox;
float bottomHitbox;
};

struct Asteroid a1;
struct Asteroid a2;

bool gameOver = false;

void moveShip()
{
    //ship movement
    if(IsKeyDown(KEY_A)) shipX -= 5;
    if(IsKeyDown(KEY_D)) shipX += 5;
    if(IsKeyDown(KEY_W)) shipY -= 5;
    if(IsKeyDown(KEY_S)) shipY += 5;
    if(shipX<20) shipX = 20;
    if(shipX>580) shipX = 580;
    if(shipY<0) shipY = 0;
    if(shipY>570) shipY = 570; //prevents ship from going off screen
}  

void shipHitbox()
{
    left = shipX - 20;
    right = shipX + 20;
    top = shipY - 15;
    bottom = shipY + 15;
}

void asteroidHitbox()
{
    a1.leftHitbox = a1.positionX - 20;
    a1.rightHitbox = a1.positionX + 20;
    a1.topHitbox = a1.positionY - 20;
    a1.bottomHitbox = a1.positionY + 20;

    a2.leftHitbox = a2.positionX - 20;
    a2.rightHitbox = a2.positionX + 20;
    a2.topHitbox = a2.positionY - 20;
    a2.bottomHitbox = a2.positionY + 20;
}    
void verticalAsteroid()
{
    a1.positionY += a1.speed;
    if (a1.positionY >620)
    {
        a1.positionY = 0;
        a1.positionX = GetRandomValue(20,580);
    }
}

void horizontalAsteroid()
{
    a2.positionX += a2.speed;
    if(a2.positionX > 620)
    {
        a2.positionX = 0;
        a2.positionY = GetRandomValue(20,580);
    }
    
}
    
void updateScore()
{
    score +=0.01;
    sprintf(scoreString, "Score: %d", (int)score);
}
    
void graphics()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTriangle((Vector2){shipX + 20, shipY +15}, (Vector2){shipX, shipY - 15}, (Vector2){shipX - 20, shipY +15}, RAYWHITE);
    DrawCircle(a1.positionX, a1.positionY, 20, WHITE);
    DrawCircle(a2.positionX, a2.positionY, 20, WHITE);
    DrawText(scoreString, 10, 10, 20, RAYWHITE);
    EndDrawing();
}

void startScreen()
{   
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Press SPACE to start", 300, 300, 100, WHITE);
    EndDrawing();


}
int main(void)
{   
    InitWindow(600,600, "Asteroid game");
    SetTargetFPS(60);
    a1.positionX = GetRandomValue(20,580);
    a1.positionY = 20;
    a1.speed = 3;
    a2.positionY = GetRandomValue(20,580);
    a2.positionX = 580;
    a2.speed = 3;
    while (!WindowShouldClose() && !gameOver)
    {   
        moveShip();
        horizontalAsteroid();
        verticalAsteroid();
        shipHitbox();
        asteroidHitbox();
        updateScore();
        graphics();
        if (score > 10){
            a1.speed = 5;
            a2.speed = 5;
        }
        if((left<a1.rightHitbox && right>a1.leftHitbox && top<a1.bottomHitbox && bottom>a1.topHitbox) || (left<a2.rightHitbox && right>a2.leftHitbox && top<a2.bottomHitbox && bottom>a2.topHitbox) ){
            gameOver = true;
        }

        
    }
    CloseWindow();
    return 0;
}  
