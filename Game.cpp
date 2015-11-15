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
	//----------------- ќкрашивает в белый цвет ----------------
	for (list<Entity>::iterator it2 = enemy->enemyShip->begin(); it2 != enemy->enemyShip->end(); it2++) {
		if (it2->sprite->getColor() == Color::Red)
			it2->sprite->setColor(Color::White);
	}

	for (list<Entity>::iterator it3 = asteroid->asteroids->begin(); it3 != asteroid->asteroids->end(); it3++) {
		if (it3->sprite->getColor() == Color::Red)
			it3->sprite->setColor(Color::White);
	}
	if (player->ship->sprite->getColor() == Color::Red)
		player->ship->sprite->setColor(Color::White);
	//----------------------------------------------------------

	// ќбработка взаимодействи€ игрока и противников
	for (list<Entity>::iterator it2 = enemy->enemyShip->begin(); it2 != enemy->enemyShip->end(); it2++) {
		if(player->ship->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds())) // столкновение игрока с врагом
		{
			if (it2->health > 0) {
				player->ship->health -= it2->damage;
				player->ship->sprite->setColor(Color::Red);
			}
			it2->health = 0;
		}
		Vector2f posEnemy = it2->sprite->getPosition(),
			posPlayer = player->ship->sprite->getPosition();
		if (IsEnterField(posPlayer, *it2)) { // враг стрел€ет
			if (it2->health > 0) {
				enemy->AddBulletEnemy(posEnemy, it2->direction, *it2);
			}
		}
	}
	
	// ќбработка попадани€ пули по игроку
	for (list<Shoot>::iterator it = enemy->bulletEnemy->begin(); it != enemy->bulletEnemy->end(); it++) {
		if (player->ship->sprite->getGlobalBounds().intersects(it->sprite->getGlobalBounds())) {
			player->ship->health -= ENEMY_DAMAGE;
			it->life = false;
			player->ship->sprite->setColor(Color::Red);
		}
	}
	
	// ќбработка попадани€ пули по врагу
	for (list<Entity>::iterator it2 = enemy->enemyShip->begin(); it2 != enemy->enemyShip->end(); it2++) {
		for (list<Shoot>::iterator it = player->bullet->begin(); it != player->bullet->end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds()))	{
				it2->health -= player->ship->damage;
				it->life = false;
				it2->sprite->setColor(Color::Red);
			}
		}
	}

	// ќбработка столкновени€ астероида с игроком
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

	// ќбработка попадани€ пули игрока по астероиду
	for (list<Entity>::iterator it3 = asteroid->asteroids->begin(); it3 != asteroid->asteroids->end(); it3++) {
		for (list<Shoot>::iterator it = player->bullet->begin(); it != player->bullet->end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) {
				it3->health -= 3 * player->ship->damage;
				it->life = false;
				it3->sprite->setColor(Color::Red);
			}
		}
	}

	// ќбработка попадани€ пули врага по астероиду
	for (list<Entity>::iterator it3 = asteroid->asteroids->begin(); it3 != asteroid->asteroids->end(); it3++) {
		for (list<Shoot>::iterator it = enemy->bulletEnemy->begin(); it != enemy->bulletEnemy->end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) {
				it3->health -= 3 * ENEMY_DAMAGE;
				it->life = false;
				it3->sprite->setColor(Color::Red);
			}
		}
	}

	// ќбработка столкновени€ противника с астероидом
	for (list<Entity>::iterator it2 = enemy->enemyShip->begin(); it2 != enemy->enemyShip->end(); it2++) {
		for (list<Entity>::iterator it3 = asteroid->asteroids->begin(); it3 != asteroid->asteroids->end(); it3++) {
			if (it2->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) // столкновение врага с астероидом
			{
				if (it3->health > 0) {
					it2->health -= ENEMY_DAMAGE;
					it2->sprite->setColor(Color::Red);
				}
				it3->health = 0;
			}
		}
	}

}

void Game::DrawObjects() { // ќтрисовка объектов
	for (Entity it3 : *enemy->enemyShip) // противники
		window->draw(*it3.sprite);
	for (Entity it2 : *asteroid->asteroids) // астероиды
		window->draw(*it2.sprite);
	for (Shoot it : *player->bullet) // пули игрока
		window->draw(*it.sprite);
	if (player->ship->isLife) {
		window->draw(*player->ship->sprite); // отрисовываетс€ игрок пока он жив
	}
	else {  // это на врем€, пока не сделаю меню
		cout << "Player dead" << endl;
		exit(1);
	}
	//window.draw(*player.shape);
	for (Shoot it : *enemy->bulletEnemy) // отрисовка вражеских пуль
		window->draw(*it.sprite);

}


