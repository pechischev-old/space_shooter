#include "Enemy.h"
#include "Entity.h"

using namespace std;
using namespace sf;

void InitializeEnemy(Enemy & enemy) {
	enemy.enemyShip = new list<Entity>;
	enemy.bulletEnemy = new list<Shoot>;
}

void Enemy::GetMoveEveryEnemy(const Time & deltaTime, float & point) {
	for (list<Entity>::iterator it = enemyShip->begin(); it != enemyShip->end();) {
		MoveEnemy(deltaTime, *it);
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
	if (timeCreateEnemy.asSeconds() > 2 ) {
		Direction dir = LEFT; //GetDirection();
		Vector2f getPositionEnemy = GetRandomPosition(dir);
		Entity addEnemy(getPositionEnemy.x, getPositionEnemy.y, "enemy1");
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
		Shoot addBullet(posEnemy.x, posEnemy.y, enemy.width, enemy.height, dir, "resourse/images/laser-red.png");
		bulletEnemy->push_back(addBullet); // создание пули и занесение ее в список
		timeCreateBulletEnemy = Time::Zero;
	}
}

void Enemy::UpdateStateEnemyBullet(const Time & deltaTime) {
	for (list<Shoot>::iterator it = bulletEnemy->begin(); it != bulletEnemy->end();) {
		//cout << game.bulletEnemy->size() << endl;
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			it = bulletEnemy->erase(it);
		}
		else  it++;
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
		case UP: movement.y = -enemy.speed;
			movement.x = 0;
			enemy.sprite->setRotation(90);
			break;
		case DOWN: movement.y = enemy.speed;
			movement.x = 0;
			enemy.sprite->setRotation(-90);
			break;
		case LEFT: movement.x = -enemy.speed;
			movement.y = 0;
			break;
		case RIGHT: movement.x = enemy.speed;
			movement.y = 0;
			enemy.sprite->setRotation(180);
			break;
		case UP_LEFT: movement.x = -enemy.speed;
			movement.y = -enemy.speed;
			enemy.sprite->setRotation(45);
			break;
		case UP_RIGHT: movement.x = enemy.speed;
			movement.y = -enemy.speed;
			enemy.sprite->setRotation(135);
			break;
		case DOWN_RIGHT: movement.x = enemy.speed;
			movement.y = enemy.speed;
			enemy.sprite->setRotation(-135);
			break;
		case DOWN_LEFT: movement.x = -enemy.speed;
			movement.y = enemy.speed;
			enemy.sprite->setRotation(-45);
			break;
		default:
			enemy.isLife = false;
			break;
		}

		enemy.x = movement.x * deltaTime.asSeconds();
		enemy.y = movement.y * deltaTime.asSeconds();

		//----------------- Коллизии --------------------------
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

Vector2f Enemy::ShootByAsteroid(Vector2f posAsteroid, Vector2f enemyPos, const Time & deltaTime) {
	float distance = sqrt((posAsteroid.x - enemyPos.x) * (posAsteroid.x - enemyPos.x) + (posAsteroid.y - enemyPos.y) * (posAsteroid.y - enemyPos.y));
	//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

	if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта

		enemyPos.x += 0.1 * deltaTime.asSeconds() * (posAsteroid.x - enemyPos.x) / distance;//идем по иксу с помощью вектора нормали
		enemyPos.y += 0.1 * deltaTime.asSeconds() * (posAsteroid.y - enemyPos.y) / distance;//идем по игреку так же
	}
	return enemyPos;
}