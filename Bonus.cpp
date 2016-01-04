#include "Bonus.h"

using namespace std;

void Bonus::AddBonus(Vector2f getPosition, TextureGame & textureGame, SSound & sSound) {
	timeCreateBonus += clock.restart();
	if (timeCreateBonus.asSeconds() > TIME_CREATE_BONUS) {
		Direction dir = DOWN; 
		typeBonus = static_cast<TypeBonuses> (Math::GetRandomNumerForSection(1, sizeTypeBonuses));
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
		case Bonus::DOUBLE_SHOT:
			name = DOUBLE_SHOT_IMAGE;
			texture = &textureGame.doubleShotTexture;
			break;
		case Bonus::TRIPLE_SHOOT:
			name = TRIPLE_SHOT_IMAGE;
			texture = &textureGame.tripleShotTexture;
			break;
		}
		Entity addBonus(getPosition, name, *texture, sSound, 1);
		addBonus.direction = dir; // присваивает сгенерированное направление
		addBonus.speed = SPEED_BONUS;
		bonuses.push_back(addBonus);
		timeCreateBonus = Time::Zero;
	}
}

void Bonus::GetMoveEveryBonus(const Time & deltaTime, RenderWindow & window) {
	for (list<Entity>::iterator it = bonuses.begin(); it != bonuses.end();) {
		it->MoveObject(deltaTime);
		it->CheckForCollisions(window);
		if (!it->isLife) {
			delete it->sprite;
			it = bonuses.erase(it);
		}
		else  ++it;
	}
}

bool CheckProbably() {
	return (Math::GetRandomNumerForSection(1, 4) == 4); // задается вероятность выпадения ;
}