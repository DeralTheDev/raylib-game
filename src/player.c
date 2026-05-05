#include "player.h"
#include "raymath.h"

static float screenWidth = 0;
static float screenHeight = 0;

static int lerpValue = 0;
static int lerpValueC = 0;

static float shootCooldown = 0;

static Color defaultColor = { 0 };

Player initPlayer(Rectangle rec, float maxSpeed, int healthNum)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	lerpValue = 2;
	lerpValueC = 5;

	shootCooldown = 10;

	defaultColor = BEIGE;

	return (Player){
		.rec = rec, .maxSpeed = maxSpeed, .healthBar = initHealthBar(healthNum, DARKGREEN), .color = defaultColor
	};
}

void updatePlayer(Player *player, JoyStick joyStick, float delta)
{
	// Update player
	player->velocity.x = Lerp(player->velocity.x, player->cVelocity.x, lerpValue * delta);
	player->velocity.y = Lerp(player->velocity.y, player->cVelocity.y, lerpValue * delta);

	player->rec.x += player->velocity.x * delta;
	player->rec.y += player->velocity.y * delta;

	// Mobile/Ipad control
	if (joyStick.baseRadius != 0)
	{
		Vector2 joyStickPos = getJoyStickPos(joyStick);

        player->cVelocity.x = player->maxSpeed / joyStick.baseRadius * joyStickPos.x;
        player->cVelocity.y = player->maxSpeed / joyStick.baseRadius * joyStickPos.y;
	}
	// Desktop control
	else
	{
		if (IsKeyDown(KEY_D)) player->cVelocity.x = player->maxSpeed;
		else if (IsKeyDown(KEY_A)) player->cVelocity.x = -player->maxSpeed;
		else player->cVelocity.x = 0;

		if (IsKeyDown(KEY_S)) player->cVelocity.y = player->maxSpeed;
		else if (IsKeyDown(KEY_W)) player->cVelocity.y = -player->maxSpeed;
		else player->cVelocity.y = 0;

		if (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			player->shoot = (player->shootCounter == 0) ? true : false;
			player->shootCounter = (player->shoot) ? 1 : player->shootCounter;
		}
	}

	if (player->shootCounter > 0)
	{
		player->shootCounter++;
		player->shootCounter = (player->shootCounter >= shootCooldown) ? 0 : player->shootCounter;
	}

	// Is shot animation
	if (player->color.r != defaultColor.r || player->color.g != defaultColor.g || player->color.b != defaultColor.b)
	{
		player->color.r = Lerp(player->color.r, defaultColor.r, lerpValueC * delta);
		player->color.g = Lerp(player->color.g, defaultColor.g, lerpValueC * delta);
		player->color.b = Lerp(player->color.b, defaultColor.b, lerpValueC * delta);
	}

	if (player->isHit)
	{
		player->color = WHITE;
		player->isHit = false;
	}

	// Window border limit
	player->rec.x = Clamp(player->rec.x, 0, screenWidth - player->rec.width);
	player->rec.y = Clamp(player->rec.y, 0, screenHeight - player->rec.height);

	// HealthBar
	updateHealthBar(&player->healthBar, delta);

	player->healthBar.recLines.x = player->rec.x - (player->healthBar.recLines.width - player->rec.width) / 2;
	player->healthBar.recLines.y = player->rec.y - player->healthBar.recLines.height - 20;
	
	player->healthBar.recBar.x = player->healthBar.recLines.x;
	player->healthBar.recBar.y = player->healthBar.recLines.y;
}

void drawPlayer(Player player, Texture2D sprite, int scale)
{
	// Draw healthBar
	drawHealthBar(player.healthBar);

	// Draw player sprite
	Rectangle source = {0, 0, sprite.width, sprite.height};
	Rectangle dest = {0, 0, source.width * scale, source.height * scale};
	dest.x = player.rec.x + (player.rec.width - dest.width) / 2;
	dest.y = player.rec.y + (player.rec.height - dest.height) / 2;
	DrawTexturePro(sprite, source, dest, (Vector2){0, 0}, 0, player.color);

	// Draw player rec
	if (player.drawRec) DrawRectangleLinesEx(player.rec, 5, GREEN);
}

void unloadPlayer(Player *player)
{
	// Unload stuff
}