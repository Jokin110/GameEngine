#include "Obstacle.h"
#include "TimeManager.h"


Obstacle::Obstacle(Vector2 _pos, float _speed, Player* _player)
{
	spritePath = "../../../../Media/obstacle.png";
	pivot = Vector2(0.5, 1);

	collider = new BoxCollider(Vector2(88, 93), Vector2(0, 0), true, this, "obstacle");

	pos = _pos;
	speed = _speed;
	player = _player;
}

void Obstacle::Start()
{
	Object::Start();
}

void Obstacle::Update()
{
	Object::Update();

	pos += Vector2().left() * speed * TimeManager::GetInstance().GetDeltaTime();

	if (pos.GetX() < -GetWidth() / 2.0)
	{
		Destroy();
	}

	if (player->GetGameOver())
	{
		Destroy();
	}
}

void Obstacle::Destroy()
{
	collider = NULL;

	Object::Destroy();
}
