#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"

using namespace sf;
using namespace std;

struct TextureGame {
	Texture playerTexture;// = new Texture;

	Texture enemyEasyTexture;// = new Texture;
	Texture enemyMiddleTexture;// = new Texture;
	Texture enemyBossTexture;// = new Texture;

	Texture asteroidSmallTexture;// = new Texture;
	Texture asteroidMediumTexture;// = new Texture;
	Texture asteroidTexture;// = new Texture;

	Texture bombTexture;// = new Texture;
	Texture decreaseTexture;// = new Texture;
	Texture increaseTexture;// = new Texture;
	Texture invulnerabilityTexture;// = new Texture;
	Texture repairTexture;// = new Texture;

	Texture explosionTexture;// = new Texture;

	Texture starTexture;// = new Texture;

	Texture redLaserTexture;// = new Texture;
	Texture blueLaserTexture;// = new Texture;
	void LoadingFromFileTexture();
};


//void DeleteTexture(TextureGame & textureGame);