#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "GroundChunk.h"
#include "Vector2.h"
#include "Text.h"
#include "Singleton.h"
#include "EngineManager.h"

class Game2Manager :public Singleton<Game2Manager>
{
	friend class Singleton<Game2Manager>;

private:
	Game2Manager();

	float speed = 200;

	float obstacleSpawnDelay = 3.0;
	float obstacleSpawnTime;

	Vector2 obstacleSpawnPos = Vector2(Vector2(GraphicManager::GetInstance().GetScreenWidth() + 50, GraphicManager::GetInstance().GetScreenHeight() * 7.0 / 8.0 + 9));

	GroundChunk chunk0 = GroundChunk(Vector2(GraphicManager::GetInstance().GetScreenWidth() / 2.0, GraphicManager::GetInstance().GetScreenHeight() * 7.0 / 8.0), speed);
	GroundChunk chunk1 = GroundChunk(Vector2(GraphicManager::GetInstance().GetScreenWidth() / 2.0 + 2400, GraphicManager::GetInstance().GetScreenHeight() * 7.0 / 8.0), speed);

	Player player = Player();

	Text* gameOverText = NULL;
	Text* pointsText = NULL;
	Text* highScoreText = NULL;
	Text* resetText = NULL;
	Text* quitText = NULL;

	float updateTextTime = 0;
	bool wasGameOver = false;

public:

	void Start();
	void Update();
	void Destroy();
};