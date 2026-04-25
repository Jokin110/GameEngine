#include "CircleCollider.h"

CircleCollider::CircleCollider(float _radius, Vector2 _offset, bool _isTrigger, Object* _parent, string _tag) : Collider(_offset, _isTrigger, _parent, _tag)
{
	radius = _radius;

	isSquare = false;
}