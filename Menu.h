#pragma once
#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>

#include "Config.h"
#include "LoadTexture.h"
#include "Font.h"

using namespace sf;
using namespace std;

enum MenuSelector {
	NEW_GAME = 1,
	CONTINUE,
	RECORDS,
	OPTIONS,
	EXIT,
	BACK
};

struct Records {
	Sprite boxRecords;
};

struct Options {
	Sprite boxOptions;
};

struct Menu {
	MenuSelector menuSelector;
	TextureMenu textureMenu;
	Sprite field;
	Sprite boxMenu;
	Records records;
	Options options;
};

void InitMenu(Menu & menu, RenderWindow & window, TextureMenu & textureMenu);
void ProcessEventsMenu(Menu & menu, GlobalBool & globalBool, Event & event);
void UpdateMenu(Menu & menu, RenderWindow & window, TextWithInfo & text);
void RenderMenu(Menu & menu, RenderWindow & window, TextWithInfo & text);

