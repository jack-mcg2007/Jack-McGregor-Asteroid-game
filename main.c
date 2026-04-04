#include "raylib.h"
#include <stdio.h>

float shipX = 300;
float shipY = 300;
Texture2D shipTexture;
//creates variables for ship position and texture

float left;
float right;
float top;
float bottom;
//creates variables for the ships hitbox

char scoreString [50];
float score = 0;

float speed;
//variable for asteroid speed

struct Asteroid{
float positionX;
float positionY;
float leftHitbox;
float rightHitbox;
float topHitbox;
float bottomHitbox;
int delay;
};
//struct storing variables for asteroids
Texture2D horiAsteroidTexture;
Texture2D vertAsteroidTexture;
//A different texture for both horizontal and vertical asteroids.
#define vertAsteroidCount 3
#define horiAsteroidCount 3
struct Asteroid verticalAsteroids [vertAsteroidCount];
struct Asteroid horizontalAsteroids [horiAsteroidCount];
//arrays storing vertical and horizontal asteroids

bool gameStarted = false;
bool gameOver = false;
//booleans used to control which screen the game shows

Texture2D nonPlayBackground;
Texture2D playBackground;

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
    if(shipY>570) shipY = 570; 
    //prevents ship from going off screen
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
    DrawTexture(playBackground, 0, 0, WHITE);
    DrawTexture(shipTexture, shipX, shipY, WHITE); //draws ship
    for(int i =0; i<vertAsteroidCount; i++)
    {
    DrawTexture(vertAsteroidTexture, verticalAsteroids[i].positionX, verticalAsteroids[i].positionY, WHITE);
    }
    for(int i =0; i<horiAsteroidCount;i++)
    {
    DrawTexture(horiAsteroidTexture, horizontalAsteroids[i].positionX, horizontalAsteroids[i].positionY, WHITE);
    }
    DrawText(scoreString, 10, 10, 20, RAYWHITE);
    EndDrawing();
}

void startScreen()
{   
    BeginDrawing();
    DrawTexture(nonPlayBackground, 0,0,WHITE);
    DrawText("Press SPACE to start", 80, 240, 40, WHITE);
    EndDrawing();
}

void endScreen()
{
    BeginDrawing();
    DrawTexture(nonPlayBackground, 0,0,WHITE);
    DrawText("GAME O V E R", 150, 240, 40, RED);
    DrawText("Press R to restart", 100, 340, 40, WHITE);
    DrawText(scoreString, 10, 10, 20, RAYWHITE);
    EndDrawing();
}

void reset()
{
    shipX = 300;
    shipY = 300;
    score = 0;

    for(int i =0; i<vertAsteroidCount; i++)
    {
        verticalAsteroids[i].positionX = GetRandomValue(20,580);
        verticalAsteroids[i].positionY = 20;
        verticalAsteroids[i].delay = i*120;
    }

    for(int i =0; i<horiAsteroidCount; i++)
    {
        horizontalAsteroids[i].positionY = GetRandomValue(20,580);
        horizontalAsteroids[i].positionX = 20;
        horizontalAsteroids[i].delay = i*120;
    }
}

int main(void)
{   
    InitWindow(600,600, "Asteroid game");
    SetTargetFPS(60);
    shipTexture = LoadTexture("ship.png");
    vertAsteroidTexture = LoadTexture("VerticalAsteroid.png");
    horiAsteroidTexture = LoadTexture("HorizontalAsteroid.png");
    nonPlayBackground = LoadTexture("baseBackground.png");
    playBackground = LoadTexture("playingBackground.png");
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

    while (!WindowShouldClose())
    {   
        if (!gameStarted)
        {
            startScreen();
            if(IsKeyPressed(KEY_SPACE)){
                gameStarted = true;
            }
            continue;
        }

        if (gameOver)
        {
            endScreen();
            if(IsKeyPressed(KEY_R))
            {
                gameOver = false;
                reset();
            }
            continue;
        }
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
        if (score > 30){
            speed = 7;
        }
        if (score > 50){
            speed = 10;
        }  
        if (score >100){
            speed = 15;
        }
    }
    CloseWindow();
    return 0;
}  
