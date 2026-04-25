#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 _size, Vector2 _offset, bool _isTrigger, Object* _parent, string _tag) : Collider(_offset, _isTrigger, _parent, _tag)
{
	size = _size;

	isSquare = true;
}