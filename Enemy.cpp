#include "Enemy.h"

using namespace std;
using namespace sf;

void InitializeEnemy(Enemy & enemy) {
	enemy.enemyShip = new list<Entity>;
	enemy.bulletEnemy = new list<Shoot>;
}

void Enemy::UpdateStateEveryEnemy(const Time & deltaTime, int & point, RenderWindow & window, Bonus & bonus) {
	for (list<Entity>::iterator it = enemyShip->begin(); it != enemyShip->end();) {
		it->MoveObject(deltaTime);
		
		if (it->health <= 0 && it->name == NAME_BOSS) {
			isBoss = false;
		}
		if (it->name != NAME_BOSS)
			SetRotationEnemy(*it);
		else {
			BorderChecks(*it, window.getSize()); //Функция движения - появления
			it->sprite->move(Border(*it, window));
		}
		it->CheckForCollisions(window);
		if (it->health <= 0) {
			it->Explosion(deltaTime);
			if (it->CurrentFrame >= 9.5) {
				point += GetRandomPoint();
			}
		}
		if (!it->isLife) {
			if (it->isKilled) {  // выпадение бонуса
				if (CheckProbably())
					bonus.AddBonus(Vector2f(it->x, it->y));
			}
			//it->texture->~Texture();
			delete it->sprite;
			it = enemyShip->erase(it);
		}
		else  ++it;
	}
}

void Enemy::AddEnemy() {
	TextureGame textureGame;
	timeCreateEnemy += clock.restart();
	if (!isBoss) {
		if (timeCreateEnemy.asSeconds() > TIME_CREATE_ENEMY) {
			int chooseEnemy = GetTypeEnemy();
			Direction dir;
			Vector2f getPositionEnemy;
			String typeEnemy;
			Texture texture;
			if (chooseEnemy == 1) {
				dir = LEFT;
				getPositionEnemy = GetRandomPosition(dir);
				typeEnemy = NAME_EASY_ENEMY;
				texture = textureGame.enemyEasyTexture;
			}
			if (chooseEnemy == 2) {
				dir = LEFT;
				getPositionEnemy = GetRandomPosition(dir);
				typeEnemy = NAME_MIDDLE_ENEMY;
				texture = textureGame.enemyMiddleTexture;
			}

			Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, typeEnemy, texture);
			addEnemy.health = health;
			addEnemy.speed = SPEED_ENEMY;
			addEnemy.direction = dir;
			addEnemy.damage = damage;
			if (typeEnemy == NAME_MIDDLE_ENEMY)
				addEnemy.health = 2 * health;
			else
				addEnemy.health = health;
			enemyShip->push_back(addEnemy);
			timeCreateEnemy = Time::Zero;
			isOneBoss = false;
		}
	}
	if (isBoss && !isOneBoss) {
		Vector2f getPositionEnemy = { 650, 350 };
		Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, NAME_BOSS, textureGame.enemyBossTexture);
		addEnemy.direction = NONE;
		addEnemy.damage = damage * 3;
		addEnemy.health = health * 10;
		addEnemy.speed = SPEED_BOSS;
		enemyShip->push_back(addEnemy);
		isOneBoss = true;
	}
}

void Enemy::AddBulletEnemy(Vector2f posEnemy, Direction & dir, Entity & enemy, Vector2f posPlayer) {
	timeCreateBulletEnemy += clock.restart();
	if (timeCreateBulletEnemy.asSeconds() > TIME_CREATE_BULLET_ENEMY) {
		Shoot addBullet(posEnemy.x, posEnemy.y, enemy.width, enemy.height, dir, PATH_TO_RED_BULLET);
		if (enemy.name == NAME_MIDDLE_ENEMY || enemy.name == NAME_BOSS) {
			addBullet.isOtherBullet = true;
			addBullet.rememPos = posPlayer;
		}
		bulletEnemy->push_back(addBullet); // создание пули и занесение ее в список
		timeCreateBulletEnemy = Time::Zero;
	}
}

void Enemy::UpdateStateBullet(const Time & deltaTime, RenderWindow & window) {
	for (list<Shoot>::iterator it = bulletEnemy->begin(); it != bulletEnemy->end();) {
		it->CheckForCollisions(window);
		if (it->isOtherBullet) {
			it->MoveBulletHardEnemy(deltaTime);
		}
		else
			it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			delete it->sprite;
			it = bulletEnemy->erase(it);
		}
		else  ++it;
	}
}

Direction GetDirection() {
	Direction dir;
	srand(time(0));
	int selectHand = 1 + rand() % 4;
	if (selectHand == 1) dir = RIGHT;
	if (selectHand == 2) dir = DOWN;
	if (selectHand == 3) dir = LEFT;
	if (selectHand == 4) dir = UP;
	return dir;
}

Vector2f GetRandomPosition(Direction & selectHand) {
	Vector2f getPosit;
	
	getPosit.x = SCRN_WIDTH; //WIDTH_ENEMY + rand() % (SCRN_HEIGTH - WIDTH_ENEMY);
	getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - 2 * HEIGTH_ENEMY);
	/*if (selectHand == RIGHT) { // слева
		getPosit.x = 0;
		getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - 2 * HEIGTH_ENEMY);
	}
	else if (selectHand == DOWN || selectHand == DOWN_LEFT || selectHand == DOWN_RIGHT) { // сверху
		getPosit.x = WIDTH_ENEMY + rand() % (SCRN_WIDTH - WIDTH_ENEMY);
		getPosit.y = 0;
	}
	else if (selectHand == LEFT) { // справа
		getPosit.x = SCRN_WIDTH;
		getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - HEIGTH_ENEMY);
	}
	else if (selectHand == UP || selectHand == UP_LEFT || selectHand == UP_RIGHT) { // снизу
		getPosit.x = WIDTH_ENEMY + rand() % (SCRN_WIDTH - WIDTH_ENEMY);
		getPosit.y = SCRN_HEIGTH;
	}*/
	return getPosit;
}

void Enemy::MoveOnSinusoid(const Time & deltaTime, Entity & entity) {
	
}

void Enemy::BorderChecks(Entity & entity, Vector2u sizeWindow) {
	float y = entity.sprite->getPosition().y;
	float height = entity.height;
	float width = entity.width;
	Vector2f limitPos = { entity.sprite->getPosition().x , 0 };
	if (y - height / 2 < 10) {
		entity.direction = DOWN;
		//limitPos.y = 1;
	}
	else if (sizeWindow.y - y + height / 2 < 10) {
		entity.direction = UP;
		//limitPos.y = -1;
	}
	else
		entity.direction = NONE;
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

void Enemy::SetRotationEnemy(Entity & enemy) {
	if (enemy.direction == UP)
		enemy.sprite->setRotation(90);
	else if (enemy.direction == DOWN)
		enemy.sprite->setRotation(-90);
	else if (enemy.direction == LEFT)
		enemy.sprite->setRotation(0);
	else if (enemy.direction == RIGHT)
		enemy.sprite->setRotation(180);
	else if (enemy.direction == UP_LEFT)
		enemy.sprite->setRotation(45);
	else if (enemy.direction == UP_RIGHT)
		enemy.sprite->setRotation(135);
	else if (enemy.direction == DOWN_LEFT)
		enemy.sprite->setRotation(-45);
	else if (enemy.direction == DOWN_RIGHT)
		enemy.sprite->setRotation(-135);
}

int GetRandomPoint() {
	srand(time(0));
	return 1 + rand() % 3;
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

int GetTypeEnemy() {
	srand(time(0));
	return 1 + rand() % 2;
}


