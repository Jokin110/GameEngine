#pragma once
#include "Object.h"
#include "BoxCollider.h"

class GroundChunk : public Object
{
private:
	BoxCollider* collider = NULL;

	float speed;

public:
	GroundChunk(Vector2 pos, float speed);

	void Start();
	void Update();
	void Destroy();
};

