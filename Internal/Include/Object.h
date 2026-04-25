#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "Collider.h"
#include <vector>

using namespace std;

class Object
{
private:
	Vector2 prevPos;

	int Clamp(int min, int max, int value);

protected:
	string name;

	Vector2 pos = Vector2(0, 0);

	Vector2 pivot = Vector2(0.5, 0.5);

	float rotation;

	float scale = 1;

	Sprite sprite;
	string spritePath;

	vector<Collider*> colliders;

	bool active;

public:
	Object();

	string GetName() { return name; }

	virtual float GetPosX() { return pos.GetX(); }
	virtual float GetPosY() { return pos.GetY(); }

	float GetWidth() { return sprite.getWidth() * scale; }
	float GetHeight() { return sprite.getHeight() * scale; }

	float GetXWithoutPivot() { return pos.GetX() - pivot.GetX() * GetWidth(); }
	float GetYWithoutPivot() { return pos.GetY() - pivot.GetY() * GetHeight(); }

	virtual float GetRotation() { return rotation; }
	float GetScale() { return scale; }

	virtual Sprite* GetSprite() { return &sprite; }
	virtual string GetSpritePath() { return spritePath; }

	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	virtual void OnCollisionEnter(Collider* other);
	virtual void OnTriggerEnter(Collider* other);

	virtual void OnCollisionStay(Collider* other);
	virtual void OnTriggerStay(Collider* other);

	virtual void OnCollisionExit(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	void UndoMovement(Collider* myCollider, Collider* other);

	void SetActive(bool _value) { active = _value; }
	bool isActive() { return active; }

	void AddCollider(Collider* collider) { colliders.push_back(collider); }
};

