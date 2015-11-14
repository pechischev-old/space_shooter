#include "Font.h"

void InitializeText(TextWithInfo & textInfo) {
	textInfo.font = new Font;
	textInfo.font->loadFromFile("resourse/fonts/Ubuntu-R.ttf");
	textInfo.textPlayerHealth = new Text("", *textInfo.font, textInfo.sizeText);
	textInfo.textPoint = new Text("", *textInfo.font, textInfo.sizeText);
}

void UpdateText(TextWithInfo & textInfo, Player & player) {
	ostringstream countHealthStr, countPoint;
	if (player.ship->health >= 0)
		countHealthStr << player.ship->health;
	else
		countHealthStr << 0;
	countPoint << player.point;
	textInfo.textPlayerHealth->setString(L"Жизнь: " + countHealthStr.str());
	textInfo.textPlayerHealth->setPosition(10, 10);
	textInfo.textPoint->setString(L"Очки: " + countPoint.str());
	textInfo.textPoint->setPosition(250, 10);
}

void DrawTextToWindow(TextWithInfo & textInfo, RenderWindow & window) {
	window.draw(*textInfo.textPlayerHealth);
	window.draw(*textInfo.textPoint);
}