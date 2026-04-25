#include "Collider.h"
#include "CollisionManager.h"
#include "Object.h"

Collider::Collider(Vector2 _offset, bool _trigger, Object* _parent, string _tag)
{
	offset = _offset;

	trigger = _trigger;

	parent = _parent;

	tag = _tag;

	collidingBefore.clear();
	collidingWith.clear();

	CollisionManager::GetInstance().AddCollider(this);
	parent->AddCollider(this);
}

bool Collider::CollidingBeforeIncludes(Collider* _c)
{
	bool value = false;

	for (int i = 0; i < collidingBefore.size(); i++)
	{
		if (collidingBefore[i] == _c)
		{
			value = true;
			break;
		}
	}

	return value;
}

bool Collider::CollidingWithIncludes(Collider* _c)
{
	bool value = false;

	for (int i = 0; i < collidingWith.size(); i++)
	{
		if (collidingWith[i] == _c)
		{
			value = true;
			break;
		}
	}

	return value;
}

void Collider::Destroy()
{
	if (parent != NULL)
	{
		parent = NULL;
	}
}


int Collider::GetOffsetX() { return offset.GetX() * GetParent()->GetScale(); }
int Collider::GetOffsetY() { return offset.GetY() * GetParent()->GetScale(); }

Object* Collider::GetParent() { return parent; }

int Collider::GetSizeX() { return size.GetX() * GetParent()->GetScale(); }
int Collider::GetSizeY() { return size.GetY() * GetParent()->GetScale(); }

int Collider::GetLeftX() { return offset.GetX() * GetParent()->GetScale(); }
int Collider::GetRightX() { return GetOffsetX() + GetSizeX(); }
int Collider::GetTopY() { return offset.GetY() * GetParent()->GetScale(); }
int Collider::GetBottomY() { return GetOffsetY() + GetSizeY(); }

Vector2 Collider::GetCenter() { return Vector2(GetOffsetX(), GetOffsetY()); }
float Collider::GetRadius() { return radius * GetParent()->GetScale(); }