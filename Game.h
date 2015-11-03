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
	std::list<Shoot> *bulletEnemy;
	//View *view;
	Clock clock;
	Time timeCreateEnemy = Time::Zero,
		timeCreateBulletEnemy = Time::Zero;
	void AddEnemy(); // Добавляет врагов
	void AddBulletEnemy(Vector2f posEnemy);
	void CheckForCollision(); // отвечает за проверку на столкновения
};


void InitializeGame(Game & game);
void DestroyGame(Game & game);
