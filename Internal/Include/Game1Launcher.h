#pragma once
#include "Game1Manager.h"
#include "EngineManager.h"

class Game1Launcher
{
private:
	bool quit = false;
public:
	Game1Launcher();
	~Game1Launcher();

	void LaunchGame();
};