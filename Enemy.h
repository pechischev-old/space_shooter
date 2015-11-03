#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()

#include "Config.h"

using namespace sf;

struct Enemy {
	Enemy(float X, float Y, float width, float heigth, String Name, Direction direction);
	Texture *texture;
	Sprite *sprite;
	Direction dirEnemy;
	String name;
	float x, y;
	float life = 100;
	bool isLife;
	Vector2f movement = { 0.f, 0.f };
	float CurrentFrame = 0;
	void MoveEnemy(const Time & deltaTime);
	void GetExplosion(const Time & deltaTime); // Анимация взрыва
};

Direction GetDirection();
Vector2f GetRandomPosition(Direction & selectHand);