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
	void CheckForCollision(); // �������� �� �������� �� ������������
	void DrawObjects();
};

void InitializeGame(Game & game);
void Delete(Game & game);