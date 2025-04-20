#pragma once

#include "customOpenALSoft.h"

class SoundSystemLevels
{
private:
	customOpenALSoft* p_customOpenALSoft;
	bool soundNotification;
public:
	SoundSystemLevels();
	~SoundSystemLevels();

	void sendSoundNotification();

	bool getSoundNotification();

	int SoundSystemLevelsMono(std::string dirFileWav, float volumeGain = 1.0, bool loopSound = false, float Velx = 0.0f, float Vely = 0.0f, float Velz = 0.0f, float Posx = 1.0f, float Posy = 0.0f, float Posz = 0.0f);

	int SoundSystemLevelsMonoBucle();

	int SoundSystemLevelsMonoStop();

	int SoundSystemLevelsStereo(std::string dirFileWav, float volumeGain = 1.0, bool loopSound = false);

	int SoundSystemLevelsStereoBucle();

	int SoundSystemLevelsStereoStop();
};