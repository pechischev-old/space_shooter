#include "asteroids.h"

using namespace sf;
using namespace std;

void Asteroid::AddAsteroid(TextureGame & textureGame, RenderWindow & window, SSound & sSound) {
	timeCreateAsteroid += clock.restart();
	if (timeCreateAsteroid.asSeconds() > timeToCreateAsteroid) {
		Direction dir = LEFT; 
		Vector2f getPosition = GetRandomPosition(dir, window);
		int speed;
		float health;
		int damage;
		String name;
		Texture *texture = NULL;
		typeAsteroid = static_cast<TypeAsteroid> (Math::GetRandomNumerForSection(1, sizeTypeAsteroid));
		switch (typeAsteroid)
		{
		case Asteroid::SMALL:
			name = NAME_SMALL_ASTEROID;
			damage = DAMAGE_SMALL_ASTEROID;
			speed = SPEED_SMALL_ASTEROID;
			health = HEALTH_SMALL_ASTEROID;
			texture = &textureGame.asteroidSmallTexture;
			break;
		case Asteroid::MIDDLE:
			name = NAME_MEDIUM_ASTEROID;
			speed = SPEED_MEIUM_ASTEROID;
			health = HEALTH_MEDIUM_ASTEROID;
			damage = DAMAGE_MEDIUM_ASTEROID;
			texture = &textureGame.asteroidMediumTexture;
			break;
		case Asteroid::BIG:
			name = NAME_ASTEROID;
			speed = SPEED_ASTEROID;
			health = HEALTH_ASTEROID;
			damage = DAMAGE_ASTEROID;
			texture = &textureGame.asteroidTexture;
			break;
		}
		
		Entity addAsteroid(getPosition, name, *texture, sSound);
		addAsteroid.direction = dir; // присваивает сгенерированное направление
		addAsteroid.speed = float(speed);
		addAsteroid.damage = float(damage);
		addAsteroid.health = float(health);
		addAsteroid.sprite->setScale(1.5f, 1.5f);
		asteroids.push_back(addAsteroid);
		timeCreateAsteroid = Time::Zero;
	}
}

void Asteroid::GetMoveEveryAsteroid(const Time & deltaTime, RenderWindow & window, Bonus & bonus, TextureGame & textureGame, SSound & sSound) {
	for (list<Entity>::iterator it = asteroids.begin(); it != asteroids.end();) {
		it->MoveObject(deltaTime);
		InitRotateAsteroid(*it);
		it->CheckForCollisions(window);
		UpdateVolume(it->explosionSound, SIZE_VOLUME_EXPLOSION);
		if (it->health <= 0) {
			it->Explosion(deltaTime, textureGame.explosionTexture);
			if (it->explosionSound.getStatus() != it->explosionSound.Playing)
				it->explosionSound.play();
		}
		if (!it->isLife) {
			if (it->isKilled) {  // выпадение бонуса
				if (CheckProbably())
					bonus.AddBonus(it->position, textureGame, sSound);
			}
			delete it->sprite;
			it = asteroids.erase(it);
		}
		else  ++it;
	}
}

void Asteroid::InitRotateAsteroid(Entity & asteroid) {
	asteroid.sprite->rotate(3);
}
