#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "raylib.h"

typedef struct
{
	Rectangle recBar;
	Rectangle recLines;
	int healthNum;
	Color color;
	float oneChunk;
} HealthBar;

HealthBar initHealthBar(int healthNum, Color color);
void updateHealthBar(HealthBar *healthBar, float delta);
void drawHealthBar(HealthBar healthBar);
void unloadHealthBar(HealthBar *healthBar);

#endif // HEALTH_BAR_H