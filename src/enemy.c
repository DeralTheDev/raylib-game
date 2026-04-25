#include "enemy.h"

static float screenWidth = 0;
static float screenHeight = 0;

static float lerpValue = 0;
static float minSpeed = 10;

static int shootCooldown = 0;

Enemy initEnemy(Rectangle rec, Vector2 v, float speed, int healthNum)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	shootCooldown = 100;

	return (Enemy){rec, v, speed, false, false, false, 0, initHealthBar(healthNum, DARKGREEN)};
}

void updateEnemy(Enemy *enemy, float delta)
{
	enemy->rec.x += enemy->velocity.x * delta;
	enemy->rec.y += enemy->velocity.y * delta;

	// Shoot cooldown
	if (!enemy->shoot)
	{
		enemy->shootCounter++;
		if (enemy->shootCounter >= shootCooldown)
		{
			enemy->shoot = true;
			enemy->shootCounter = 0;
		}
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