#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdint>
#include <iostream>


#include "Config.h"
#include "Player.h"
#include "Font.h"

using namespace sf;
using namespace std;

struct S_GUI {
	Sprite decreaseSprite;
	Sprite increaseSprite;
	Sprite invulnerabilitySprite;
	Sprite tripleShotSprite;
	Sprite doubleShotSprite;
	RectangleShape emptyBar;
	RectangleShape bar;
	Vector2u sizeBonus; // ��� ������ ������ �������
	void InitGUI(TextureGame & textureGame, RenderWindow & window);
	void UpdateGUI(TextWithInfo & textGame, float timeUseBonus, PlayerState & state, RenderWindow & window);
	void DrawGUI(TextWithInfo & textGame, PlayerState & state, RenderWindow & window);

};

void InitSpriteGUI(Sprite & sprite, Texture & texture);
void UpdateState(Sprite & sprite, RenderWindow & window, Text & textTime);
void UpdateStateBar(RectangleShape & rect, RenderWindow & window);
void UpdateHealthBar(RectangleShape & bar, float health, RectangleShape & rect);