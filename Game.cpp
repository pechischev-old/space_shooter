#include "Game.h"


using namespace sf;
using namespace std;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.enemy = new list<Enemy>;
	game.window = new RenderWindow(VideoMode(SCRN_HEIGTH, SCRN_WIDTH), "Main Game");
	InitializePlayer(*game.player);
}

void Game::AddEnemy() {
	timeCreateEnemy += clock.restart();
	if (timeCreateEnemy.asSeconds() > 4) {
		Enemy addEnemy(GetRandomPosition().x, GetRandomPosition().y, WIDTH_ENEMY, HEIGTH_ENEMY, "EasyEnemy");
		enemy->push_back(addEnemy);
		timeCreateEnemy = Time::Zero;
	}
}

void Game::CheckForCollision() {
	// Обработка столкновения игрока с противником
	for (list<Enemy>::iterator it2 = enemy->begin(); it2 != enemy->end(); it2++) {
		if (player->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds()))
		{
			//player->lifePlayer -= ENEMY_DAMAGE;
			//it2->isLife = false;
			//player->x -= 
		}
	}
	// Обработка попадания пули по врагу
	for (list<Enemy>::iterator it2 = enemy->begin(); it2 != enemy->end(); it2++) {
		for (list<Shoot>::iterator it = player->bullet->begin(); it != player->bullet->end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds()))	{
				it2->life -= PLAYER_DAMAGE;
				it->life = false;
			}
		}
	}
}

void DestroyGame(Game & game) {
	delete &game;
}



