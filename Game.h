#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
//#include "View.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;

struct Game
{
	RenderWindow* window;
	Player *player;
	Enemy *enemy;
	//View *view;
	void CheckForCollision(); // отвечает за проверку на столкновения
};

void InitializeGame(Game & game);
void DestroyGame(Game & game);
