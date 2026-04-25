#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(float _radius = 0, Vector2 _offset = Vector2(0, 0), bool _isTrigger = false, Object* _parent = NULL, string _tag = "");
};

