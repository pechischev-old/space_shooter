#include "Enemy.h"

using namespace std;
using namespace sf;

void Enemy::UpdateStateEveryEnemy(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame, Vector2f posPlayer, int & point) {
	for (list<Entity>::iterator it = enemyShip.begin(); it != enemyShip.end();) {
		if (it->name != NAME_BOSS) {
			SetMove(window, *it);
		}
		it->MoveObject(deltaTime);
		UpdateDirection(window, *it);
		if (it->name == NAME_KAMIKAZE_ENEMY) {
			MoveKamikaze(deltaTime, posPlayer, *it);
		}
		if (it->health <= 0 && it->name == NAME_BOSS) {
			bossState.isBoss = false;
			bossState.isRage = false;
		}
		if (it->name != NAME_BOSS) {
			if (it->name == NAME_TOWER_ENEMY) {
				ReferenceRotationTowardPlayer(*it, posPlayer);
			}
			
		}
		else { // ��� �����
			BorderChecks(*it, window.getSize()); //������� �������� - ���������
		}
		it->CheckForCollisions(window);
		if (it->health <= 0) {
			it->Explosion(deltaTime, textureGame.explosionTexture);
		}
		if (!it->isLife) {
			if (it->isKilled) {  // ��������� ������
				if (CheckProbably())
					bonus.AddBonus(Vector2f(it->x, it->y), textureGame);
				--point;
			}
			delete it->sprite;
			it = enemyShip.erase(it);
		}
		else  ++it;
	}
}

void Enemy::AddEnemy(TextureGame & textureGame) {
	auto GetTypeEnemy = [&]() {
		srand(unsigned int(time(NULL)));
		return 1 + rand() % 4;
	};

	timeCreateEnemy += clock.restart();
	if (!bossState.isBoss) {
		if (timeCreateEnemy.asSeconds() > timeToCreateEnemy) {
			int chooseEnemy = GetTypeEnemy();
			Direction dir;
			Vector2f getPositionEnemy;
			String typeEnemy;
			Texture *texture = NULL;
			int countEnemy = 0;
			if (chooseEnemy == 1) { // ������� ����� switch
				dir = LEFT;
				typeEnemy = NAME_EASY_ENEMY;
				texture = &textureGame.enemyEasyTexture;
				countEnemy = numberEnemy.numberEasyEnemy;
			}
			if (chooseEnemy == 2) {
				dir = LEFT;
				typeEnemy = NAME_MIDDLE_ENEMY;
				texture = &textureGame.enemyMiddleTexture;
				countEnemy = numberEnemy.numberMiddleEnemy;
			}
			if (chooseEnemy == 3) {
				dir = LEFT;
				typeEnemy = NAME_TOWER_ENEMY;
				texture = &textureGame.enemyTowerTexture;
				countEnemy = numberEnemy.numberTowerEnemy;
			}
			if (chooseEnemy == 4) {
				dir = LEFT;
				typeEnemy = NAME_KAMIKAZE_ENEMY;
				texture = &textureGame.enemyKamikazeTexture;
				countEnemy = numberEnemy.numberKamikaze;
			}
			for (int i = 1; i <= countEnemy; ++i) {
				getPositionEnemy = GetRandomPosition(dir);
				Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, typeEnemy, *texture);
				addEnemy.health = float(health);
				addEnemy.speed = float(SPEED_ENEMY);
				if (typeEnemy == NAME_TOWER_ENEMY) {

					addEnemy.speed = float(SPEED_TOWER);
					addEnemy.sprite->setScale(-1, 1);
				}
				addEnemy.direction = dir;
				addEnemy.damage = float(damage);
				if (typeEnemy == NAME_MIDDLE_ENEMY)
					addEnemy.health = 2 * float(health);
				else
					addEnemy.health = float(health);
				enemyShip.push_back(addEnemy);
			}
			timeCreateEnemy = Time::Zero;
			bossState.isOneBoss = false;
		}
	}
	if (bossState.isBoss && !bossState.isOneBoss) {
		Vector2f getPositionEnemy = { 650, 350 };
		Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, NAME_BOSS, textureGame.enemyBossTexture);
		addEnemy.direction = UP;
		addEnemy.damage = float(damage);
		addEnemy.health = float(health) * RATE_HEALTH_BOSS;
		addEnemy.speed = SPEED_BOSS;
		enemyShip.push_back(addEnemy);
		bossState.isOneBoss = true;
	}
}

