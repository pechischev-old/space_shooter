#include "Menu.h"

void ProcessEventsMenu(RenderWindow & window, Menu & menu, GlobalBool & globalBool, Event & event) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (menu.menuSelector == NEW_GAME) {
			globalBool.g_isMenu = false;
			menu.stateMenu.isNewGame = true;
			menu.restart();
		}
		if (menu.menuSelector == CONTINUE) {
			if (menu.stateMenu.isNewGame) {
				globalBool.g_isMenu = false;
			}
		}
		if (menu.menuSelector == RECORDS) {
			menu.stateMenu.isInstruction = true;
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
		if (menu.stateMenu.isNewGame) {
			globalBool.g_isMenu = false;
		}
	}
	else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && !menu.stateMenu.isMainMenu) {
		menu.stateMenu.isOptions = false;
		menu.stateMenu.isMainMenu = true;
		menu.stateMenu.isInstruction = false;
	}
}

void InitMenu(Menu & menu, RenderWindow & window, TextureMenu & textureMenu, TextWithInfo & text) {
	textureMenu.LoadingFromFileTextureForMenu();
	menu.background.setTexture(textureMenu.fieldTexture);
	menu.instruction.boxInstruction.setTexture(textureMenu.instructionTexture);
	UpdateTextMenu(window, text);
}

void UpdateMenu(Menu & menu, RenderWindow & window, TextWithInfo & text) {
	menu.background.setTextureRect(IntRect(0, 0, window.getSize().x, window.getSize().y));
	UpdateTextMenu(window, text);
	SelectButtons(window, text, menu.menuSelector);
}

void RenderMenu(Menu & menu, RenderWindow & window, TextWithInfo & text) {
	window.clear();
	window.draw(menu.background);
	if (menu.stateMenu.isMainMenu) {
		DrawTextToMenu(text, window);
	}
	if (menu.stateMenu.isInstruction) {
		window.draw(menu.instruction.boxInstruction);
	}
	if (menu.stateMenu.isOptions) {

	}
	window.display();
}