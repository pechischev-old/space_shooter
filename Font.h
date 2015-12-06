#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdint>
#include <iostream>

#include "Player.h"

using namespace sf;
using namespace std;

struct TextWithInfo {
	Font font;
	Text textPlayerHealth;
	Text textPoint;
	Text textNewGame;
	Text textContinue;
	Text textRecords;
	Text textOption;
	Text textExit;
	Text textScore;
	Text textAboutRecord;
	int sizeText = 32;
};

void InitializeText(TextWithInfo & textInfo);
void InitString(Text & text, String & str, Font & font, int sizeText);
void UpdateText(TextWithInfo & textInfo, Player & player);

void ReferenceLinePosition(Vector2u sizeWindow, Text & text, Vector2f & posPrevText, int sizeText);
void SelectTextWithMouse(RenderWindow & window, Text & text);
void UpdateTextMenu(RenderWindow & window, TextWithInfo & textInfo);
void DrawTextToWindow(TextWithInfo & textInfo, RenderWindow & window);
void DrawTextToMenu(TextWithInfo & textInfo, RenderWindow & window);
