#include "asteroids.h"

using namespace sf;
using namespace std;

void InitializeAsteroid(Asteroid & asteroid) {
	asteroid.asteroids = new list<Entity>;
}

void Asteroid::AddAsteroid() {
	timeCreateAsteroid += clock.restart();
	if (timeCreateAsteroid.asSeconds() > TIME_CREATE_ASTEROID) {
		Direction dir = LEFT; //GetDirection();
		Vector2f getPosition = GetRandomPosition(dir);
		int objectSize = SpecifySize();
		int speed;
		float health;
		String name;
		if (objectSize == 1) {
			name = NAME_ASTEROID;
			speed = 200;
			health = 250;
		}
		else if (objectSize == 2) {
			name = NAME_MEDIUM_ASTEROID;
			speed = 230;
			health = 150;
		}
		else if (objectSize == 3) {
			name = NAME_SMALL_ASTEROID;
			speed = 250;
			health = 50;
		}
		Entity addAsteroid(getPosition.x, getPosition.y, name);
		addAsteroid.direction = dir; // присваивает сгенерированное направление
		addAsteroid.speed = speed;
		addAsteroid.health = health;
		asteroids->push_back(addAsteroid);
		timeCreateAsteroid = Time::Zero;
	}
}

void Asteroid::GetMoveEveryAsteroid(const Time & deltaTime, RenderWindow & window) {
	for (list<Entity>::iterator it = asteroids->begin(); it != asteroids->end();) {
		it->MoveObject(deltaTime);
		SetRotateAsteroid(*it);
		it->CheckForCollisions(window);
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

void Asteroid::SetRotateAsteroid(Entity & asteroid) {
	asteroid.sprite->rotate(3);
}

int SpecifySize() {
	srand(time(0));
	int point = 1 + rand() % 2;
	return point;
}