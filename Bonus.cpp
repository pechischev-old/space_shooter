#include "Bonus.h"

using namespace std;

void InitializeBonus(Bonus & bonus) {
	bonus.bonuses = new list<Entity>;
}

void Bonus::AddBonus(Vector2f getPosition) {
	TextureGame textureGame;
	timeCreateBonus += clock.restart();
	if (timeCreateBonus.asSeconds() > TIME_CREATE_BONUS) {
		Direction dir = DOWN; 
		int objectSize = SpecifySizeBonus();
		int speed;
		String name;
		Texture texture;
		if (objectSize == 1) {
			name = REPAIR_IMAGE;
			texture = textureGame.repairTexture;
		}
		else if (objectSize == 2) {
			name = DECREASE_IMAGE;
			texture = textureGame.decreaseTexture;
		}
		else if (objectSize == 3) {
			name = INCREASE_DAMAGE_IMAGE;
			texture = textureGame.increaseTexture;
		}
		else if (objectSize == 4) {
			name = INVULNERABILITY_IMAGE;
			texture = textureGame.invulnerabilityTexture;
		}
		else if (objectSize == 5) {
			name = BOMB_IMAGE;
			texture = textureGame.bombTexture;
		}
		Entity addBonus(getPosition.x, getPosition.y, name, texture);
		addBonus.direction = dir; // присваивает сгенерированное направление
		addBonus.speed = SPEED_BONUS;
		bonuses->push_back(addBonus);
		timeCreateBonus = Time::Zero;
	}
}

void Bonus::GetMoveEveryBonus(const Time & deltaTime, RenderWindow & window) {
	for (list<Entity>::iterator it = bonuses->begin(); it != bonuses->end();) {
		it->MoveObject(deltaTime);
		it->CheckForCollisions(window);
		if (!it->isLife) {
			//it->texture->~Texture();
			delete it->sprite;
			it = bonuses->erase(it);
		}
		else  ++it;
	}
}

int SpecifySizeBonus() {
	srand(time(0));
	int point = 1 + rand() % 5;
	return point;
}

int IssuanceProbability() {
	srand(time(0));
	int point = 1 + rand() % 4;
	return point;
}

bool CheckProbably() {
	if (IssuanceProbability() == 4)
		return true;
	return false;
}