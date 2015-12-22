#include "Game.h"

using namespace sf;
using namespace std;

void InitializeGame(Game & game, SSound & sSound) {
	game.player = new Player;
	game.enemy = new Enemy;
	game.textInfo = new TextWithInfo;
	game.asteroid = new Asteroid;
	game.bonus = new Bonus;
	game.star = new Star;
	game.textureGame.LoadingFromFileTexture();
	InitializePlayer(*game.player, game.textureGame, sSound);
	InitializeText(*game.textInfo);
}

void Game::IncreaseCharacteristicsObjects() {
	if (player->point <= 0 ) { 
		if (player->levelGame == MAX_LEVEL_GAME) {
			enemy->bossState.isBoss = true;
		}
		else {
			enemy->damage += INCREASED_DAMAGE_ENEMY;
			enemy->health += INCREASED_HEALTH_ENEMY;
			countEnemy += INCREASED_COUNT_ENEMY;
			player->point = countEnemy;
			player->levelGame += 1;
			//-------- увеличение количества кораблей врагов
			enemy->numberEnemy.numberEasyEnemy += 1;
			if (player->levelGame >= 2)
				enemy->numberEnemy.numberMiddleEnemy += 1;
			if (player->levelGame >= 3 )
				enemy->numberEnemy.numberKamikaze += 1;
			if (player->levelGame >= 4)
				enemy->numberEnemy.numberTowerEnemy += 1;
			//---------- уменьшение времени появления враждебных объектов
			if (asteroid->timeToCreateAsteroid > 0.3f)
				asteroid->timeToCreateAsteroid -= DIFFERENT_TIME_CREATE_ASTEROID;
			if (enemy->timeToCreateEnemy > 0.3f)
				enemy->timeToCreateEnemy -= DIFFERENT_TIME_CREATE_ENEMY;
		}
	}
}

bool hasIntersection(Sprite & object1, Sprite & object2) {
	return object1.getGlobalBounds().intersects(object2.getGlobalBounds());
}

