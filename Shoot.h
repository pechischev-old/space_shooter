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
	Shoot(Vector2f position, Direction dir, Texture & texture, String Name);
	Vector2f position;
	Vector2f oldPosition;
	Direction dir;
	Sprite *sprite;
	String name;
	float rotation = 0;
	int damage;
	Vector2f movement = { 0.f, 0.f };
	Vector2f rememPos;
	float currentFrame = 0; // нужно для анимации
	float health;
	bool isExplosion = false;
	bool isOtherBullet = false;
	bool isRocket = false;
	bool life = true; //флаг жизни
	void Explosion(const Time & deltaTime, Texture & texture);
	void CheckForCollisions(RenderWindow & window);
	void MoveBulletHardEnemy(const Time & deltaTime, Vector2f posObject, int speed);
};

void UpdateStateBullet(const Time & deltaTime, RenderWindow & window, list<Shoot> & bullets, TextureGame & textureGame, Vector2f posPlayer);
void ClearList(list<Shoot> & bullets);