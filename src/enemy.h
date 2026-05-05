#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "health_bar.h"

typedef struct
{
	Rectangle rec;
	Vector2 velocity;
	float maxSpeed;
	bool shoot;
	bool isHit;
	bool isDestroyed;
	int shootCounter;
	HealthBar healthBar;
	bool drawRec;
	Color color;
} Enemy;

Enemy initEnemy(Rectangle rec, Vector2 v, float speed, int healthNum);
void updateEnemy(Enemy *enemy, float delta);
void drawEnemy(Enemy enemy, Texture2D sprite, int scale);
void unloadEnemy(Enemy *enemy);

#endif // ENEMY_H