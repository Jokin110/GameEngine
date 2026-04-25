#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector2
{
private:
	float x = 0;
	float y = 0;

public:
	Vector2(float _x = 0, float _y = 0);
	float GetX() { return x; }
	float GetY() { return y; }

	float GetMagnitude() { return sqrt(x * x + y * y); }
	Vector2 GetNormalized() { return GetMagnitude() == 0 ? zero() : Vector2(x, y) / GetMagnitude(); }
	Vector2 Lerp(Vector2, Vector2, float);

	Vector2 operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2 operator*(float);
	Vector2& operator*=(float);
	Vector2 operator/(float);
	Vector2& operator/=(float);
	Vector2& operator=(const Vector2& other);
	bool operator==(const Vector2& other);


	Vector2 zero() { return Vector2(0, 0); }
	Vector2 up() { return Vector2(0, -1); }
	Vector2 down() { return Vector2(0, 1); }
	Vector2 left() { return Vector2(-1, 0); }
	Vector2 right() { return Vector2(1, 0); }
};

