#include "Vector2.h"
#include <math.h>


Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y)
{
}

Vector2::~Vector2()
{
}

float Vector2::length()
{
	return sq4root(x * x + y * y);
}

float Vector2::dot(Vector2 vec2)
{
	return x*vec2.x + y*vec2.y;
}

float Vector2::dot(Vector2 vec1, Vector2 vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y;;
}

float Vector2::cross(Vector2 vec)
{
	return x * vec.y - y * vec.x;
}

Vector2 Vector2::absolute()
{
	return Vector2(abs(x), abs(y));
}

Vector2 Vector2::normalized()
{
	float length = this->length();

	return Vector2(x / length,y / length);
}

Vector2 Vector2::rotate(float angle)
{
	double rad = TO_RADIANS(angle);
	double cosine = cos(rad);
	double sine = sin(rad);

	return Vector2(x * cosine - y * sine, x * sine + y * cosine);
}

Vector2 operator+(Vector2 v1, Vector2 v2) { return Vector2(v1.x + v2.x, v1.y + v2.y); }
Vector2 operator-(Vector2 v1, Vector2 v2) { return Vector2(v1.x - v2.x, v1.y - v2.y); }
Vector2 operator-(Vector2 v) { return Vector2(-v.x, -v.y); }
Vector2 operator*(Vector2 v1, float s) { return Vector2(v1.x*s, v1.y*s); }
Vector2 operator*(float s, Vector2 v1) { return Vector2(v1.x*s, v1.y*s); }