#include "projectile.h"

Projectile initProjectile(Rectangle rec, float speed, int id)
{
	return (Projectile){rec, (Vector2){0, 0}, speed, id};
}

void updateProjectile(Projectile *prj, float delta)
{
	prj->rec.x += prj->velocity.x * delta;
	prj->rec.y += prj->velocity.y * delta;

	prj->velocity.x = prj->maxSpeed;
}

void drawProjectile(Projectile prj)
{
	DrawRectangleRec(prj.rec, MAROON);
}

bool projectileCollided(Projectile prj, Rectangle rec)
{
	return CheckCollisionRecs(prj.rec, rec);
}

void unloadProjectile(Projectile *prj)
{
	// Unload projectile data
}