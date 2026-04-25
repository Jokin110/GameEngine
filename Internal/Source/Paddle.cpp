#include "Paddle.h"
#include "GraphicManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "EngineManager.h"

Paddle::Paddle(Vector2 _pos, bool _playerLeft)
{
	pos = _pos;
	playerLeft = _playerLeft;

	spritePath = playerLeft ? "../../../../Media/paddleBlue.bmp" : "../../../../Media/paddleRed.bmp";

	collider = new BoxCollider(Vector2(10, 108), Vector2(0, 0), false, this, "paddle");
}

void Paddle::Start()
{
	Object::Start();
}

void Paddle::Update()
{
	Object::Update();

	if (playerLeft)
	{
		if (InputManager::GetInstance().GetKey(SDL_SCANCODE_W) || InputManager::GetInstance().GetJoystickAxisRaw(1) == -1)
		{
			pos += Vector2().up() * speed * TimeManager::GetInstance().GetDeltaTime();
		}
		if (InputManager::GetInstance().GetKey(SDL_SCANCODE_S) || InputManager::GetInstance().GetJoystickAxisRaw(1) == 1)
		{
			pos += Vector2().down() * speed * TimeManager::GetInstance().GetDeltaTime();
		}
	}
	else
	{
		if (InputManager::GetInstance().GetKey(SDL_SCANCODE_UP) || InputManager::GetInstance().GetJoystickAxisRaw(3) == -1)
		{
			pos += Vector2().up() * speed * TimeManager::GetInstance().GetDeltaTime();
		}
		if (InputManager::GetInstance().GetKey(SDL_SCANCODE_DOWN) || InputManager::GetInstance().GetJoystickAxisRaw(3) == 1)
		{
			pos += Vector2().down() * speed * TimeManager::GetInstance().GetDeltaTime();
		}
	}

	if (pos.GetY() - GetHeight() / 2.0 <= 0.0)
	{
		pos = Vector2(pos.GetX(), GetHeight() / 2.0);
	}
	else if (pos.GetY() + GetHeight() / 2.0 >= GraphicManager::GetInstance().GetScreenHeight())
	{
		pos = Vector2(pos.GetX(), GraphicManager::GetInstance().GetScreenHeight() - GetHeight() / 2.0);
	}
}

void Paddle::Reset()
{
	pos = Vector2(pos.GetX(), GraphicManager::GetInstance().GetScreenHeight() / 2.0);
}

void Paddle::Destroy()
{
	collider = NULL;

	Object::Destroy();
}
