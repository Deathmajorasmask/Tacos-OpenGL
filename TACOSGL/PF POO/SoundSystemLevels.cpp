#include "SoundSystemLevels.h"

SoundSystemLevels::SoundSystemLevels() {
	p_customOpenALSoft = new customOpenALSoft();
};

SoundSystemLevels::~SoundSystemLevels() {
	delete p_customOpenALSoft;
};

void SoundSystemLevels::sendSoundNotification() {
	soundNotification = true;
}

bool SoundSystemLevels::getSoundNotification() {
	if (soundNotification) {
		soundNotification = false;
		return true;
	}
	return false;
}

int SoundSystemLevels::SoundSystemLevelsMono(std::string dirFileWav, float volumeGain, bool loopSound, float Velx, float Vely, float Velz, float Posx, float Posy, float Posz) {
	return p_customOpenALSoft->customOALSSoundMono(dirFileWav, volumeGain, loopSound, Velx, Vely, Velz, Posx, Posy,Posz);
}

int SoundSystemLevels::SoundSystemLevelsMonoBucle() {
	return p_customOpenALSoft->customOALSSoundMonoBucle();
}

int SoundSystemLevels::SoundSystemLevelsMonoStop() {
	return p_customOpenALSoft->customOALSSoundMonoStop();
}

int SoundSystemLevels::SoundSystemLevelsStereo(std::string dirFileWav, float volumeGain, bool loopSound) {
	return p_customOpenALSoft->customOALSSoundStereo(dirFileWav,volumeGain,loopSound);
}

int SoundSystemLevels::SoundSystemLevelsStereoBucle() {
	return p_customOpenALSoft->customOALSSoundStereoBucle();
}

int SoundSystemLevels::SoundSystemLevelsStereoStop() {
	return p_customOpenALSoft->customOALSSoundStereoStop();
}