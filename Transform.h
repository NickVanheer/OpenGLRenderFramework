#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "Camera.h"
class Transform
{
public:
	Transform();
	virtual ~Transform();
	Vector3 GetTranslation();
	Matrix4 GetTransformation();
	Matrix4 GetProjectedTransformation();
	void SetTranslation(Vector3 translation);
	void SetTranslation(float x, float y, float z);

	Vector3 GetRotation();
	void SetRotation(Vector3 rotation);
	void SetRotation(float x, float y, float z);

	Vector3 GetScale();
	void SetScale(Vector3 scale);
	void SetScale(float x, float y, float z);

	static void SetProjection(float width, float height, float fov, float zFar, float zNear);

	//static Camera* CameraInstance;
	static float Z_NEAR;
	static float Z_FAR;
	static float WIDTH;
	static float HEIGHT;
	static float FOV;
	static Camera* GetCamera() { return camera; }
	static void SetCamera(Camera* val);
	static Camera* camera;
private:
	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;



};

