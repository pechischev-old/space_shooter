#include "Shoot.h"
#include "math.h"

using namespace sf;
using namespace std;

Shoot::Shoot(float X, float Y, float width, float heigth, Direction direction, Texture & texture, String Name) {
	sprite = new Sprite;
	sprite->setTexture(texture);
	sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite->setScale(2, 2);
	sprite->setPosition(X + heigth / 11, Y + width / 11);
	dir = direction;
	name = Name;
	x = X;
	y = Y;
	dx = x;
	dy = y;
	life = true;
}

void Shoot::CheckForCollisions(RenderWindow & window) {
	//----------------- Коллизии --------------------------
	float height = sprite->getLocalBounds().height;
	float width = sprite->getLocalBounds().width;
	// если уходит за экран, то прекращает свое существование
	if (sprite->getPosition().x < 0 - width){
		life = false;
	}
	if (sprite->getPosition().y < 0 - height) {
		life = false;
	}
	if (sprite->getPosition().x >= window.getSize().x + width) {
		life = false;
	}
	if (sprite->getPosition().y >= window.getSize().y + height) {
		life = false;
	}
	
}

void Shoot::Explosion(const Time & deltaTime, Texture & texture) { // изменить название функции
	x = sprite->getPosition().x;
	y = sprite->getPosition().y;
	delete(sprite);
	sprite = new Sprite;
	currentFrame += SPEED_FRAMES_BULLET * deltaTime.asSeconds();
	if (currentFrame <= NUMBER_OF_FRAMES_BULLET) {
		sprite->setTexture(texture);
		sprite->setOrigin(WIDTH_EXPLOSION / 2, HEIGTH_EXPLOSION / 2);
		sprite->setTextureRect(IntRect(WIDTH_EXPLOSION * int(currentFrame), 0, WIDTH_EXPLOSION, HEIGTH_EXPLOSION));
		sprite->setPosition(x, y);
	}
	else {
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
		movement.x = 0;
		movement.y = 0;
		break;
	}

	x = movement.x * deltaTime.asSeconds();
	y = movement.y * deltaTime.asSeconds();

	sprite->move(x, y);
}

void Shoot::MoveBulletHardEnemy(const Time & deltaTime) {
	if (!isExplosion) {
		x += float(SPEED_HARD_ENEMY * deltaTime.asSeconds() * (rememPos.x - dx));
		y += float(SPEED_HARD_ENEMY * deltaTime.asSeconds() * (rememPos.y - dy));
		sprite->setPosition(x, y);
		sprite->setRotation(float(atan2((rememPos.y - dy), (rememPos.x - dx)) * 180 / M_PI));
	}
}

void Shoot::MoveRocket(const Time & deltaTime, Vector2f posPlayer) {
	if (!isExplosion) {
		//float distance = sqrt((posPlayer.x - x)*(posPlayer.x - x) + (posPlayer.x - y)*(posPlayer.x - y));
		//x += 5 * (posPlayer.x - x) / distance;  // совершает рывки почему-то
		//y += 5 * (posPlayer.y - y) / distance;
		x += float(SPEED_HARD_ENEMY * deltaTime.asSeconds() * (posPlayer.x - x));
		y += float(SPEED_HARD_ENEMY * deltaTime.asSeconds() * (posPlayer.y - y));
		sprite->setPosition(x, y);
		sprite->setRotation(float(atan2((posPlayer.y - y), (posPlayer.x - x)) * 180 / M_PI));
	}
}


void UpdateStateBullet(const Time & deltaTime, RenderWindow & window, list<Shoot> & bullets, TextureGame & textureGame, Vector2f posPlayer) {
	for (list<Shoot>::iterator it = bullets.begin(); it != bullets.end();) {
		it->CheckForCollisions(window);
		if (it->isOtherBullet) {
			it->MoveBulletHardEnemy(deltaTime);
		}
		else if ( it->isRocket) {
			it->MoveRocket(deltaTime, posPlayer);
		}
		else {
			it->MoveBullet(deltaTime);
		}
		if (it->isExplosion) {
			it->dir = NONE;
			if (it->name != NAME_ELECTRIC_BULLET) {
				it->Explosion(deltaTime, textureGame.explosionBulletTexture);
			}
			else {
				it->life = false; // отдельная анимация 
			}
		}
		if (!it->life) {
			it->isExplosion = false;
			delete it->sprite;
			it = bullets.erase(it);
		}
		else  ++it;
	}
}


void ClearList(list<Shoot> & bullets) {
	for (list<Shoot>::iterator i = bullets.begin(); i != bullets.end(); ++i) {
		delete i->sprite;
	}
	while (bullets.size() != 0) {
		bullets.pop_back();
	}
}