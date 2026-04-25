#pragma once
#include "Singleton.h"
#include "Object.h"
#include "Collider.h"
#include <vector>
#include <math.h>

using namespace std;

class CollisionManager :public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;

private:

	// Private constructor to avoid more than one instance
	CollisionManager() {};

	vector<Collider*> colliders;
	vector<Collider*> collidersToRemove;

	void RemoveColliders();

	bool CheckSquaresCollision(Collider* r1, Collider* r2);
	bool CheckCirclesCollision(Collider* c1, Collider* c2);
	bool CheckCircleSquareCollision(Collider* c, Collider* r);

	void CheckCollisions();

public:

	void Init();

	void Update(void);

	void Destroy();

	void AddCollider(Collider* _collider);
};