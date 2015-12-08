#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Font.h"
#include "asteroids.h"
#include "Bonus.h"
#include "star.h"

using namespace sf;

struct Game
{
	TextureGame textureGame;
	Player *player;
	Enemy *enemy;
	Asteroid *asteroid;
	Bonus *bonus;
	TextWithInfo *textInfo;
	Star *star;
	Clock clock;
	float timeGame = 0;
	int oldOrder = 0; // старший порядок числа (для усложнения игры)
	void CheckForCollision(RenderWindow & window, const Time & deltaTime, TextureGame & textureGame); // отвечает за проверку на столкновения
	void DrawObjects(RenderWindow & window);
	void IncreaseCharacteristicsObjects();
	void UseBonus(const Time & deltaTime);
};

void InitializeGame(Game & game);
void ResetGame(Game & game);
void processEventsGame(Game & game, GlobalBool & globalBool, Event & event);
void updateGame(Game & game, const Time & deltaTime, RenderWindow & window, GlobalBool & globalBool);
void renderGame(RenderWindow & window, Game & game);
void Delete(Game & game);