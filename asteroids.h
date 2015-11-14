#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()


#include "Entity.h"
#include "Enemy.h"
#include "Config.h"

using namespace sf;

struct Asteroid {
	std::list<Entity> *asteroids;
	Vector2f movement = { 0.f, 0.f };
	Clock clock;
	Time timeCreateAsteroid = Time::Zero;
	float CurrentFrame = 0;
	void AddAsteroid();
	void GetMoveEveryAsteroid(const Time & deltaTime);
	void MoveAsteroid(const Time & deltaTime, Entity & asteroid);
};

void InitializeAsteroid(Asteroid & asteroid);
int SpecifySize();