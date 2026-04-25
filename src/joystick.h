#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "raylib.h"

typedef struct
{
	Vector2 basePos;
	float baseRadius;
	Vector2 cPos;
	float cRadius;
	Vector2 cDir;
	bool drag;
	int touchId;
} JoyStick;

JoyStick initJoyStick(Vector2 baseV, float radius);
void updateJoyStick(JoyStick *joyStick, float delta);
void drawJoyStick(JoyStick joyStick);
void unloadJoyStick(JoyStick *joyStick);

Vector2 getJoyStickPos(JoyStick joyStick);

#endif // JOYSTICK_H