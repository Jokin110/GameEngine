#pragma once
#include "Object.h"
#include "BoxCollider.h"
#include "Player.h"

class Obstacle : public Object
{
private:
	BoxCollider* collider;
	float speed;

	Player* player = NULL;

public:
	Obstacle(Vector2 pos, float speed, Player*);

	void Start();
	void Update();
	void Destroy();
};

