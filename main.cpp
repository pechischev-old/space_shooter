#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <math.h>

#include "Game.h"
#include "Menu.h"
#include "Music.h"

using namespace sf;
using namespace std;


const Time TIME_PER_FRAME = seconds(1.f / 60.f);

void processEvents(RenderWindow & window, Menu & menu, Game & game, GlobalBool & globalBool, SSound & sSound) {
	Event event;
	while (window.pollEvent(event))
	{
	
		if (globalBool.g_isMenu) {
			ProcessEventsMenu(window, menu, globalBool, event); // вызов меню	
		}
		else {
			processEventsGame(game, event, window);
			globalBool.g_isMenu = event.type == Event::KeyPressed && event.key.code == Keyboard::Escape;
		}
		
		// Окно закрыли
		if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::T)) {
			window.close();
		}
	}

}

int CallGame(GlobalBool & globalBool, Menu & menu, SSound & sSound)
{
	
	RenderWindow window(VideoMode(SCRN_WIDTH, SCRN_HEIGTH), TITLE_GAME);
	
	Game *game = new Game();
	
	sSound.LoadSound();
	InitializeGame(*game, sSound);
	InitMenu(menu, window, menu.textureMenu, *game->textInfo);

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	Player & player = *game->player;
	menu.restart = [&]() {
		ResetGame(*game);
	};

	window.setVerticalSyncEnabled(true);
	
	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(window, menu, *game, globalBool, sSound);
			if (globalBool.g_isMenu) {
				UpdateMenu(menu, window, *game->textInfo);
			}
			else {
				updateGame(*game, TIME_PER_FRAME, window, globalBool, sSound);
			}
		}
		if (globalBool.g_isMenu) {
			RenderMenu(menu, window, *game->textInfo);
		}
		else {
			renderGame(window, *game);
		}
	}
	Delete(*game);
	delete game;
	return 0;
}

int main()
{
	Menu menu;
	SSound sSound;
	GlobalBool globalBool; // обявление глобальных булевских переменных
	CallGame(globalBool, menu, sSound);

	return 0;
}

