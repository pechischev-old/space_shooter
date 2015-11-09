#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Shoot.h"
#include <iostream>
#include <list>

#include "Config.h"

using namespace sf;



struct PlayerState {
	bool isMove = false;  // флаг движения
	bool isShoot = false; // флаг выстрела
	bool isAlive = false;
};


struct Player
{
	Entity *ship;
	//RectangleShape *shape;
	Direction direction, directionShoot;
	PlayerState playerState;
	//float vX, vY; // координаты носа
	Vector2i posMouse;
	Vector2i dirRotation = { 0, 0 };
	Clock clock;
	Time timeCreateBullet = Time::Zero;
	std::list<Shoot> *bullet;
	//Функции для игрока
	void AddBullet(RenderWindow & window);
	void CheckPlayerLife();
};

Direction GetDirectionShoot(Vector2i posMouse, Vector2f posPlayer);
void InitializePlayer(Player & player);
void Control(Player & player);
void MovePlayer(Player & player, const Time & deltaTime);
Vector2f Border(float X, float Y, Vector2f posPlayer, int rotation);