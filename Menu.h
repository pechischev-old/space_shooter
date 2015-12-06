#pragma once
#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>

#include "Config.h"
#include "LoadTexture.h"
#include "Font.h"

using namespace sf;
using namespace std;

struct StateMenu {
	bool isRecords = false;
	bool isOptions = false;
	bool isMainMenu = true;
};

struct Records {
	Sprite boxRecords;
};

struct Options {
	Sprite boxOptions;
};

struct Menu {
	MenuSelector menuSelector = NO_SELECT;
	TextureMenu textureMenu;
	StateMenu stateMenu;
	Sprite field;
	Sprite boxMenu;
	Records records;
	Options options;
};

void InitMenu(Menu & menu, RenderWindow & window, TextureMenu & textureMenu, TextWithInfo & text);
void ProcessEventsMenu(RenderWindow & window, Menu & menu, GlobalBool & globalBool, Event & event);
void UpdateMenu(Menu & menu, RenderWindow & window, TextWithInfo & text);
void RenderMenu(Menu & menu, RenderWindow & window, TextWithInfo & text);

