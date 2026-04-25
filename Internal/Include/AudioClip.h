#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <stdio.h>

class AudioClip
{
private:
	Mix_Chunk* sourceClip = NULL;
	Mix_Music* sourceMusic = NULL;
	const char* src;
	int loop = 0;
	bool music;

public:
	AudioClip(const char* src, bool loop = false, bool music = false);
	~AudioClip() { Destroy(); }

	void Play();
	void Pause();
	void Stop();

	void Destroy();

	void LoadFile();
};
