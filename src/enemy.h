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
	bool isShot;
	bool isDestroyed;
	Vector2 cVelocity;
	int shootCounter;
	HealthBar healthBar;
} Enemy;

Enemy initEnemy(Rectangle rec, Vector2 v, float speed, int healthNum);
void updateEnemy(Enemy *enemy, Rectangle targetRec, float delta);
void drawEnemy(Enemy enemy);
void unloadEnemy(Enemy *enemy);

#endif // ENEMY_H