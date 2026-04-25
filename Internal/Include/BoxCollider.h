#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(Vector2 _size = Vector2(0, 0), Vector2 _offset = Vector2(0, 0), bool _isTrigger = false, Object* _parent = NULL, string _tag = "");
};
