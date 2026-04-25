#include "GameManager.h"

GameManager::GameManager() 
{

}

void GameManager::Update()
{
	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_D) && !created)
	{
		DotObject* dot4 = new DotObject(400, 100, false, true, "Dot 4");

		//delete(dot4);
		//dot4 = NULL;

		created = true;
		printf("Dot created with name %s!\n", dot4->GetName());
	}
}