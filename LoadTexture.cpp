#include "LoadTexture.h"

void LoadingFromFileTexture(TextureGame & textureGame) {
	textureGame.playerTexture = new Texture;
	textureGame.playerTexture->loadFromFile(PATH_PLAYER_SHIP);
	textureGame.asteroidMediumTexture.loadFromFile(PATH_MEIUM_ASTEROID);
	textureGame.asteroidSmallTexture.loadFromFile(PATH_SMALL_ASTEROID);
	textureGame.asteroidTexture.loadFromFile(PATH_ASTEROID);

	textureGame.blueLaserTexture.loadFromFile(PATH_TO_BLUE_BULLET);
	textureGame.redLaserTexture.loadFromFile(PATH_TO_RED_BULLET);
	textureGame.bombTexture.loadFromFile(PATH_BOMB);
	textureGame.decreaseTexture.loadFromFile(PATH_DECREASE);
	textureGame.increaseTexture.loadFromFile(PATH_INCREASE_DAMAGE);
	textureGame.invulnerabilityTexture.loadFromFile(PATH_INVULNERABILITY);

	textureGame.repairTexture.loadFromFile(PATH_REPAIR);
	textureGame.starTexture.loadFromFile(PATH_STAR);
	textureGame.enemyBossTexture.loadFromFile(PATH_BOSS);
	textureGame.enemyEasyTexture.loadFromFile(PATH_EASY_ENEMY);
	textureGame.enemyMiddleTexture.loadFromFile(PATH_MIDDLE_ENEMY);
	textureGame.explosionTexture.loadFromFile(PATH_TO_EXPLOSION);
}

void DeleteTexture(TextureGame & textureGame) {
	delete textureGame.playerTexture;
}