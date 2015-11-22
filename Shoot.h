#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Config.h"

using namespace sf; 

struct Shoot {
	Shoot(float X, float Y, float WIDTH, float  HEIGTH, Direction dir, String path);
	float x, y, dx, dy;
	Direction dir, rememberDir;
	Texture *texture;
	Sprite *sprite;
	float rotation = 0;
	int damage;
	Vector2f movement = { 0.f, 0.f };
	Vector2f rememPos = { -1.f, -1.f };
	bool isOtherBullet = false;
	float distance;
	bool life = true; //флаг жизни
	void MoveBullet(const Time & deltaTime);
	void CheckForCollisions(RenderWindow & window);
	void MoveBulletHardEnemy(const Time & deltaTime);
};