void Enemy::AddBulletEnemy(Entity & enemy, Vector2f posPlayer, Texture & texture, Time & timeCreateBullet) {
	timeCreateBullet += clock.getElapsedTime();
	Vector2f posEnemy = enemy.sprite->getPosition();
	if (timeCreateBullet.asSeconds() > TIME_CREATE_BULLET_ENEMY) {
		Shoot addBullet(posEnemy.x, posEnemy.y, enemy.width, enemy.height, LEFT, texture, NAME_BULLET);
		if ((enemy.name == NAME_MIDDLE_ENEMY || enemy.name == NAME_BOSS) && !bossState.isRage) {
			addBullet.isOtherBullet = true;
			addBullet.rememPos = posPlayer;
		}
		else if (enemy.name == NAME_TOWER_ENEMY) {
			addBullet.isRocket = true;
			addBullet.rememPos = posPlayer;
			addBullet.name = NAME_ROCKET;
		}
		bulletEnemy.push_back(addBullet); // �������� ���� � ��������� �� � ������
		timeCreateBullet = Time::Zero;
	}
}

void Enemy::BorderChecks(Entity & entity, Vector2u sizeWindow) {
	float height = entity.height;
	float top = entity.sprite->getGlobalBounds().top;
	float bottom = top + height;
	
	if (top <= 10)
		entity.direction = DOWN;
	else if (bottom > sizeWindow.y - 10)
		entity.direction = UP;
}

void Enemy::Evasion(Vector2f posBullet, Entity & entity, Vector2u sizeWindow) {
	float y = entity.sprite->getPosition().y;
	if (posBullet.y < y )
		entity.direction = DOWN;
	else if (posBullet.y > y)
		entity.direction = UP;
	else
		entity.direction = NONE;
}

void Enemy::CalmBoss() {
	if (bossState.isRage) {
		timeForCalm += clock.restart();
		if (timeForCalm.asMicroseconds() > 100) {
			rage -= 5;
			bossState.isRage = rage > 0;
			timeForCalm = Time::Zero;
		}
		if (rage <= 0) {
			switch (selector) {
			case TRIPLE_SHOT: selector = ELECTRICAL;
				break;
			case ELECTRICAL: selector = POWERFUL_SHOOTING;
				break;
			case POWERFUL_SHOOTING: selector = CROSS_FIRE;
				break;
			case CROSS_FIRE: selector = TRIPLE_SHOT;
				break;
			}
		}
	}
}

void Enemy::ReferenceRotationTowardPlayer(Entity & enemy, Vector2f posPlayer) {
	Vector2f posEnemy = enemy.sprite->getPosition();
	enemy.sprite->setRotation(float(atan2((posPlayer.y - posEnemy.y), (posPlayer.x - posEnemy.x)) * 180 / M_PI));
}

void Enemy::MoveKamikaze(const Time & deltaTime, Vector2f posPlayer, Entity & enemy) {
	if (enemy.health > 0) {
		Vector2f posEnemy = enemy.sprite->getPosition();
		float distance = sqrt((posPlayer.x - posEnemy.x)*(posPlayer.x - posEnemy.x) + (posPlayer.x - posEnemy.y)*(posPlayer.x - posEnemy.y));
		posEnemy.x += 5 * (posPlayer.x - posEnemy.x) / distance;  // ��������� ����� ������-��
		posEnemy.y += 5 * (posPlayer.y - posEnemy.y) / distance;
		enemy.sprite->setPosition(posEnemy.x, posEnemy.y);
	}
}

