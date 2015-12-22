#pragma once
#include <SFML/Graphics.hpp>


#include "Entity.h"
#include "Shoot.h"
#include "Music.h"
#include <iostream>
#include <list>

#include "Config.h"
#include "Music.h"

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
	Sound takeBonus;
	int scaleBullet = 2;
	int gun = 0;
	std::list<Shoot> bullet;
	int maxHealth = MAX_HEALTH;
	int maxDamage = MAX_DAMAGE;
	int point = POINT_FOR_ADVANCE;
	int levelGame = 1;

	//������� ��� ������
	void AddBullet(Texture & texture, Vector2f posPoint, float time, String name);
	void CheckPlayerLife();
	void RecoveryMove();
	void PlaySoundAtDead();
		void ChangeWeapons(TextureGame & textureGame, Vector2f posPoint);
};

void InitializePlayer(Player & player, TextureGame & textureGame, SSound & sSound);
void Control(Player & player, Event & event);
void MovePlayer(Player & player, const Time & deltaTime, RenderWindow & window);
void ResetPlayer(Player & player, TextureGame & textureGame);