void Game::CheckForCollision(RenderWindow & window, const Time & deltaTime, TextureGame & textureGame) {
	//----------------- Окрашивает в белый цвет ----------------
	if (player->ship->sprite->getColor() == Color::Red)
		player->ship->sprite->setColor(Color::White);
	//----------------------------------------------------------
	for (auto &enemyShip : enemy->enemyShip) {
		//----------------- Окрашивает в белый цвет ----------------
		if (enemyShip.sprite->getColor() == Color::Red)
			enemyShip.sprite->setColor(Color::White);
		//----------------------- Обработка взаимодействия игрока и противников ------------------------------------
		if (hasIntersection(*player->ship->sprite, *enemyShip.sprite)) // столкновение игрока с врагом
		{
			if (enemyShip.health > 0) {
				if (!player->playerState.isInvulnerability) {
					player->ship->health -= enemyShip.damage;
					player->ship->sprite->setColor(Color::Red);
				}
			}
			if (player->ship->health > 0) {
				if (enemyShip.name == NAME_BOSS)
					player->ship->health = 0;
				else
					enemyShip.health = 0;
			}
		}
		Vector2f posEnemy = enemyShip.sprite->getPosition(),
			posPlayer = player->ship->sprite->getPosition();
		//----------------------------- враг стреляет -----------------------------------------------------
	  if (enemyShip.health > 0 && enemyShip.name != NAME_KAMIKAZE_ENEMY) {
			if (IsEnterField(posPlayer, enemyShip) && enemyShip.name == NAME_EASY_ENEMY) {
				enemy->AddBulletEnemy(enemyShip, posPlayer, textureGame.redLaserTexture, enemyShip.timeCreateBullet);
			}
			else if (enemyShip.name == NAME_TOWER_ENEMY || enemyShip.name == NAME_BOSS) {
				if (enemy->bossState.isRage && enemyShip.name == NAME_BOSS)
					SpecialShootingBoss(*enemy, enemyShip, textureGame);
				else if (enemyShip.name == NAME_TOWER_ENEMY)
					enemy->AddBulletEnemy(enemyShip, posPlayer, textureGame.rocketTexture, enemyShip.timeCreateBullet);
				else if (enemyShip.name == NAME_BOSS)
					enemy->AddBulletEnemy(enemyShip, posPlayer, textureGame.redLaserTexture, enemyShip.timeCreateBullet);
			}
			else if (IsSeePlayer(posPlayer, enemyShip, window.getSize()) && enemyShip.name == NAME_MIDDLE_ENEMY) { // враг стреляет
					
					enemy->AddBulletEnemy(enemyShip, posPlayer, textureGame.greenLaserTexture, enemyShip.timeCreateBullet);
					
			}
			
		}
		//------------------------------- Обработка попадания пули по врагу ----------------------------------------
		for (auto &playerullet : player->bullet) {
			if (hasIntersection(*playerullet.sprite, *enemyShip.sprite)) {
				if (!playerullet.isExplosion)
					enemyShip.health -= player->ship->damage;
				if (enemyShip.health > 0 && enemyShip.name != NAME_ELECTRIC_BULLET)
					playerullet.isExplosion = true;
				enemyShip.sprite->setColor(Color::Red);
				if (enemyShip.name == NAME_BOSS) {
					if (enemy->rage <= POINT_FOR_RAGE && !enemy->bossState.isRage) {
						enemy->rage += 5;
					}
					else {
						enemy->bossState.isRage = true;
					}
				}
			}
			/*if (it2.name == NAME_BOSS) {
				if (IsEnterField(Vector2f(it.sprite->getPosition()), it2)) { // Проверка на вхождение пули в область видимости
					//enemy->Evasion(Vector2f(it->sprite->getPosition()), *it2, window->getSize()); // Функция уклонения
				}
			}*/
		}
		//---------------------------- Обработка столкновения противника с астероидом ------------------------------
		for (auto &asteroid : asteroid->asteroids) {
			if (hasIntersection(*enemyShip.sprite, *asteroid.sprite)) // столкновение врага с астероидом
			{
				asteroid.health = 0;
			}
		}
	}
	
	// Обработка попадания пули по игроку
	for (auto &enemyBullet : enemy->bulletEnemy) {
		if (hasIntersection(*player->ship->sprite, *enemyBullet.sprite)) {
			if (!player->playerState.isInvulnerability) {
				if (!enemyBullet.isExplosion)
					player->ship->health -= enemy->damage;
				player->ship->sprite->setColor(Color::Red);
			}
			if (enemyBullet.name == NAME_ELECTRIC_BULLET) {
				player->playerState.isMove = false;
				player->direction = NONE;
				player->timeRecoveryMove = Time::Zero;
				enemy->bossState.isRage = false;
				enemy->rage = 0;
			}
			enemyBullet.isExplosion = true;
		}
		// Обработка попадания по ракете
		for (auto &playerBullet : player->bullet) {
			if (hasIntersection(*enemyBullet.sprite, *playerBullet.sprite)) {
				if (enemyBullet.name == NAME_ROCKET) {
					if (!playerBullet.isExplosion)
						enemyBullet.health -= playerBullet.damage;
					if (playerBullet.name != NAME_ELECTRIC_BULLET)
						playerBullet.isExplosion = true;
				}
			}
		}
	}
	// Обработка астеройдов
	for (auto &asteroid : asteroid->asteroids) {
		//----------------- Окрашивает в белый цвет ----------------
		if (asteroid.sprite->getColor() == Color::Red)
			asteroid.sprite->setColor(Color::White);
		//------------------------------ Обработка столкновения астероида с игроком ---------------------------------
		if (hasIntersection(*player->ship->sprite, *asteroid.sprite)) // столкновение игрока с врагом
		{
			if (asteroid.health > 0) {
				if (!player->playerState.isInvulnerability) {
					player->ship->health -= asteroid.damage;
					player->ship->sprite->setColor(Color::Red);
				}
			}
			asteroid.health = 0;
		}
		//------------------------------ Обработка попадания пули игрока по астероиду -------------------------------
		for (auto &playerBullet : player->bullet) {
			if (hasIntersection(*playerBullet.sprite, *asteroid.sprite)) {
				if (!playerBullet.isExplosion)
					asteroid.health -= 3 * player->ship->damage;
				if (asteroid.health > 0)
					playerBullet.isExplosion = true;
				asteroid.sprite->setColor(Color::Red);
			}
		}
		//------------------------------------ Обработка попадания пули врага по астероиду --------------------------
		for (auto &enemyBullet : enemy->bulletEnemy) {
			if (hasIntersection(*enemyBullet.sprite, *asteroid.sprite)) {
				if (!enemyBullet.isExplosion)
					asteroid.health -= 3 * enemy->damage;
				enemyBullet.isExplosion = true;
				asteroid.sprite->setColor(Color::Red);
			}
		}
	}
	// Обработка подбирания бонусов
	for (auto &bonus : bonus->bonuses) {
		if (hasIntersection(*player->ship->sprite, *bonus.sprite) && player->ship->health > 0) {
			player->takeBonus.play();
			if (bonus.name == REPAIR_IMAGE) {
				player->playerState.isRepair = true;
			}
			if (bonus.name == INVULNERABILITY_IMAGE) {
				player->playerState.isInvulnerability = true;
				player->playerState.isDecrease = false;
				player->playerState.isIncreaseDamage = false;
			}
			if (bonus.name == INCREASE_DAMAGE_IMAGE) {
				player->playerState.isIncreaseDamage = true;
				player->playerState.isInvulnerability = false;
				player->playerState.isDecrease = false;
			}
			if (bonus.name == DECREASE_IMAGE) {
				player->playerState.isIncreaseDamage = false;
				player->playerState.isInvulnerability = false;
				player->playerState.isDecrease = true;
			}
			if (bonus.name == BOMB_IMAGE) {
				player->playerState.isBomb = true;
			}
			
			bonus.isLife = false;
			
		}
	}
}

