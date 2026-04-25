#pragma once
#include "Singleton.h"
#include "SaveManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "GraphicManager.h"
#include "SoundManager.h"
#include <SDL_thread.h>

class EngineManager : public Singleton<EngineManager>
{
	friend class Singleton<EngineManager>;

private:

	// Private constructor to avoid more than one instance
	EngineManager() { CreateSingletons(); }

	bool success;

	static int StartGraphicThread(void * data);

	SDL_Thread* graphicThread;

	bool graphicInit;
	bool graphicInstanceCreated;
	bool engineInit;
	bool canInitGraphic;
	bool canDestroyGraphic;
	bool graphicDestroyed;
	bool render;

	bool* quit;
	SDL_mutex* mut;

public:
	void CreateSingletons();

	bool Init(bool* quit);

	void UpdatePre();

	void UpdatePos();

	void LateUpdate();

	void Destroy();

	void Quit();
};
