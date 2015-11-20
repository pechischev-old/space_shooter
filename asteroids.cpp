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
		int damage;
		String name;
		if (objectSize == 1) {
			name = NAME_ASTEROID;
			speed = SPEED_ASTEROID;
			health = HEALTH_ASTEROID;
			damage = DAMAGE_ASTEROID;
		}
		else if (objectSize == 2) {
			name = NAME_MEDIUM_ASTEROID;
			speed = SPEED_MEIUM_ASTEROID;
			health = HEALTH_MEDIUM_ASTEROID;
			damage = DAMAGE_MEDIUM_ASTEROID;
		}
		else if (objectSize == 3) {
			name = NAME_SMALL_ASTEROID;
			damage = DAMAGE_SMALL_ASTEROID;
			speed = SPEED_SMALL_ASTEROID;
			health = HEALTH_SMALL_ASTEROID;
		}
		Entity addAsteroid(getPosition.x, getPosition.y, name);
		addAsteroid.direction = dir; // присваивает сгенерированное направление
		addAsteroid.speed = speed;
		addAsteroid.damage = damage;
		addAsteroid.health = health;
		asteroids->push_back(addAsteroid);
		timeCreateAsteroid = Time::Zero;
	}
}

void Asteroid::GetMoveEveryAsteroid(const Time & deltaTime, RenderWindow & window, Bonus & bonus) {
	for (list<Entity>::iterator it = asteroids->begin(); it != asteroids->end();) {
		it->MoveObject(deltaTime);
		SetRotateAsteroid(*it);
		it->CheckForCollisions(window);
		if (it->health <= 0) {
			it->Explosion(deltaTime);
			
		}
		if (!it->isLife) {
			if (it->isKilled) {  // выпадение бонуса
				if (CheckProbably())
					bonus.AddBonus(Vector2f(it->x, it->y));
			}
			it->texture->~Texture();
			delete it->sprite;
			it = asteroids->erase(it);
		}
		else  ++it;
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