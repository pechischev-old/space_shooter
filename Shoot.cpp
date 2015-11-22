#include "Shoot.h"
#include "math.h"

#define PI 3.14159265    

using namespace sf;
using namespace std;

Shoot::Shoot(float X, float Y, float width, float heigth, Direction direction, String path) {
	texture = new Texture;
	sprite = new Sprite;
	texture->loadFromFile(path);
	sprite->setTexture(*texture);
	sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	sprite->setScale(2, 2);
	sprite->setPosition(X + heigth / 11, Y + width / 11);
	dir = direction;
	x = X;
	y = Y;
	dx = x;
	dy = y;
	life = true;
}

void Shoot::CheckForCollisions(RenderWindow & window) {
	//----------------- Коллизии --------------------------
	// если уходит за экран, то прекращает свое существование
	if (sprite->getPosition().x < 0 - WIDTH_BULLET){
		life = false;
	}
	if (sprite->getPosition().y < 0 - HEIGTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().x >= window.getSize().x + WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().y >= window.getSize().y + HEIGTH_BULLET) {
		life = false;
	}
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
		life = false; 
		break;
	}

	x = movement.x * deltaTime.asSeconds();
	y = movement.y * deltaTime.asSeconds();

	sprite->move(x, y);
}

void Shoot::MoveBulletHardEnemy(const Time & deltaTime) {
	x += SPEED_HARD_ENEMY * deltaTime.asSeconds() * (rememPos.x - dx) ;
	y += SPEED_HARD_ENEMY * deltaTime.asSeconds() * (rememPos.y - dy) ;
	sprite->setPosition(x, y);
	sprite->setRotation(atan2((rememPos.y - dy), (rememPos.x - dx)) * 180 / PI);
}
