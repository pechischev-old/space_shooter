#include "LoadTexture.h"

void TextureGame::LoadingFromFileTexture() {
	playerTexture.loadFromFile(PATH_PLAYER_SHIP);
	asteroidMediumTexture.loadFromFile(PATH_MEDIUM_ASTEROID);
	asteroidSmallTexture.loadFromFile(PATH_SMALL_ASTEROID);
	asteroidTexture.loadFromFile(PATH_ASTEROID);

	blueLaserTexture.loadFromFile(PATH_TO_BLUE_BULLET);
	redLaserTexture.loadFromFile(PATH_TO_RED_BULLET);
	greenLaserTexture.loadFromFile(PATH_TO_GREEN_BULLET);
	electricBullet.loadFromFile(PATH_ELECTRIC_BULLET);
	rocketTexture.loadFromFile(PATH_ROCKET);

	bombTexture.loadFromFile(PATH_BOMB);
	decreaseTexture.loadFromFile(PATH_DECREASE);
	increaseTexture.loadFromFile(PATH_INCREASE_DAMAGE);
	invulnerabilityTexture.loadFromFile(PATH_INVULNERABILITY);

	repairTexture.loadFromFile(PATH_REPAIR);
	starTexture.loadFromFile(PATH_STAR);

	enemyBossTexture.loadFromFile(PATH_BOSS);
	enemyEasyTexture.loadFromFile(PATH_EASY_ENEMY);
	enemyMiddleTexture.loadFromFile(PATH_MIDDLE_ENEMY);
	enemyTowerTexture.loadFromFile(PATH_TOWER_ENEMY);
	enemyKamikazeTexture.loadFromFile(PATH_KAMIKAZE_ENEMY);

	explosionTexture.loadFromFile(PATH_TO_EXPLOSION);
	explosionBulletTexture.loadFromFile(PATH_TO_EXPLOSION_BULLET);

	healthBarTexture.loadFromFile(PATH_HEALTH_BAR);
	emptyBarTexture.loadFromFile(PATH_EMPTY_BAR);
	rageBarTexture.loadFromFile(PATH_RAGE_BAR);

}

void TextureMenu::LoadingFromFileTextureForMenu() {
	fieldTexture.loadFromFile(PATH_FIELD);
	instructionTexture.loadFromFile(PATH_INSTRUCTION);
}