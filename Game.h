#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
//#include "View.h"
#include "Player.h"

using namespace sf;

struct Game
{
	RenderWindow* window;
	Player *player;

	//View *view;
};

void InitializeGame(Game & game);
void DestroyGame(Game & game);
