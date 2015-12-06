#include "Menu.h"

void ProcessEventsMenu(RenderWindow & window, Menu & menu, GlobalBool & globalBool, Event & event) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (menu.menuSelector == NEW_GAME) {
			globalBool.g_isMenu = false;
			globalBool.g_isRestart = true;
			globalBool.g_isNewGame = true;
			globalBool.g_isPause = false;
		}
		if (menu.menuSelector == CONTINUE) {
			if (globalBool.g_isNewGame) {
				globalBool.g_isMenu = false;
				globalBool.g_isPause = false;
			}
		}
		if (menu.menuSelector == RECORDS) {
			menu.stateMenu.isRecords = true;
			menu.stateMenu.isMainMenu = false;
		}
		if (menu.menuSelector == OPTIONS) {
			menu.stateMenu.isOptions = true;
			menu.stateMenu.isMainMenu = false;
		}
		if (menu.menuSelector == EXIT) {
			window.close();
		}
	}

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && menu.stateMenu.isMainMenu) {
			globalBool.g_isMenu = false;
	}
	else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && !menu.stateMenu.isMainMenu) {
		menu.stateMenu.isOptions = false;
		menu.stateMenu.isMainMenu = true;
		menu.stateMenu.isRecords = false;
	}
}

void InitMenu(Menu & menu, RenderWindow & window, TextureMenu & textureMenu, TextWithInfo & text) {
	textureMenu.LoadingFromFileTextureForMenu();
	menu.field.setTexture(textureMenu.fieldTexture);
	UpdateTextMenu(window, text);
}

void UpdateMenu(Menu & menu, RenderWindow & window, TextWithInfo & text) {
	menu.field.setTextureRect(IntRect(0, 0, window.getSize().x, window.getSize().y));
	UpdateTextMenu(window, text);
	SelectButtons(window, text, menu.menuSelector);
}

void RenderMenu(Menu & menu, RenderWindow & window, TextWithInfo & text) {
	window.clear();
	window.draw(menu.field);
	if (menu.stateMenu.isMainMenu) {
		DrawTextToMenu(text, window);
	}
	if (menu.stateMenu.isRecords) {

	}
	if (menu.stateMenu.isOptions) {

	}
	window.display();
}