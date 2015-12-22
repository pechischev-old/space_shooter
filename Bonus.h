#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib>

#include "Config.h"
#include "Entity.h"

using namespace sf;

struct Bonus {
	std::list<Entity> bonuses;
	enum TypeBonuses {
		REPAIR = 1,
		DECREASE,
		INCREASE_DAMAGE,
		INVULNERABILITY,
		BOMB,
		sizeTypeBonuses = 5
	};
	TypeBonuses typeBonus;
	Clock clock;
	Time timeCreateBonus = Time::Zero;
	int probabilityOccurrence;
	void AddBonus(Vector2f getPosition, TextureGame & textureGame, SSound & sSound);
	void GetMoveEveryBonus(const Time & deltaTime, RenderWindow & window);
};

bool CheckProbably();  