void Enemy::UpdateDirection(RenderWindow & window, Entity & enemy) {
	Vector2f position = enemy.sprite->getPosition();
	Vector2u sizeWindow = window.getSize();
	Vector2f sizeEnemy = { enemy.width, enemy.height };
	if ((position.y - sizeEnemy.y / 2) <= 0 && enemy.direction == UP) {
		enemy.direction = DOWN;
	}
	else if ((position.y + sizeEnemy.y / 2) >= sizeWindow.y && enemy.direction == DOWN) {
		enemy.direction = UP;
	}
	else if ((position.x - sizeEnemy.x / 2) <= 0 && (enemy.direction == LEFT)) {
		enemy.direction = RIGHT;
	}
	else if ((position.x + sizeEnemy.x / 2) >= sizeWindow.x && enemy.direction == RIGHT) {
		enemy.direction = LEFT;
	}
}

void Enemy::SetMove(RenderWindow & window, Entity & enemy) {
	Vector2f position = enemy.sprite->getPosition();
	auto isNoBorder = [&](RenderWindow & window, Vector2f position) {
		float distance = 100;
		bool flagOne = distance <= position.x && position.x <= window.getSize().x - distance;
		bool flagTwo = 0 <= position.y && position.y <= window.getSize().y;
		return flagOne && flagTwo; };

	if (isNoBorder(window, position)) {
		enemy.timeChangeDirection += clock.restart();
		if (enemy.timeChangeDirection.asSeconds() > 2) {
			enemy.direction = GetDirection(enemy.direction);
			enemy.timeChangeDirection = Time::Zero;
		}
	}
}

Direction GetDirection(Direction oldDir) {
	Direction dir;
	srand(unsigned int(time(NULL)));
	int selectHand = 1 + rand() % 3;
	if (oldDir == UP) {
		if (selectHand == 1) dir = RIGHT;
		if (selectHand == 2) dir = DOWN;
		if (selectHand == 3) dir = LEFT;
	}
	else if (oldDir == LEFT) {
		if (selectHand == 1) dir = RIGHT;
		if (selectHand == 2) dir = DOWN;
		if (selectHand == 3) dir = UP;
	}
	else if (oldDir == RIGHT) {
		if (selectHand == 1) dir = LEFT;
		if (selectHand == 2) dir = DOWN;
		if (selectHand == 3) dir = UP;
	}
	else if (oldDir == DOWN) {
		if (selectHand == 1) dir = RIGHT;
		if (selectHand == 2) dir = LEFT;
		if (selectHand == 3) dir = UP;
	}
	
	return dir;
}

Vector2f GetRandomPosition(Direction & selectHand) {
	Vector2f getPosit;

	getPosit.x = float(SCRN_WIDTH); //WIDTH_ENEMY + rand() % (SCRN_HEIGTH - WIDTH_ENEMY);
	getPosit.y = float(HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - 2 * HEIGTH_ENEMY));
	/*if (selectHand == RIGHT) { // �����
	getPosit.x = 0;
	getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - 2 * HEIGTH_ENEMY);
	}
	else if (selectHand == DOWN ) { // ������
	getPosit.x = WIDTH_ENEMY + rand() % (SCRN_WIDTH - WIDTH_ENEMY);
	getPosit.y = 0;
	}
	else if (selectHand == LEFT) { // ������
	getPosit.x = SCRN_WIDTH;
	getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - HEIGTH_ENEMY);
	}
	else if (selectHand == UP || selectHand == UP_LEFT || selectHand == UP_RIGHT) { // �����
	getPosit.x = WIDTH_ENEMY + rand() % (SCRN_WIDTH - WIDTH_ENEMY);
	getPosit.y = SCRN_HEIGTH;
	}*/
	return getPosit;
}

