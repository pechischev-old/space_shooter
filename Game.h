#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
//#include "View.h"
#include "Player.h"
#include "Enemy.h"
#include "Font.h"
#include "asteroids.h"

using namespace sf;

struct Game
{
	RenderWindow *window;
	Player *player;
	Enemy *enemy;
	Asteroid *asteroid;
	TextWithInfo *textInfo;
	//View *view;
	void CheckForCollision(); // отвечает за проверку на столкновения
	void DrawObjects();
};

void InitializeGame(Game & game);
