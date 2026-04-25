#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"

typedef struct
{
	Rectangle rec;
	Vector2 velocity;
	float maxSpeed;
	int id; // 0 = unknown; 1 = player; 2 = enemy;
} Projectile;

Projectile initProjectile(Rectangle rec, float speed, int id);
void updateProjectile(Projectile *prj, float delta);
void drawProjectile(Projectile prj);
bool projectileCollided(Projectile prj, Rectangle rec);
void unloadProjectile(Projectile *prj);

#endif // PROJECTILE_H