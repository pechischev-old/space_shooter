#include "Game.h"


using namespace sf;
using namespace std;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.enemy = new Enemy;
	game.window = new RenderWindow(VideoMode(SCRN_WIDTH, SCRN_HEIGTH), "Main Game");
	InitializePlayer(*game.player);
	InitializeEnemy(*game.enemy);
}

void Game::CheckForCollision() {
	
	if (player->ship->sprite->getColor() == Color::Red)
		player->ship->sprite->setColor(Color::White);
	// Обработка взаимодействия игрока и противников
	for (list<Entity>::iterator it2 = enemy->enemyShip->begin(); it2 != enemy->enemyShip->end(); it2++) {
		if(player->ship->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds())) // столкновение игрока с врагом
		{
			if (it2->health > 0) {
				player->ship->health -= ENEMY_DAMAGE;
				player->ship->sprite->setColor(Color::Red);
			}
			it2->health = 0;
		}
		if (it2->sprite->getPosition().x - player->ship->sprite->getPosition().x < 500  && it2->sprite->getPosition().x - player->ship->sprite->getPosition().x > 0) { // враг стреляет
			if (it2->health > 0) {
				enemy->AddBulletEnemy(it2->sprite->getPosition());					
			}
		}
	}
	
	// Обработка попадания пули по игроку
	for (list<Shoot>::iterator it = enemy->bulletEnemy->begin(); it != enemy->bulletEnemy->end(); it++) {
		if (player->ship->sprite->getGlobalBounds().intersects(it->sprite->getGlobalBounds())) {
			player->ship->health -= ENEMY_DAMAGE;
			it->life = false;
			player->ship->sprite->setColor(Color::Red);
		}
	}
	
	// Обработка попадания пули по врагу
	for (list<Entity>::iterator it2 = enemy->enemyShip->begin(); it2 != enemy->enemyShip->end(); it2++) {
		if (it2->sprite->getColor() == Color::Red)
			it2->sprite->setColor(Color::White);
		for (list<Shoot>::iterator it = player->bullet->begin(); it != player->bullet->end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds()))	{
				it2->health -= PLAYER_DAMAGE;
				it->life = false;
				it2->sprite->setColor(Color::Red);
			}
		}
		
	}
}

void DestroyGame(Game & game) {
	delete &game;
}



