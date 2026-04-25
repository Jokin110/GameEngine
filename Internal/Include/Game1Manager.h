#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Vector2.h"
#include "Text.h"
#include "Singleton.h"
#include "EngineManager.h"

class Game1Manager :public Singleton<Game1Manager>
{
	friend class Singleton<Game1Manager>;

private:
	Game1Manager();

	Paddle paddleLeft = Paddle(Vector2(GraphicManager::GetInstance().GetScreenWidth() / 10.0, GraphicManager::GetInstance().GetScreenHeight() / 2.0), true);
	Paddle paddleRight = Paddle(Vector2(GraphicManager::GetInstance().GetScreenWidth() * 0.9, GraphicManager::GetInstance().GetScreenHeight() / 2.0), false);

	Ball ball = Ball();

	Text* pointsText = NULL;
	Text* winnerText = NULL;
	Text* resetText = NULL;
	Text* quitText = NULL;

	AudioClip* music = NULL;

	int playerLeftPoints = 0;
	int playerRightPoints = 0;

	int winPoints = 11;

	void Reset();

	bool gameOver = false;

public:

	void Start();
	void Update();
	void Destroy();

	void Point(bool);
};

