#include <stdio.h>
#include <string>
#include "Game1Launcher.h"
#include "Game2Launcher.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[])
{
	Game1Launcher game1Launcher;
	Game2Launcher game2Launcher;

	int userInput = 0;

	do
	{
		cout << "Choose what game to launch: \n\t1 - Game 1. \n\t2 - Game 2. \n> ";
		cin >> userInput;

		switch (userInput)
		{
		case 1:
			game1Launcher.LaunchGame();
			break;
		case 2:
			game2Launcher.LaunchGame();
			break;
		}

	} while (userInput > 0 && userInput < 3);

	/*
	//Main loop flag
	bool quit = false;

	//Start up SDL and create window
	if (!EngineManager::GetInstance().Init(&quit))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Event handler
		SDL_Event e;

		gameManager.Start();

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

			gameManager.Update();

			EngineManager::GetInstance().UpdatePos();

			EngineManager::GetInstance().LateUpdate();
		}
	}

	//Free resources and close SDL
	gameManager.Destroy();
	EngineManager::GetInstance().Destroy();
	*/

	return 0;
}