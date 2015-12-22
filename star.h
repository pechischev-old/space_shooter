#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib>

#include "Entity.h"
#include "Config.h"
#include "Enemy.h"

using namespace sf;

struct Star {
	std::list<Entity> stars;
	float speed;
	Clock clock;
	Time timeCreateStar = Time::Zero;
	Vector2u sizeStar;
	void UpdateStateStar(const Time & deltaTime, RenderWindow & window);
	void AddStar(TextureGame & textureGame, RenderWindow & window, SSound & sSound);
};

void LoadStarInList(Star & star, const Time & deltaTime, RenderWindow & window, TextureGame & textureGame);