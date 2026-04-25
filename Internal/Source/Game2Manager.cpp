#include "Game2Manager.h"

Game2Manager::Game2Manager()
{
	obstacleSpawnTime = 0.0f;

	gameOverText = new Text("../../../../Media/Fonts/lazy.ttf", 64, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() / 2, GraphicManager::GetInstance().GetScreenHeight() / 2), Vector2(0.5, 0.5));
	gameOverText->SetActive(false);
	pointsText = new Text("../../../../Media/Fonts/lazy.ttf", 32, { 0, 0, 0 }, Vector2(10, 10), Vector2(0, 0));
	highScoreText = new Text("../../../../Media/Fonts/lazy.ttf", 32, { 0, 0, 0 }, Vector2(10, 45), Vector2(0, 0));
	resetText = new Text("../../../../Media/Fonts/lazy.ttf", 20, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() * 0.95, 35), Vector2(1, 0));
	resetText->SetActive(false);
	quitText = new Text("../../../../Media/Fonts/lazy.ttf", 20, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() * 0.95, 10), Vector2(1, 0));
}

void Game2Manager::Start()
{
	gameOverText->SetText("Game Over!");
	pointsText->SetText("Points: 0");
	highScoreText->SetText("Highscore: " + to_string(player.GetHighScore()));
	resetText->SetText("Press R or Square to reset");
	quitText->SetText("Press Q or Start to quit");

	updateTextTime = TimeManager::GetInstance().GetTime() + 1.0;
}

void Game2Manager::Update()
{
	if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_Q) || InputManager::GetInstance().GetJoystickButtonDown(7))
	{
		EngineManager::GetInstance().Quit();
	}

	if ((InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_R) || InputManager::GetInstance().GetJoystickButtonDown(2)) && player.GetGameOver())
	{
		player.Reset();
		wasGameOver = false;

		// Hide Game Over UI and reset score tracker
		gameOverText->SetActive(false);
		resetText->SetActive(false);
		pointsText->SetText("Points: 0");
		highScoreText->SetText("Highscore: " + to_string(player.GetHighScore()));
	}

	if (obstacleSpawnTime <= TimeManager::GetInstance().GetTime())
	{
		Obstacle* newObstacle = new Obstacle(obstacleSpawnPos, speed, &player);
		obstacleSpawnTime = TimeManager::GetInstance().GetTime() + obstacleSpawnDelay;
	}

	if (updateTextTime <= TimeManager::GetInstance().GetTime() && !player.GetGameOver())
	{
		pointsText->SetText("Points: " + to_string((int)player.GetPoints()));
		updateTextTime = TimeManager::GetInstance().GetTime() + 1.0;
	}

	if (player.GetGameOver() && !wasGameOver)
	{
		wasGameOver = true;
		gameOverText->SetActive(true);
		resetText->SetActive(true);
		pointsText->SetText("Points: " + to_string((int)player.GetPoints()));
		highScoreText->SetText("Highscore: " + to_string(player.GetHighScore()));
	}
}

void Game2Manager::Destroy()
{
	gameOverText = NULL;
	pointsText = NULL;
	highScoreText = NULL;
	resetText = NULL;
	quitText = NULL;

	DestroySingleton();
}