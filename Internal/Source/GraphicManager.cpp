#include "GraphicManager.h"


bool GraphicManager::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}

			//Initialize SDL_ttf
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}

	vector<Object*>* objects = ObjectManager::GetInstance().GetObjects();

	//Load media
	for (int i = 0; i < objectsToLoad.size(); i++)
	{
		if (!objectsToLoad[i]->GetSprite()->loadFromFile(objectsToLoad[i]->GetSpritePath()))
		{
			printf("Failed to load dot texture!\n");
			success = false;
		}
	}

	for (int i = 0; i < texts.size(); i++)
	{
		if (texts[i]->InitFont())
		{
			if (!texts[i]->GetSprite()->loadFromRenderedText(texts[i]->GetText(), texts[i]->GetFont(), texts[i]->GetColor()))
			{
				printf("Failed to load text texture!\n");
				success = false;
			}
		}
		else
		{
			printf("Failed to load text font!\n");
			success = false;
		}
	}

	return success;
}

void GraphicManager::Update()
{
	RemoveTexts();

	for (int i = 0; i < objectsToLoad.size(); i++)
	{
		objectsToLoad[i]->GetSprite()->loadFromFile(objectsToLoad[i]->GetSpritePath());
	}

	objectsToLoad.clear();

	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	// Render object sprites
	vector<Object*>* objects = ObjectManager::GetInstance().GetObjects();

	for (int i = 0; i < (*objects).size(); i++)
	{
		if ((*objects)[i]->isActive())
			(*objects)[i]->GetSprite()->render((*objects)[i]->GetXWithoutPivot(), (*objects)[i]->GetYWithoutPivot(), (*objects)[i]->GetScale());
	}

	// Render texts
	for (int i = 0; i < texts.size(); i++)
	{
		if (texts[i]->GetIsActive())
			texts[i]->GetSprite()->render(texts[i]->GetPosWithoutAnchors().GetX(), texts[i]->GetPosWithoutAnchors().GetY(), texts[i]->GetScale());
	}

	//Update screen
	SDL_RenderPresent(renderer);
}

void GraphicManager::RemoveTexts()
{
	while (textsToRemove.size() > 0)
	{
		for (int i = 0; i < texts.size(); i++)
		{
			Text* textToRemove = textsToRemove[0];
			if (texts[i] == textToRemove)
			{
				texts.erase(texts.begin() + i);
				textsToRemove.erase(textsToRemove.begin());

				//delete objectToRemove;
				textToRemove = NULL;

				break;
			}
		}
	}
}

void GraphicManager::Destroy()
{
	vector<Object*>* objects = ObjectManager::GetInstance().GetObjects();

	//Free loaded images
	for (int i = 0; i < (*objects).size(); i++)
	{
		if ((*objects)[i] != NULL)
			(*objects)[i]->GetSprite()->free();
	}

	for (int i = 0; i < texts.size(); i++)
	{
		if (texts[i] != NULL)
		{
			texts[i]->Destroy();
			delete texts[i];
			texts[i] = NULL;
		}
	}

	texts.clear();

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	DestroySingleton();
}


SDL_Renderer* GraphicManager::GetRenderer() { return renderer; }