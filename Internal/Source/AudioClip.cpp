#include "AudioClip.h"
#include "SoundManager.h"

AudioClip::AudioClip(const char* _src, bool _loop, bool _music)
{
	src = _src;
	if (_loop)
		loop = -1;
	else
		loop = 0;
	music = _music;

	SoundManager::GetInstance().AddAudioClip(this);
}

void AudioClip::Play()
{
	if (!music)
	{
		if (Mix_Paused(-1) == 0 || Mix_Playing(-1) == 0)
			Mix_PlayChannel(-1, sourceClip, loop);
		else
			Mix_Resume(-1);
	}
	else
	{
		if (Mix_PausedMusic() == 1 || Mix_PlayingMusic() == 0)
			Mix_PlayMusic(sourceMusic, loop);
		else
			Mix_ResumeMusic();

		printf("Music playing!\n");
	}
}

void AudioClip::Pause()
{
	if (!music)
		Mix_Pause(-1);
	else
		Mix_PauseMusic();
}

void AudioClip::Stop()
{
	if (!music)
		Mix_HaltChannel(-1);
	else
		Mix_HaltMusic();
}

void AudioClip::Destroy()
{
	if (sourceClip != NULL)
	{
		Mix_FreeChunk(sourceClip);
		sourceClip = NULL;
	}
	if (sourceMusic != NULL)
	{
		Mix_FreeMusic(sourceMusic);
		sourceMusic = NULL;
	}

	SoundManager::GetInstance().RemoveAudioClip(this);
}

void AudioClip::LoadFile()
{
	if (!music)
	{
		sourceClip = Mix_LoadWAV(src);

		if (sourceClip == NULL)
			printf("Failed to load audio\n");
	}
	else
	{
		sourceMusic = Mix_LoadMUS(src);

		if (sourceMusic == NULL)
			printf("Failed to load music\n");
	}
}