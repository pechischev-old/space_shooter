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
	Text textNumber;
	Text textNewGame;
	Text textContinue;
	Text textInstruction;
	Text textOption;
	Text textExit;
	Text textScore;
	Text textLosing;
	Text textWin;
	Text textLevel;
	Text textTimeUseBonus;
	int sizeText = 32;
	
};

void InitializeText(TextWithInfo & textInfo);
void InitString(Text & text, String & str, Font & font, int sizeText);
void UpdateTextGame(TextWithInfo & textInfo, Player & player, RenderWindow & window);
float GetWidth(Text & text);

void ReferenceLinePosition(Vector2u sizeWindow, Text & text, Vector2f & posPrevText, int sizeText);
void SelectTextWithMouse(RenderWindow & window, Text & text, MenuSelector & selector, MenuSelector selectMenu);
void SelectButtons(RenderWindow & window, TextWithInfo & textInfo, MenuSelector & selector);
void UpdateTextMenu(RenderWindow & window, TextWithInfo & textInfo);

void OutputMessageAboutEndGame(RenderWindow & window, Text & text);
void DrawTextToGame(TextWithInfo & textInfo, RenderWindow & window);
void DrawTextToMenu(TextWithInfo & textInfo, RenderWindow & window);
