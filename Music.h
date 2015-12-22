#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Config.h"

using namespace sf;
using namespace std;

struct SMusic {

};

struct SSound {
	SoundBuffer shootBuffer;
    SoundBuffer explosionBuffer;
	SoundBuffer mouseClickBuffer;
	SoundBuffer takeBonusSound;
	void LoadSound();
};

void UpdateVolume(Sound & sound, float sizeVolume);