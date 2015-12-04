#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Shoot.h"
#include <iostream>
#include <list>

#include "Config.h"

using namespace sf;

struct PlayerState {
	bool isMove;  // ���� ��������
	bool isShoot = false; // ���� ��������
	bool isAlive;
	//--- ��������� � ������
	bool isRepair = false; // ���� �������������� �����
	bool isIncreaseDamage = false; // ���� ���������� �����
	bool isInvulnerability = false; // ���� ������������
	bool isDecrease = false; // ���� ����������
	bool isBomb = false; // ���� �����
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
	//������� ��� ������
	void AddBullet(TextureGame & textureGame);
	void CheckPlayerLife();
	void RecoveryMove();
};

void InitializePlayer(Player & player, TextureGame & textureGame);
void Control(Player & player);
void MovePlayer(Player & player, const Time & deltaTime);