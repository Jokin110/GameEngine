#include "Game1Manager.h"

Game1Manager::Game1Manager() 
{
	pointsText = new Text("../../../../Media/Fonts/lazy.ttf", 32, { 0, 0, 0 }, Vector2(10, 10), Vector2(0, 0));
	resetText = new Text("../../../../Media/Fonts/lazy.ttf", 20, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() * 0.95, 35), Vector2(1, 0));
	resetText->SetActive(false);
	quitText = new Text("../../../../Media/Fonts/lazy.ttf", 20, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() * 0.95, 10), Vector2(1, 0));

	winnerText = new Text("../../../../Media/Fonts/lazy.ttf", 64, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() / 2, GraphicManager::GetInstance().GetScreenHeight() / 2), Vector2(0.5, 0.5));
	winnerText->SetActive(false);

	music = new AudioClip("../../../../Media/Sound/music.wav", true, true);
}

void Game1Manager::Start()
{
	music->Play();

	pointsText->SetText("Score: 0 - 0");
	resetText->SetText("Press R to reset");
	quitText->SetText("Press Q or Start to quit");
}

void Game1Manager::Update()
{
	if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_Q) || InputManager::GetInstance().GetJoystickButtonDown(7))
	{
		EngineManager::GetInstance().Quit();
	}

	if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_M))
	{
		music->Pause();
	}

	if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_R) && gameOver)
	{
		Reset();
	}
}

void Game1Manager::Point(bool leftPlayer)
{
	if (leftPlayer)
	{
		playerLeftPoints++;
		string pointsString = "Score: " + to_string(playerLeftPoints) + " - " + to_string(playerRightPoints);
		pointsText->SetText(pointsString);

		if (playerLeftPoints >= winPoints)
		{
			TimeManager::GetInstance().SetTimeScale(0.0);
			winnerText->SetText("Left Player Wins!!");
			winnerText->SetActive(true);
			gameOver = true;
			resetText->SetActive(true);
		}
	}
	else
	{
		playerRightPoints++;
		string pointsString = "Score: " + to_string(playerLeftPoints) + " - " + to_string(playerRightPoints);
		pointsText->SetText(pointsString);

		if (playerRightPoints >= winPoints)
		{
			TimeManager::GetInstance().SetTimeScale(0.0);
			winnerText->SetText("Right Player Wins!!");
			winnerText->SetActive(true);
			gameOver = true;
			resetText->SetActive(true);
		}
	}
}

void Game1Manager::Reset()
{
	ball.Reset();
	paddleLeft.Reset();
	paddleRight.Reset();

	winnerText->SetActive(false);
	resetText->SetActive(false);

	playerLeftPoints = 0;
	playerRightPoints = 0;
	string pointsString = "Score: " + to_string(playerLeftPoints) + " - " + to_string(playerRightPoints);
	pointsText->SetText(pointsString);

	TimeManager::GetInstance().SetTimeScale(1.0);

	gameOver = false;
}

void Game1Manager::Destroy()
{
	music = NULL;

	pointsText = NULL;
	winnerText = NULL;

	DestroySingleton();
}