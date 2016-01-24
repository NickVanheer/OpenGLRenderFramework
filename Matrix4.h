#pragma once
#include "Vector3.h"
struct Matrix4
{
public:
	Matrix4();
	virtual ~Matrix4();
	//Not really that secure but fast
	float m[4][4];
	float singleArray[16];

	void InitializeIdentity();
	void InitializeCamera(Vector3 forward, Vector3 up);
	void InitializeTranslation(float x, float y, float z);
	void InitializeScale(float x, float y, float z);
	void InitializeRotation(float x, float y, float z);
	void InitializeProjection(float width, float height, float fov, float zFar, float zNear);

	Matrix4 Multiply(Matrix4 input);

	float* CalculateSingleArray();

	
	
};

