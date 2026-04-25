#pragma once
#include "Object.h"
#include "BoxCollider.h"
#include "InputManager.h"
#include "AudioClip.h"
#include "Text.h"
#include "EngineManager.h"

class DotObject : public Object
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 111;
	static const int DOT_HEIGHT = 111;

	//Maximum axis velocity of the dot
	float DOT_VEL = 100;

	//Initializes the variables
	DotObject(Vector2 pos, bool canMove, bool collider, string name = "New Game Object");

	void UpdateVelocity();

	//Moves the dot
	void move();

	void Start();
	void Update();
	void Destroy();

	void OnCollisionEnter(Collider* other);
	void OnCollisionExit(Collider* other);
	void OnCollisionStay(Collider* other);
	void OnTriggerEnter(Collider* other);

private:
	//The velocity of the dot
	Vector2 velocity;

	AudioClip* sound = NULL;
	AudioClip* music = NULL;

	Text* testText = NULL;

	BoxCollider* collider = NULL;

	bool canMove;
};

