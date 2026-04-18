#include "joystick.h"

JoyStick initJoyStick(Vector2 baseV, float radius)
{
	return (JoyStick){baseV, radius, baseV, radius - radius * 0.5f, (Vector2){0, 0}};
}

void updateJoyStick(JoyStick *joyStick, float delta)
{
	int gesture = GetGestureDetected();
	Vector2 getTouchPos = GetTouchPosition(0);

	if (gesture == GESTURE_DRAG)
	{
		joyStick->cPos = getTouchPos;
	}
	else
	{
		joyStick->cPos = joyStick->basePos;
	}
}

void drawJoyStick(JoyStick joyStick)
{
	DrawCircleLinesV(joyStick.basePos, joyStick.baseRadius, DARKGRAY);
	DrawCircleV(joyStick.cPos, joyStick.cRadius, DARKGRAY);
}

void unloadJoyStick(JoyStick *joyStick)
{
	// Unload joyStick data
}