#pragma once
#include "Vector3.h"
#include "Matrix4.h"
class Camera;
class Transform
{
public:
	Transform();
	virtual ~Transform();
	Transform operator=(const Transform& other);
	Vector3 GetPosition() const;
	Matrix4 GetTransformation();
	//Matrix4 GetProjectedTransformation(Camera* camer);
	void SetPosition(const Vector3& translation);
	void SetPosition(float x, float y, float z);

	Vector3 GetRotation() const;
	void SetRotation(const Vector3& rotation);
	void SetRotation(float x, float y, float z);

	Vector3 GetScale() const;
	void SetScale(const Vector3& scale);
	void SetScale(float x, float y, float z);
	void Scale(float x, float y, float z);

	//static Camera* CameraInstance;
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;



};

