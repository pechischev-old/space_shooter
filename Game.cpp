#include "Game.h"


using namespace sf;
using namespace std;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.enemy = new Enemy;
	game.window = new RenderWindow(VideoMode(SCRN_WIDTH, SCRN_HEIGTH), "Main Game");
	game.textInfo = new TextWithInfo;
	game.asteroid = new Asteroid;
	InitializePlayer(*game.player);
	InitializeEnemy(*game.enemy);
	InitializeAsteroid(*game.asteroid);
	InitializeText(*game.textInfo);
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
				enemy->AddBulletEnemy(it2->sprite->getPosition(), it2->direction, *it2);
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

	for (list<Entity>::iterator it3 = asteroid->asteroids->begin(); it3 != asteroid->asteroids->end(); it3++) {
		if (player->ship->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) // столкновение игрока с врагом
		{
			if (it3->health > 0) {
				player->ship->health -= ENEMY_DAMAGE;
				player->ship->sprite->setColor(Color::Red);
			}
			it3->health = 0;
		}
	}

	for (list<Entity>::iterator it3 = asteroid->asteroids->begin(); it3 != asteroid->asteroids->end(); it3++) {
		if (it3->sprite->getColor() == Color::Red)
			it3->sprite->setColor(Color::White);
		for (list<Shoot>::iterator it = player->bullet->begin(); it != player->bullet->end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) {
				it3->health -= 3 * PLAYER_DAMAGE;
				it->life = false;
				it3->sprite->setColor(Color::Red);
			}
		}
	}

}

void Game::DrawObjects() { // Отрисовка объектов
	for (Entity it3 : *enemy->enemyShip)
		window->draw(*it3.sprite);
	for (Entity it2 : *asteroid->asteroids)
		window->draw(*it2.sprite);
	for (Shoot it : *player->bullet)
		window->draw(*it.sprite);
	if (player->ship->isLife) {
		window->draw(*player->ship->sprite);
	}
	else
		cout << "Player dead" << endl;
	//window.draw(*player.shape);
	for (Shoot it : *enemy->bulletEnemy)
		window->draw(*it.sprite);

}


