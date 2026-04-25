#include "Vector2.h"

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2 Vector2::Lerp(Vector2 _v1, Vector2 _v2, float _value)
{
	Vector2 step = Vector2(_v2.x - _v1.x, _v2.y - _v1.y) * _value;
		
	return _v1 + step;
}

Vector2 Vector2::operator+(const Vector2& _other)
{
	return Vector2(x + _other.x, y + _other.y);
}

Vector2& Vector2::operator+=(const Vector2& _other)
{
	x = x + _other.x;
	y = y + _other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& _other)
{
	return Vector2(x - _other.x, y - _other.y);
}

Vector2& Vector2::operator-=(const Vector2& _other)
{
	x = x - _other.x;
	y = y - _other.y;

	return *this;
}

Vector2 Vector2::operator*(float _f)
{
	return Vector2(x * _f, y * _f);
}

Vector2& Vector2::operator*=(float _f)
{
	x = x * _f;
	y = y * _f;

	return *this;
}

Vector2 Vector2::operator/(float _f)
{
	return Vector2(x / _f, y / _f);
}

Vector2& Vector2::operator/=(float _f)
{
	x = x / _f;
	y = y / _f;

	return *this;
}

Vector2& Vector2::operator=(const Vector2& _other)
{
	x = _other.x;
	y = _other.y;

	return *this;
}

bool Vector2::operator==(const Vector2& _other)
{
	return (x == _other.x && y == _other.y);
}