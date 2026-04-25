#include "EngineManager.h"

void EngineManager::CreateSingletons()
{
	SaveManager::CreateSingleton();

	TimeManager::CreateSingleton();

	InputManager::CreateSingleton();

	ObjectManager::CreateSingleton();

	CollisionManager::CreateSingleton();

	graphicInstanceCreated = false;
	graphicInit = false;
	engineInit = false;
	canInitGraphic = false;
	canDestroyGraphic = false;
	graphicDestroyed = false;
	render = false;

	EngineManager* data = this;
	mut = SDL_CreateMutex();
	graphicThread = SDL_CreateThread(StartGraphicThread, "Graphic Thread", (void*) data);

	GraphicManager::CreateSingleton();

	//while (!graphicInstanceCreated)
		//SDL_Delay(1);

	SoundManager::CreateSingleton();
}

int EngineManager::StartGraphicThread(void* data)
{
	EngineManager* engineManager = (EngineManager*)data;

	/*
	if (SDL_mutexP(engineManager->mut) == -1)
	{
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}

	GraphicManager::CreateSingleton();
	engineManager->graphicInstanceCreated = true;

	if (SDL_mutexV(engineManager->mut) == -1)
	{
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}

	while (!engineManager->canInitGraphic)
		SDL_Delay(1);

	if (SDL_mutexP(engineManager->mut) == -1)
	{
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}

	/*
	if (!GraphicManager::GetInstance().Init())
	{
		engineManager->success = false;
		return -1;
	}
	

	engineManager->graphicInit = true;

	if (SDL_mutexV(engineManager->mut) == -1)
	{
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}
	*/

	while (!engineManager->engineInit)
		SDL_Delay(1);

	while (!engineManager->canDestroyGraphic)
	{
		while (!engineManager->render)
			SDL_Delay(1);

		if (SDL_mutexP(engineManager->mut) == -1)
		{
			fprintf(stderr, "Couldn't lock mutex\n");
			exit(-1);
		}

		//printf("Graphic update\n");
		GraphicManager::GetInstance().Update();


		if (SDL_mutexV(engineManager->mut) == -1)
		{
			fprintf(stderr, "Couldn't unlock mutex\n");
			exit(-1);
		}

		engineManager->render = false;

		SDL_Delay(0);
	}

	/*
	if (SDL_mutexP(engineManager->mut) == -1)
	{
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}

	GraphicManager::GetInstance().Destroy();

	engineManager->graphicDestroyed = true;

	if (SDL_mutexV(engineManager->mut) == -1)
	{
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}
	*/

	return 0;
}

bool EngineManager::Init(bool* _quit)
{
	if (SDL_mutexP(mut) == -1)
	{
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}

	success = true;

	SaveManager::GetInstance().Init();

	TimeManager::GetInstance().Init();

	if (!InputManager::GetInstance().Init())
		success = false;

	ObjectManager::GetInstance().Init();
	CollisionManager::GetInstance().Init();

	if (SDL_mutexV(mut) == -1)
	{
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}

	canInitGraphic = true;

	//while (!graphicInit)
		//SDL_Delay(1);

	
	if (!GraphicManager::GetInstance().Init())
		success = false;
	

	if (SDL_mutexP(mut) == -1)
	{
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}

	if (!SoundManager::GetInstance().Init())
		success = false;

	quit = _quit;

	engineInit = true;

	if (SDL_mutexV(mut) == -1)
	{
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}

	return success;
}

void EngineManager::UpdatePre()
{
	//printf("Engine update\n");

	SDL_Delay(1);

	TimeManager::GetInstance().Update();
	InputManager::GetInstance().Update();
	ObjectManager::GetInstance().Update();
}

void EngineManager::UpdatePos()
{
	CollisionManager::GetInstance().Update();
	render = true;
	//GraphicManager::GetInstance().Update();
	SoundManager::GetInstance().Update();
}

void EngineManager::LateUpdate()
{
	InputManager::GetInstance().LateUpdate();
}

void EngineManager::Destroy()
{
	SoundManager::GetInstance().Destroy();

	canDestroyGraphic = true;

	//while (!graphicDestroyed)
		//SDL_Delay(1);

	int threadState;
	SDL_WaitThread(graphicThread, &threadState);

	GraphicManager::GetInstance().Destroy();

	CollisionManager::GetInstance().Destroy();
	ObjectManager::GetInstance().Destroy();
	InputManager::GetInstance().Destroy();
	TimeManager::GetInstance().Destroy();
	SaveManager::GetInstance().Destroy();

	SDL_DestroyMutex(mut);

	quit = NULL;

	DestroySingleton();
}

void EngineManager::Quit()
{
	*quit = true;
}