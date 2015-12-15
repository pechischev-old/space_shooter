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
	srand(unsigned int(time(NULL)));
	game.textureGame.LoadingFromFileTexture();
	InitializePlayer(*game.player, game.textureGame);
	InitializeText(*game.textInfo);
}

void Game::IncreaseCharacteristicsObjects() {
	if (player->point <= 0 ) { 
		if (player->levelGame == MAX_LEVEL_GAME) {
			enemy->bossState.isBoss = true;
		}
		else {
			// ������� � ��������� ��� �����
			enemy->damage += 15;
			enemy->health += 30;
			countEnemy += 10;
			player->point = countEnemy;
			player->levelGame += 1;
			player->ship->health = float(player->maxHealth); // �������������� ��������
			//-------- ���������� ���������� �������� ������
			enemy->numberEnemy.numberEasyEnemy += 1;
			if (player->levelGame >= 2)
				enemy->numberEnemy.numberMiddleEnemy += 1;
			if (player->levelGame >= 3 )
				enemy->numberEnemy.numberKamikaze += 1;
			if (player->levelGame >= 4)
				enemy->numberEnemy.numberTowerEnemy += 1;
			//---------- ���������� ������� ��������� ���������� ��������
			if (asteroid->timeToCreateAsteroid > 0.3)
				asteroid->timeToCreateAsteroid -= 0.07f;
			if (enemy->timeToCreateEnemy > 0.3)
				enemy->timeToCreateEnemy -= 0.1f;
		}
	}
}

bool hasIntersection(Sprite & object1, Sprite & object2) {
	return object1.getGlobalBounds().intersects(object2.getGlobalBounds());
}

