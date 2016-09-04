#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::~Quaternion()
{
}

Quaternion* Quaternion::Normalize()
{
	float length = this->Length();

	x /= length;
	y /= length;
	z /= length;
	w /= length;

	return this;
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(-x,-y,-z,w);
}

Quaternion * Quaternion::Multiply(Quaternion q)
{
	float w_ = w * q.w - x * q.x - y * q.y - z * q.z;
	float x_ = x * q.w + w * q.x + y * q.z - z * q.y;
	float y_ = y * q.w + w * q.y + z * q.x - x * q.z;
	float z_ = z * q.w + w * q.z + x * q.y - y * q.x;

	return new Quaternion(x_, y_, z_, w_);
}

Quaternion * Quaternion::Multiply(Vector3 v)
{
	float w_ = -x * v.x - y * v.y - z * v.z;
	float x_ =  w * v.x + y * v.z - z * v.y;
	float y_ =  w * v.y + z * v.x - x * v.z;
	float z_ =  w * v.z + x * v.y - y * v.x;

	return new Quaternion(x_, y_, z_, w_);
}

float Quaternion::Length()
{
	return sq4root(x*x + y*y + z*z + w*w);
}
