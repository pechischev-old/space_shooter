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

	RectangleShape bar;
	Sprite healthBar;
	Vector2u sizeBonus; // все бонусы одного размера
	void InitGUI(TextureGame & textureGame);
	void UpdateGUI(TextWithInfo & textGame, float timeUseBonus, PlayerState & state, RenderWindow & window);
	void DrawGUI(TextWithInfo & textGame, PlayerState & state, RenderWindow & window);

};

void InitSpriteGUI(Sprite & sprite, Texture & texture);
void UpdateState(Sprite & sprite, RenderWindow & window, Text & textTime);
void UpdateStateBar(Sprite & sprite, RenderWindow & window);
void UpdateHealthBar(RectangleShape & bar, float health, FloatRect & healthBar, Sprite & sprite);