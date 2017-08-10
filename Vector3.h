#pragma once

#include <stdio.h>
#include <math.h>
#include "Helpers.h"
#include "Vector2.h"
class Vector3
{
public:
	float x, y, z;
	Vector3(float _x = 0.0, float _y = 0.0, float _z = 0.0) { x = _x; y = _y; z = _z; };
	operator float *() { return &x; };
	bool operator<(const Vector3& v1) const
	{
		return true;
	}

	bool operator==(const Vector3& v1)
	{
		if (x == v1.x && y == v1.y && z == v1.z)
			return true;
		return false;
	}

	bool operator!=(const Vector3& v1)
	{
		if (x == v1.x && y == v1.y && z == v1.z)
			return false;
		return true;
	}
	bool operator()(const Vector3& v1)
	{
		if (x == v1.x && y == v1.y && z == v1.z)
			return false;
		return true;
	}

	float length() const;

	float dot(Vector3 vec2) const;
	float dot(Vector3 vec1, Vector3 vec2) const;
	Vector3 cross(Vector3 vec) const;
	Vector3 absolute() const;
	Vector3 lerp(Vector3 dest, float lerpFactor) const;

	Vector2 getXY() const;
	Vector2 getYZ() const;
	Vector2 getZX() const;

	Vector2 getYX() const;
	Vector2 getZY() const;
	Vector2 getXZ() const;

	Vector3 normalized() const; 
	Vector3 rotateAroundAxis(float angle, Vector3 axis);

};

float magnitude(Vector3 v);
Vector3 normalize(Vector3 v);


Vector3 operator+(Vector3 v1, Vector3 v2);
Vector3 operator-(Vector3 v);
Vector3 operator-(Vector3 v1, Vector3 v2);
Vector3 operator*(Vector3 v1, float s);
Vector3 operator*(float s, Vector3 v1);
Vector3 operator/(Vector3 v1, float s);
float   operator^(Vector3 v1, Vector3 v2);  // DOT product
Vector3 operator*(Vector3 v1, Vector3 v2);   // CROSS product
Vector3 planelineintersection(Vector3 n, float d, Vector3 p1, Vector3 p2);



class matrix
{
public:
	Vector3 x, y, z;
	matrix() {
		x = Vector3(1.0f, 0.0f, 0.0f);
		y = Vector3(0.0f, 1.0f, 0.0f);
		z = Vector3(0.0f, 0.0f, 1.0f);
	};
	matrix(Vector3 _x, Vector3 _y, Vector3 _z) { x = _x; y = _y; z = _z; };
};

matrix transpose(matrix m);
Vector3 operator*(matrix m, Vector3 v);
matrix operator*(matrix m1, matrix m2);



