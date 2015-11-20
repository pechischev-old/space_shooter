#include "star.h"

using namespace std;

void InitializeStar(Star & star) {
	star.stars = new list<Entity>;
}

void LoadStarInList(Star & star, const Time & deltaTime, RenderWindow & window) {
	bool isEndLoading = false;
	while (star.stars->size() < 25) {
		star.AddStar();
		star.UpdateStateStar(deltaTime, window);
	}
	isEndLoading = true;
}

void Star::AddStar() {
	if (stars->size() < 60) {
		timeCreateStar += clock.restart();
		if (timeCreateStar.asSeconds() > 0.7) {
			Direction dir = LEFT;
			Vector2f setPosition = GetRandomPosition(dir);
			Entity addStar(setPosition.x, setPosition.y, NAME_STAR);
			addStar.direction = LEFT;
			addStar.speed = SetRandomSpeed();
			stars->push_back(addStar);
			timeCreateStar = Time::Zero;
		}
	}

}

void Star::UpdateStateStar(const Time & deltaTime, RenderWindow & window) {
	for (list<Entity>::iterator it5 = stars->begin(); it5 != stars->end();) {
		it5->MoveObject(deltaTime);
		it5->CheckForCollisions(window);
		if (!it5->isLife) {
			/*it5->texture->~Texture();
			delete it5->sprite;
			it5 = stars->erase(it5);*/
			Direction dir = LEFT;
			Vector2f posit = GetRandomPosition(dir);
			it5->isLife = true;
			it5->sprite->setPosition(posit);
		}
		 ++it5;
	}
}

int SetRandomSpeed() {
	srand(time(0));
	int speed = 270 + rand() % 400;
	return speed;
}