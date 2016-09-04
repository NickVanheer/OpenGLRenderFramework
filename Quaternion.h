#pragma once
#include "Helpers.h"
#include "Vector3.h"
class Quaternion
{
public:
	Quaternion(float x, float y, float z, float w);
	virtual ~Quaternion();

	float Length();
	Quaternion* Normalize();
	Quaternion Conjugate();
	Quaternion* Multiply(Quaternion q);
	Quaternion* Multiply(Vector3 v);
	float x;
	float y;
	float z;
	float w;
private:

};

