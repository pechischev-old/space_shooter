#include "Enemy.h"


using namespace std;
using namespace sf;

Enemy::Enemy(float X, float Y, float width, float heigth, String Name, Direction direction) {
	texture = new Texture;
	sprite = new Sprite;
	x = X;
	y = Y;
	texture->loadFromFile("resourse/images/enemy1.png");
	sprite->setTexture(*texture);
	sprite->setTextureRect(IntRect(0, 0, WIDTH_ENEMY, HEIGTH_ENEMY));
	sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	sprite->setPosition(x, y);
	dirEnemy = direction;
	name = Name;
	isLife = true;
}

void Enemy::GetExplosion(const Time & deltaTime) {
	x = sprite->getPosition().x;
	y = sprite->getPosition().y;
	delete(texture);
	delete(sprite);
	texture = new Texture;
	sprite = new Sprite;
	CurrentFrame += 10 * deltaTime.asSeconds();
	if (CurrentFrame <= 10) {
		texture->loadFromFile("resourse/images/explosion.png");
		sprite->setTexture(*texture);
		sprite->setOrigin(WIDTH_EXPLOSION / 2, HEIGTH_EXPLOSION / 2);
		sprite->setTextureRect(IntRect(WIDTH_EXPLOSION * int(CurrentFrame), 0, WIDTH_EXPLOSION, HEIGTH_EXPLOSION));
		sprite->setPosition(x, y);
	}
	else isLife = false;
	
}

void Enemy::MoveEnemy(const Time & deltaTime) {
	if (life > 0) {
		Vector2f movement = sprite->getPosition();

		switch (dirEnemy) {
			case UP: movement.y = -SPEED_ENEMY;
				movement.x = 0;
				sprite->setRotation(90);
				break;
			case DOWN: movement.y = SPEED_ENEMY;
				movement.x = 0;
				sprite->setRotation(-90);
				break;
			case LEFT: movement.x = -SPEED_ENEMY;
				movement.y = 0;
				break;
			case RIGHT: movement.x = SPEED_ENEMY;
				movement.y = 0;
				sprite->setRotation(180);
				break;
			case UP_LEFT: movement.x = -SPEED_ENEMY;
				movement.y = -SPEED_ENEMY;
				sprite->setRotation(45);
				break;
			case UP_RIGHT: movement.x = SPEED_ENEMY;
				movement.y = -SPEED_ENEMY;
				sprite->setRotation(135);
				break;
			case DOWN_RIGHT: movement.x = SPEED_ENEMY;
				movement.y = SPEED_ENEMY;
				sprite->setRotation(-135);
				break;
			case DOWN_LEFT: movement.x = -SPEED_ENEMY;
				movement.y = SPEED_ENEMY;
				sprite->setRotation(-45);
				break;
		default:
			life = false;
			break;
		}

		x = movement.x * deltaTime.asSeconds();
		y = movement.y * deltaTime.asSeconds();

		//----------------- Коллизии --------------------------
		// если уходит за экран, то прекращает свое существование
		if (sprite->getPosition().x < 0 - WIDTH_ENEMY) {
			isLife = false;
		}
		if (sprite->getPosition().y < 0 - HEIGTH_ENEMY) {
			isLife = false;
		}
		if (sprite->getPosition().x >= SCRN_WIDTH + WIDTH_ENEMY) {
			isLife = false;
		}
		if (sprite->getPosition().y >= SCRN_HEIGTH + HEIGTH_ENEMY) {
			isLife = false;
		}

		sprite->move(x, y);
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
