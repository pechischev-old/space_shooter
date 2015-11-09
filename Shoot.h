#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Config.h"

using namespace sf; 

struct Shoot {
	Shoot(float X, float Y, float WIDTH, float  HEIGTH, Direction dir, String path);
	float x, y;
	Direction dir, rememberDir;
	Texture *texture;
	Sprite *sprite;
	float rotation = 0;
	Vector2f movement = { 0.f, 0.f };
	Vector2i pos_mouse;
	bool life = true; //флаг жизни
	void MoveBullet(const Time & deltaTime);
};