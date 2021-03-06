#include "asteroids.h"

using namespace sf;
using namespace std;

void InitializeAsteroid(Asteroid & asteroid) {
	
}

void Asteroid::AddAsteroid(TextureGame & textureGame) {
	timeCreateAsteroid += clock.restart();
	if (timeCreateAsteroid.asSeconds() > timeToCreateAsteroid) {
		Direction dir = LEFT; //GetDirection();
		Vector2f getPosition = GetRandomPosition(dir);
		int objectSize = SpecifySize();
		int speed;
		float health;
		int damage;
		String name;
		Texture *texture = NULL;
		if (objectSize == 1) {
			name = NAME_ASTEROID;
			speed = SPEED_ASTEROID;
			health = HEALTH_ASTEROID;
			damage = DAMAGE_ASTEROID;
			texture = &textureGame.asteroidTexture;
		}
		else if (objectSize == 2) {
			name = NAME_MEDIUM_ASTEROID;
			speed = SPEED_MEIUM_ASTEROID;
			health = HEALTH_MEDIUM_ASTEROID;
			damage = DAMAGE_MEDIUM_ASTEROID;
			texture = &textureGame.asteroidMediumTexture;
		}
		else if (objectSize == 3) {
			name = NAME_SMALL_ASTEROID;
			damage = DAMAGE_SMALL_ASTEROID;
			speed = SPEED_SMALL_ASTEROID;
			health = HEALTH_SMALL_ASTEROID;
			texture = &textureGame.asteroidSmallTexture;
		}
		Entity addAsteroid(getPosition.x, getPosition.y, name, *texture);
		addAsteroid.direction = dir; // ����������� ��������������� �����������
		addAsteroid.speed = float(speed);
		addAsteroid.damage = float(damage);
		addAsteroid.health = float(health);
		asteroids.push_back(addAsteroid);
		timeCreateAsteroid = Time::Zero;
	}
}

void Asteroid::GetMoveEveryAsteroid(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame) {
	for (list<Entity>::iterator it = asteroids.begin(); it != asteroids.end();) {
		it->MoveObject(deltaTime);
		SetRotateAsteroid(*it);
		it->CheckForCollisions(window);
		if (it->health <= 0) {
			it->Explosion(deltaTime, textureGame.explosionTexture);
			
		}
		if (!it->isLife) {
			if (it->isKilled) {  // ��������� ������
				if (CheckProbably())
					bonus.AddBonus(Vector2f(it->x, it->y), textureGame);
			}
			delete it->sprite;
			it = asteroids.erase(it);
		}
		else  ++it;
	}
}

void Asteroid::SetRotateAsteroid(Entity & asteroid) {
	asteroid.sprite->rotate(3);
}

int SpecifySize() {
	srand(unsigned int(time(NULL)));
	int point = 1 + rand() % 2;
	return point;
}