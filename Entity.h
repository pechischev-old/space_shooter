#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


#include "Config.h"

using namespace sf;

struct Entity {
	Entity(float X, float Y, float Width, float Height, String Name);
	float x;
	float y;
	float width;
	float height;
	float health; // здоровье сущности
	float damage; // урон который наносит сущность
	float speed; // скорость сущности
	Direction direction;
	String name;
	Texture *texture;
	Sprite *sprite;
	bool isLife;
	float CurrentFrame = 0;
	void GetExplosion(const Time & deltaTime);
};
