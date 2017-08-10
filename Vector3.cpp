#pragma once
#include <stdio.h>
#include <math.h>

#include "Vector3.h"
#include "Quaternion.h"


float magnitude(Vector3 v) {
	return (float)sqrt(sq4root(v.x) + sq4root(v.y) + sq4root(v.z));
}
Vector3 normalize(Vector3 v) {
	float d = magnitude(v);
	if (d == 0) {
		printf("Can't normalize ZERO Vector3\n");
		d = 0.1f;
	}
	v.x /= d;
	v.y /= d;
	v.z /= d;
	return v;
}

Vector3 operator+(Vector3 v1, Vector3 v2) { return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
Vector3 operator-(Vector3 v1, Vector3 v2) { return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
Vector3 operator-(Vector3 v) { return Vector3(-v.x, -v.y, -v.z); }
Vector3 operator*(Vector3 v1, float s) { return Vector3(v1.x*s, v1.y*s, v1.z*s); }
Vector3 operator*(float s, Vector3 v1) { return Vector3(v1.x*s, v1.y*s, v1.z*s); }
Vector3 operator/(Vector3 v1, float s) { return v1*(1.0f / s); }
float  operator^(Vector3 v1, Vector3 v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }

Vector3 operator*(Vector3 v1, Vector3 v2) {
	return Vector3(
		v1.y * v2.z - v1.z*v2.y,
		v1.z * v2.x - v1.x*v2.z,
		v1.x * v2.y - v1.y*v2.x);
}
Vector3 planelineintersection(Vector3 n, float d, Vector3 p1, Vector3 p2) {
	//returns the point where the line p1-p2 intersects the plane n&d
	Vector3 dif = p2 - p1;
	float dn = n^dif;
	float t = -(d + (n^p1)) / dn;
	return p1 + (dif*t);
}


// Matrix Implementation
matrix transpose(matrix m) {
	return matrix(Vector3(m.x.x, m.y.x, m.z.x),
		Vector3(m.x.y, m.y.y, m.z.y),
		Vector3(m.x.z, m.y.z, m.z.z));
}
Vector3 operator*(matrix m, Vector3 v) {
	m = transpose(m); // since column ordered
	return Vector3(m.x^v, m.y^v, m.z^v);
}
matrix operator*(matrix m1, matrix m2) {
	m1 = transpose(m1);
	return matrix(m1*m2.x, m1*m2.y, m1*m2.z);
}

float Vector3::length() const
{
	return sq4root(x * x + y * y + z * z);
}

float Vector3::dot(Vector3 vec2) const
{
	return x*vec2.x + y*vec2.y + z*vec2.z;
}

float Vector3::dot(Vector3 vec1, Vector3 vec2) const
{
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

Vector2 Vector3::getXY() const
{
	return Vector2(x, y);
}

Vector2 Vector3::getYZ() const
{
	return Vector2(y, z);
}
 
Vector2 Vector3::getZX() const
{
	return Vector2(z,x);
}
 
Vector2 Vector3::getYX() const
{
	return Vector2(y, x);
}

Vector2 Vector3::getZY() const
{
	return Vector2(z,y);
}

Vector2 Vector3::getXZ() const
{
	return Vector2(x, z);
}

Vector3 Vector3::cross(Vector3 vec) const
{
	float x_ = y * vec.z - z * vec.y;
	float y_ = z * vec.x - x * vec.z;
	float z_ = x * vec.y - y * vec.x;

	return Vector3(x_, y_, z_);
}

Vector3 Vector3::absolute() const
{
	return Vector3(abs(x), abs(y), abs(z));
}

Vector3 Vector3::lerp(Vector3 dest, float lerpFactor) const
{
	Vector3 a = dest - Vector3(x,y,z);
	return (a * lerpFactor) + Vector3(x,y,z);
}

Vector3 Vector3::normalized() const
{
	float length = this->length();

	return Vector3(x / length, y / length, z / length);
}

Vector3 Vector3::rotateAroundAxis(float angle, Vector3 axis)
{
	float sinAngle = sin(-angle);
	float cosAngle = cos(-angle);

	Vector3 rotX = cross(axis *  sinAngle);
	Vector3 rotY = Vector3(x, y, z) * cosAngle;
	Vector3 rotZ = axis * dot(axis * (1 - cosAngle));

	Vector3 result = rotX + rotY + rotZ;

	x = result.x;
	y = result.y;
	z = result.z;

	return result;
}
