#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime> // содержит time()

#include "Config.h"

using namespace sf;

typedef enum
{
	NONE_2,
	UP_2,
	DOWN_2,
	LEFT_2,
	RIGHT_2,
	UP_LEFT_2,
	UP_RIGHT_2,
	DOWN_LEFT_2,
	DOWN_RIGHT_2
} DirEnemy;

struct EnemyState {
	bool isMove = false;  // флаг движения
	bool isShoot = false; // флаг выстрела
	bool isAlive = false; //флаг жизни
};

struct Enemy {
	Enemy(float X, float Y, float width, float heigth, String Name);
	Texture *texture;
	Sprite *sprite;
	DirEnemy direction;
	EnemyState enemyState;
	String name;
	float x, y;
	float life = 100;
	bool isLife;
	Vector2f movement = { 0.f, 0.f };
	float CurrentFrame = 0;
	void MoveEnemy(const Time & deltaTime);
	void GetExplosion(const Time & deltaTime); // Анимация взрыва
};

void InitializeEnemy(Enemy & enemy);
Vector2f GetRandomPosition();