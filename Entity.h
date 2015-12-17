#pragma once
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <list>

#include "Config.h"
#include "LoadTexture.h"

using namespace sf;
using namespace std;

struct Entity {
	Entity(Vector2f position, String Name, Texture & texture);
	Vector2f position;
	Vector2f sizeObject;
	float health; // здоровье сущности
	float damage; // урон который наносит сущность
	float speed; // скорость сущности
	Direction direction;
	String name;
	Sprite *sprite;
	bool isLife;
	bool isKilled;
	float CurrentFrame = 0;
	void Explosion(const Time & deltaTime, Texture & texture);
	void CheckForCollisions(RenderWindow & window);
	void MoveObject(const Time & deltaTime);

	void SetRotationObject(Vector2f posPoint);
	Time timeChangeDirection = Time::Zero; // для врагов
	Time timeCreateBullet = Time::Zero; // для врагов
};


Vector2f Border(Entity & object, RenderWindow & window);
void ClearListObject(list<Entity> & objects);