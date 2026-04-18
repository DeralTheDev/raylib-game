/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include <stdio.h>

#include "raylib.h"
#include "screens.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include "joystick.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static float screenWidth = 0.0f;
static float screenHeight = 0.0f;
static float delta = 0.0f;

static int framesCounter = 0;
static int finishScreen = 0;

static Player player = { 0 };

static const int prjArrSize = 50; // Only 50 projectiles on-screen
static Projectile prjArr[prjArrSize] = { 0 };
static int prjArrIndex = 0;

static const int enemyArrSize = 10; // Only 10 enemies on-screen
static Enemy enemyArr[enemyArrSize] = { 0 };
static int enemyArrIndex = 0;
static int enemyCounter = 0;
static int enemyCooldown = 0;

static JoyStick joyStick = { 0 };

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

static void prjArrDel(Projectile prjArr[50], int index, int *currSize)
{
    for (int i = index; i < (*currSize) - 1; i++)
        prjArr[i] = prjArr[i + 1];
    (*currSize)--;
}

static void enemyArrDel(Enemy enemyArr[50], int index, int *currSize)
{
    for (int i = index; i < (*currSize) - 1; i++)
        enemyArr[i] = enemyArr[i + 1];
    (*currSize)--;
}

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    delta = 0.0f;

    framesCounter = 0;
    finishScreen = 0;

    player = initPlayer((Rectangle){150, 0, 75, 50}, (Vector2){0, 0}, 300, 10);
    player.rec.y = (screenHeight - player.rec.height) / 2;

    for (int i = 0; i < prjArrSize; i++)
    {
        prjArr[i] = (Projectile){ 0 };
    }
    prjArrIndex = 0;

    for (int i = 0; i < enemyArrSize; i++)
    {
        enemyArr[i] = (Enemy){ 0 };
    }
    enemyArrIndex = 0;
    enemyCounter = 0;
    enemyCooldown = 100;

    if (onMobileIpad)
    {
        SetGesturesEnabled(GESTURE_HOLD);
        joyStick = initJoyStick((Vector2){screenWidth * 0.15f, screenHeight * 0.8f}, screenWidth * 0.1f);
    }
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    delta = GetFrameTime();

    if (onMobileIpad) updateJoyStick(&joyStick, delta);

    updatePlayer(&player, delta);

    // Shoot projectile
    if (player.shoot && prjArrIndex < sizeof(prjArr) / sizeof(Projectile))
    {
        prjArr[prjArrIndex] = initProjectile(
            (Rectangle){
                player.rec.x + player.rec.width, 0, 15, 8},
            (Vector2){0, 0}, 1000, 1
        );
        prjArr[prjArrIndex].rec.y = player.rec.y + (player.rec.height - prjArr[prjArrIndex].rec.height) / 2;
        prjArrIndex++;
        player.shoot = false;
    }

    // Enemy
    if (enemyArrIndex >= enemyArrSize) enemyCounter = 0;
    else enemyCounter++;

    if (enemyCounter >= enemyCooldown)
    {
        enemyArr[enemyArrIndex] = initEnemy(
            (Rectangle){GetRandomValue(screenWidth + 50, screenWidth + 150), GetRandomValue(0, screenHeight), 75, 50},
            (Vector2){0, 0}, GetRandomValue(100, 300), GetRandomValue(3, 10)
        );
        enemyArrIndex++;
        enemyCounter = 0;
    }

    for (int i = 0; i < enemyArrIndex; i++)
    {
        updateEnemy(&enemyArr[i], player.rec, delta);
        if (enemyArr[i].shoot && prjArrIndex < prjArrSize)
        {
            prjArr[prjArrIndex] = initProjectile(
                (Rectangle){
                    enemyArr[i].rec.x, 0, 15, 8},
                (Vector2){0, 0}, -500, 2
            );
            prjArr[prjArrIndex].rec.y = enemyArr[i].rec.y + (enemyArr[i].rec.height - prjArr[prjArrIndex].rec.height) / 2;
            prjArrIndex++;
            enemyArr[i].shoot = false;
        }

        if (enemyArr[i].rec.x + enemyArr[i].rec.width <= 0)
            enemyArrDel(enemyArr, i, &enemyArrIndex);
    }

    // Projectiles
    for (int i = 0; i < prjArrIndex; i++)
    {
        updateProjectile(&prjArr[i], delta);

        // If projectile out of window, DELETE IT
        if (prjArr[i].rec.x >= screenWidth || prjArr[i].rec.x - prjArr[i].rec.width <= 0)
        {
            prjArrDel(prjArr, i, &prjArrIndex);
        }

        // Projectile collision check
        if (projectileCollided(prjArr[i], player.rec) && prjArr[i].id == 2)
        {
            prjArrDel(prjArr, i, &prjArrIndex);
            player.healthBar.healthNum--;
        }

        for (int j = 0; j < enemyArrIndex; j++)
        {
            if (projectileCollided(prjArr[i], enemyArr[j].rec) && prjArr[i].id == 1)
            {
                prjArrDel(prjArr, i, &prjArrIndex);
                enemyArr[j].healthBar.healthNum--;
                if (enemyArr[j].healthBar.healthNum <= 0)
                    enemyArrDel(enemyArr, j, &enemyArrIndex);
            }
        }
    }

    //if (player.healthBar.healthNum <= 0) finishScreen = 1;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    Vector2 pos = {10, 10};
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, fontSize, 4, MAROON);
    // Draw projectile(s)
    for (int i = 0; i < prjArrIndex; i++)
    {
        DrawRectangleRec(prjArr[i].rec, MAROON);
    }

    // Draw player
    drawPlayer(player);

    // Draw enemy(s)
    for (int i = 0; i < enemyArrIndex; i++)
    {
        drawEnemy(enemyArr[i]);
    }

    if (onMobileIpad)
    {
        Vector2 pos = {10, 50};
        DrawTextEx(font, "ON MOBILE/IPAD", pos, fontSize, 4, DARKGREEN);

        drawJoyStick(joyStick);
    }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    unloadPlayer(&player);

    for (int i = 0; i < prjArrIndex; i++)
    {
        unloadProjectile(&prjArr[i]);
    }
    prjArrIndex = 0;

    for (int i = 0; i < enemyArrIndex; i++)
    {
        unloadEnemy(&enemyArr[i]);
    }
    enemyArrIndex = 0;
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}