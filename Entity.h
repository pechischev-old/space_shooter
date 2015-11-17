#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Config.h"

using namespace sf;

struct Entity {
	Entity(float x, float y, String Name);
	float x;
	float y;
	float width;
	float height;
	float health; // �������� ��������
	float damage; // ���� ������� ������� ��������
	float speed; // �������� ��������
	Direction direction, rememberDir;
	String name;
	Texture *texture;
	Sprite *sprite;
	bool isLife;
	float CurrentFrame = 0;
	void Explosion(const Time & deltaTime);
	void CheckForCollisions(RenderWindow & window);
	void MoveObject(const Time & deltaTime);
};