void Game::UseBonus(const Time & deltaTime, TextureGame & textureGame){ 
	PlayerState & playerState = player->playerState;
	if (playerState.isRepair) { // восстановление здоровья
		player->ship->health = float(player->maxHealth);
		playerState.isRepair = false;
	}
	if (playerState.isInvulnerability) { // неуязвимость
		timeUseBonus += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Blue);
		if (timeUseBonus > TIME_USE_INVULNERABILITY_IN_SECONDS) {
			player->ship->sprite->setColor(Color::White);
			playerState.isInvulnerability = false;
			timeUseBonus = 0;
		}
	}
	if (playerState.isDecrease) { // уменьшение размеров
		timeUseBonus += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Yellow);
		player->ship->sprite->setScale(0.5, 0.5);
		if (timeUseBonus > TIME_USE_DECREASE_IN_SECONDS) {
			player->ship->sprite->setColor(Color::White);
			playerState.isDecrease = false;
			timeUseBonus = 0;
		}
	}
	else {
		player->ship->sprite->setScale(1, 1);
	}
	
	if (playerState.isIncreaseDamage) { // увеличение урона
		timeUseBonus += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Magenta);
		player->scaleBullet = 3;
		player->ship->damage = float(player->maxDamage) * 3;
		if (timeUseBonus > TIME_USE_INCREASE_IN_SECONDS) {
			player->ship->sprite->setColor(Color::White);
			playerState.isIncreaseDamage = false;
			timeUseBonus = 0;
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

void processEventsGame(Game & game, Event & event, RenderWindow & window)
{
	Player & player = *game.player;
	Control(player, event);
	
	//--------------------------- Выстрел --------------------------
	if (player.ship->health > 0) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			player.playerState.isShoot = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.playerState.isShoot = true;
		}
	}
	//------------------------- Пауза -------------------------------
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {  //  Поставить на паузу или снять с паузы игру
		if (!game.isPause) {
			game.isPause = true;
		}
		else {
			game.isPause = false;
		}
	}
	//--------------------------------------------------------------
	
}

void updateGame(Game & game, const Time & deltaTime, RenderWindow & window, GlobalBool & globalBool, SSound & sSound)
{
	if (!game.isPause && game.player->ship->isLife) {
		Player & player = *game.player;
		Enemy & enemy = *game.enemy;
		Asteroid & asteroid = *game.asteroid;
		Bonus & bonus = *game.bonus;
		Star & star = *game.star;
		PlayerState & playerState = player.playerState;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		//--------------- Функции игры ---------------------

		game.IncreaseCharacteristicsObjects();
		game.CheckForCollision(window, deltaTime, game.textureGame);
		game.UseBonus(deltaTime, game.textureGame);
		//---------------- Интерфейс -----------------------
		UpdateTextWithHealth(*game.textInfo, *game.player, window);
		//---------------- Функции звезд -------------------
		//LoadStarInList(star, deltaTime, window, *game.textureGame); // добавить загрузочный экран
		star.AddStar(game.textureGame, window, sSound);
		star.UpdateStateStar(deltaTime, window);
		//---------------- Функции игрока ------------------
		Vector2f posPlayer = player.ship->sprite->getPosition();
		if (player.ship->health <= 0) {
			player.ship->direction = NONE;
			player.ship->Explosion(deltaTime, game.textureGame.explosionTexture);
			player.PlaySoundAtDead();
		}
		else {
			MovePlayer(player, deltaTime, window); // задает координаты движения
			player.ship->sprite->move(Border(*player.ship, window));
			player.ChangeWeapons(game.textureGame, pos);
			player.ship->SetRotationObject(pos);
			player.RecoveryMove();
			UpdateVolume(player.takeBonus, SIZE_VOLUME_TAKE_BONUS);
			UpdateVolume(player.ship->shootSound, SIZE_VOLUME_SHOOT);
		}
		UpdateStateBullet(deltaTime, window, player.bullet, game.textureGame, posPlayer);
		//---------------- Функции противников -------------
		enemy.UpdateStateEveryEnemy(deltaTime, window, bonus, game.textureGame, posPlayer, player.point, sSound);
		enemy.AddEnemy(game.textureGame, window, sSound);
		enemy.CalmBoss();
		UpdateStateBullet(deltaTime, window, enemy.bulletEnemy, game.textureGame, posPlayer);
		//--------------- Функции астероидов ---------------
		if (!enemy.bossState.isBoss)
			asteroid.AddAsteroid(game.textureGame, window, sSound);
		asteroid.GetMoveEveryAsteroid(deltaTime, window, bonus, game.textureGame, sSound);
		//---------------- Функции бонусов -----------------
		bonus.GetMoveEveryBonus(deltaTime, window);
	}
}

void renderGame(RenderWindow & window, Game & game) {
	window.clear();
	//if (!game.gameState.isLoading) {
	game.DrawObjects(window);
	DrawTextToGame(*game.textInfo, window);
	//}
	if (!game.player->ship->isLife) {
		OutputMessageAboutLosing(window, *game.textInfo);
	}
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
	game.timeUseBonus = 0;
	game.player->point = POINT_FOR_ADVANCE;
	game.asteroid->timeToCreateAsteroid = TIME_CREATE_ASTEROID;
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