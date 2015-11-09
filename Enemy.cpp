#include "Enemy.h"
#include "Entity.h"

using namespace std;
using namespace sf;

void InitializeEnemy(Enemy & enemy) {
	enemy.enemyShip = new list<Entity>;
	enemy.bulletEnemy = new list<Shoot>;
}

void Enemy::GetMoveEveryEnemy(const Time & deltaTime) {
	for (list<Entity>::iterator it = enemyShip->begin(); it != enemyShip->end();) {
		MoveEnemy(deltaTime, *it);
		if (it->health <= 0)
			it->GetExplosion(deltaTime);
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
	if (timeCreateEnemy.asSeconds() > 2 && enemyShip->size() < 2) {
		Direction dir = LEFT;//GetDirection();
		Vector2f getPositionEnemy = GetRandomPosition(dir);
		Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, WIDTH_ENEMY, HEIGTH_ENEMY, "enemy1");
		addEnemy.direction = dir;
		enemyShip->push_back(addEnemy);
		timeCreateEnemy = Time::Zero;
	}
}

void Enemy::AddBulletEnemy(Vector2f posEnemy) {
	timeCreateBulletEnemy += clock.restart();
	if (timeCreateBulletEnemy.asSeconds() > 0.1) {
		Shoot addBullet(posEnemy.x, posEnemy.y, WIDTH_BULLET, HEIGTH_BULLET, LEFT, "resourse/images/laser-red.png");
		bulletEnemy->push_back(addBullet); // создание пули и занесение ее в список
		timeCreateBulletEnemy = Time::Zero;
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
	/*if (selectHand == 5) dir = UP_LEFT;
	if (selectHand == 6) dir = UP_RIGHT;
	if (selectHand == 7) dir = DOWN_LEFT;
	if (selectHand == 8) dir = DOWN_RIGHT;*/
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

void Enemy::MoveEnemy(const Time & deltaTime, Entity & enemy) {
	if (enemy.health > 0) {
		Vector2f movement = enemy.sprite->getPosition();
		switch (enemy.direction) {
		case UP: movement.y = -SPEED_ENEMY;
			movement.x = 0;
			enemy.sprite->setRotation(90);
			break;
		case DOWN: movement.y = SPEED_ENEMY;
			movement.x = 0;
			enemy.sprite->setRotation(-90);
			break;
		case LEFT: movement.x = -SPEED_ENEMY;
			movement.y = 0;
			break;
		case RIGHT: movement.x = SPEED_ENEMY;
			movement.y = 0;
			enemy.sprite->setRotation(180);
			break;
		case UP_LEFT: movement.x = -SPEED_ENEMY;
			movement.y = -SPEED_ENEMY;
			enemy.sprite->setRotation(45);
			break;
		case UP_RIGHT: movement.x = SPEED_ENEMY;
			movement.y = -SPEED_ENEMY;
			enemy.sprite->setRotation(135);
			break;
		case DOWN_RIGHT: movement.x = SPEED_ENEMY;
			movement.y = SPEED_ENEMY;
			enemy.sprite->setRotation(-135);
			break;
		case DOWN_LEFT: movement.x = -SPEED_ENEMY;
			movement.y = SPEED_ENEMY;
			enemy.sprite->setRotation(-45);
			break;
		default:
			enemy.isLife = false;
			break;
		}

		enemy.x = movement.x * deltaTime.asSeconds();
		enemy.y = movement.y * deltaTime.asSeconds();

		//-----------------  оллизии --------------------------
		// если уходит за экран, то прекращает свое существование
		if (enemy.sprite->getPosition().x < 0 - enemy.width) {
			enemy.isLife = false;
		}
		if (enemy.sprite->getPosition().y < 0 - enemy.height) {
			enemy.isLife = false;
		}
		if (enemy.sprite->getPosition().x >= SCRN_WIDTH + enemy.width){
			enemy.isLife = false;
		}
		if (enemy.sprite->getPosition().y >= SCRN_HEIGTH + enemy.height) {
			enemy.isLife = false;
		}

		enemy.sprite->move(enemy.x, enemy.y);
	}
}