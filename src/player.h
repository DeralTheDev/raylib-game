#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct
{
	Rectangle rec;
	Vector2 velocity;
	float maxSpeed;
} Player;

Player initPlayer(Rectangle rec, Vector2 pos, float maxSpeed);
void updatePlayer(Player *player, float delta);
void drawPlayer(Player player);
void unloadPlayer(Player *player);

#endif // PLAYER_H