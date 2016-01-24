#include "Matrix4.h"
#include "Helpers.h"
#include <math.h>

Matrix4::Matrix4()
{
}


Matrix4::~Matrix4()
{
}

void Matrix4::InitializeIdentity()
{
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	CalculateSingleArray();
}

void Matrix4::InitializeProjection(float width, float height, float fov, float zFar, float zNear)
{
	float aratio = width / height;
	double halfFOV = TO_RADIANS(fov / 2);
	float tanHalfFOV = (float)tan(halfFOV);
	float zRange = zNear - zFar;

	m[0][0] = 1 / (tanHalfFOV * aratio);	m[0][1] = 0;	m[0][2] = 0;						m[0][3] = 0;
	m[1][0] = 0;				m[1][1] = (float)1.0 / tanHalfFOV;	m[1][2] = 0;						m[1][3] = 0;
	m[2][0] = 0;				m[2][1] = 0;				m[2][2] = (-zNear - zFar)/zRange;	m[2][3] = 2 * zFar * zNear / zRange;
	m[3][0] = 0;				m[3][1] = 0;				m[3][2] = 1;						m[3][3] = 0;

	CalculateSingleArray();
}

void Matrix4::InitializeCamera(Vector3 forward, Vector3 up)
{
	Vector3 f = forward;
	f = f.normalized();

	//right vector
	Vector3 r = up;
	r = r.normalized();
	r = r.cross(f);

	Vector3 u = f.cross(r);

	m[0][0] = r.x;	m[0][1] = r.y;	m[0][2] = r.z;	m[0][3] = 0;
	m[1][0] = u.x;	m[1][1] = u.y;	m[1][2] = u.z;	m[1][3] = 0;
	m[2][0] = f.x;	m[2][1] = f.y;	m[2][2] = f.z;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	CalculateSingleArray();
}


void Matrix4::InitializeTranslation(float x, float y, float z)
{
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = x;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = y;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = z;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	CalculateSingleArray();
}

void Matrix4::InitializeScale(float x, float y, float z)
{
	m[0][0] = x;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = y;	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = z;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	CalculateSingleArray();
}

void Matrix4::InitializeRotation(float x, float y, float z)
{
	Matrix4 rx, ry, rz;
	x = (float)TO_RADIANS(x);
	y = (float)TO_RADIANS(y);
	z = (float)TO_RADIANS(z);

	//z (see Vector rotate for 2D plane rotations, broke up here)
	rz.m[0][0] = cos(z);	rz.m[0][1] = -sin(z);	rz.m[0][2] = 0;			rz.m[0][3] = 0;
	rz.m[1][0] = sin(z);	rz.m[1][1] = cos(z);	rz.m[1][2] = 0;			rz.m[1][3] = 0;
	rz.m[2][0] = 0;			rz.m[2][1] = 0;			rz.m[2][2] = 1;			rz.m[2][3] = 0;
	rz.m[3][0] = 0;			rz.m[3][1] = 0;			rz.m[3][2] = 0;			rz.m[3][3] = 1;

	//x
	rx.m[0][0] = 1;			rx.m[0][1] = 0;			rx.m[0][2] = 0;			rx.m[0][3] = 0;
	rx.m[1][0] = 0;			rx.m[1][1] = cos(x);	rx.m[1][2] = -sin(x);	rx.m[1][3] = 0;
	rx.m[2][0] = 0;			rx.m[2][1] = sin(x);	rx.m[2][2] = cos(x);	rx.m[2][3] = 0;
	rx.m[3][0] = 0;			rx.m[3][1] = 0;			rx.m[3][2] = 0;			rx.m[3][3] = 1;

	//y
	ry.m[0][0] = cos(y);	ry.m[0][1] = 0;		ry.m[0][2] = -sin(y);	ry.m[0][3] = 0;
	ry.m[1][0] = 0;			ry.m[1][1] = 1;		ry.m[1][2] = 0;			ry.m[1][3] = 0;
	ry.m[2][0] = sin(y);	ry.m[2][1] = 0;		ry.m[2][2] = cos(y);			ry.m[2][3] = 0;
	ry.m[3][0] = 0;			ry.m[3][1] = 0;		ry.m[3][2] = 0;			ry.m[3][3] = 1;


	Matrix4 finalMatrix = rz.Multiply(ry.Multiply(rx));

	m[0][0] = finalMatrix.m[0][0];	m[0][1] = finalMatrix.m[0][1];	m[0][2] = finalMatrix.m[0][2];	m[0][3] = finalMatrix.m[0][3];
	m[1][0] = finalMatrix.m[1][0];	m[1][1] = finalMatrix.m[1][1];	m[1][2] = finalMatrix.m[1][2];	m[1][3] = finalMatrix.m[1][3];
	m[2][0] = finalMatrix.m[2][0];	m[2][1] = finalMatrix.m[2][1];	m[2][2] = finalMatrix.m[2][2];	m[2][3] = finalMatrix.m[2][3];
	m[3][0] = finalMatrix.m[3][0];	m[3][1] = finalMatrix.m[3][1];	m[3][2] = finalMatrix.m[3][2];	m[3][3] = finalMatrix.m[3][3];

	CalculateSingleArray();
}

Matrix4 Matrix4::Multiply(Matrix4 input)
{
	Matrix4 res = Matrix4();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.m[i][j] = 
				m[i][0] * input.m[0][j] +
				m[i][1] * input.m[1][j] +
				m[i][2] * input.m[2][j] +
				m[i][3] * input.m[3][j];
		}
	}

	CalculateSingleArray();
	return res;
}
//TODO: dimension right?
float* Matrix4::CalculateSingleArray()
{
	int index = 0;
	for (short x = 0; x < 4; x++)
	{
		for (short y = 0; y < 4; y++)
		{
			singleArray[index] = m[x][y];
			index++;
		}
	}

	return singleArray;
}


