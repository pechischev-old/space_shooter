#include "Game.h"


using namespace sf;
using namespace std;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.enemy = new list<Enemy>;
	game.bulletEnemy = new list<Shoot>;
	game.window = new RenderWindow(VideoMode(SCRN_WIDTH, SCRN_HEIGTH), "Main Game");
	InitializePlayer(*game.player);
}

void Game::AddEnemy() {
	timeCreateEnemy += clock.restart();
	if (timeCreateEnemy.asSeconds() > 2) {
		Direction dir = LEFT;//GetDirection();
		Vector2f getPositionEnemy = GetRandomPosition(dir);
		Enemy addEnemy(getPositionEnemy.x, getPositionEnemy.y, WIDTH_ENEMY, HEIGTH_ENEMY, "EasyEnemy", dir);
		enemy->push_back(addEnemy);
		timeCreateEnemy = Time::Zero;
	}
}

void Game::AddBulletEnemy(Vector2f posEnemy) {
	timeCreateBulletEnemy += clock.restart();
	if (timeCreateBulletEnemy.asSeconds() > 0.0005) {
		Shoot addBullet(posEnemy.x, posEnemy.y, WIDTH_BULLET, HEIGTH_BULLET, LEFT, "resourse/images/laser-red.png");
		bulletEnemy->push_back(addBullet); // создание пули и занесение ее в список
		timeCreateBulletEnemy = Time::Zero;
	}
}

void Game::CheckForCollision() {
	// Обработка взаимодействия игрока и противников
	for (list<Enemy>::iterator it2 = enemy->begin(); it2 != enemy->end(); it2++) {
		if (player->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds()))
		{
			/*if (it2->life > 0)
				player->lifePlayer -= ENEMY_DAMAGE;*/
			it2->life = 0;
		}
		if (it2->sprite->getPosition().x - player->sprite->getPosition().x < 250  && it2->sprite->getPosition().x - player->sprite->getPosition().x > 0) {
			if (it2->life > 0) {
				AddBulletEnemy(it2->sprite->getPosition());					
			}
		}
	}
	for (list<Shoot>::iterator it = bulletEnemy->begin(); it != bulletEnemy->end(); it++) {
		if (player->sprite->getGlobalBounds().intersects(it->sprite->getGlobalBounds())) {
			player->lifePlayer -= ENEMY_DAMAGE;
			it->life = false;
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



