#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()

#include "Config.h"
#include "Entity.h"

using namespace sf;

struct Bonus {
	std::list<Entity> bonuses;
	Clock clock;
	Time timeCreateBonus = Time::Zero;
	int probabilityOccurrence;
	void AddBonus(Vector2f getPosition, TextureGame & textureGame);
	void GetMoveEveryBonus(const Time & deltaTime, RenderWindow & window);
};

void InitializeBonus(Bonus & bonus);
int IssuanceProbability();
int SpecifySizeBonus();
bool CheckProbably();