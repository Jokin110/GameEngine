#pragma once

#include "Singleton.h"
#include "SDL.h"

/**
Input Manager class
*/
class TimeManager :public Singleton<TimeManager>
{
	friend class Singleton<TimeManager>;

private:
	// Private constructor to avoid more than one instance
	TimeManager() {};

	float prevFrameTime = 0;

	float time = 0;
	float deltaTime = 0;

	float timeScale = 1;

	float unscaledTime = 0;
	float unscaledDeltaTime = 0;

public:
	void Init();

	void Update(void);

	void Destroy();

	float GetTime() { return time; }
	float GetDeltaTime() { return deltaTime; }

	float GetTimeScale() { return timeScale; }
	void SetTimeScale(float _timeScale) { timeScale = _timeScale; }

	float GetUnscaledTime() { return unscaledTime; }
	float GetUnscaledDeltaTime() { return unscaledDeltaTime; }
};