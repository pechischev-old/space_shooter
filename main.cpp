#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <math.h>

#include "Game.h"
#include "Menu.h"

using namespace sf;
using namespace std;


const Time TIME_PER_FRAME = seconds(1.f / 60.f);

void processEvents(RenderWindow & window, Menu & menu, Game & game, GlobalBool & globalBool) {
	Event event;
	while (window.pollEvent(event))
	{
		if (globalBool.g_isMenu) {
			ProcessEventsMenu(window, menu, globalBool, event); // вызов меню	
		}
		else {
			processEventsGame(game, globalBool, event, window);
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {  //  ѕоставить на паузу или сн€ть с паузы игру
			if (!globalBool.g_isPause) {
				globalBool.g_isPause = true;
			}
			else {
				globalBool.g_isPause = false;
			}
		}


		// ќкно закрыли
		if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::T)) {
			window.close();
		}
	}

}

int CallGame(GlobalBool & globalBool, Menu & menu)
{
	
	RenderWindow window(VideoMode(SCRN_WIDTH, SCRN_HEIGTH), TITLE_GAME);
	
	Game *game = new Game();
	InitializeGame(*game);
	InitMenu(menu, window, menu.textureMenu, *game->textInfo);

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	Player & player = *game->player;
	
	window.setVerticalSyncEnabled(true);
	
	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(window, menu, *game, globalBool);
			if ((!globalBool.g_isMenu && !globalBool.g_isPause) && globalBool.g_isNewGame) {
				updateGame(*game, TIME_PER_FRAME, window, globalBool);
			}
			else {
				UpdateMenu(menu, window, *game->textInfo);
			}
			
		}
		if (globalBool.g_isRestart) {
			ResetGame(*game);
			globalBool.g_isRestart = false;
		}
		if ((!globalBool.g_isMenu) && globalBool.g_isNewGame) {
			renderGame(window, *game);
		}
		else {
			RenderMenu(menu, window, *game->textInfo);
		}
	}
	Delete(*game);
	delete game;
	return 0;
}

int main()
{
	Menu menu;
	GlobalBool globalBool; // об€вление глобальных булевских переменных
	CallGame(globalBool, menu);

	return 0;
}

