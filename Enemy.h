#pragma once
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <sstream>
#include <list>

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
		Time timeCreateEnemy = Time::Zero;
		Time timeCreateBulletEnemy = Time::Zero;
		Time timeForCalm = Time::Zero;
	struct BossState {
	
		bool isBoss = false;
		bool isOneBoss = false;
		bool isEvasion = false; // Флаг уклонения
		bool isShock = false;
		bool isRage = false;
	};
	BossState bossState;
		float timeToCreateEnemy = float(TIME_CREATE_ENEMY);
		int damage = FIRST_EVER_DAMAGE_ENEMY;
		int health = FIRST_EVER_HEALTH_ENEMY;
		int rage = 0;
	struct NumberEnemy {
		int numberEasyEnemy = COUNT_EASY_ENEMY;
		int numberMiddleEnemy = COUNT_MIDDLE_ENEMY;
		int numberTowerEnemy = COUNT_TOWER_ENEMY;
		int numberKamikaze = COUNT_KAMIKAZE_ENEMY;
	};
	NumberEnemy numberEnemy;
	enum  TypeEnemy {
		EASY = 1,
		MIDDLE,
		KAMIKAZE,
		TOWER,
		sizeTypeEnemy = 4
	};
	TypeEnemy idEnemy;
	Selector selector = TRIPLE_SHOT;
		int selectorShooting = 0;
	void AddEnemy(TextureGame & textureGame, RenderWindow & window);
	void AddBulletEnemy(Entity & enemy, Vector2f posPlayer, Texture & texture, Time & timeCreateBullet);

	void UpdateStateEveryEnemy(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame, Vector2f posPlayer, int & point);

	void Evasion(Vector2f posBullet, Entity & entity, Vector2u sizeWindow);
	void BorderChecks(Entity & entity, Vector2u sizeWindow);
	void CalmBoss();
	void SetMove(RenderWindow & window, Entity & enemy);
	
	void UpdateDirection(RenderWindow & window, Entity & enemy);
	void MoveKamikaze(const Time & deltaTime, Vector2f posPlayer, Entity & enemy);
};

void SpecialShootingBoss(Enemy & enemy, Entity & boss, TextureGame & textureGame);
void ResetEnemy(Enemy & enemy);
	Direction GetDirection(Direction dir);
	Vector2f GetRandomPosition(Direction & selectHand, RenderWindow & window);
	bool IsEnterField(Vector2f & playerPos, Entity & enemy);
	bool IsSeePlayer(Vector2f & playerPos, Entity & enemy, Vector2u & sizeWindow);
