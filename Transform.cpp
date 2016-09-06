#include "Transform.h"
#include "Camera.h"
Transform::Transform()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}


Transform::~Transform()
{
}

Vector3 Transform::GetPosition()
{
	return position;
}

Matrix4 Transform::GetTransformation()
{
	Matrix4 positionM;
	positionM.InitializeTranslation(position.x, position.y, position.z);

	Matrix4 rotationM;
	rotationM.InitializeRotation(rotation.x, rotation.y, rotation.z);

	Matrix4 scaleM;
	scaleM.InitializeScale(scale.x, scale.y, scale.z);

	Matrix4 finalM = positionM.Multiply(rotationM.Multiply(scaleM));
	return finalM;
}

/*
Matrix4 Transform::GetProjectedTransformation(Camera* camera)
{
	Matrix4 finalM = Matrix4();
	finalM = camera->GetViewProjection().Multiply(GetTransformation());

	return finalM;
}
*/


void Transform::SetPosition(Vector3 position)
{
	this->position = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	this->position = Vector3(x, y, z);
}

Vector3 Transform::GetRotation()
{
	return this->rotation;
}

void Transform::SetRotation(Vector3 rotation)
{
	this->rotation = rotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	this->rotation = Vector3(x, y, z);
}

Vector3 Transform::GetScale()
{
	return this->scale;
}

void Transform::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void Transform::Scale(float x, float y, float z)
{

	this->scale.x *= x == 0 ? 1 : x;
	this->scale.y *= y == 0 ? 1 : y;
	this->scale.z *= z == 0 ? 1 : z;
}

void Transform::SetScale(float x, float y, float z)
{
	this->scale = Vector3(x, y, z);
}