void SpecialShootingBoss(Enemy & enemy, Entity & boss, TextureGame & textureGame) {
	enemy.timeCreateBulletEnemy += enemy.clock.restart();
	double time = TIME_CREATE_BULLET_ENEMY * 2;
	Vector2f posEnemy = boss.sprite->getPosition();
	if (enemy.timeCreateBulletEnemy.asSeconds() > time) {
		switch (enemy.selector) {
		case ELECTRICAL: {
			Shoot addBullet(posEnemy.x, posEnemy.y, boss.width, boss.height, LEFT, textureGame.electricBullet, NAME_ELECTRIC_BULLET);
			enemy.bulletEnemy.push_back(addBullet);
			break; }
		case TRIPLE_SHOT: {	
			Shoot addBullet1(posEnemy.x, posEnemy.y - 30, boss.width, boss.height, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet2(posEnemy.x, posEnemy.y, boss.width, boss.height, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet3(posEnemy.x, posEnemy.y + 30, boss.width, boss.height, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			enemy.bulletEnemy.push_back(addBullet1);
			enemy.bulletEnemy.push_back(addBullet2);
			enemy.bulletEnemy.push_back(addBullet3);
			break; }
		case POWERFUL_SHOOTING: {
			Shoot addBullet(posEnemy.x, posEnemy.y, boss.width, boss.height, LEFT, textureGame.blueLaserTexture, NAME_BULLET);
			addBullet.sprite->setScale(4, 4);
			addBullet.damage = int(boss.damage) * 2;
			enemy.bulletEnemy.push_back(addBullet);
			break; }
		case CROSS_FIRE: {
			Shoot addBullet1(posEnemy.x, posEnemy.y, boss.width, boss.height, UP_LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet2(posEnemy.x, posEnemy.y, boss.width, boss.height, DOWN_LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet3(posEnemy.x, posEnemy.y, boss.width, boss.height, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			enemy.bulletEnemy.push_back(addBullet1);
			enemy.bulletEnemy.push_back(addBullet2);
			enemy.bulletEnemy.push_back(addBullet3);
			break; }
		}
		enemy.timeCreateBulletEnemy = Time::Zero;
	}
}

bool IsEnterField(Vector2f & playerPos, Entity & enemy) {
	Vector2f posEnemy = enemy.sprite->getPosition(),
		posPlayer = playerPos;
	float widthEnemy = enemy.width;
	float heightEnemy = enemy.height;
	if (posEnemy.y - heightEnemy / 2 - 40  <= posPlayer.y &&  posPlayer.y <= heightEnemy / 2 + 40 + posEnemy.y)
		if (posEnemy.x - widthEnemy / 2 - 400  <= posPlayer.x && posPlayer.x <= widthEnemy / 2 + posEnemy.x)
			return true;
	return false;
}

bool IsSeePlayer(Vector2f & playerPos, Entity & enemy, Vector2u & sizeWindow) {
	Vector2f posEnemy = enemy.sprite->getPosition(),
		posPlayer = playerPos;
	float widthEnemy = enemy.width;
	float heightEnemy = enemy.height;
	if (posEnemy.y - heightEnemy / 2 - sizeWindow.x <= posPlayer.y &&  posPlayer.y <= heightEnemy / 2 + sizeWindow.x + posEnemy.y)
		if (posEnemy.x - widthEnemy / 2 - sizeWindow.x <= posPlayer.x && posPlayer.x <= widthEnemy / 2 + posEnemy.x)
			return true;
	return false;
}

void ResetEnemy(Enemy & enemy) {
	enemy.bossState.isBoss = false;
	enemy.bossState.isOneBoss = false;
	enemy.bossState.isEvasion = false;
	enemy.bossState.isShock = false;
	enemy.bossState.isRage = false;
	enemy.damage = FIRST_EVER_DAMAGE_ENEMY;
	enemy.health = FIRST_EVER_HEALTH_ENEMY;
	enemy.rage = 0;
	enemy.selector = TRIPLE_SHOT;
	enemy.selectorShooting = 0;
}

