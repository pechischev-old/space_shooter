#include "Enemy.h"
#include "Entity.h"

using namespace std;
using namespace sf;

void InitializeEnemy(Enemy & enemy) {
	enemy.enemyShip = new list<Entity>;
	enemy.bulletEnemy = new list<Shoot>;
}

void Enemy::SetMoveEveryEnemy(const Time & deltaTime, float & point, RenderWindow & window) {
	for (list<Entity>::iterator it = enemyShip->begin(); it != enemyShip->end();) {
		it->MoveObject(deltaTime);
		SetRotationEnemy(*it);
		it->CheckForCollisions(window);
		if (it->health <= 0) {
			it->Explosion(deltaTime);
			if (it->CurrentFrame >= 9.5)
				point += GetRandomPoint();
		}
		if (!it->isLife) {
			it->texture->~Texture();
			delete it->sprite;
			it = enemyShip->erase(it);
		}
		else  it++;
	}
}

void Enemy::AddEnemy() {
	timeCreateEnemy += clock.restart();
	if (timeCreateEnemy.asSeconds() > TIME_CREATE_ENEMY) {
		Direction dir = LEFT; //GetDirection();
		Vector2f getPositionEnemy = GetRandomPosition(dir);
		String typeEnemy = NAME_EASY_ENEMY;
		Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, typeEnemy);
		addEnemy.speed = SPEED_ENEMY;
		addEnemy.direction = dir; // присваивает сгенерированное направление
		addEnemy.damage = 20;
		enemyShip->push_back(addEnemy);
		timeCreateEnemy = Time::Zero;
	}
}

void Enemy::AddBulletEnemy(Vector2f posEnemy, Direction & dir, Entity & enemy) {
	timeCreateBulletEnemy += clock.restart();
	if (timeCreateBulletEnemy.asSeconds() > 0.3) {
		Shoot addBullet(posEnemy.x, posEnemy.y, enemy.width, enemy.height, dir, PATH_TO_RED_BULLET);
		bulletEnemy->push_back(addBullet); // создание пули и занесение ее в список
		timeCreateBulletEnemy = Time::Zero;
	}
}

void Enemy::UpdateStateEnemyBullet(const Time & deltaTime, RenderWindow & window) {
	for (list<Shoot>::iterator it = bulletEnemy->begin(); it != bulletEnemy->end();) {
		//cout << game.bulletEnemy->size() << endl;
		it->CheckForCollisions(window);
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
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
	getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - HEIGTH_ENEMY);
	if (selectHand == RIGHT) { // слева
		getPosit.x = 0;
		getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - 2 * HEIGTH_ENEMY);
	}
	else if (selectHand == DOWN || selectHand == DOWN_LEFT || selectHand == DOWN_RIGHT) { // сверху
		getPosit.x = WIDTH_ENEMY + rand() % (SCRN_WIDTH - WIDTH_ENEMY);
		getPosit.y = 0;
	}
	else if (selectHand == LEFT) { // справа
		getPosit.x = SCRN_WIDTH;
		getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_HEIGTH - 2 * HEIGTH_ENEMY);
	}
	else if (selectHand == UP || selectHand == UP_LEFT || selectHand == UP_RIGHT) { // снизу
		getPosit.x = WIDTH_ENEMY + rand() % (SCRN_WIDTH - WIDTH_ENEMY);
		getPosit.y = SCRN_HEIGTH;
	}
	return getPosit;
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
	int point = 1 + rand() % 3;
	return point;
}

bool IsEnterField(Vector2f & playerPos, Entity & enemy) {
	Vector2f posEnemy = enemy.sprite->getPosition(),
		posPlayer = playerPos;
	float widthEnemy = enemy.width;
	float heightEnemy = enemy.height;
	bool isEnterField = false;
	if (posEnemy.y - heightEnemy / 2 - 40  <= posPlayer.y &&  posPlayer.y <= heightEnemy / 2 + 40 + posEnemy.y)
		if (posEnemy.x - widthEnemy / 2 - 400  <= posPlayer.x && posPlayer.x <= widthEnemy / 2 + posEnemy.x)
			isEnterField = true;
	return isEnterField;
}
