#include "player.h"

float screenWidth = 0;
float screenHeight = 0;

Player initPlayer(Rectangle rec, Vector2 pos, float maxSpeed)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	return (Player){rec, pos, maxSpeed};
}

void updatePlayer(Player *player, float delta)
{
	// Update player
	player->rec.x += player->velocity.x * delta;
	player->rec.y += player->velocity.y * delta;

	if (IsKeyDown(KEY_D))
		player->velocity.x = (!(IsKeyDown(KEY_S) || IsKeyDown(KEY_W))) ? player->maxSpeed : player->maxSpeed / 1.4f;
	else if (IsKeyDown(KEY_A))
		player->velocity.x = (!(IsKeyDown(KEY_S) || IsKeyDown(KEY_W))) ? -player->maxSpeed : -player->maxSpeed / 1.4f;
	else player->velocity.x = 0;

	if (IsKeyDown(KEY_S))
		player->velocity.y = (!(IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) ? player->maxSpeed : player->maxSpeed / 1.4f;
	else if (IsKeyDown(KEY_W))
		player->velocity.y = (!(IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) ? -player->maxSpeed : -player->maxSpeed / 1.4f;
	else player->velocity.y = 0;

	// Window border limit
	if (player->rec.x < 0) player->rec.x = 0;
    else if (player->rec.x + player->rec.width > screenWidth) player->rec.x = screenWidth - player->rec.width;

    if (player->rec.y < 0) player->rec.y = 0;
    else if (player->rec.y + player->rec.height > screenHeight) player->rec.y = screenHeight - player->rec.height;
}

void drawPlayer(Player player)
{
	// Draw player
	DrawRectangleRec(player.rec, DARKBLUE);
}

void unloadPlayer(Player *player)
{
	// Unload player data
}