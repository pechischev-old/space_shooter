#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	float timeUseBonus = 0;
	int countEnemy = POINT_FOR_ADVANCE;
	bool isPause = false;
	void CheckForCollision(RenderWindow & window, const Time & deltaTime, TextureGame & textureGame); // отвечает за проверку на столкновения
	void DrawObjects(RenderWindow & window);
	void IncreaseCharacteristicsObjects();
	void UseBonus(const Time & deltaTime, TextureGame & textureGame);
};

void InitializeGame(Game & game, SSound & sSound);
void ResetGame(Game & game);
bool hasIntersection(Sprite & object1, Sprite & object2);
void processEventsGame(Game & game, Event & event, RenderWindow & window);
void updateGame(Game & game, const Time & deltaTime, RenderWindow & window, GlobalBool & globalBool, SSound & sSound);
void renderGame(RenderWindow & window, Game & game);
void Delete(Game & game);