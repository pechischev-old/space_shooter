#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
//#include "View.h"
#include "Player.h"
#include "Enemy.h"
#include "Font.h"
#include "asteroids.h"
#include "Bonus.h"

using namespace sf;

struct Game
{
	RenderWindow *window;
	Player *player;
	Enemy *enemy;
	Asteroid *asteroid;
	Bonus *bonus;
	TextWithInfo *textInfo;
	Clock clock;
	//Time timeGame = Time::Zero;
	float timeGame = 0;
	int oldOrder = 0; // старший порядок числа (для усложнения игры)
	void CheckForCollision(); // отвечает за проверку на столкновения
	void DrawObjects();
	void IncreaseCharacteristicsObjects();
	void UseBonus(const Time & deltaTime);
};

void InitializeGame(Game & game);
void Delete(Game & game);