#include "Font.h"

void InitString(Text & text, String & str, Font & font, int sizeText) {
	text.setString(str);
	text.setFont(font);
	text.setCharacterSize(sizeText);
	float width = text.getGlobalBounds().width;
	text.setOrigin( width / 2, sizeText / 2);
}

void InitializeText(TextWithInfo & textInfo) {
	textInfo.font.loadFromFile(PATH_TO_FONT);
	InitString(textInfo.textPlayerHealth, String(""), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textPoint, String(""), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textNewGame, String(TEXT_NEW_GAME), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textContinue, String(TEXT_CONTINUE), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textRecords, String(TEXT_RECORDS), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textOption, String(TEXT_OPTIONS), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textExit, String(TEXT_EXIT), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textAboutRecord, String(TEXT_ABOUT_RECORD), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textScore, String(""), textInfo.font, textInfo.sizeText);
}

void ReferenceLinePosition(Vector2u sizeWindow, Text & text, Vector2f & posPrevText, int sizeText) {
	float distance = (sizeWindow.y - COUNT_STRING_IN_MENU * sizeText) / (RATE_LINE_SPACING * COUNT_STRING_IN_MENU);
	float x = sizeWindow.x / 2;
	float y = distance + posPrevText.y;
	text.setPosition(x, y);
	//posPrevText = { x, y };
}

void UpdateText(TextWithInfo & textInfo, Player & player) {
	ostringstream countHealthStr, countPoint;
	if (player.ship->health >= 0)
		countHealthStr << player.ship->health;
	else
		countHealthStr << 0;
	countPoint << player.point;
	textInfo.textPlayerHealth.setString(TEXT_HEALTH + countHealthStr.str());
	textInfo.textPlayerHealth.setPosition(10, 10);
	textInfo.textPoint.setString(TEXT_POINT + countPoint.str());
	textInfo.textPoint.setPosition(250, 10); // сделать зависимость от размеров окна и длины предыдущей строки
}

void SelectTextWithMouse(RenderWindow & window, Text & text) {
	if (IntRect(text.getGlobalBounds()).contains(Mouse::getPosition(window))) {
		text.setColor(Color::Yellow);
		
	}
	else {
		text.setColor(Color::White);
	}
}

void UpdateTextMenu(RenderWindow & window, TextWithInfo & textInfo) {
	Vector2f pos = { 0, 0 };
	ReferenceLinePosition(window.getSize(), textInfo.textNewGame, pos, textInfo.sizeText);
	SelectTextWithMouse(window, textInfo.textNewGame);

	pos = textInfo.textNewGame.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textContinue, pos, textInfo.sizeText);
	SelectTextWithMouse(window, textInfo.textContinue);

	pos = textInfo.textContinue.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textRecords, pos, textInfo.sizeText);
	SelectTextWithMouse(window, textInfo.textRecords);

	pos = textInfo.textRecords.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textOption, pos, textInfo.sizeText);
	SelectTextWithMouse(window, textInfo.textOption);

	pos = textInfo.textOption.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textExit, pos, textInfo.sizeText);
	SelectTextWithMouse(window, textInfo.textExit);

}

void DrawTextToWindow(TextWithInfo & textInfo, RenderWindow & window) {
	window.draw(textInfo.textPlayerHealth);
	window.draw(textInfo.textPoint);
}

void DrawTextToMenu(TextWithInfo & textInfo, RenderWindow & window) {
	window.draw(textInfo.textNewGame);
	window.draw(textInfo.textContinue);
	window.draw(textInfo.textRecords);
	window.draw(textInfo.textOption);
	window.draw(textInfo.textExit);
}
