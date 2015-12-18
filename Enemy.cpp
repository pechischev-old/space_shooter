#include "Enemy.h"

using namespace std;
using namespace sf;

void Enemy::UpdateStateEveryEnemy(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame, Vector2f posPlayer, int & point) {

	for (auto &it : enemyShip) {
		if (it.name != NAME_BOSS ) {
			SetMove(window, it);
		}
		it.MoveObject(deltaTime);
		UpdateDirection(window, it);
		if (it.name == NAME_KAMIKAZE_ENEMY) {
			MoveKamikaze(deltaTime, posPlayer, it);
		}
		if (it.health <= 0 && it.name == NAME_BOSS) {
			bossState.isBoss = false;
			bossState.isRage = false;
		}
		if (it.name != NAME_BOSS) {
			if (it.name != NAME_KAMIKAZE_ENEMY)
				it.SetRotationObject(posPlayer);
		}
		else { // для босса
			BorderChecks(it, window.getSize()); //Функция движения - появления
		}
		it.CheckForCollisions(window);
		if (it.health <= 0) {
			it.Explosion(deltaTime, textureGame.explosionTexture);
		}
	}
	auto updatedEnd = std::remove_if(enemyShip.begin(), enemyShip.end(), [&](Entity &entity) {
		if (!entity.isLife) {
			if (entity.isKilled) {  // выпадение бонуса
				if (CheckProbably())
					bonus.AddBonus(entity.position, textureGame);
				--point;
			}
			delete entity.sprite;
		}
		return !entity.isLife;
	});
	enemyShip.erase(updatedEnd, enemyShip.end());
}

