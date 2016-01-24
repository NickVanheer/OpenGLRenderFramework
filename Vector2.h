#pragma once
#include "Helpers.h"


struct Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	virtual ~Vector2();


	bool operator==(const Vector2& v1)
	{
		if (x == v1.x && y == v1.y)
			return true;
		return false;
	}

	bool operator!=(const Vector2& v1)
	{
		if (x == v1.x && y == v1.y)
			return false;
		return true;
	}
	bool operator()(const Vector2& v1)
	{
		if (x == v1.x && y == v1.y)
			return false;
		return true;
	}

	float length();

	float dot(Vector2 vec2);
	float dot(Vector2 vec1, Vector2 vec2);

	Vector2 absolute();
	Vector2 normalized();
	Vector2 rotate(float angle);

	float x;
	float y;
};

Vector2 operator+(Vector2 v1, Vector2 v2);
Vector2 operator-(Vector2 v);
Vector2 operator-(Vector2 v1, Vector2 v2);
Vector2 operator*(Vector2 v1, float s);
Vector2 operator*(float s, Vector2 v1);
Vector2 operator/(Vector2 v1, float s);
float  operator^(Vector2 v1, Vector2 v2);  // DOT product
Vector2 operator*(Vector2 v1, Vector2 v2);   // CROSS product
Vector2 planelineintersection(Vector2 n, float d, Vector2 p1, Vector2 p2);

