#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Shoot.h"
#include <iostream>
#include <list>

#include "Config.h"

using namespace sf;

struct PlayerState {
	bool isMove;  // флаг движени€
	bool isShoot = false; // флаг выстрела
	bool isAlive;
	//--- перенести в бонусы
	bool isRepair = false; // флаг восстановлени€ жизни
	bool isIncreaseDamage = false; // флаг увеличени€ урона
	bool isInvulnerability = false; // флаг неу€звимости
	bool isDecrease = false; // флаг уменьшени€
	bool isBomb = false; // флаг бомбы
	//---
};

struct Player
{
	Entity *ship;
	Direction direction, directionShoot;
	PlayerState playerState;
	Clock clock;                        
	Time timeCreateBullet = Time::Zero;
	Time timeRecoveryMove; 
	int scaleBullet = 2;
	std::list<Shoot> bullet;
	int point = 0;
	int maxHealth = MAX_HEALTH;
	int maxDamage = MAX_DAMAGE;
	//‘ункции дл€ игрока
	void AddBullet(TextureGame & textureGame);
	void CheckPlayerLife();
	void RecoveryMove();
};

void InitializePlayer(Player & player, TextureGame & textureGame);
void Control(Player & player);
void MovePlayer(Player & player, const Time & deltaTime);