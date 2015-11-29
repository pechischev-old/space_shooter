#include "Game.h"


using namespace sf;
using namespace std;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.enemy = new Enemy;
	game.window = new RenderWindow(VideoMode(SCRN_WIDTH, SCRN_HEIGTH), TITLE_GAME);
	game.textInfo = new TextWithInfo;
	game.asteroid = new Asteroid;
	game.bonus = new Bonus;
	game.star = new Star;
	game.textureGame.LoadingFromFileTexture();
	InitializePlayer(*game.player, game.textureGame);
	InitializeText(*game.textInfo);
}

void Game::IncreaseCharacteristicsObjects() {
	if ( player->point / POINT_FOR_ADVANCE == oldOrder + 1) { // переделать диапозон очков
		enemy->damage += 15;
		enemy->health += 30;
		oldOrder += 1;
		enemy->isBoss = true;
		cout << "Enemy stand hard " << endl;
	}
}

void Game::CheckForCollision() {
	//----------------- Окрашивает в белый цвет ----------------
	if (player->ship->sprite->getColor() == Color::Red)
		player->ship->sprite->setColor(Color::White);
	//----------------------------------------------------------

	for (list<Entity>::iterator it2 = enemy->enemyShip.begin(); it2 != enemy->enemyShip.end(); ++it2) {
		//----------------- Окрашивает в белый цвет ----------------
		if (it2->sprite->getColor() == Color::Red)
			it2->sprite->setColor(Color::White);
		//----------------------- Обработка взаимодействия игрока и противников ------------------------------------
		if(player->ship->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds())) // столкновение игрока с врагом
		{
			if (it2->health > 0) {
				if (!player->playerState.isInvulnerability) {
					player->ship->health -= it2->damage;
					player->ship->sprite->setColor(Color::Red);
				}
			}
			if (player->ship->health > 0) {
				if (it2->name == NAME_BOSS)
					player->ship->health = 0;
				else 
					it2->health = 0;
			}
		}
		Vector2f posEnemy = it2->sprite->getPosition(),
			posPlayer = player->ship->sprite->getPosition();
		if (IsEnterField(posPlayer, *it2) && it2->name == NAME_EASY_ENEMY) { // враг стреляет
			if (it2->health > 0) {
				enemy->AddBulletEnemy(posEnemy, it2->direction, *it2, posPlayer, textureGame);
			}
		}
		if (IsSeePlayer(posPlayer, *it2, window->getSize()) && it2->name != NAME_EASY_ENEMY) { // враг стреляет
			if (it2->health > 0) {
				enemy->AddBulletEnemy(posEnemy, it2->direction, *it2, posPlayer, textureGame);

			}
		}
		//------------------------------- Обработка попадания пули по врагу ----------------------------------------
		for (list<Shoot>::iterator it = player->bullet.begin(); it != player->bullet.end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds())) {
				it2->health -= player->ship->damage;
				if (it2->health > 0)
					it->life = false;
				it2->sprite->setColor(Color::Red);
			}
			if (it2->name == NAME_BOSS) {
				if (IsEnterField(Vector2f(it->sprite->getPosition()), *it2)) { // Проверка на вхождение пули в область видимости
					enemy->Evasion(Vector2f(it->sprite->getPosition()), *it2, window->getSize()); // Функция уклонения
				}
			}
		}
		//---------------------------- Обработка столкновения противника с астероидом ------------------------------
		for (list<Entity>::iterator it3 = asteroid->asteroids.begin(); it3 != asteroid->asteroids.end(); ++it3) {
			if (it2->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) // столкновение врага с астероидом
			{
				if (it3->health > 0) {

					it2->health -= it2->damage;
					it2->sprite->setColor(Color::Red);
				}
				it3->health = 0;
			}
		}
	}
	
	// Обработка попадания пули по игроку
	for (list<Shoot>::iterator it = enemy->bulletEnemy.begin(); it != enemy->bulletEnemy.end(); ++it) {
		if (player->ship->sprite->getGlobalBounds().intersects(it->sprite->getGlobalBounds())) {
			if (!player->playerState.isInvulnerability) {
				player->ship->health -= enemy->damage;
				player->ship->sprite->setColor(Color::Red);
			}
			it->life = false;
		}
	}

	for (list<Entity>::iterator it3 = asteroid->asteroids.begin(); it3 != asteroid->asteroids.end(); ++it3) {
		//----------------- Окрашивает в белый цвет ----------------
		if (it3->sprite->getColor() == Color::Red)
			it3->sprite->setColor(Color::White);
		//------------------------------ Обработка столкновения астероида с игроком ---------------------------------
		if (player->ship->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) // столкновение игрока с врагом
		{
			if (it3->health > 0) {
				if (!player->playerState.isInvulnerability) {
					player->ship->health -= enemy->damage;
					player->ship->sprite->setColor(Color::Red);
				}
			}
			it3->health = 0;
		}
		//------------------------------ Обработка попадания пули игрока по астероиду -------------------------------
		for (list<Shoot>::iterator it = player->bullet.begin(); it != player->bullet.end(); ++it) {
			if (it->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) {
				it3->health -= 3 * player->ship->damage;
				if (it3->health > 0)
					it->life = false;
				it3->sprite->setColor(Color::Red);
			}
		}
		//------------------------------------ Обработка попадания пули врага по астероиду --------------------------
		for (list<Shoot>::iterator it = enemy->bulletEnemy.begin(); it != enemy->bulletEnemy.end(); ++it) {
			if (it->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) {
				it3->health -= 3 * enemy->damage;
				it->life = false;
				it3->sprite->setColor(Color::Red);
			}
		}
	}
	// Обработка подбирания бонусов
	for (list<Entity>::iterator it4 = bonus->bonuses.begin(); it4 != bonus->bonuses.end(); ++it4) {
		if (player->ship->sprite->getGlobalBounds().intersects(it4->sprite->getGlobalBounds())) {
			if (it4->name == REPAIR_IMAGE) {
				player->playerState.isRepair = true;
			}
			if (it4->name == INVULNERABILITY_IMAGE) {
				player->playerState.isInvulnerability = true;
				player->playerState.isDecrease = false;
				player->playerState.isIncreaseDamage = false;
			}
			if (it4->name == INCREASE_DAMAGE_IMAGE) {
				player->playerState.isIncreaseDamage = true;
				player->playerState.isInvulnerability = false;
				player->playerState.isDecrease = false;
			}
			if (it4->name == DECREASE_IMAGE) {
				player->playerState.isIncreaseDamage = false;
				player->playerState.isInvulnerability = false;
				player->playerState.isDecrease = true;
			}
			if (it4->name == BOMB_IMAGE) {
				player->playerState.isBomb = true;
			}
			it4->isLife = false;
		}
	}
}

