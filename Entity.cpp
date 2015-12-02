#include "Entity.h"


using namespace sf;
using namespace std;

Entity::Entity(float x, float y, String Name, Texture & texture) {
	this->x = x; 
	this->y = y;
	name = Name;
	sprite = new Sprite;
	sprite->setTexture(texture);
	width = texture.getSize().x;
	height = texture.getSize().y;
	sprite->setTextureRect(IntRect(0, 0, width, height));
	sprite->setOrigin(width / 2, height / 2);
	sprite->setPosition(x, y);
	isLife = true;
	health = 100;
}

void Entity::Explosion(const Time & deltaTime, Texture & texture) { // изменить название функции
	x = sprite->getPosition().x;
	y = sprite->getPosition().y;
	delete(sprite);
	sprite = new Sprite;
	CurrentFrame += NUMBER_OF_FRAMES * deltaTime.asSeconds();
	if (CurrentFrame <= NUMBER_OF_FRAMES) {
		sprite->setTexture(texture);
		sprite->setOrigin(WIDTH_EXPLOSION / 2, HEIGTH_EXPLOSION / 2);
		sprite->setScale(1.5, 1.5);
		sprite->setTextureRect(IntRect(WIDTH_EXPLOSION * int(CurrentFrame), 0, WIDTH_EXPLOSION, HEIGTH_EXPLOSION));
		sprite->setPosition(x, y);
	}
	else {
		isKilled = true;
		isLife = false;
	}

}

void Entity::CheckForCollisions(RenderWindow & window) {
	//----------------- Коллизии --------------------------
	// если уходит за экран, то прекращает свое существование
	if (sprite->getPosition().x < 0 - width) {
		isLife = false;
	}
	if (sprite->getPosition().y < 0 - height) {
		isLife = false;
	}
	if (sprite->getPosition().x >= window.getSize().x + width) {
		isLife = false;
	}
	if (sprite->getPosition().y >= window.getSize().y + height) {
		isLife = false;
	}
}

void Entity::MoveObject(const Time & deltaTime) {
	if (health > 0) {
		Vector2f movement = sprite->getPosition();
		switch (direction) {
		case UP: movement.y = -speed;
			movement.x = 0;
			break;
		case DOWN: movement.y = speed;
			movement.x = 0;
			break;
		case LEFT: movement.x = -speed;
			movement.y = 0;
			break;
		case RIGHT: movement.x = speed;
			movement.y = 0;
			break;
		case UP_LEFT: movement.x = -speed;
			movement.y = -speed;
			break;
		case UP_RIGHT: movement.x = speed;
			movement.y = -speed;
			break;
		case DOWN_RIGHT: movement.x = speed;
			movement.y = speed;
			break;
		case DOWN_LEFT: movement.x = -speed;
			movement.y = speed;
			break;
		default:
			movement.x = 0;
			movement.y = 0;
			break;
		}

		x = movement.x * deltaTime.asSeconds();
		y = movement.y * deltaTime.asSeconds();

		sprite->move(x, y);
	}
}

Vector2f Border(Entity & object, RenderWindow & window) {
	Vector2f limit(0.f, 0.f);
	float heigth = object.height,
		width = object.width,
		X = object.x,
		Y = object.y;
	Vector2f posObject = object.sprite->getPosition();

	if (window.getSize().x <= posObject.x + width / 2) {
		X = -BORDER;
	}
	if (0 >= posObject.x - width / 2) {
		X = BORDER;
	}
	if (window.getSize().y <= posObject.y + heigth / 2) {
		Y = -BORDER;
	}
	if (0 >= posObject.y - heigth / 2) {
		Y = BORDER;
	}
	limit.x = X;
	limit.y = Y;
	return limit;
}

void ClearListObject(list<Entity> & objects) {
	for (list<Entity>::iterator i = objects.begin(); i != objects.end(); ++i) {
		delete i->sprite;
	}
	while (objects.size() != 0) {
		objects.pop_back();
	}
}