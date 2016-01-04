#include "Font.h"

void InitString(Text & text, String & str, Font & font, int sizeText) {
	text.setString(str);
	text.setFont(font);
	text.setCharacterSize(sizeText);
	float width = text.getGlobalBounds().width;
	text.setOrigin( width / 2, float(sizeText) / 2);
}

void InitializeText(TextWithInfo & textInfo) {
	textInfo.font.loadFromFile(PATH_TO_FONT);
	InitString(textInfo.textNumber, String(""), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textNewGame, String(TEXT_NEW_GAME), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textContinue, String(TEXT_CONTINUE), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textInstruction, String(TEXT_INSTRUCTION), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textOption, String(TEXT_OPTIONS), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textExit, String(TEXT_EXIT), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textLosing, String(TEXT_ABOUT_LOSING), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textWin, String(TEXT_ABOUT_WIN), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textScore, String(""), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textLevel, String(""), textInfo.font, textInfo.sizeText);
	InitString(textInfo.textTimeUseBonus, String(""), textInfo.font, textInfo.sizeText);
}

void ReferenceLinePosition(Vector2u sizeWindow, Text & text, Vector2f & posPrevText, int sizeText) {
	float distance = (sizeWindow.y - COUNT_STRING_IN_MENU * sizeText) / (RATE_LINE_SPACING * COUNT_STRING_IN_MENU);
	float x = float(sizeWindow.x) / 2;
	float y = distance + posPrevText.y;
	text.setPosition(x, y);
}

float GetWidth(Text & text) {
	return text.getLocalBounds().width;
}

void UpdateTextGame(TextWithInfo & textInfo, Player & player, RenderWindow & window) {
	
	String countHealthStr;
	textInfo.textNumber.setString(TEXT_POINT + to_string(player.point));
	textInfo.textNumber.setPosition(10, 10); 
	textInfo.textLevel.setString(TEXT_LEVEL + to_string(player.levelGame));
	float width = GetWidth(textInfo.textLevel);
	float widthWindow = float(window.getSize().x);
	textInfo.textLevel.setPosition(widthWindow - width * 2, 10);
}

void SelectTextWithMouse(RenderWindow & window, Text & text, MenuSelector & selector, MenuSelector selectMenu) {
	if (IntRect(text.getGlobalBounds()).contains(Mouse::getPosition(window))) {
		text.setColor(Color::Yellow);
		selector = selectMenu;
	}
	else {
		text.setColor(Color::White);
	}
}

void SelectButtons(RenderWindow & window, TextWithInfo & textInfo, MenuSelector & selector) {
	selector = NO_SELECT;
	SelectTextWithMouse(window, textInfo.textNewGame, selector, NEW_GAME);
	SelectTextWithMouse(window, textInfo.textContinue, selector, CONTINUE);
	SelectTextWithMouse(window, textInfo.textInstruction, selector, RECORDS);
	SelectTextWithMouse(window, textInfo.textOption, selector, OPTIONS);
	SelectTextWithMouse(window, textInfo.textExit, selector, EXIT);
}

void UpdateTextMenu(RenderWindow & window, TextWithInfo & textInfo) {
	Vector2f pos = { 0, 0 };
	ReferenceLinePosition(window.getSize(), textInfo.textNewGame, pos, textInfo.sizeText);

	pos = textInfo.textNewGame.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textContinue, pos, textInfo.sizeText);

	pos = textInfo.textContinue.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textInstruction, pos, textInfo.sizeText);

	pos = textInfo.textInstruction.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textOption, pos, textInfo.sizeText);

	pos = textInfo.textOption.getPosition();
	ReferenceLinePosition(window.getSize(), textInfo.textExit, pos, textInfo.sizeText);
}

void DrawTextToGame(TextWithInfo & textInfo, RenderWindow & window) {
	window.draw(textInfo.textNumber);
	window.draw(textInfo.textLevel);
}

void DrawTextToMenu(TextWithInfo & textInfo, RenderWindow & window) {
	window.draw(textInfo.textNewGame);
	window.draw(textInfo.textContinue);
	window.draw(textInfo.textInstruction);
	window.draw(textInfo.textOption);
	window.draw(textInfo.textExit);
}


void OutputMessageAboutEndGame(RenderWindow & window, Text & text) {
	Vector2u sizeWindow = window.getSize();
	text.setPosition(float(sizeWindow.x) / 2, float(sizeWindow.y) / 2);
	window.draw(text);
}