#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdint>
#include <iostream>

#include "Player.h"

using namespace sf;
using namespace std;

struct TextWithInfo {
	Font *font;
	Text *textPlayerHealth;
	Text *textPoint;
	int sizeText = 32;
};

void InitializeText(TextWithInfo & textInfo);
void UpdateText(TextWithInfo & textInfo, Player & player);
void DrawTextToWindow(TextWithInfo & textInfo, RenderWindow & window);
