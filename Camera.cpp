#include "Camera.h"

Vector3 Camera::YAXIS = Vector3(0, 1, 0);
Camera::Camera(float fov, float aspectRatio, float zNear, float zFar)
{
	this->position = Vector3(0, 0, 0);
	this->forward = Vector3(0, 0, 1);
	this->up = Vector3(0, 1.0f, 0);

	this->forward = this->forward.normalized();
	this->up = this->up.normalized();

	this->projection = Matrix4();
	this->projection.InitializePerspective(fov, aspectRatio, zFar, zNear); //paramter far near right
}

Matrix4 Camera::GetViewProjection()
{
	Matrix4 cameraRotation;
	cameraRotation.InitializeRotation(forward, up);

	Matrix4 cameraTranslation;
	cameraTranslation.InitializeTranslation(-position.x, -position.y, -position.z);

	Matrix4 finalM = projection.Multiply(cameraRotation.Multiply(cameraTranslation));
	return finalM;
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
	forward.rotate(angle, Vector3(0, 1, 0));

	up = forward.cross(horizontalAxis).normalized();
}
