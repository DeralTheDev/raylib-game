#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "health_bar.h"

typedef struct
{
	Rectangle rec;
	Vector2 velocity;
	float maxSpeed;
	Vector2 cVelocity;
	bool shoot;
	int shootCounter;
	HealthBar healthBar;
} Player;

Player initPlayer(Rectangle rec, Vector2 pos, float maxSpeed, int healthNum);
void updatePlayer(Player *player, float delta);
void drawPlayer(Player player);
void unloadPlayer(Player *player);

#endif // PLAYER_H