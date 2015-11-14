#include "asteroids.h"

using namespace sf;
using namespace std;

void InitializeAsteroid(Asteroid & asteroid) {
	asteroid.asteroids = new list<Entity>;
}

void Asteroid::AddAsteroid() {
	timeCreateAsteroid += clock.restart();
	if (timeCreateAsteroid.asSeconds() > 1.1) {
		Direction dir = LEFT; //GetDirection();
		Vector2f getPosition = GetRandomPosition(dir);
		int objectSize = SpecifySize();
		int speed;
		String name;
		if (objectSize == 1) {
			name = "asteroid";
			speed = 200;
		}
		else if (objectSize == 2) {
			name = "asteroid-medium";
			speed = 230;
		}
		else if (objectSize == 3) {
			name = "asteroid-small";
			speed = 250;
		}
		Entity addAsteroid(getPosition.x, getPosition.y, name);
		addAsteroid.direction = dir; // присваивает сгенерированное направление
		addAsteroid.speed = speed;
		asteroids->push_back(addAsteroid);
		timeCreateAsteroid = Time::Zero;
	}
}

void Asteroid::GetMoveEveryAsteroid(const Time & deltaTime) {
	for (list<Entity>::iterator it = asteroids->begin(); it != asteroids->end();) {
		MoveAsteroid(deltaTime, *it);
		if (it->health <= 0) {
			it->Explosion(deltaTime);
		}
		if (!it->isLife) {
			it->texture->~Texture();
			delete it->sprite;
			it = asteroids->erase(it);
		}
		else  it++;
	}
}

void Asteroid::MoveAsteroid(const Time & deltaTime, Entity & asteroid) {
	if (asteroid.health > 0) {
		Vector2f movement = asteroid.sprite->getPosition();
		switch (asteroid.direction) {
		case UP: movement.y = -asteroid.speed;
			movement.x = 0;
			asteroid.sprite->setRotation(90);
			break;
		case DOWN: movement.y = asteroid.speed;
			movement.x = 0;
			asteroid.sprite->setRotation(-90);
			break;
		case LEFT: movement.x = -asteroid.speed;
			movement.y = 0;
			break;
		case RIGHT: movement.x = asteroid.speed;
			movement.y = 0;
			asteroid.sprite->setRotation(180);
			break;
		case UP_LEFT: movement.x = -asteroid.speed;
			movement.y = -asteroid.speed;
			asteroid.sprite->setRotation(45);
			break;
		case UP_RIGHT: movement.x = asteroid.speed;
			movement.y = -asteroid.speed;
			asteroid.sprite->setRotation(135);
			break;
		case DOWN_RIGHT: movement.x = asteroid.speed;
			movement.y = asteroid.speed;
			asteroid.sprite->setRotation(-135);
			break;
		case DOWN_LEFT: movement.x = -asteroid.speed;
			movement.y = asteroid.speed;
			asteroid.sprite->setRotation(-45);
			break;
		default:
			asteroid.isLife = false;
			break;
		}

		asteroid.x = movement.x * deltaTime.asSeconds();
		asteroid.y = movement.y * deltaTime.asSeconds();

		//-----------------  оллизии --------------------------
		// если уходит за экран, то прекращает свое существование
		if (asteroid.sprite->getPosition().x < 0 - asteroid.width) {
			asteroid.isLife = false;
		}
		if (asteroid.sprite->getPosition().y < 0 - asteroid.height) {
			asteroid.isLife = false;
		}
		if (asteroid.sprite->getPosition().x >= SCRN_WIDTH + asteroid.width) {
			asteroid.isLife = false;
		}
		if (asteroid.sprite->getPosition().y >= SCRN_HEIGTH + asteroid.height) {
			asteroid.isLife = false;
		}
		asteroid.sprite->rotate(3);
		asteroid.sprite->move(asteroid.x, asteroid.y);
	}

}

int SpecifySize() {
	srand(time(0));
	int point = 1 + rand() % 2;
	return point;
}