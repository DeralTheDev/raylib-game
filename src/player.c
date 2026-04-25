#include "player.h"
#include "raymath.h"

static float screenWidth = 0;
static float screenHeight = 0;

static float lerpValue = 0;

static float shootCooldown = 0;

Player initPlayer(Rectangle rec, float maxSpeed, int healthNum)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	lerpValue = 0.025f;

	shootCooldown = 10;

	return (Player){rec, (Vector2){0, 0}, maxSpeed, (Vector2){0, 0}, false, 0, initHealthBar(healthNum, DARKGREEN)};
}

void updatePlayer(Player *player, float delta)
{
	// Update player
	player->velocity.x = Lerp(player->velocity.x, player->cVelocity.x, lerpValue);
	player->velocity.y = Lerp(player->velocity.y, player->cVelocity.y, lerpValue);

	player->rec.x += player->velocity.x * delta;
	player->rec.y += player->velocity.y * delta;

	if (IsKeyDown(KEY_D)) player->cVelocity.x = player->maxSpeed;
	else if (IsKeyDown(KEY_A)) player->cVelocity.x = -player->maxSpeed;
	else player->cVelocity.x = 0;

	if (IsKeyDown(KEY_S)) player->cVelocity.y = player->maxSpeed;
	else if (IsKeyDown(KEY_W)) player->cVelocity.y = -player->maxSpeed;
	else player->cVelocity.y = 0;

	// Shoot
	if (IsKeyDown(KEY_SPACE) || IsGestureDetected(GESTURE_TAP))
	{
		player->shoot = (player->shootCounter == 0) ? true : false;
		if (player->shoot) player->shootCounter = 1;
	}

	if (player->shootCounter > 0)
	{
		player->shootCounter++;
		if (player->shootCounter >= shootCooldown) player->shootCounter = 0;
	}

	// Window border limit
	player->rec.x = Clamp(player->rec.x, 0, screenWidth - player->rec.width);
	player->rec.y = Clamp(player->rec.y, 0, screenHeight - player->rec.height);

	// HealthBar
	updateHealthBar(&player->healthBar, delta);

	player->healthBar.recLines.x = player->rec.x - (player->healthBar.recLines.width - player->rec.width) / 2;
	player->healthBar.recLines.y = player->rec.y - player->healthBar.recLines.height - 10.0f;
	
	player->healthBar.recBar.x = player->healthBar.recLines.x;
	player->healthBar.recBar.y = player->healthBar.recLines.y;
}

void drawPlayer(Player player)
{
	// Draw player
	DrawRectangleRec(player.rec, DARKBLUE);
	// Draw healthBar
	drawHealthBar(player.healthBar);

	DrawText(TextFormat("x: %d, y: %d, %d", (int)player.rec.x, (int)player.rec.y, player.shootCounter), 10, screenHeight * 0.9f, 20, DARKGREEN);
}

void unloadPlayer(Player *player)
{
	// Unload player data
}