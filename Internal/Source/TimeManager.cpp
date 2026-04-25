#include "TimeManager.h"

void TimeManager::Init()
{
	float prevFrameTime = 0;

	float time = 0;
	float deltaTime = 0;

	float timeScale = 1;

	float unscaledTime = 0;
	float unscaledDeltaTime = 0;
}

void TimeManager::Update()
{
	deltaTime = (SDL_GetTicks() - prevFrameTime) / 1000 * timeScale;
	unscaledDeltaTime = (SDL_GetTicks() - prevFrameTime) / 1000;

	time += deltaTime;
	unscaledTime += unscaledDeltaTime;

	prevFrameTime = SDL_GetTicks();
}

void TimeManager::Destroy()
{
	DestroySingleton();
}