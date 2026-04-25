#pragma once
#include "Object.h"
#include "CircleCollider.h"
#include "AudioClip.h"

class Ball : public Object
{
private:
	float speed = 250.0f;
	Vector2 dir;

	CircleCollider* collider;

	AudioClip* paddleTouchSound = NULL;

public:
	Ball();

	void Start();
	void Update();
	void Destroy();

	void OnCollisionEnter(Collider* other);

	void Reset();
};

