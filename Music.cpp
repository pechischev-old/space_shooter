#include "Music.h"


void SSound::LoadSound() {
	shootBuffer.loadFromFile(PATH_SHOOT_SOUND);
	explosionBuffer.loadFromFile(PATH_EXPLOSION_SOUND);
	mouseClickBuffer.loadFromFile(PATH_MOUSECLICK_SOUND);
	takeBonusSound.loadFromFile(PATH_PICK_UP_BONUS_SOUND);
}

void UpdateVolume(Sound & sound, float sizeVolume) {
	sound.setVolume(sizeVolume);
}

