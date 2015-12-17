#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"

using namespace sf;
using namespace std;

struct TextureGame {
	Texture playerTexture;

	Texture enemyEasyTexture;
	Texture enemyMiddleTexture;
	Texture enemyBossTexture;
	Texture enemyTowerTexture;
	Texture enemyKamikazeTexture;

	Texture asteroidSmallTexture;
	Texture asteroidMediumTexture;
	Texture asteroidTexture;

	Texture bombTexture;
	Texture decreaseTexture;
	Texture increaseTexture;
	Texture invulnerabilityTexture;
	Texture repairTexture;

	Texture explosionTexture;
	Texture explosionBulletTexture;

	Texture starTexture;

	Texture redLaserTexture;
	Texture blueLaserTexture;
	Texture greenLaserTexture;
	Texture electricBullet;
	Texture rocketTexture;

	Texture healthBarTexture;
	Texture emptyBarTexture;
	Texture rageBarTexture;

	Texture fieldTexture;

	void LoadingFromFileTexture();
};

struct TextureMenu {
	Texture fieldTexture;
	Texture instructionTexture;
	void LoadingFromFileTextureForMenu();
};
