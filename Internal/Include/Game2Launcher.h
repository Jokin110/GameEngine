#pragma once
#include "Game2Manager.h"
#include "EngineManager.h"

class Game2Launcher
{
private:
	bool quit = false;
public:
	Game2Launcher();
	~Game2Launcher();

	void LaunchGame();
};