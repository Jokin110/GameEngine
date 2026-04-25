#include "Object.h"
#include "ObjectManager.h"
#include "GraphicManager.h"

Object::Object()
{
	rotation = 0;

	ObjectManager::GetInstance().AddObject(this);

	GraphicManager::GetInstance().AddObject(this);

	active = true;
}

int Object::Clamp(int _min, int _max, int _value)
{
	int value = _value;

	if (_value < _min)
		value = _min;
	else if (_value > _max)
		value = _max;

	return value;
}

void Object::Start()
{

}

void Object::Update()
{
	prevPos = pos;
}

void Object::Destroy()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		colliders[i]->Destroy();
		colliders[i] = NULL;
	}

	ObjectManager::GetInstance().RemoveObject(this);
}

void Object::UndoMovement(Collider* _myCollider, Collider* _other)
{
	if (_myCollider->GetIsSquare() && _other->GetIsSquare())
	{
		if (pos.GetX() > prevPos.GetX())
		{
			pos = Vector2(Clamp(prevPos.GetX(), pos.GetX(), _other->GetParent()->GetXWithoutPivot() + _other->GetLeftX() - _myCollider->GetRightX() + (pos.GetX() - GetXWithoutPivot())), pos.GetY());
		}
		else if (pos.GetX() < prevPos.GetX())
		{
			pos = Vector2(Clamp(pos.GetX(), prevPos.GetX(), _other->GetParent()->GetXWithoutPivot() + _other->GetRightX() - _myCollider->GetLeftX() + (pos.GetX() - GetXWithoutPivot())), pos.GetY());
		}

		if (pos.GetY() > prevPos.GetY())
		{
			pos = Vector2(pos.GetX(), Clamp(prevPos.GetY(), pos.GetY(), _other->GetParent()->GetYWithoutPivot() + _other->GetTopY() - _myCollider->GetBottomY() + (pos.GetY() - GetYWithoutPivot())));
		}
		else if (pos.GetY() < prevPos.GetY())
		{
			pos = Vector2(pos.GetX(), Clamp(pos.GetY(), prevPos.GetY(), _other->GetParent()->GetYWithoutPivot() + _other->GetBottomY() - _myCollider->GetTopY() + (pos.GetY() - GetYWithoutPivot())));
		}
	}
	else
	{
		pos = prevPos;
	}
}

void Object::OnCollisionEnter(Collider* _other)
{

}

void Object::OnTriggerEnter(Collider* _other)
{

}

void Object::OnCollisionStay(Collider* _other)
{

}

void Object::OnTriggerStay(Collider* _other)
{

}

void Object::OnCollisionExit(Collider* _other)
{

}

void Object::OnTriggerExit(Collider* _other)
{

}