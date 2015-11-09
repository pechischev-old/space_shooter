#include "Entity.h"


using namespace sf;
using namespace std;

Entity::Entity(float X, float Y, float Width, float Height, String Name) {
	x = X; 
	y = Y;
	width = Width;
	height = Height;
	name = Name;
	texture = new Texture;
	sprite = new Sprite;
	texture->loadFromFile("resourse/images/" + name + ".png");
	sprite->setTexture(*texture);
	sprite->setTextureRect(IntRect(0, 0, width, height));
	sprite->setOrigin(width / 2, height / 2);
	sprite->setPosition(x, y);
	isLife = true;
	health = 100;
}

void Entity::GetExplosion(const Time & deltaTime) {
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