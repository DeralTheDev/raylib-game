#include "enemy.h"
#include "raymath.h"

static float screenWidth = 0;
static float screenHeight = 0;

static float lerpValue = 0;
static float minSpeed = 30;

static int shootCooldown = 0;

Enemy initEnemy(Rectangle rec, Vector2 v, float speed, int healthNum)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	lerpValue = 0.025f;

	shootCooldown = 100;

	return (Enemy){rec, v, speed, false, false, false, (Vector2){0, 0}, 0, initHealthBar(healthNum, DARKGREEN)};
}

void updateEnemy(Enemy *enemy, Rectangle targetRec, float delta)
{
	enemy->velocity.x = Lerp(enemy->velocity.x, enemy->cVelocity.x, lerpValue);
	enemy->velocity.y = Lerp(enemy->velocity.y, enemy->cVelocity.y, lerpValue);

	enemy->rec.x += enemy->velocity.x * delta;
	enemy->rec.y += enemy->velocity.y * delta;

	enemy->cVelocity.x = (fabs(enemy->rec.x - targetRec.x + targetRec.width) > 100.0f) ? -enemy->maxSpeed : -minSpeed;

	// Track the target, if successfull then shoot
	if (fabs(enemy->rec.y - targetRec.y) <= 3.0f)
	{
		enemy->shoot = (enemy->shootCounter == 0) ? true : false;
		if (enemy->shoot) enemy->shootCounter = 1;
	}
	else
	{
		enemy->cVelocity.y = (enemy->rec.y - targetRec.y < 0) ? enemy->maxSpeed : -enemy->maxSpeed;
	}

	// Shoot cooldown
	if (enemy->shootCounter > 0)
	{
		enemy->shootCounter++;
		if (enemy->shootCounter >= shootCooldown) enemy->shootCounter = 0;
	}

	// HealthBar
	updateHealthBar(&enemy->healthBar, delta);

	enemy->healthBar.recLines.x = enemy->rec.x - (enemy->healthBar.recLines.width - enemy->rec.width) / 2;
	enemy->healthBar.recLines.y = enemy->rec.y - enemy->healthBar.recLines.height - 10;

	enemy->healthBar.recBar.x = enemy->healthBar.recLines.x;
	enemy->healthBar.recBar.y = enemy->healthBar.recLines.y;
}

void drawEnemy(Enemy enemy)
{
	DrawRectangleRec(enemy.rec, PURPLE);
	// Draw healthbar
	drawHealthBar(enemy.healthBar);
}

void unloadEnemy(Enemy *enemy)
{
	// Unload enemy data
}