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
	void InitializeRotation(Vector3 forward, Vector3 up);
	void InitializeTranslation(float x, float y, float z);
	void InitializeScale(float x, float y, float z);
	void InitializeRotation(float x, float y, float z);
	void InitializePerspective(float fov, float aspectRatio, float zFar, float zNear);

	Matrix4 Multiply(Matrix4 input);

	float* CalculateSingleArray();

	
	
};

