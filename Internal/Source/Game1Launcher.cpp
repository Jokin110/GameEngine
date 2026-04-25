#include "Game1Launcher.h"

Game1Launcher::Game1Launcher()
{

}

Game1Launcher::~Game1Launcher()
{

}

void Game1Launcher::LaunchGame()
{
	EngineManager::CreateSingleton();
	Game1Manager::CreateSingleton();

	quit = false;

	//Start up SDL and create window
	if (!EngineManager::GetInstance().Init(&quit))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Event handler
		SDL_Event e;

		Game1Manager::GetInstance().Start();

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
			}

			EngineManager::GetInstance().UpdatePre();

			Game1Manager::GetInstance().Update();

			EngineManager::GetInstance().UpdatePos();

			EngineManager::GetInstance().LateUpdate();
		}
	}

	//Free resources and close SDL
	EngineManager::GetInstance().Destroy();
	Game1Manager::GetInstance().Destroy();	// Game Manager is destroyed after engine because the program breaks if the other way
}