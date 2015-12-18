#include "Shoot.h"
#include "math.h"

using namespace sf;
using namespace std;

Shoot::Shoot(Vector2f position, Vector2f sizeObject, Direction direction, Texture & texture, String Name) {
	sprite = new Sprite;
	sprite->setTexture(texture);
	sprite->setOrigin(float(texture.getSize().x) / 2, float(texture.getSize().y) / 2);
	sprite->setScale(2, 2);
	sprite->setPosition(position.x + sizeObject.x / 2, position.y + sizeObject.y / 2);
	dir = direction;
	name = Name;
	this->position = position;
	oldPosition = position;
	life = true;
	health = 100;
}

void Shoot::CheckForCollisions(RenderWindow & window) {
	//----------------- �������� --------------------------
	float height = sprite->getLocalBounds().height;
	float width = sprite->getLocalBounds().width;
	// ���� ������ �� �����, �� ���������� ���� �������������
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

void Shoot::Explosion(const Time & deltaTime, Texture & texture) { // �������� �������� �������
	position = sprite->getPosition();
	delete(sprite);
	sprite = new Sprite;
	currentFrame += SPEED_FRAMES_BULLET * deltaTime.asSeconds();
	if (currentFrame <= NUMBER_OF_FRAMES_BULLET) {
		sprite->setTexture(texture);
		sprite->setOrigin(WIDTH_EXPLOSION / 2, HEIGTH_EXPLOSION / 2);
		sprite->setTextureRect(IntRect(WIDTH_EXPLOSION * int(currentFrame), 0, WIDTH_EXPLOSION, HEIGTH_EXPLOSION));
		sprite->setScale(1.5f, 1.5f);
		sprite->setPosition(position);
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

	position.x = movement.x * deltaTime.asSeconds();
	position.y = movement.y * deltaTime.asSeconds();

	sprite->move(position);
}

void Shoot::MoveBulletHardEnemy(const Time & deltaTime, Vector2f posObject, int speed) {
	Vector2f newPosition = isRocket ? position : oldPosition;
	position.x += speed * Math::Normalize(posObject, newPosition).x;
	position.y += speed * Math::Normalize(posObject, newPosition).y;
	sprite->setPosition(position);
	sprite->setRotation(Math::CalculateRotate(posObject, newPosition));
}

void UpdateStateBullet(const Time & deltaTime, RenderWindow & window, list<Shoot> & bullets, TextureGame & textureGame, Vector2f posPlayer) {
	for (auto  &it : bullets) {
		it.CheckForCollisions(window);
		if (it.isOtherBullet && !it.isExplosion) {
			it.MoveBulletHardEnemy(deltaTime, it.rememPos, SPEED_OTHER_BULLET);
		}
		else if ( it.isRocket && !it.isExplosion) {
			it.MoveBulletHardEnemy(deltaTime, posPlayer, SPEED_ROCKET);
		}
		else {
			it.MoveBullet(deltaTime);
		}
		if (it.isExplosion) {
			it.dir = NONE;
			if (it.name != NAME_ELECTRIC_BULLET) {
				it.Explosion(deltaTime, textureGame.explosionBulletTexture);
			}
			else {
				it.life = false; // ��������� �������� 
			}
		}
		if (it.name == NAME_ROCKET) {
			it.life = it.health > 0;
		}
	}
	auto updatedEnd = std::remove_if(bullets.begin(), bullets.end(), [&](Shoot & bullet) {
		if (!bullet.life) {
			bullet.isExplosion = false;
			delete bullet.sprite;
		}
		return !bullet.life;
	});
	bullets.erase(updatedEnd, bullets.end());
}

void ClearList(list<Shoot> & bullets) {
	for (list<Shoot>::iterator i = bullets.begin(); i != bullets.end(); ++i) {
		delete i->sprite;
	}
	while (bullets.size() != 0) {
		bullets.pop_back();
	}
}