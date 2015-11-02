#include "Enemy.h"


using namespace std;
using namespace sf;

Enemy::Enemy(float X, float Y, float width, float heigth, String Name) {
	texture = new Texture;
	sprite = new Sprite;
	x = X;
	y = Y;
	texture->loadFromFile("resourse/images/enemy1.png");
	sprite->setTexture(*texture);
	sprite->setTextureRect(IntRect(0, 0, WIDTH_ENEMY, HEIGTH_ENEMY));
	sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	sprite->setPosition(x, y);
	direction = LEFT_2;
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
	//cout << CurrentFrame << endl;
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

		switch (direction) {
			/*case UP: movement.y = -SPEED_ENEMY;
				movement.x = 0;
				break;
			case DOWN: movement.y = SPEED_ENEMY;
				movement.x = 0;
				break;*/
		case LEFT_2: movement.x = -SPEED_ENEMY;
			movement.y = 0;
			break;
			/*case RIGHT: movement.x = SPEED_ENEMY;
				movement.y = 0;
				break;
			case UP_LEFT: movement.x = -SPEED_ENEMY;
				movement.y = -SPEED_ENEMY;
				sprite->setRotation(-135);
				break;
			case UP_RIGHT: movement.x = SPEED_ENEMY;
				movement.y = -SPEED_ENEMY;
				sprite->setRotation(-45);
				break;
			case DOWN_RIGHT: movement.x = SPEED_ENEMY;
				movement.y = SPEED_ENEMY;
				sprite->setRotation(45);
				break;
			case DOWN_LEFT: movement.x = -SPEED_ENEMY;
				movement.y = SPEED_ENEMY;
				sprite->setRotation(135);
				break;*/
		default:
			life = false; // будет стрелять при остановке корабля
						  // нужно будет вычислить местоположение носа корабля
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
		if (sprite->getPosition().x >= SCRN_HEIGTH + WIDTH_ENEMY) {
			isLife = false;
		}
		if (sprite->getPosition().y >= SCRN_WIDTH + HEIGTH_ENEMY) {
			isLife = false;
		}

		sprite->move(x, y);
	}
}

Vector2f GetRandomPosition() {
	Vector2f getPosit;
	srand(time(0));
	getPosit.x = SCRN_HEIGTH; //WIDTH_ENEMY + rand() % (SCRN_HEIGTH - WIDTH_ENEMY);
	getPosit.y = HEIGTH_ENEMY + rand() % (SCRN_WIDTH - HEIGTH_ENEMY);
	return getPosit;
}
