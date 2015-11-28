#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Shoot.h"
#include <iostream>
#include <list>

#include "Config.h"

using namespace sf;

struct PlayerState {
	bool isMove = false;  // ���� ��������
	bool isShoot = false; // ���� ��������
	bool isAlive = false;
	bool isRepair = false; // ���� �������������� �����
	bool isIncreaseDamage = false; // ���� ���������� �����
	bool isInvulnerability = false; // ���� ������������
	bool isDecrease = false; // ���� ����������
	bool isBomb = false; // ���� �����
};

struct Player
{
	Entity *ship;
	Direction direction, directionShoot;
	PlayerState playerState;
	Clock clock;                        
	Time timeCreateBullet = Time::Zero; 
	float scaleBullet = 2;
	std::list<Shoot> bullet;
	int point = 0;
	int maxHealth = MAX_HEALTH;
	int maxDamage = MAX_DAMAGE;
	//������� ��� ������
	void AddBullet(); 
	void CheckPlayerLife();
	void UpdateStateBulletPlayer(const Time & deltaTime, RenderWindow & window);
};

Direction GetDirectionShoot(Vector2i posMouse, Vector2f posPlayer);
void InitializePlayer(Player & player, TextureGame & textureGame);
void Control(Player & player);
void MovePlayer(Player & player, const Time & deltaTime);