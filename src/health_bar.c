#include "health_bar.h"

static float defaultWidth = 0;
static float defaultHeight = 0;

HealthBar initHealthBar(int healthNum, Color color)
{
	defaultWidth = 100;
	defaultHeight = 20;

	return (HealthBar){
		(Rectangle){0, 0, defaultWidth, defaultHeight},
		(Rectangle){0, 0, defaultWidth, defaultHeight},
		healthNum, color, defaultWidth / healthNum
	};
}

void updateHealthBar(HealthBar *healthBar, float delta)
{
	healthBar->recBar.width = healthBar->oneChunk * healthBar->healthNum;
}

void drawHealthBar(HealthBar healthBar)
{
	DrawRectangleLinesEx(healthBar.recLines, 3, healthBar.color);
	DrawRectangleRec(healthBar.recBar, healthBar.color);
}

void unloadHealthBar(HealthBar *healthBar)
{
	// Unload healthBar data
}