void Game::UseBonus(const Time & deltaTime){
	PlayerState & playerState = player->playerState;
	if (playerState.isRepair) {
		player->ship->health = float(player->maxHealth);
		playerState.isRepair = false;
	}
	if (playerState.isInvulnerability) {
		timeGame += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Blue);
		if (timeGame > 30) {
			player->ship->sprite->setColor(Color::White);
			playerState.isInvulnerability = false;
			timeGame = 0;
		}
	}
	if (playerState.isDecrease) { // уменьшение размеров
		timeGame += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Yellow);
		player->ship->sprite->setScale(0.5, 0.5);
		if (timeGame > 15) {
			player->ship->sprite->setColor(Color::White);
			playerState.isDecrease = false;
			timeGame = 0;
		}
	}
	else {
		player->ship->sprite->setScale(1, 1);
	}
	
	if (playerState.isIncreaseDamage) { // увеличение урона
		timeGame += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Magenta);
		player->scaleBullet = 3;
		player->ship->damage = float(player->maxDamage) * 3;
		if (timeGame > 20) {
			player->ship->sprite->setColor(Color::White);
			playerState.isIncreaseDamage = false;
			timeGame = 0;
		}
	}
	else {
		player->ship->damage = float(player->maxDamage);
		player->scaleBullet = 2;
	}
	if (playerState.isBomb) {
		for (list<Entity>::iterator it2 = enemy->enemyShip.begin(); it2 != enemy->enemyShip.end(); ++it2) {
			if (it2->name != NAME_BOSS)
				it2->health = 0;
		}
		for (list<Entity>::iterator it3 = asteroid->asteroids.begin(); it3 != asteroid->asteroids.end(); ++it3) {
			it3->health = 0;
		}
		playerState.isBomb = false;
	}
}

void Game::DrawObjects() { // Отрисовка объектов
	for (Entity it : star->stars)
		window->draw(*it.sprite);
	for (Shoot it : player->bullet) // пули игрока
		window->draw(*it.sprite);
	for (Shoot it : enemy->bulletEnemy) // отрисовка вражеских пуль
		window->draw(*it.sprite);
	for (Entity it3 : enemy->enemyShip) // противники
		window->draw(*it3.sprite);
	for (Entity it2 : asteroid->asteroids) // астероиды
		window->draw(*it2.sprite);
	for (Entity it4 : bonus->bonuses)
		window->draw(*it4.sprite);
	if (player->ship->isLife) {
		window->draw(*player->ship->sprite); // отрисовывается игрок пока он жив
	}
	else {  // это на время, пока не сделаю меню
		cout << "Player dead" << endl;
		window->close();
	}
}

void Delete(Game & game) {
	delete game.star;
	delete game.bonus;
	delete game.asteroid;
	delete game.enemy;
	delete game.player;
	delete game.textInfo;
	delete game.window;	
}


