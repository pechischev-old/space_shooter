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
	std::list<Enemy> *enemy;
	//View *view;

	Clock clock;
	Time timeCreateEnemy = Time::Zero;
	void AddEnemy(); // ��������� ������
	void CheckForCollision(); // �������� �� �������� �� ������������
};


void InitializeGame(Game & game);
void DestroyGame(Game & game);
