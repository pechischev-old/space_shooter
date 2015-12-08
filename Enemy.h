#pragma once
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <sstream>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()

#include "Entity.h"
#include "Config.h"
#include "Shoot.h"
#include "asteroids.h"
#include "Bonus.h"

using namespace sf;

enum Selector {
	ELECTRICAL,
	TRIPLE_SHOT,
	POWERFUL_SHOOTING,
	CROSS_FIRE
};

struct Enemy {
	std::list<Entity> enemyShip;
	std::list<Shoot> bulletEnemy;
	Clock clock;
	Time timeCreateEnemy = Time::Zero,
		timeCreateBulletEnemy = Time::Zero,
		timeForCalm = Time::Zero; 
	//--- Занести в отдельную структуру
	bool isBoss = false; 
	bool isOneBoss = false; 
	bool isEvasion = false; // Флаг уклонения
	bool isShock = false;
	bool isRage = false;
	//--------------
	float timeToCreateEnemy = TIME_CREATE_ENEMY;
	int damage = FIRST_EVER_DAMAGE_ENEMY;
	int health = FIRST_EVER_HEALTH_ENEMY;
	bool selectorTower = true;
	int rage = 0;
	Selector selector = TRIPLE_SHOT;
	int selectorShooting = 0;
	void AddEnemy(TextureGame & textureGame);
	void AddBulletEnemy(Vector2f posEnemy, Direction & dir, Entity & enemy, Vector2f posPlayer, Texture & texture);
	void UpdateStateEveryEnemy(const Time & deltaTime, int & point, RenderWindow & window, Bonus & bonus, TextureGame & textureGame, Vector2f posPlayer);
	void SetRotationEnemy(Entity & enemy); 
	void ReferenceRotationTowardPlayer(Entity & enemy, Vector2f posPlayer);

	void MoveOnSinusoid(const Time & deltaTime, Entity & entity);
	void Evasion(Vector2f posBullet, Entity & entity, Vector2u sizeWindow);
	void BorderChecks(Entity & entity, Vector2u sizeWindow);
	void CalmBoss();
};

Direction GetDirection();
Vector2f GetRandomPosition(Direction & selectHand);
int GetRandomPoint();
int GetTypeEnemy();
bool IsEnterField(Vector2f & playerPos, Entity & enemy);
bool IsSeePlayer(Vector2f & playerPos, Entity & enemy, Vector2u & sizeWindow);
void SpecialShootingBoss(Enemy & enemy, Entity & boss, TextureGame & textureGame);
void ResetEnemy(Enemy & enemy);