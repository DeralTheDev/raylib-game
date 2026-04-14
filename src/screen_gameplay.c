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

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static float screenWidth = 0.0f;
static float screenHeight = 0.0f;
static float delta = 0.0f;

static int framesCounter = 0;
static int finishScreen = 0;

// Player
typedef struct
{
    Rectangle rec;
    Vector2 velocity;
    float maxSpeed;
} Player;

static Player player = { 0 };

static void normalizeVector2(Vector2 *v, float speed)
{
    v->x = (v->x > 0) ? speed / 1.4142f : -speed / 1.4142f;
    v->y = (v->y > 0) ? speed / 1.4142f : -speed / 1.4142f;
}

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    delta = 0.0f;

    framesCounter = 0;
    finishScreen = 0;

    player = (Player){
        (Rectangle){screenWidth/2+25, screenHeight/2+25, 50, 50},
        (Vector2){0, 0}, 300
    };
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    delta = GetFrameTime();

    // Player Update
    player.rec.x += player.velocity.x * delta;
    player.rec.y += player.velocity.y * delta;

    if (IsKeyDown(KEY_D)) player.velocity.x = player.maxSpeed;
    else if (IsKeyDown(KEY_A)) player.velocity.x = -player.maxSpeed;
    else player.velocity.x = 0;
        
    if (IsKeyDown(KEY_W)) player.velocity.y = -player.maxSpeed;
    else if (IsKeyDown(KEY_S)) player.velocity.y = player.maxSpeed;
    else player.velocity.y = 0;

    // Normalize Player velocity
    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) && (IsKeyDown(KEY_S) || IsKeyDown(KEY_W)))
    {
        normalizeVector2(&player.velocity, player.maxSpeed);
    }

    // Screen border limit
    if (player.rec.x <= 0) player.rec.x = 0;
    else if (player.rec.x + player.rec.width >= screenWidth)
        player.rec.x = screenWidth - player.rec.width;

    if (player.rec.y <= 0) player.rec.y = 0;
    else if (player.rec.y + player.rec.height >= screenHeight)
        player.rec.y = screenHeight - player.rec.height;

    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        // finishScreen = 2 // Back to TITLE
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    // Draw Player
    DrawRectangleRec(player.rec, BLUE);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}