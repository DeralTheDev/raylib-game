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
#include <math.h>

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

// Only 100 projectiles from player and enemy(s) on-screen
static Projectile prjArr[100] = { 0 };
static int prjArrSize = 0;
static int prjArrIndex = 0;

// Only 5 enemies on-screen
static Enemy enemyArr[5] = { 0 };
static int enemyArrSize = 0;
static int enemyArrIndex = 0;
static int enemyCounter = 0;
static int enemyCooldown = 0;

static JoyStick joyStick = { 0 };
static int maxTouchPoint = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

static void prjArrDel(Projectile prjArr[100], int index, int *currSize)
{
    for (int i = index; i < (*currSize) - 1; i++)
        prjArr[i] = prjArr[i + 1];
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

    player = initPlayer((Rectangle){150, 0, 75, 50}, 300, 10);
    player.rec.y = (screenHeight - player.rec.height) / 2;

    prjArrSize = sizeof(prjArr) / sizeof(Projectile);
    for (int i = 0; i < prjArrSize; i++)
    {
        prjArr[i] = (Projectile){ 0 };
    }
    prjArrIndex = 0;

    enemyArrSize = sizeof(enemyArr) / sizeof(Enemy);
    for (int i = 0; i < enemyArrSize; i++)
    {
        enemyArr[i] = (Enemy){ 0 };
    }
    enemyArrIndex = 0;
    enemyCounter = 0;
    enemyCooldown = 100;

    if (onMobileIpad)
    {
        joyStick = initJoyStick((Vector2){screenWidth * 0.15f, screenHeight * 0.75f}, screenWidth * 0.1f);
        maxTouchPoint = 2;
    }
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    delta = GetFrameTime();

    if (onMobileIpad)
    {
        int touchCount = GetTouchPointCount();
        if (touchCount > maxTouchPoint) touchCount = maxTouchPoint;
        for (int i = 0; i < touchCount; i++)
        {
            Vector2 touchPos = GetTouchPosition(i);
            int touchId = GetTouchPointId(i);

            // joyStick
            if (hypot(joyStick.basePos.x - touchPos.x, joyStick.basePos.y - touchPos.y) <= joyStick.baseRadius && !joyStick.drag)
                joyStick.touchId = touchId;

            if (joyStick.touchId == touchId) joyStick.drag = true;
            else joyStick.drag = false;

            if (joyStick.drag) joyStick.cPos = touchPos;
            else joyStick.cPos = joyStick.basePos;

            // player shoot
            if (joyStick.touchId != touchId)
            {
                player.shoot = (player.shootCounter == 0) ? true : false;
                if (player.shoot) player.shootCounter = 1;
            }
        }

        updateJoyStick(&joyStick, delta);
    }

    /*
    BUG: When the player starts shooting while being around lots of
    enemies it sinks or floats.
    */
    updatePlayer(&player, joyStick, delta);

    // Shoot projectile
    if (player.shoot && prjArrIndex < prjArrSize)
    {
        prjArr[prjArrIndex] = initProjectile(
            (Rectangle){player.rec.x + player.rec.width, 0, 15, 8}, 1000, 1
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
        int randIndex = GetRandomValue(0, enemyArrSize - 1);
        while (enemyArr[randIndex].maxSpeed != 0) randIndex = GetRandomValue(0, enemyArrSize - 1);
        enemyArr[randIndex] = initEnemy(
            (Rectangle){GetRandomValue(screenWidth + 50, screenWidth + 150), randIndex * (screenHeight / enemyArrSize) + 25, 75, 50},
            (Vector2){-GetRandomValue(50, 200), 0}, GetRandomValue(100, 300), GetRandomValue(3, 10)
        );
        enemyArrIndex++;
        enemyCounter = 0;
    }

    for (int i = 0; i < enemyArrSize; i++)
    {
        if (enemyArr[i].maxSpeed != 0)
        {
            updateEnemy(&enemyArr[i], delta);
            if (enemyArr[i].shoot && prjArrIndex < prjArrSize)
            {
                prjArr[prjArrIndex] = initProjectile(
                    (Rectangle){enemyArr[i].rec.x, 0, 15, 8}, -500, 2
                );
                prjArr[prjArrIndex].rec.y = enemyArr[i].rec.y + (enemyArr[i].rec.height - prjArr[prjArrIndex].rec.height) / 2;
                prjArrIndex++;
                enemyArr[i].shoot = false;
            }

            if (enemyArr[i].rec.x + enemyArr[i].rec.width <= 0)
            {
                enemyArr[i] = (Enemy){ 0 };
                enemyArrIndex--;
            }
        }
    }

    // Projectiles
    for (int i = 0; i < prjArrIndex; i++)
    {
        updateProjectile(&prjArr[i], delta);

        // If projectile out of window, DELETE IT
        if (prjArr[i].rec.x >= screenWidth || prjArr[i].rec.x + prjArr[i].rec.width <= 0)
        {
            prjArrDel(prjArr, i, &prjArrIndex);
        }

        // Projectile collision check
        if (projectileCollided(prjArr[i], player.rec) && prjArr[i].id == 2)
        {
            prjArrDel(prjArr, i, &prjArrIndex);
            player.healthBar.healthNum--;
        }

        for (int j = 0; j < enemyArrSize; j++)
        {
            if (projectileCollided(prjArr[i], enemyArr[j].rec) && prjArr[i].id == 1)
            {
                prjArrDel(prjArr, i, &prjArrIndex);
                enemyArr[j].healthBar.healthNum--;
                if (enemyArr[j].healthBar.healthNum <= 0)
                {
                    enemyArr[j] = (Enemy){ 0 };
                    enemyArrIndex--;
                }
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
    DrawTextEx(font, TextFormat("projectiles: %d", prjArrIndex), (Vector2){10, 200}, fontSize, 4, MAROON);
    // Draw projectile(s)
    for (int i = 0; i < prjArrIndex; i++)
    {
        DrawRectangleRec(prjArr[i].rec, MAROON);
    }

    // Draw player
    drawPlayer(player);

    // Draw enemy(s)
    for (int i = 0; i < enemyArrSize; i++)
    {
        if (enemyArr[i].maxSpeed != 0) drawEnemy(enemyArr[i]);
    }

    if (onMobileIpad)
    {
        Vector2 pos = {10, 50};
        DrawTextEx(font, "ON MOBILE/IPAD", pos, fontSize, 4, DARKGREEN);

        drawJoyStick(joyStick);

        DrawTextEx(font, TextFormat("%d", GetTouchPointCount()), (Vector2){10, 400}, fontSize, 4, MAROON);
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

    if (onMobileIpad) unloadJoyStick(&joyStick);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}