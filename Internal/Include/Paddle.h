#pragma once
#include "Object.h"
#include "BoxCollider.h"

class Paddle : public Object
{
private:
	BoxCollider* collider = NULL;
	float speed = 300.0;
	bool playerLeft;

public:
	Paddle(Vector2 pos, bool leftPlayer);

	void Start();
	void Update();
	void Destroy();

	void Reset();
	Collider* GetCollider() { return collider; }
};

