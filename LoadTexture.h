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

	Texture asteroidSmallTexture;
	Texture asteroidMediumTexture;
	Texture asteroidTexture;

	Texture bombTexture;
	Texture decreaseTexture;
	Texture increaseTexture;
	Texture invulnerabilityTexture;
	Texture repairTexture;

	Texture explosionTexture;

	Texture starTexture;

	Texture redLaserTexture;
	Texture blueLaserTexture;
	Texture electricBullet;
	void LoadingFromFileTexture();
};
