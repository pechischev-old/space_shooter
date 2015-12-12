#include "Game.h"

using namespace sf;
using namespace std;

void InitializeGame(Game & game) {
	game.player = new Player;
	game.enemy = new Enemy;
	game.textInfo = new TextWithInfo;
	game.asteroid = new Asteroid;
	game.bonus = new Bonus;
	game.star = new Star;
	game.textureGame.LoadingFromFileTexture();
	InitializePlayer(*game.player, game.textureGame);
	InitializeText(*game.textInfo);
}

void Game::IncreaseCharacteristicsObjects() {
	if (player->point == 0 ) { // переделать диапозон очков
		enemy->damage += 15;
		enemy->health += 30;
		countEnemy += 10;
		player->point = countEnemy;
		player->levelGame += 1;
		//-------- увеличение количества кораблей врагов
		enemy->numberEnemy.numberEasyEnemy += 1;
		enemy->numberEnemy.numberKamikaze += 1;
		enemy->numberEnemy.numberMiddleEnemy += 1;
		enemy->numberEnemy.numberTowerEnemy += 1;
		//---------- уменьшение времени появления враждебных объектов
		if (asteroid->timeToCreateAsteroid > 0.3)
			asteroid->timeToCreateAsteroid -= 0.07f;
		if (enemy->timeToCreateEnemy > 0.3)
			enemy->timeToCreateEnemy -= 0.1f;
		if (player->levelGame == MAX_LEVEL_GAME)
			enemy->bossState.isBoss = true;
	}
}

void Game::CheckForCollision(RenderWindow & window, const Time & deltaTime, TextureGame & textureGame) {
	//----------------- Окрашивает в белый цвет ----------------
	if (player->ship->sprite->getColor() == Color::Red)
		player->ship->sprite->setColor(Color::White);
	//----------------------------------------------------------
	for (list<Entity>::iterator it2 = enemy->enemyShip.begin(); it2 != enemy->enemyShip.end(); ++it2) {
		//----------------- Окрашивает в белый цвет ----------------
		if (it2->sprite->getColor() == Color::Red)
			it2->sprite->setColor(Color::White);
		//----------------------- Обработка взаимодействия игрока и противников ------------------------------------
		if (player->ship->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds())) // столкновение игрока с врагом
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
		//----------------------------- враг стреляет -----------------------------------------------------
	  if (it2->health > 0 && it2->name != NAME_KAMIKAZE_ENEMY) {
			if (IsEnterField(posPlayer, *it2) && it2->name == NAME_EASY_ENEMY) {

				enemy->AddBulletEnemy(*it2, posPlayer, textureGame.redLaserTexture, it2->timeCreateBullet);
			}

			else if (IsSeePlayer(posPlayer, *it2, window.getSize()) && it2->name != NAME_EASY_ENEMY && it2->name != NAME_TOWER_ENEMY) { // враг стреляет
					if (!enemy->bossState.isRage) // переделать условие
						enemy->AddBulletEnemy(*it2, posPlayer, textureGame.redLaserTexture, it2->timeCreateBullet);
					else if (enemy->bossState.isRage && it2->name == NAME_BOSS)
						SpecialShootingBoss(*enemy, *it2, textureGame);
			}
			else if (it2->name == NAME_TOWER_ENEMY) {
					enemy->AddBulletEnemy(*it2, posPlayer, textureGame.rocketTexture, it2->timeCreateBullet);
			}
		}
		//------------------------------- Обработка попадания пули по врагу ----------------------------------------
		for (list<Shoot>::iterator it = player->bullet.begin(); it != player->bullet.end(); it++) {
			if (it->sprite->getGlobalBounds().intersects(it2->sprite->getGlobalBounds())) {
				if (!it->isExplosion)
					it2->health -= player->ship->damage;
				if (it2->health > 0)
					it->isExplosion = true;
				it2->sprite->setColor(Color::Red);
				if (it2->name == NAME_BOSS) {
					if (enemy->rage <= POINT_FOR_RAGE && !enemy->bossState.isRage) {
						enemy->rage += 5;
					}
					else {
						enemy->bossState.isRage = true;
					}
				}
			}
			if (it2->name == NAME_BOSS) {
				if (IsEnterField(Vector2f(it->sprite->getPosition()), *it2)) { // Проверка на вхождение пули в область видимости
					//enemy->Evasion(Vector2f(it->sprite->getPosition()), *it2, window->getSize()); // Функция уклонения
				}
			}
		}
		//---------------------------- Обработка столкновения противника с астероидом ------------------------------
		for (list<Entity>::iterator it3 = asteroid->asteroids.begin(); it3 != asteroid->asteroids.end(); ++it3) {
			if (it2->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) // столкновение врага с астероидом
			{
				it3->health = 0;
			}
		}
	}
	
	// Обработка попадания пули по игроку
	for (list<Shoot>::iterator it = enemy->bulletEnemy.begin(); it != enemy->bulletEnemy.end(); ++it) {
		if (player->ship->sprite->getGlobalBounds().intersects(it->sprite->getGlobalBounds())) {
			if (!player->playerState.isInvulnerability) {
				if (!it->isExplosion)
					player->ship->health -= enemy->damage;
				player->ship->sprite->setColor(Color::Red);
			}
			if (it->name == NAME_ELECTRIC_BULLET) {
				player->playerState.isMove = false;
				player->direction = NONE;
				player->timeRecoveryMove = Time::Zero;
				enemy->bossState.isRage = false;
				enemy->rage = 0;
			}
			it->isExplosion = true;
		}
		// Обработка попадания по ракете
		for (list<Shoot>::iterator playerBullet = player->bullet.begin(); playerBullet != player->bullet.end(); ++playerBullet) {
			if (it->sprite->getGlobalBounds().intersects(playerBullet->sprite->getGlobalBounds())) {
				if (it->name == NAME_ROCKET) {
					it->isExplosion = true;
					playerBullet->isExplosion = true;
				}
			}
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
				if (!it->isExplosion)
					it3->health -= 3 * player->ship->damage;
				if (it3->health > 0)
					it->isExplosion = true;
				it3->sprite->setColor(Color::Red);
			}
		}
		//------------------------------------ Обработка попадания пули врага по астероиду --------------------------
		for (list<Shoot>::iterator it = enemy->bulletEnemy.begin(); it != enemy->bulletEnemy.end(); ++it) {
			if (it->sprite->getGlobalBounds().intersects(it3->sprite->getGlobalBounds())) {
				if (!it->isExplosion)
					it3->health -= 3 * enemy->damage;
				it->isExplosion = true;
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

void Game::DrawObjects(RenderWindow & window) { // Отрисовка объектов
	for (Entity it : star->stars)
		window.draw(*it.sprite);
	for (Entity it3 : enemy->enemyShip) // противники
		window.draw(*it3.sprite);
	for (Entity it2 : asteroid->asteroids) // астероиды
		window.draw(*it2.sprite);
	for (Entity it4 : bonus->bonuses) // бонусы
		window.draw(*it4.sprite);
	if (player->ship->isLife) {
		window.draw(*player->ship->sprite); // отрисовывается игрок пока он жив
	}
	for (Shoot it : player->bullet) // пули игрока
		window.draw(*it.sprite);
	for (Shoot it : enemy->bulletEnemy) // отрисовка вражеских пуль
		window.draw(*it.sprite);
}

void processEventsGame(Game & game, GlobalBool & globalBool, Event & event)
{
	Player & player = *game.player;
	Control(player);
	//--------------------------- Выстрел --------------------------
	if (player.ship->health > 0) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			player.playerState.isShoot = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.playerState.isShoot = true;
		}
	}
	//--------------------------------------------------------------
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		globalBool.g_isMenu = true;
}

