#pragma once
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <list>

#include "Config.h"
#include "Entity.h"

using namespace sf; 
using namespace std;

struct Shoot {
	Shoot(float X, float Y, float WIDTH, float  HEIGTH, Direction dir, Texture & texture, String Name);
	float x, y, dx, dy;
	Direction dir;
	Sprite *sprite;
	String name;
	float rotation = 0;
	int damage;
	Vector2f movement = { 0.f, 0.f };
	Vector2f rememPos;
	float currentFrame = 0;
	bool isExplosion = false;
	bool isOtherBullet = false;
	bool isRocket = false;
	bool life = true; //флаг жизни
	void Explosion(const Time & deltaTime, Texture & texture);
	void MoveBullet(const Time & deltaTime);
	void CheckForCollisions(RenderWindow & window);
	void MoveBulletHardEnemy(const Time & deltaTime);
	void MoveRocket(const Time & deltaTime, Vector2f posPlayer);
};

void UpdateStateBullet(const Time & deltaTime, RenderWindow & window, list<Shoot> & bullets, TextureGame & textureGame, Vector2f posPlayer);
void ClearList(list<Shoot> & bullets);