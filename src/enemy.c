#include "enemy.h"
#include "raymath.h"

static float screenWidth = 0;
static float screenHeight = 0;

static float lerpValue = 0;

static int shootCooldown = 0;

static Color defaultColor = { 0 };

Enemy initEnemy(Rectangle rec, Vector2 v, float maxSpeed, int healthNum)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	lerpValue = 5;

	shootCooldown = 200;

	defaultColor = MAROON;

	return (Enemy){.rec = rec, .velocity = v, .maxSpeed = maxSpeed, .healthBar = initHealthBar(healthNum, DARKGREEN), .color = defaultColor};
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

	// Is shot animation
	enemy->color.r = (int)Lerp(enemy->color.r, defaultColor.r, lerpValue * delta);
	enemy->color.g = (int)Lerp(enemy->color.g, defaultColor.g, lerpValue * delta);
	enemy->color.b = (int)Lerp(enemy->color.b, defaultColor.b, lerpValue * delta);

	if (enemy->isHit)
	{
		enemy->color = WHITE;
		enemy->isHit = false;
	}

	// HealthBar
	updateHealthBar(&enemy->healthBar, delta);

	enemy->healthBar.recLines.x = enemy->rec.x - (enemy->healthBar.recLines.width - enemy->rec.width) / 2;
	enemy->healthBar.recLines.y = enemy->rec.y - enemy->healthBar.recLines.height - 20;

	enemy->healthBar.recBar.x = enemy->healthBar.recLines.x;
	enemy->healthBar.recBar.y = enemy->healthBar.recLines.y;
}

void drawEnemy(Enemy enemy, Texture2D sprite, int scale)
{
	// Draw healthbar
	drawHealthBar(enemy.healthBar);

	// Draw enemy sprite
	Rectangle source = {0, 0, sprite.width, sprite.height};
	Rectangle dest = {0, 0, sprite.width * scale, sprite.height * scale};
	dest.x = enemy.rec.x + (enemy.rec.width - dest.width) / 2;
	dest.y = enemy.rec.y + (enemy.rec.height - dest.height) / 2;
	DrawTexturePro(sprite, source, dest, (Vector2){dest.width, dest.height}, 180, enemy.color);

	// Draw enemy rec
	if (enemy.drawRec) DrawRectangleLinesEx(enemy.rec, 5, GREEN);
}

void unloadEnemy(Enemy *enemy)
{
	// Unload stuff
}