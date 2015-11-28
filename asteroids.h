#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()


#include "Entity.h"
#include "Enemy.h"
#include "Config.h"
#include "Bonus.h"

using namespace sf;

struct Asteroid {
	std::list<Entity> asteroids;
	Clock clock;
	Time timeCreateAsteroid = Time::Zero;
	float CurrentFrame = 0;
	void AddAsteroid(TextureGame & textureGame);
	void GetMoveEveryAsteroid(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame);
	void SetRotateAsteroid(Entity & asteroid);
};

void InitializeAsteroid(Asteroid & asteroid);
int SpecifySize();