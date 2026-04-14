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
#include <stdbool.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static float screenWidth = GetScreenWidth();
static float screenHeight = GetScreenHeight();
static float delta = 0.0f;

static int framesCounter = 0;
static int finishScreen = 0;

// Player
typedef struct
{
    Rectangle rec;
    Vector2 velocity;
    float maxSpeed;
    bool normalized;
} Player;

static Player player = { 0 };

void normalizeVector2(Vector2 *v)
{
    v->x /= 3.14; v->y /= 3.14;
}

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    delta = 0.0f;

    framesCounter = 0;
    finishScreen = 0;

    player = (Player){
        (Rectangle){screenWidth/2+25, screenHeight/2+25, 50, 50},
        (Vector2){0, 0}, 500, false
    };
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    delta = GetFrameTime();

    // Player Update
    player.rec.x += player.velocity * delta;
    player.rec.y += player.velocity * delta;

    if (IsKeyDown(KEY_D)) player.velocity.x = player.maxSpeed;
    else if (IsKeyDown(KEY_A)) player.velocity.x = -player.maxSpeed;
    else player.velocity.x = 0; player.normalized = false;

    if (IsKeyDown(KEY_W)) player.velocity.y = -player.maxSpeed;
    else if (IsKeyDown(KEY_S)) player.velocity.y = player.maxSpeed;
    else player.velocity.y = 0; player.normalized = false;

    // Normalize Player velocity
    if (!player.normalized && (player.velocity.x && player.velocity.y))
    {
        normalizeVector2(&player.velocity);
        player.normalized = true;
    }

    if (player.rec.x <= 0) player.rec.x = 0;
    else if (player.rec.x + player.rec.width >= GetScreenWidth()) player.x = GetScreenWidth() - player.width;

    if (player.rec.y <= 0) player.rec.y = 0;
    else if (player.recy)

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
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

    DrawRectangleRec(player, BLUE);
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