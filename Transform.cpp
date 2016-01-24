#include "Transform.h"

 float Transform::Z_NEAR;
 float Transform::Z_FAR;
 float Transform::WIDTH;
 float Transform::HEIGHT;
 float Transform::FOV;
 Camera* Transform::CameraInstance;
Transform::Transform()
{
	translation = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}


Transform::~Transform()
{
}

Vector3 Transform::GetTranslation()
{
	return translation;
}

Matrix4 Transform::GetTransformation()
{
	Matrix4 translationM;
	translationM.InitializeTranslation(translation.x, translation.y, translation.z);

	Matrix4 rotationM;
	rotationM.InitializeRotation(rotation.x, rotation.y, rotation.z);

	Matrix4 scaleM;
	scaleM.InitializeScale(scale.x, scale.y, scale.z);

	Matrix4 finalM = translationM.Multiply(rotationM.Multiply(scaleM));
	return finalM;
}

Matrix4 Transform::GetProjectedTransformation()
{
	Matrix4 transformationMatrix = GetTransformation();
	Matrix4 projectionMatrix;
	projectionMatrix.InitializeProjection(WIDTH, HEIGHT, FOV, Z_FAR, Z_NEAR);

	Matrix4 cameraRotation;
	cameraRotation.InitializeCamera(camera->GetForward(), camera->GetUp());

	Matrix4 cameraTranslation;
	cameraTranslation.InitializeTranslation(-camera->GetPosition().x, -camera->GetPosition().y, -camera->GetPosition().z);

	Matrix4 finalM = projectionMatrix.Multiply(cameraRotation.Multiply(cameraTranslation.Multiply(transformationMatrix)));
	return finalM;

	/*
	Matrix4 cameraRotation;
	cameraRotation.InitializeCamera(camera.GetForward(), camera.GetUp());

	Matrix4 cameraTranslation;
	cameraTranslation.InitializeTranslation(-camera.GetPosition().x, -camera.GetPosition().y, -camera.GetPosition().z);
	*/
	finalM = projectionMatrix.Multiply(transformationMatrix);

	return finalM;
}

void Transform::SetTranslation(Vector3 translation)
{
	this->translation = translation;
}

void Transform::SetTranslation(float x, float y, float z)
{
	this->translation = Vector3(x, y, z);
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

void Transform::SetScale(float x, float y, float z)
{
	this->scale = Vector3(x, y, z);
}

void Transform::SetProjection(float width, float height, float fov, float zFar, float zNear)
{
	Transform::WIDTH = width;
	Transform::HEIGHT = height;
	Transform::FOV = fov;
	Transform::Z_FAR = zFar;
	Transform::Z_NEAR = zNear;
}

void Transform::SetCamera(Camera * val)
{
	camera = val;
	Transform::CameraInstance = val;
}
