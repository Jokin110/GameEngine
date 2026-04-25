#pragma once

#include "Singleton.h"
#include "AudioClip.h"
#include <vector>

using namespace std;

class SoundManager :public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;

private:
	// Private constructor to avoid more than one instance
	SoundManager() { audioClips.clear(); clipsToRemove.clear(); };

	vector<AudioClip*> audioClips;
	vector<AudioClip*> clipsToRemove;

public:
	bool Init();

	void Update(void);

	void Destroy();

	void AddAudioClip(AudioClip* clip);
	void RemoveAudioClip(AudioClip* clip);

	void LoadAudioFiles();
};