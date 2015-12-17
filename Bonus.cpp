#include "Bonus.h"

using namespace std;

void Bonus::AddBonus(Vector2f getPosition, TextureGame & textureGame) {
	auto SpecifySizeBonus  = [&]() {
		int point = 1 + rand() % 5;
		return point;
	};
	timeCreateBonus += clock.restart();
	if (timeCreateBonus.asSeconds() > TIME_CREATE_BONUS) {
		Direction dir = DOWN; 
		typeBonus = static_cast<TypeBonuses> (SpecifySizeBonus());
		String name;
		Texture *texture = NULL;
		switch (typeBonus)
		{
		case Bonus::REPAIR:
			name = REPAIR_IMAGE;
			texture = &textureGame.repairTexture;
			break;
		case Bonus::DECREASE:
			name = DECREASE_IMAGE;
			texture = &textureGame.decreaseTexture;
			break;
		case Bonus::INCREASE_DAMAGE:
			name = INCREASE_DAMAGE_IMAGE;
			texture = &textureGame.increaseTexture;
			break;
		case Bonus::INVULNERABILITY:
			name = INVULNERABILITY_IMAGE;
			texture = &textureGame.invulnerabilityTexture;
			break;
		case Bonus::BOMB:
			name = BOMB_IMAGE;
			texture = &textureGame.bombTexture;
			break;
		}
		Entity addBonus(getPosition, name, *texture);
		addBonus.direction = dir; // присваивает сгенерированное направление
		addBonus.speed = SPEED_BONUS;
		bonuses.push_back(addBonus);
		timeCreateBonus = Time::Zero;
	}
}

void Bonus::GetMoveEveryBonus(const Time & deltaTime, RenderWindow & window) {
	for (auto &it : bonuses) {
		it.MoveObject(deltaTime);
		it.CheckForCollisions(window);
	}
	auto updatedEnd = std::remove_if(bonuses.begin(), bonuses.end(), [&](Entity &entity) {
		if (!entity.isLife) {
			delete entity.sprite;
		}
		return !entity.isLife;
	});
	bonuses.erase(updatedEnd, bonuses.end());
}

int IssuanceProbability() {
	int point = 1 + rand() % 4;
	return point;
}

bool CheckProbably() {
	if (IssuanceProbability() == 4)
		return true;
	return false;
}