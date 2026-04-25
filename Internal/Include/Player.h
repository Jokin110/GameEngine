#pragma once
#include "Object.h"
#include "BoxCollider.h"

class Player : public Object
{
private:
	BoxCollider* collider;
	bool canJump = true;

	void Jump();

	bool gameOver = false;

	Vector2 velocity = Vector2(0, 0);

	float fallSpeed = 250;
	float jumpForce = 250;

	float points = 0;
	int highScore = 0;

	Vector2 resetPos;

public:
	Player();

	void Start();
	void Update();
	void Destroy();

	void EndGame();
	void Reset();

	void OnTriggerEnter(Collider* other);

	bool GetGameOver() { return gameOver; }
	float GetPoints() { return points; }
	int GetHighScore() { return highScore; }
};