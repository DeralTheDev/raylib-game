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
#include "player.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static float screenWidth = 0.0f;
static float screenHeight = 0.0f;
static float delta = 0.0f;

static int framesCounter = 0;
static int finishScreen = 0;

static Player player = { 0 };

bool onMobileOrIpad = false;

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

    player = initPlayer((Rectangle){100, 0, 75, 50}, (Vector2){0, 0}, 300);
    player.rec.y = (screenHeight - player.rec.height) / 2;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    delta = GetFrameTime();

    updatePlayer(&player, delta);

    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        // finishScreen = 2 // Back to TITLE
        finishScreen = 1;
        PlaySound(fxCoin);
    }

    if (GetTouchPointCount() > 0 && !onMobileOrIpad) onMobileOrIpad = true;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    // Draw Player
    drawPlayer(player);

    if (onMobileOrIpad) DrawText("On Mobile/Ipad", 10, 50, 20, DARKGREEN);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    unloadPlayer(&player);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}