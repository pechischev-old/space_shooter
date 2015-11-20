#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
//#include "View.h"
#include "Player.h"
#include "Enemy.h"
#include "Font.h"
#include "asteroids.h"
#include "Bonus.h"
#include "star.h"

using namespace sf;

struct GameState {
	bool isNewGame;
	bool isContinue;
	bool isLoading;
	bool isExit;
	bool isMenu;

};

struct Game
{
	RenderWindow *window;
	Player *player;
	Enemy *enemy;
	Asteroid *asteroid;
	Bonus *bonus;
	TextWithInfo *textInfo;
	GameState gameState;
	Star *star;
	Clock clock;
	float timeGame = 0;
	int oldOrder = 0; // старший порядок числа (для усложнения игры)
	void CheckForCollision(); // отвечает за проверку на столкновения
	void DrawObjects();
	void IncreaseCharacteristicsObjects();
	void UseBonus(const Time & deltaTime);
};

void InitializeGame(Game & game);
void Delete(Game & game);