#include "SoundManager.h"

bool SoundManager::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
	}

	LoadAudioFiles();

	return success;
}

void SoundManager::Update()
{
	while (clipsToRemove.size() > 0)
	{
		for (int i = 0; i < audioClips.size(); i++)
		{
			AudioClip* clipToRemove = clipsToRemove[0];
			if (audioClips[i] == clipToRemove)
			{
				audioClips.erase(audioClips.begin() + i);
				clipsToRemove.erase(clipsToRemove.begin());

				clipToRemove = NULL;

				break;
			}
		}
	}
}

void SoundManager::Destroy()
{
	for (int i = 0; i < audioClips.size(); i++)
	{
		if (audioClips[i] != NULL)
		{
			audioClips[i]->Destroy();
			delete audioClips[i];
			audioClips[i] = NULL;
		}
	}

	audioClips.clear();

	Mix_Quit();

	DestroySingleton();
}

void SoundManager::AddAudioClip(AudioClip* _clip)
{
	audioClips.push_back(_clip);
}

void SoundManager::RemoveAudioClip(AudioClip* _clip)
{
	clipsToRemove.push_back(_clip);
}

void SoundManager::LoadAudioFiles()
{
	for (int i = 0; i < audioClips.size(); i++)
	{
		audioClips[i]->LoadFile();
	}
}