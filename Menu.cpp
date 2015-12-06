#include "Menu.h"

void ProcessEventsMenu(Menu & menu, GlobalBool & globalBool, Event & event) {
	
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape ) { // что-то сделать
			globalBool.g_isMenu = false;
	}
}

void InitMenu(Menu & menu, RenderWindow & window, TextureMenu & textureMenu) {
	textureMenu.LoadingFromFileTextureForMenu();
	menu.field.setTexture(textureMenu.fieldTexture);
}

void UpdateMenu(Menu & menu, RenderWindow & window, TextWithInfo & text) {
	menu.field.setTextureRect(IntRect(0, 0, window.getSize().x, window.getSize().y));
	UpdateTextMenu(window, text);
}

void RenderMenu(Menu & menu, RenderWindow & window, TextWithInfo & text) {
	window.clear();
	window.draw(menu.field);
	DrawTextToMenu(text, window);
	window.display();
}