void Game::CheckForCollision(RenderWindow & window, const Time & deltaTime, TextureGame & textureGame) {
	//----------------- ���������� � ����� ���� ----------------
	if (player->ship->sprite->getColor() == Color::Red)
		player->ship->sprite->setColor(Color::White);
	//----------------------------------------------------------
	for (auto &enemyShip : enemy->enemyShip) {
		//----------------- ���������� � ����� ���� ----------------
		if (enemyShip.sprite->getColor() == Color::Red)
			enemyShip.sprite->setColor(Color::White);
		//----------------------- ��������� �������������� ������ � ����������� ------------------------------------
		if (hasIntersection(*player->ship->sprite, *enemyShip.sprite)) // ������������ ������ � ������
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
		//----------------------------- ���� �������� -----------------------------------------------------
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
			else if (IsSeePlayer(posPlayer, enemyShip, window.getSize()) && enemyShip.name == NAME_MIDDLE_ENEMY) { // ���� ��������
					
					enemy->AddBulletEnemy(enemyShip, posPlayer, textureGame.greenLaserTexture, enemyShip.timeCreateBullet);
					
			}
			
		}
		//------------------------------- ��������� ��������� ���� �� ����� ----------------------------------------
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
				if (IsEnterField(Vector2f(it.sprite->getPosition()), it2)) { // �������� �� ��������� ���� � ������� ���������
					//enemy->Evasion(Vector2f(it->sprite->getPosition()), *it2, window->getSize()); // ������� ���������
				}
			}*/
		}
		//---------------------------- ��������� ������������ ���������� � ���������� ------------------------------
		for (auto &asteroid : asteroid->asteroids) {
			if (hasIntersection(*enemyShip.sprite, *asteroid.sprite)) // ������������ ����� � ����������
			{
				asteroid.health = 0;
			}
		}
	}
	
	// ��������� ��������� ���� �� ������
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
		// ��������� ��������� �� ������
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
	// ��������� ����������
	for (auto &asteroid : asteroid->asteroids) {
		//----------------- ���������� � ����� ���� ----------------
		if (asteroid.sprite->getColor() == Color::Red)
			asteroid.sprite->setColor(Color::White);
		//------------------------------ ��������� ������������ ��������� � ������� ---------------------------------
		if (hasIntersection(*player->ship->sprite, *asteroid.sprite)) // ������������ ������ � ������
		{
			if (asteroid.health > 0) {
				if (!player->playerState.isInvulnerability) {
					player->ship->health -= asteroid.damage;
					player->ship->sprite->setColor(Color::Red);
				}
			}
			asteroid.health = 0;
		}
		//------------------------------ ��������� ��������� ���� ������ �� ��������� -------------------------------
		for (auto &playerBullet : player->bullet) {
			if (hasIntersection(*playerBullet.sprite, *asteroid.sprite)) {
				if (!playerBullet.isExplosion)
					asteroid.health -= 3 * player->ship->damage;
				if (asteroid.health > 0)
					playerBullet.isExplosion = true;
				asteroid.sprite->setColor(Color::Red);
			}
		}
		//------------------------------------ ��������� ��������� ���� ����� �� ��������� --------------------------
		for (auto &enemyBullet : enemy->bulletEnemy) {
			if (hasIntersection(*enemyBullet.sprite, *asteroid.sprite)) {
				if (!enemyBullet.isExplosion)
					asteroid.health -= 3 * enemy->damage;
				enemyBullet.isExplosion = true;
				asteroid.sprite->setColor(Color::Red);
			}
		}
	}
	// ��������� ���������� �������
	for (auto &bonus : bonus->bonuses) {
		if (hasIntersection(*player->ship->sprite, *bonus.sprite)) {
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
	if (playerState.isRepair) {
		player->ship->health = float(player->maxHealth);
		playerState.isRepair = false;
	}
	if (playerState.isInvulnerability) {
		timeUseBonus += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Blue);
		if (timeUseBonus > 30) {
			player->ship->sprite->setColor(Color::White);
			playerState.isInvulnerability = false;
			timeUseBonus = 0;
		}
	}
	if (playerState.isDecrease) { // ���������� ��������
		timeUseBonus += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Yellow);
		player->ship->sprite->setScale(0.5, 0.5);
		if (timeUseBonus > 15) {
			player->ship->sprite->setColor(Color::White);
			playerState.isDecrease = false;
			timeUseBonus = 0;
		}
	}
	else {
		player->ship->sprite->setScale(1, 1);
	}
	
	if (playerState.isIncreaseDamage) { // ���������� �����
		timeUseBonus += 1 * deltaTime.asSeconds();
		player->ship->sprite->setColor(Color::Magenta);
		player->scaleBullet = 3;
		player->ship->damage = float(player->maxDamage) * 3;
		if (timeUseBonus > 20) {
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

void Game::DrawObjects(RenderWindow & window) { // ��������� ��������
	for (Entity it : star->stars)
		window.draw(*it.sprite);
	for (Entity it3 : enemy->enemyShip) // ����������
		window.draw(*it3.sprite);
	for (Entity it2 : asteroid->asteroids) // ���������
		window.draw(*it2.sprite);
	for (Entity it4 : bonus->bonuses) // ������
		window.draw(*it4.sprite);
	if (player->ship->isLife) {
		window.draw(*player->ship->sprite); // �������������� ����� ���� �� ���
	}
	for (Shoot it : player->bullet) // ���� ������
		window.draw(*it.sprite);
	for (Shoot it : enemy->bulletEnemy) // ��������� ��������� ����
		window.draw(*it.sprite);
}

void processEventsGame(Game & game, GlobalBool & globalBool, Event & event, RenderWindow & window)
{
	Player & player = *game.player;
	Control(player, event);
	
	//--------------------------- ������� --------------------------
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

	Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
	Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

	//--------------- ������� ���� ---------------------

	game.IncreaseCharacteristicsObjects();
	game.CheckForCollision(window, deltaTime, game.textureGame);
	game.UseBonus(deltaTime, game.textureGame);
	//---------------- ��������� -----------------------
	UpdateTextWithHealth(*game.textInfo, *game.player, window);
	//---------------- ������� ����� -------------------
	//LoadStarInList(star, deltaTime, window, *game.textureGame); // �������� ����������� �����
	star.AddStar(game.textureGame, window);
	star.UpdateStateStar(deltaTime, window);
	//---------------- ������� ������ ------------------
	Vector2f posPlayer = player.ship->sprite->getPosition();
	if (player.ship->health <= 0) {
		player.ship->direction = NONE;
		player.ship->Explosion(deltaTime, game.textureGame.explosionTexture);
		
	}
	else {
		MovePlayer(player, deltaTime); // ������ ���������� ��������
		player.ship->sprite->move(Border(*player.ship, window));
		player.ChangeWeapons(game.textureGame, pos);
		player.ship->SetRotationObject(pos);
		player.RecoveryMove();
		UpdateStateBullet(deltaTime, window, player.bullet, game.textureGame, posPlayer);
	}
	if (!player.ship->isLife && !globalBool.g_isRestart) {
		globalBool.g_isPause = true;
	}
	else {
		globalBool.g_isPause = false;
	}
	
	//---------------- ������� ����������� -------------
	enemy.UpdateStateEveryEnemy(deltaTime, window, bonus, game.textureGame, posPlayer, player.point);
	enemy.AddEnemy(game.textureGame, window);
	enemy.CalmBoss();
	UpdateStateBullet(deltaTime, window, enemy.bulletEnemy, game.textureGame, posPlayer);
	//--------------- ������� ���������� ---------------
	if (!enemy.bossState.isBoss)
		asteroid.AddAsteroid(game.textureGame, window);
	asteroid.GetMoveEveryAsteroid(deltaTime, window, bonus, game.textureGame);
	//---------------- ������� ������� -----------------
	bonus.GetMoveEveryBonus(deltaTime, window);
}

void renderGame(RenderWindow & window, Game & game)
{
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