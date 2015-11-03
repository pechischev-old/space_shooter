#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Config.h"

using namespace sf;



struct PlayerState {
	bool isMove = false;  // флаг движения
	bool isShoot = false; // флаг выстрела
	bool isAlive = false;
};

struct Shoot {
	Shoot(float X, float Y, float WIDTH, float  HEIGTH, Direction dir, String path);
	float x, y;
	Direction dir, rememberDir;
	Texture *texture;
	Sprite *sprite;
	float rotation = 0;
	Vector2f movement = { 0.f, 0.f };
	Vector2i pos_mouse;
	bool life = true; //флаг жизни
	void MoveBullet(const Time & deltaTime);
};


struct Player
{
	RectangleShape *shape;
	Texture *texture;
	Sprite *sprite;
	Direction direction, directionShoot;
	PlayerState playerState;
	float x, y;
	//float vX, vY; // координаты носа
	float rotation = 0;
	float lifePlayer = 100;
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
