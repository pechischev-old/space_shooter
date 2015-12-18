#include "Entity.h"


using namespace sf;
using namespace std;

Entity::Entity(Vector2f position, String Name, Texture & texture) {
	this->position = position;
	name = Name;
	sprite = new Sprite;
	sprite->setTexture(texture);
	sizeObject = Vector2f(texture.getSize());
	sprite->setTextureRect(IntRect(0, 0, int(sizeObject.x), int(sizeObject.y)));
	sprite->setOrigin(sizeObject.x / 2, sizeObject.y / 2);
	sprite->setPosition(position);
	isLife = true;
	isKilled = false;
	health = 100;
}

void Entity::Explosion(const Time & deltaTime, Texture & texture) { // изменить название функции
	position = sprite->getPosition();
	delete(sprite);
	sprite = new Sprite;
	CurrentFrame += SPEED_FRAMES * deltaTime.asSeconds();
	if (CurrentFrame <= NUMBER_OF_FRAMES) {
		sprite->setTexture(texture);
		sprite->setOrigin(WIDTH_EXPLOSION / 2, HEIGTH_EXPLOSION / 2);
		sprite->setScale(2.5, 2.5);
		sprite->setTextureRect(IntRect(WIDTH_EXPLOSION * int(CurrentFrame), 0, WIDTH_EXPLOSION, HEIGTH_EXPLOSION));
		sprite->setPosition(position);
	}
	else {
		isKilled = true;
		isLife = false;
	}

}

void Entity::CheckForCollisions(RenderWindow & window) {
	//----------------- Коллизии --------------------------
	// если уходит за экран, то прекращает свое существование
	if (sprite->getPosition().x < 0 - sizeObject.x) {
		isLife = false;
	}
	if (sprite->getPosition().y < 0 - sizeObject.y) {
		isLife = false;
	}
	if (sprite->getPosition().x >= window.getSize().x + sizeObject.x) {
		isLife = false;
	}
	if (sprite->getPosition().y >= window.getSize().y + sizeObject.y) {
		isLife = false;
	}
}

void Entity::MoveObject(const Time & deltaTime) {
	if (health > 0 ) { 	
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
		case UP_LEFT: movement.x = -speed / sqrt(2.f);
			movement.y = -speed / sqrt(2.f);
			break;
		case UP_RIGHT: movement.x = speed / sqrt(2.f);
			movement.y = -speed / sqrt(2.f);
			break;
		case DOWN_RIGHT: movement.x = speed / sqrt(2.f);
			movement.y = speed / sqrt(2.f);
			break;
		case DOWN_LEFT: movement.x = -speed / sqrt(2.f);
			movement.y = speed / sqrt(2.f);
			break;
		default:
			movement.x = 0;
			movement.y = 0;
			break;
		}
		position = movement * deltaTime.asSeconds();
		if (name != NAME_PLAYER_SHIP)
			sprite->move(position);
	}
}

void Entity::SetRotationObject(Vector2f posPoint) {
	Vector2f posObject = sprite->getPosition();
	sprite->setRotation(Math::CalculateRotate(posPoint, posObject));
}

Vector2f Border(Entity & object, RenderWindow & window) {
	Vector2f limit(0.f, 0.f);
	float heigth = object.sizeObject.y,
		width = object.sizeObject.x,
		X = object.position.x,
		Y = object.position.y;
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