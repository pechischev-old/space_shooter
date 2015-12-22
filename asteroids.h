#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Entity.h"
#include "Enemy.h"
#include "Config.h"
#include "Bonus.h"

using namespace sf;

struct Asteroid {
	std::list<Entity> asteroids;
	Clock clock;
	Time timeCreateAsteroid = Time::Zero;
	enum TypeAsteroid {
		SMALL = 1,
		MIDDLE,
		BIG,
		sizeTypeAsteroid = 3
	};
	TypeAsteroid typeAsteroid;
	float timeToCreateAsteroid = float(TIME_CREATE_ASTEROID);
	void AddAsteroid(TextureGame & textureGame, RenderWindow & window, SSound & sSound);
	void GetMoveEveryAsteroid(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame, SSound & sSound);
	void InitRotateAsteroid(Entity & asteroid);
};