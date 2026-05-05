/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
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
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // TODO: Update ENDING screen variables here!

    framesCounter++;

    if (framesCounter >= 50)
    {
        if (GetKeyPressed() != KEY_NULL || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) finishScreen = 2;
        if (framesCounter >= 100) framesCounter = 0;
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    // TODO: Draw ENDING screen here!
    const char *str = "Game Over...";
    Vector2 pos = {
        (GetScreenWidth() - MeasureTextEx(font, str, fontSize, dSpacing).x) / 2,
        (GetScreenHeight() - MeasureTextEx(font, str, fontSize, dSpacing).y) / 2
    };
    DrawTextEx(font, str, pos, fontSize, dSpacing, RAYWHITE);

    if (framesCounter >= 50)
    {
        const char *str1 = "Press anything to restart.";
        Vector2 pos1 = {
            (GetScreenWidth() - MeasureTextEx(font, str1, (int)(fontSize * 0.75f), dSpacing).x) / 2,
            (int)(pos.y * 1.2f) + MeasureTextEx(font, str1, (int)(fontSize * 0.75f), dSpacing).y
        };
        DrawTextEx(font, str1, pos1, (int)(fontSize * 0.75f), dSpacing, RAYWHITE);
    }
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}