#include "GroundChunk.h"
#include "TimeManager.h"
#include "GraphicManager.h"

GroundChunk::GroundChunk(Vector2 _pos, float _speed)
{
	spritePath = "../../../../Media/groundChunk.png";

	pivot = Vector2(0.5, 0.0);

	collider = new BoxCollider(Vector2(2400, 16), Vector2(0, 8), true, this, "ground");

	speed = _speed;

	pos = _pos;
}

void GroundChunk::Start()
{
	Object::Start();
}

void GroundChunk::Update()
{
	Object::Update();

	pos += Vector2().left() * speed * TimeManager::GetInstance().GetDeltaTime();

	if (pos.GetX() < -GetWidth() / 2.0)
	{
		pos = Vector2(GetWidth() * 1.5, GraphicManager::GetInstance().GetScreenHeight() * 7.0 / 8.0);
	}
}

void GroundChunk::Destroy()
{
	collider = NULL;

	Object::Destroy();
}