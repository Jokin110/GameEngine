#include "Player.h"
#include "GraphicManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SaveManager.h"

Player::Player()
{
	spritePath = "../../../../Media/dinosaur.png";
	pivot = Vector2(0.5, 1.0);

	collider = new BoxCollider(Vector2(44, 89), Vector2(0, 0), false, this, "player");

	resetPos = Vector2(GraphicManager::GetInstance().GetScreenWidth() / 8.0, GraphicManager::GetInstance().GetScreenHeight() * 7.0 / 8.0 + 9);
	pos = resetPos;
}

void Player::Start()
{
	Object::Start();

	highScore = SaveManager::GetInstance().GetInt("highscore", 0);
}

void Player::Update()
{
	Object::Update();

	if ((InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_SPACE) || InputManager::GetInstance().GetMouseButtonDown(1) || InputManager::GetInstance().GetJoystickButtonDown(0)) && canJump)
	{
		Jump();
	}

	if (!canJump)
	{
		velocity += Vector2().down() * fallSpeed * TimeManager::GetInstance().GetDeltaTime();
	}

	pos += velocity * TimeManager::GetInstance().GetDeltaTime();

	points += TimeManager::GetInstance().GetDeltaTime();
}

void Player::Jump()
{
	velocity = Vector2().up() * jumpForce;
	canJump = false;
}

void Player::Reset()
{
	TimeManager::GetInstance().SetTimeScale(1.0);

	points = 0;
	gameOver = false;
	pos = resetPos;
}

void Player::EndGame()
{
	TimeManager::GetInstance().SetTimeScale(0);
	gameOver = true;

	if (points > highScore)
	{
		highScore = points;
		SaveManager::GetInstance().SetInt("highscore", highScore);
	}
}

void Player::OnTriggerEnter(Collider* other)
{
	Object::OnTriggerEnter(other);

	if (other->GetTag() == "ground")
	{
		canJump = true;
		velocity = Vector2().zero();
	}
	else if (other->GetTag() == "obstacle")
	{
		EndGame();
	}
}

void Player::Destroy()
{
	collider = NULL;
	Object::Destroy();
}