#include "star.h"

using namespace std;

void LoadStarInList(Star & star, const Time & deltaTime, RenderWindow & window, TextureGame & textureGame) {
	bool isEndLoading = false;
	while (star.stars.size() < 25) {
		//star.AddStar(*textureGame.starTexture);
		star.UpdateStateStar(deltaTime, window);
	}
	isEndLoading = true;
}

void Star::AddStar(TextureGame & textureGame, RenderWindow & window) {
	auto SetRandomSpeed = [&]() {
		int speed = 270 + rand() % 400;
		return speed;
	};
	if (stars.size() < 40) {
		timeCreateStar += clock.restart();
		if (timeCreateStar.asSeconds() > 0.7) {
			Direction dir = LEFT;
			Vector2f setPosition = GetRandomPosition(dir, window);
			Entity addStar(setPosition, NAME_STAR, textureGame.starTexture);
			addStar.direction = LEFT;
			addStar.speed = float(SetRandomSpeed());
			stars.push_back(addStar);
			timeCreateStar = Time::Zero;
		}
	}

}

void Star::UpdateStateStar(const Time & deltaTime, RenderWindow & window) {
	for (auto &it5 : stars) {
		it5.MoveObject(deltaTime);
		it5.CheckForCollisions(window);
		if (!it5.isLife) {
			Direction dir = LEFT;
			Vector2f posit = GetRandomPosition(dir, window);
			it5.isLife = true;
			it5.sprite->setPosition(posit);
		}
	}
}