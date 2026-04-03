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

float speed;

struct Asteroid{
float positionX;
float positionY;
float leftHitbox;
float rightHitbox;
float topHitbox;
float bottomHitbox;
int delay;
};
#define vertAsteroidCount 3
#define horiAsteroidCount 3
struct Asteroid verticalAsteroids [vertAsteroidCount];
struct Asteroid horizontalAsteroids [horiAsteroidCount];

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
    for(int i =0; i<vertAsteroidCount; i++){
        verticalAsteroids[i].leftHitbox = verticalAsteroids[i].positionX - 20;
        verticalAsteroids[i].rightHitbox = verticalAsteroids[i].positionX + 20;
        verticalAsteroids[i].topHitbox = verticalAsteroids[i].positionY - 20;
        verticalAsteroids[i].bottomHitbox = verticalAsteroids[i].positionY + 20;
    }

    for(int i =0; i<horiAsteroidCount; i++){
        horizontalAsteroids[i].leftHitbox = horizontalAsteroids[i].positionX - 20;
        horizontalAsteroids[i].rightHitbox = horizontalAsteroids[i].positionX + 20;
        horizontalAsteroids[i].topHitbox = horizontalAsteroids[i].positionY - 20;
        horizontalAsteroids[i].bottomHitbox = horizontalAsteroids[i].positionY + 20; 
    }
}    
void verticalAsteroidMovement()
{
    for(int i =0; i<vertAsteroidCount; i++)
    {
        if(verticalAsteroids[i].delay>0)
        {
            verticalAsteroids[i].delay--;
            continue;
        }
        verticalAsteroids[i].positionY += speed;
        if (verticalAsteroids[i].positionY>580){
        verticalAsteroids[i].positionX = GetRandomValue(20,580);
        verticalAsteroids[i].positionY = 20;
        }
    }
}

void horizontalAsteroidMovement()
{
    for(int i =0; i<horiAsteroidCount; i++)
    {
        if(horizontalAsteroids[i].delay>0)
        {
            horizontalAsteroids[i].delay--;
            continue;
        }
        horizontalAsteroids[i].positionX += speed;
        if (horizontalAsteroids[i].positionX>580){
        horizontalAsteroids[i].positionY = GetRandomValue(20,580);
        horizontalAsteroids[i].positionX = 20;
        }
    }
}

void collisionCheck()
{
    for(int i=0; i<vertAsteroidCount; i++)
    {
        if(left<verticalAsteroids[i].rightHitbox && right>verticalAsteroids[i].leftHitbox && top<verticalAsteroids[i].bottomHitbox && bottom>verticalAsteroids[i].topHitbox)
        {
            gameOver = true;
        }
    }
    for(int i=0; i<horiAsteroidCount; i++)
    {
        if(left<horizontalAsteroids[i].rightHitbox && right>horizontalAsteroids[i].leftHitbox && top<horizontalAsteroids[i].bottomHitbox && bottom>horizontalAsteroids[i].topHitbox)
        {
            gameOver = true;
        }
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
    DrawTriangle((Vector2){shipX + 20, shipY +15}, (Vector2){shipX, shipY - 15}, (Vector2){shipX - 20, shipY +15}, RAYWHITE); //draws ship
    for(int i =0; i<vertAsteroidCount; i++)
    {
    DrawCircle(verticalAsteroids[i].positionX, verticalAsteroids[i].positionY, 20, WHITE);
    }
    for(int i =0; i<horiAsteroidCount;i++)
    {
    DrawCircle(horizontalAsteroids[i].positionX, horizontalAsteroids[i].positionY, 20, WHITE);
    }
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
        for(int i =0; i<vertAsteroidCount; i++)
        {
             verticalAsteroids[i].positionX = GetRandomValue(20,580);
             verticalAsteroids[i].positionY = 20;
        }
        for(int i =0; i<horiAsteroidCount; i++)
         {
             horizontalAsteroids[i].positionY = GetRandomValue(20,580);
             horizontalAsteroids[i].positionX = 20;
         }

        for(int i =0; i<vertAsteroidCount; i++)
        {
            verticalAsteroids[i].delay = i*120;
        }
        for(int i =0; i<horiAsteroidCount; i++)
        {
            horizontalAsteroids[i].delay = i*120;
        }
        speed = 3;

    while (!WindowShouldClose() && !gameOver)
    {   
        moveShip();
        horizontalAsteroidMovement();
        verticalAsteroidMovement();
        shipHitbox();
        asteroidHitbox();
        updateScore();
        graphics();
        collisionCheck();
        if (score > 10){
            speed = 5;
        }
  

        
    }
    CloseWindow();
    return 0;
}  
