#pragma once
#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <functional>

#include "Config.h"
#include "LoadTexture.h"
#include "Font.h"

using namespace sf;
using namespace std;

struct StateMenu {
	bool isInstruction = false;
	bool isOptions = false;
	bool isMainMenu = true;
	bool isNewGame = false;
};

struct Instruction {
	Sprite boxInstruction;
};

struct Options {
	Sprite boxOptions;
};

struct Menu {
	MenuSelector menuSelector = NO_SELECT;
	TextureMenu textureMenu;
	StateMenu stateMenu;
	Sprite background;
	Instruction instruction;
	Options options;
	function<void()> restart;
};

void InitMenu(Menu & menu, RenderWindow & window, TextureMenu & textureMenu, TextWithInfo & text);
void ProcessEventsMenu(RenderWindow & window, Menu & menu, GlobalBool & globalBool, Event & event);
void UpdateMenu(Menu & menu, RenderWindow & window, TextWithInfo & text);
void RenderMenu(Menu & menu, RenderWindow & window, TextWithInfo & text);

