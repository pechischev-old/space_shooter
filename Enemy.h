#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <list>
#include <cstdlib>
#include <ctime> // �������� time()

#include "Entity.h"
#include "Config.h"
#include "Shoot.h"
#include "Bonus.h"

using namespace sf;

struct Enemy {
	std::list<Entity> *enemyShip;
	std::list<Shoot> *bulletEnemy;
	Vector2f movement = { 0.f, 0.f };
	Clock clock;
	Time timeCreateEnemy = Time::Zero,
		timeCreateBulletEnemy = Time::Zero;
	bool isBoss = false;
	bool isOneBoss = false; 
	bool isEvasion = false; // ���� ���������
	int damage = FIRST_EVER_DAMAGE_ENEMY;
	int health = FIRST_EVER_HEALTH_ENEMY;
	void AddEnemy();
	void AddBulletEnemy(Vector2f posEnemy, Direction & dir, Entity & enemy, Vector2f posPlayer);
	void UpdateStateEveryEnemy(const Time & deltaTime, int & point, RenderWindow & window, Bonus & bonus);
	void SetRotationEnemy(Entity & enemy); 
	void UpdateStateEnemyBullet(const Time & deltaTime, RenderWindow & window);
	void MoveOnSinusoid(const Time & deltaTime, Entity & entity);
	void Evasion(Vector2f posBullet, Entity & entity, Vector2u sizeWindow);
	void BorderChecks(Entity & entity, Vector2u sizeWindow);
};

void InitializeEnemy(Enemy & enemy);
;
Direction GetDirection();
Vector2f GetRandomPosition(Direction & selectHand);
int GetRandomPoint();
int GetTypeEnemy();
bool IsEnterField(Vector2f & playerPos, Entity & enemy);
bool IsSeePlayer(Vector2f & playerPos, Entity & enemy, Vector2u & sizeWindow);