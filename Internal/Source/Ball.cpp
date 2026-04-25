#include "Ball.h"
#include "GraphicManager.h"
#include "TimeManager.h"
#include "Game1Manager.h"
#include "InputManager.h"
#include "EngineManager.h"

Ball::Ball()
{
	collider = new CircleCollider(10.5, Vector2(0, 0), false, this, "ball");

	spritePath = "../../../../Media/ball.bmp";

	scale = 1.5;

	paddleTouchSound = new AudioClip("../../../../Media/Sound/paddleTouch.wav");
}

void Ball::Start()
{
	Object::Start();

	Reset();
}

void Ball::Update()
{
	Object::Update();

	pos += dir.GetNormalized() * speed * TimeManager::GetInstance().GetDeltaTime();

	if (pos.GetY() - GetHeight() / 2.0 < 0.0)
	{
		pos = Vector2(pos.GetX(), GetHeight() / 2.0);

		dir = Vector2(dir.GetX(), -dir.GetY());
	}
	else if (pos.GetY() + GetHeight() / 2.0 > GraphicManager::GetInstance().GetScreenHeight())
	{
		pos = Vector2(pos.GetX(), GraphicManager::GetInstance().GetScreenHeight() - GetHeight() / 2.0);

		dir = Vector2(dir.GetX(), -dir.GetY());
	}

	if (pos.GetX() - GetWidth() / 2.0 < 0.0)
	{
		Game1Manager::GetInstance().Point(false);
		Reset();
	}

	if (pos.GetX() + GetWidth() / 2.0 > GraphicManager::GetInstance().GetScreenWidth())
	{
		Game1Manager::GetInstance().Point(true);
		Reset();
	}
}

void Ball::Destroy()
{
	collider = NULL;

	paddleTouchSound = NULL;

	Object::Destroy();
}

void Ball::OnCollisionEnter(Collider* other)
{
	Object::OnCollisionEnter(other);

	if (other->GetTag() == "paddle")
	{

		if (pos.GetY() > other->GetParent()->GetPosY() + other->GetParent()->GetHeight() / 6.0)
		{
			dir = Vector2(-dir.GetX(), 1.0);
		}
		else if (pos.GetY() < other->GetParent()->GetPosY() - other->GetParent()->GetHeight() / 6.0)
		{
			dir = Vector2(-dir.GetX(), -1.0);
		}
		else
		{
			dir = Vector2(-dir.GetX(), 0.0);
		}

		paddleTouchSound->Play();
	}
}

void Ball::Reset()
{
	pos = Vector2(GraphicManager::GetInstance().GetScreenWidth() / 2.0, GraphicManager::GetInstance().GetScreenHeight() / 2.0);

	dir = rand() % 2 == 0 ? Vector2().left() : Vector2().right();
}