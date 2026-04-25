#pragma once

#include "Vector2.h"
#include <vector>

using namespace std;

class Object;

class Collider
{
protected:
	Vector2 size;
	float radius;

	Vector2 offset;

	bool trigger;

	vector<Collider*> collidingBefore;
	vector<Collider*> collidingWith;

	Object* parent;

	string tag;

	bool isSquare = true;

public:
	Collider(Vector2 _offset, bool _trigger, Object* _parent, string _tag);
	virtual ~Collider() { Destroy(); }

	int GetOffsetX();
	int GetOffsetY();

	bool isTrigger() { return trigger; }

	bool GetIsSquare() { return isSquare; }

	vector<Collider*>* GetCollidingBefore() { return &collidingBefore; }
	bool CollidingBeforeIncludes(Collider* c);

	vector<Collider*>* GetCollidingWith() { return &collidingWith; }
	bool CollidingWithIncludes(Collider* c);

	Object* GetParent();

	int GetSizeX();
	int GetSizeY();

	int GetLeftX();
	int GetRightX();
	int GetTopY();
	int GetBottomY();

	Vector2 GetCenter();
	float GetRadius();

	string GetTag() { return tag; }

	void Destroy();
};

