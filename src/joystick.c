#include "joystick.h"
#include <math.h>

JoyStick initJoyStick(Vector2 baseV, float radius)
{
	return (JoyStick){baseV, radius, baseV, radius * 0.5f, (Vector2){0, 0}, false};
}

void updateJoyStick(JoyStick *joyStick, float delta)
{
	Vector2 touchPos = GetTouchPosition(GetTouchPointCount());

	if (hypot(touchPos.x - joyStick->basePos.x, touchPos.y - joyStick->basePos.y) <= joyStick->baseRadius)
	{
		if (IsGestureDetected(GESTURE_DRAG)) joyStick->drag = true;
	}
	if (!IsGestureDetected(GESTURE_DRAG)) joyStick->drag = false;

	if (joyStick->drag) joyStick->cPos = touchPos;
	else joyStick->cPos = joyStick->basePos;
	
	if (hypot(joyStick->cPos.x - joyStick->basePos.x, joyStick->cPos.y - joyStick->basePos.y) >= joyStick->baseRadius)
	{
		float ratio = joyStick->baseRadius / hypot(joyStick->cPos.x - joyStick->basePos.x, joyStick->cPos.y - joyStick->basePos.y);
		joyStick->cPos.x = joyStick->basePos.x + (joyStick->cPos.x - joyStick->basePos.x) * ratio;
		joyStick->cPos.y = joyStick->basePos.y + (joyStick->cPos.y - joyStick->basePos.y) * ratio;
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

Vector2 getJoyStickPos(JoyStick joyStick)
{
	return (Vector2){joyStick.cPos.x - joyStick.basePos.x, joyStick.cPos.y - joyStick.basePos.y};
}