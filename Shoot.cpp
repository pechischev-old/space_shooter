#include "Shoot.h"

using namespace sf;
using namespace std;

Shoot::Shoot(float X, float Y, float width, float heigth, Direction direction, String path) {
	texture = new Texture;
	sprite = new Sprite;
	texture->loadFromFile(path);
	sprite->setTexture(*texture);
	sprite->setOrigin(WIDTH_BULLET / 2, HEIGTH_BULLET / 2);
	sprite->setPosition(X + heigth / 11, Y + width / 11);
	dir = direction;
	x = X;
	y = Y;
	life = true;
}

void Shoot::MoveBullet(const Time & deltaTime) {
	Vector2f movement = sprite->getPosition();
	switch (dir) {
	case UP: movement.y = -SPEED_BULLET;
		movement.x = 0;
		sprite->setRotation(-90);
		break;
	case DOWN: movement.y = SPEED_BULLET;
		movement.x = 0;
		sprite->setRotation(90);
		break;
	case LEFT: movement.x = -SPEED_BULLET;
		movement.y = 0;
		sprite->setRotation(-180);
		break;
	case RIGHT: movement.x = SPEED_BULLET;
		movement.y = 0;
		break;
	case UP_LEFT: movement.x = -SPEED_BULLET;
		movement.y = -SPEED_BULLET;
		sprite->setRotation(-135);
		break;
	case UP_RIGHT: movement.x = SPEED_BULLET;
		movement.y = -SPEED_BULLET;
		sprite->setRotation(-45);
		break;
	case DOWN_RIGHT: movement.x = SPEED_BULLET;
		movement.y = SPEED_BULLET;
		sprite->setRotation(45);
		break;
	case DOWN_LEFT: movement.x = -SPEED_BULLET;
		movement.y = SPEED_BULLET;
		sprite->setRotation(135);
		break;
	default:
		life = false; // будет стрелять при остановке корабля
		break;
	}

	x = movement.x * deltaTime.asSeconds();
	y = movement.y * deltaTime.asSeconds();

	//----------------- Коллизии --------------------------
	// если уходит за экран, то прекращает свое существование
	if (sprite->getPosition().x < 0 - WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().y < 0 - WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().x >= SCRN_WIDTH + WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().y >= SCRN_HEIGTH + HEIGTH_BULLET) {
		life = false;
	}
	//------------------------------------------------------
	sprite->move(x, y);
}
