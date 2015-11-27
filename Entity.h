#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Config.h"
#include "LoadTexture.h"

using namespace sf;
using namespace std;

struct Entity {
	Entity(float x, float y, String Name, Texture texture1);
	float x;
	float y;
	float width;
	float height;
	float health; // здоровье сущности
	float damage; // урон который наносит сущность
	float speed; // скорость сущности
	Direction direction, rememberDir;
	String name;
	Texture texture;
	Sprite *sprite;
	bool isLife;
	bool isKilled = false;
	float CurrentFrame = 0;
	void Explosion(const Time & deltaTime);
	void CheckForCollisions(RenderWindow & window);
	void MoveObject(const Time & deltaTime);
};

Vector2f Border(Entity & object, RenderWindow & window);