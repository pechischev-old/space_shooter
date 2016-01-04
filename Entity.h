#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <list>

#include "Config.h"
#include "Music.h"
#include "LoadTexture.h"

using namespace sf;
using namespace std;

struct Entity {
	Entity(Vector2f position, String Name, Texture & texture, SSound & sSound, int maxCountFrame);
	Vector2f position;
	Vector2f sizeObject;
	float health; // �������� ��������
	float damage; // ���� ������� ������� ��������
	float speed; // �������� ��������
	Direction direction;
	String name;
	Sprite *sprite;
	bool isLife;
	bool isKilled;
	float CurrentFrame = 0;
	float animationFrame = 2;
	void Explosion(const Time & deltaTime, Texture & texture);
	void CheckForCollisions(RenderWindow & window);
	void MoveObject(const Time & deltaTime);
	

	void SetRotationObject(Vector2f posPoint);
	Time timeChangeDirection = Time::Zero; // ��� ������
	Time timeCreateBullet = Time::Zero; // ��� ������

	Sound explosionSound;
	Sound shootSound;
};

void Animation(const Time & deltaTime, Entity & object, int beginFrame, int endFrame, float speedFrames, float & animationFrame);
Vector2f Border(Entity & object, RenderWindow & window);
void ClearListObject(list<Entity> & objects);