#include "Camera.h"

Vector3 Camera::YAXIS = Vector3(0, 1, 0);
Camera::Camera()
{
	this->position = Vector3(0, 0, 0);
	this->forward = Vector3(0, 0, 1);
	this->up = Vector3(0, 1, 0);

	this->forward = this->forward.normalized();
	this->up = this->up.normalized();
}
Camera::Camera(Vector3 pos, Vector3 forward, Vector3 up)
{
	this->position = pos;
	this->forward = forward;
	this->up = up;

	this->forward.normalized();
	this->up.normalized();
}


Camera::~Camera()
{
}

void Camera::Move(Vector3 direction, float amount)
{
	position = position + (direction * amount);
}

Vector3 Camera::GetLeft()
{
	return forward.cross(up).normalized();
}

Vector3 Camera::GetRight()
{
	return up.cross(forward).normalized();
}

void Camera::RotateX(float angle)
{
	Vector3 horizontalAxis = Camera::YAXIS.cross(forward).normalized();
	forward.rotate(angle, horizontalAxis);

	up = forward.cross(horizontalAxis).normalized();
}

void Camera::RotateY(float angle)
{
	Vector3 horizontalAxis = Camera::YAXIS.cross(forward).normalized();
	forward.rotate(angle, Camera::YAXIS);

	up = forward.cross(horizontalAxis).normalized();
}
