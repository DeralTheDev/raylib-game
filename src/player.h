#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "health_bar.h"
#include "joystick.h"

typedef struct
{
	Rectangle rec;
	Vector2 velocity;
	float maxSpeed;
	Vector2 cVelocity;
	bool shoot;
	int shootCounter;
	bool isHit;
	HealthBar healthBar;
	bool drawRec;
	Color color;
} Player;

Player initPlayer(Rectangle rec, float maxSpeed, int healthNum);
void updatePlayer(Player *player, JoyStick joyStick, float delta);
void drawPlayer(Player player, Texture2D sprite, int scale);
void unloadPlayer(Player *player);

#endif // PLAYER_H