void updateGame(Game & game, const Time & deltaTime, RenderWindow & window, GlobalBool & globalBool)
{
	Player & player = *game.player;
	Enemy & enemy = *game.enemy;
	Asteroid & asteroid = *game.asteroid;
	Bonus & bonus = *game.bonus;
	Star & star = *game.star;
	PlayerState & playerState = player.playerState;

	//--------------- Функции игры ---------------------

	game.IncreaseCharacteristicsObjects();
	game.CheckForCollision(window, deltaTime, game.textureGame);
	game.UseBonus(deltaTime);
	//---------------- Интерфейс -----------------------
	UpdateTextWithHealth(*game.textInfo, *game.player, window);
	//---------------- Функции звезд -------------------
	//LoadStarInList(star, deltaTime, window, *game.textureGame); // добавить загрузочный экран
	star.AddStar(game.textureGame);
	star.UpdateStateStar(deltaTime, window);
	//---------------- Функции игрока ------------------
	Vector2f posPlayer = player.ship->sprite->getPosition();
	if (player.ship->health <= 0) {
		player.ship->direction = NONE;
		player.ship->Explosion(deltaTime, game.textureGame.explosionTexture);
	}
	else {
		MovePlayer(player, deltaTime); // задает координаты движения
		player.ship->sprite->move(Border(*player.ship, window));
		player.AddBullet(game.textureGame);
		player.RecoveryMove();
		UpdateStateBullet(deltaTime, window, player.bullet, game.textureGame, posPlayer);
	}
	if (!player.ship->isLife && !globalBool.g_isRestart) {
		globalBool.g_isPause = true;
	}
	else {
		globalBool.g_isPause = false;
	}
	
	//---------------- Функции противников -------------
	enemy.UpdateStateEveryEnemy(deltaTime, window, bonus, game.textureGame, posPlayer, player.point);
	enemy.AddEnemy(game.textureGame);
	enemy.CalmBoss();
	UpdateStateBullet(deltaTime, window, enemy.bulletEnemy, game.textureGame, posPlayer);
	//--------------- Функции астероидов ---------------
	if (!enemy.bossState.isBoss)
		asteroid.AddAsteroid(game.textureGame);
	asteroid.GetMoveEveryAsteroid(deltaTime, window, bonus, game.textureGame);
	//---------------- Функции бонусов -----------------
	bonus.GetMoveEveryBonus(deltaTime, window);
}

void renderGame(RenderWindow & window, Game & game)
{
	window.clear();
	//if (!game.gameState.isLoading) {
	game.DrawObjects(window);
	DrawTextToGame(*game.textInfo, window);
	//}
	window.display();
}

void ResetGame(Game & game) {
	ClearList(game.player->bullet);
	ClearList(game.enemy->bulletEnemy);
	ClearListObject(game.enemy->enemyShip);
	ClearListObject(game.asteroid->asteroids);
	ClearListObject(game.bonus->bonuses);
	ResetPlayer(*game.player, game.textureGame);
	ResetEnemy(*game.enemy);
	game.timeGame = 0;
	game.player->point = POINT_FOR_ADVANCE;
}

void Delete(Game & game) {
	ClearList(game.player->bullet);
	ClearList(game.enemy->bulletEnemy);
	ClearListObject(game.enemy->enemyShip);
	ClearListObject(game.asteroid->asteroids);
	ClearListObject(game.bonus->bonuses);
	ClearListObject(game.star->stars);
	delete game.star;
	delete game.bonus;
	delete game.asteroid;
	delete game.enemy;
	delete game.player;
	delete game.textInfo;
	
}