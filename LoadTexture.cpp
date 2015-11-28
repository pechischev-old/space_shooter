#include "LoadTexture.h"

void TextureGame::LoadingFromFileTexture() {
	playerTexture.loadFromFile(PATH_PLAYER_SHIP);
	asteroidMediumTexture.loadFromFile(PATH_MEIUM_ASTEROID);
	asteroidSmallTexture.loadFromFile(PATH_SMALL_ASTEROID);
	asteroidTexture.loadFromFile(PATH_ASTEROID);

	blueLaserTexture.loadFromFile(PATH_TO_BLUE_BULLET);
	redLaserTexture.loadFromFile(PATH_TO_RED_BULLET);
	bombTexture.loadFromFile(PATH_BOMB);
	decreaseTexture.loadFromFile(PATH_DECREASE);
	increaseTexture.loadFromFile(PATH_INCREASE_DAMAGE);
	invulnerabilityTexture.loadFromFile(PATH_INVULNERABILITY);

	repairTexture.loadFromFile(PATH_REPAIR);
	starTexture.loadFromFile(PATH_STAR);
	enemyBossTexture.loadFromFile(PATH_BOSS);
	enemyEasyTexture.loadFromFile(PATH_EASY_ENEMY);
	enemyMiddleTexture.loadFromFile(PATH_MIDDLE_ENEMY);
	explosionTexture.loadFromFile(PATH_TO_EXPLOSION);
}

/*void DeleteTexture(TextureGame & textureGame) {
	delete textureGame.playerTexture;
	delete textureGame.asteroidMediumTexture;
	delete textureGame.asteroidSmallTexture;
	delete textureGame.asteroidTexture;
	delete textureGame.blueLaserTexture;
	delete textureGame.bombTexture;
	delete textureGame.decreaseTexture;
	delete textureGame.enemyBossTexture;
	delete textureGame.enemyEasyTexture;
	delete textureGame.enemyMiddleTexture;
	delete textureGame.explosionTexture;
	delete textureGame.increaseTexture;
	delete textureGame.invulnerabilityTexture;
	delete textureGame.redLaserTexture;
	delete textureGame.repairTexture;
	delete textureGame.starTexture;
}*/