void Enemy::AddEnemy(TextureGame & textureGame, RenderWindow & window) {

	timeCreateEnemy += clock.restart();
	if (!bossState.isBoss) {
		if (timeCreateEnemy.asSeconds() > timeToCreateEnemy) {
			Direction dir = LEFT;
			Vector2f getPositionEnemy;
			String typeEnemy;
			Texture *texture = NULL;
			idEnemy = static_cast<TypeEnemy> (Math::GetRandomNumerForSection(1, sizeTypeEnemy));
			int countEnemy = 0;
			switch (idEnemy)
			{
			case TypeEnemy::EASY:
				typeEnemy = NAME_EASY_ENEMY;
				texture = &textureGame.enemyEasyTexture;
				countEnemy = numberEnemy.numberEasyEnemy;
				break;
			case TypeEnemy::MIDDLE:
				typeEnemy = NAME_MIDDLE_ENEMY;
				texture = &textureGame.enemyMiddleTexture;
				countEnemy = numberEnemy.numberMiddleEnemy;
				break;
			case TypeEnemy::KAMIKAZE:
				typeEnemy = NAME_TOWER_ENEMY;
				texture = &textureGame.enemyTowerTexture;
				countEnemy = numberEnemy.numberTowerEnemy;
				break;
			case TypeEnemy::TOWER:
				typeEnemy = NAME_KAMIKAZE_ENEMY;
				texture = &textureGame.enemyKamikazeTexture;
				countEnemy = numberEnemy.numberKamikaze;
				break;
			}
			for (int i = 1; i <= countEnemy; ++i) {
				if (i == 1)
					dir = static_cast<Direction>(Math::GetRandomNumerForSection(1, 4));
				else
					dir = static_cast<Direction>(GetDirection(dir));
				getPositionEnemy = GetRandomPosition(dir, window);
				Entity addEnemy(getPositionEnemy, typeEnemy, *texture);
				addEnemy.health = float(health);
				addEnemy.speed = float(SPEED_ENEMY);
				if (typeEnemy == NAME_TOWER_ENEMY) {
					addEnemy.speed = float(SPEED_TOWER);
				}
				addEnemy.sprite->setScale(-1, 1);
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
	if (bossState.isBoss && !bossState.isOneBoss) { // переделать
		Vector2f getPositionEnemy = { 650, 350 };
		Entity addEnemy(getPositionEnemy, NAME_BOSS, textureGame.enemyBossTexture);
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
	float timeCreate = TIME_CREATE_BULLET_ENEMY;
	if (enemy.name == NAME_TOWER_ENEMY)
		timeCreate = TIME_CREATE_ROCKET;
	if (timeCreateBullet.asSeconds() > timeCreate) {
		Shoot addBullet(posEnemy, enemy.sizeObject, LEFT, texture, NAME_BULLET);
		if (enemy.name != NAME_TOWER_ENEMY && !bossState.isRage) {
			addBullet.isOtherBullet = true;
			addBullet.rememPos = posPlayer;
		}
		else if (enemy.name == NAME_TOWER_ENEMY) {
			addBullet.isRocket = true;
			addBullet.rememPos = posPlayer;
			addBullet.name = NAME_ROCKET;
		}
		bulletEnemy.push_back(addBullet); // создание пули и занесение ее в список
		timeCreateBullet = Time::Zero;
	}
}

void Enemy::BorderChecks(Entity & entity, Vector2u sizeWindow) {
	float height = entity.sizeObject.y;
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

void Enemy::MoveKamikaze(const Time & deltaTime, Vector2f posPlayer, Entity & enemy) {
	if (enemy.health > 0) {
		Vector2f posEnemy = enemy.sprite->getPosition();
		posEnemy.x += SPEED_KAMIKAZE *  Math::Normalize(posPlayer, posEnemy).x;
		posEnemy.y += SPEED_KAMIKAZE *  Math::Normalize(posPlayer, posEnemy).y;
		enemy.sprite->setPosition(posEnemy);
	}
}

void Enemy::UpdateDirection(RenderWindow & window, Entity & enemy) {
	Vector2f position = enemy.sprite->getPosition();
	Vector2u sizeWindow = window.getSize();
	Vector2f sizeEnemy = enemy.sizeObject;
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
	int selectHand = Math::GetRandomNumerForSection(1, 3);
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

Vector2f GetRandomPosition(Direction & selectHand, RenderWindow & window) {
	Vector2f getPosit;
	Vector2u sizeWindow = window.getSize();
	if (selectHand == RIGHT) { // слева
	getPosit.x = 0;
	getPosit.y = float(Math::GetRandomNumerForSection(BORDER_CREATE, (sizeWindow.y - BORDER_CREATE)));
	}
	else if (selectHand == DOWN ) { // сверху
	getPosit.x = float(Math::GetRandomNumerForSection(BORDER_CREATE, (sizeWindow.x - BORDER_CREATE)));
	getPosit.y = 0;
	}
	else if (selectHand == LEFT) { // справа
	getPosit.x = float(sizeWindow.x);
	getPosit.y = float(Math::GetRandomNumerForSection(BORDER_CREATE, (sizeWindow.y - BORDER_CREATE)));
	}
	else if (selectHand == UP) { // снизу
	getPosit.x = float(Math::GetRandomNumerForSection(BORDER_CREATE, (sizeWindow.x - BORDER_CREATE)));
	getPosit.y = float(sizeWindow.y);
	}
	return getPosit;
}

void SpecialShootingBoss(Enemy & enemy, Entity & boss, TextureGame & textureGame) {
	enemy.timeCreateBulletEnemy += enemy.clock.restart();
	double time = TIME_CREATE_BULLET_ENEMY * 2;
	Vector2f posEnemy = boss.sprite->getPosition();
	if (enemy.timeCreateBulletEnemy.asSeconds() > time) {
		switch (enemy.selector) {
		case ELECTRICAL: {
			Shoot addBullet(posEnemy, boss.sizeObject, LEFT, textureGame.electricBullet, NAME_ELECTRIC_BULLET);
			enemy.bulletEnemy.push_back(addBullet);
			break; }
		case TRIPLE_SHOT: {	
			Shoot addBullet1(Vector2f(posEnemy.x, posEnemy.y - 30), boss.sizeObject, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet2(posEnemy, boss.sizeObject, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet3(Vector2f(posEnemy.x, posEnemy.y + 30), boss.sizeObject, LEFT, textureGame.redLaserTexture, NAME_BULLET);
			enemy.bulletEnemy.push_back(addBullet1);
			enemy.bulletEnemy.push_back(addBullet2);
			enemy.bulletEnemy.push_back(addBullet3);
			break; }
		case POWERFUL_SHOOTING: {
			Shoot addBullet(posEnemy, boss.sizeObject, LEFT, textureGame.blueLaserTexture, NAME_BULLET);
			addBullet.sprite->setScale(4, 4);
			addBullet.damage = int(boss.damage) * 2;
			enemy.bulletEnemy.push_back(addBullet);
			break; }
		case CROSS_FIRE: {
			Shoot addBullet1(posEnemy, boss.sizeObject, UP_LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet2(posEnemy, boss.sizeObject, DOWN_LEFT, textureGame.redLaserTexture, NAME_BULLET);
			Shoot addBullet3(posEnemy, boss.sizeObject, LEFT, textureGame.redLaserTexture, NAME_BULLET);
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
	float angle = enemy.sprite->getRotation();
	Transform transform;
	FloatRect rect = transform.rotate(angle, Vector2f(posEnemy)).transformRect(FloatRect(posEnemy, Vector2f(DISTANCE_FOR_ATACK, DISTANCE_FOR_ATACK / 10)));
	return rect.contains(posPlayer);
}

bool IsSeePlayer(Vector2f & playerPos, Entity & enemy, Vector2u & sizeWindow) { 
	Vector2f posEnemy = enemy.sprite->getPosition(),
		posPlayer = playerPos;
	float angle = enemy.sprite->getRotation();
	Transform transform;
	FloatRect rect = transform.rotate(angle, Vector2f(posEnemy)).transformRect(FloatRect(posEnemy, Vector2f(float(sizeWindow.x) / 1.5f, float(sizeWindow.y) / 1.5f))); 
	// задаю поворот и размеры области стрельбы 
	return rect.contains(posPlayer);
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
	enemy.timeToCreateEnemy = TIME_CREATE_ENEMY;
	enemy.numberEnemy.numberEasyEnemy = COUNT_EASY_ENEMY;
	enemy.numberEnemy.numberKamikaze = COUNT_KAMIKAZE_ENEMY;
	enemy.numberEnemy.numberMiddleEnemy = COUNT_MIDDLE_ENEMY;
	enemy.numberEnemy.numberTowerEnemy = COUNT_TOWER_ENEMY;
}

