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
};

struct Player
{
	Entity *ship;
	//RectangleShape *shape;
	Direction direction, directionShoot;
	PlayerState playerState;
	//float vX, vY; // ���������� ����
	Vector2i posMouse;
	Vector2i dirRotation = { 0, 0 };
	Clock clock;
	Time timeCreateBullet = Time::Zero;
	std::list<Shoot> *bullet;
	float point = 0;
	//������� ��� ������
	void AddBullet(RenderWindow & window);
	void CheckPlayerLife();
	void UpdateStatePlayerBullet(const Time & deltaTime);
};

Direction GetDirectionShoot(Vector2i posMouse, Vector2f posPlayer);
void InitializePlayer(Player & player);
void Control(Player & player);
void MovePlayer(Player & player, const Time & deltaTime);
Vector2f Border(Player & player);