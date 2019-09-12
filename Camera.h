#pragma once
#include "Vector3.h"
#include "Matrix4.h"
class Camera
{
public:
	Camera(float fov, float aspectRatio, float zNear, float zFar);
	~Camera();
	static Vector3 YAXIS;
	Vector3 GetPosition() const { return position; }
	void SetPosition(Vector3 val) { position = val; }
	Vector3 GetForward() const { return forward; }
	void SetForward(Vector3 val) { forward = val; }
	Vector3 GetUp() const { return up; }
	void SetUp(Vector3 val) { up = val; }

	void Move(Vector3 direction, float amount);
	void MoveForward(float amount);
	void MoveRight(float amount);
	void MoveLeft(float amount);
	void MoveUp(float amount);
	Vector3 GetLeft();
	Vector3 GetRight();


	void RotateX(float angle);
	void RotateY(float angle);
	const Matrix4 GetViewProjection() const;
private:
	Vector3 position;
	Vector3 forward;
	Vector3 up;
	Matrix4 projection;
};

