#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()

#include "Entity.h"
#include "Config.h"
#include "Shoot.h"

using namespace sf;

struct Enemy {
	std::list<Entity> *enemyShip;
	std::list<Shoot> *bulletEnemy;
	Vector2f movement = { 0.f, 0.f };
	Clock clock;
	Time timeCreateEnemy = Time::Zero,
		timeCreateBulletEnemy = Time::Zero;
	void AddEnemy();
	void AddBulletEnemy(Vector2f posEnemy, Direction & dir, Entity & enemy);
	void GetMoveEveryEnemy(const Time & deltaTime, float & point);
	void MoveEnemy(const Time & deltaTime, Entity & enemy);
	void UpdateStateEnemyBullet(const Time & deltaTime);
};

void InitializeEnemy(Enemy & enemy);
Direction GetDirection();
Vector2f GetRandomPosition(Direction & selectHand);
int GetRandomPoint();