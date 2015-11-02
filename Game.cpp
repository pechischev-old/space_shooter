#include "Game.h"


using namespace sf;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.window = new RenderWindow(VideoMode(SCRN_HEIGTH, SCRN_WIDTH), "Main Game");
	InitializePlayer(*game.player);
}

void DestroyGame(Game & game) {
	delete &game;
}



