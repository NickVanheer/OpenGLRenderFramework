#pragma once
#include <tchar.h>
#include "Vector3.h"
#include <vector>
#include "Vertex.h"

struct BaseLight
{
	Vector3 color;
	float intensity;

	BaseLight()
	{

	}

	BaseLight(Vector3 color, float intensity)
	{
		this->color = color;
		this->intensity = intensity;
	}
};

struct DirectionalLight 
{
	BaseLight base;
	Vector3 direction;

	DirectionalLight()
	{

	}

	DirectionalLight(BaseLight base, Vector3 direction) 
	{
		this->base = base;
		this->direction = direction.normalized();
	}
};

class RenderUtil
{
public:
	RenderUtil();
	virtual ~RenderUtil();
	static void ClearScreen();

	static void InitGraphics();

	static char* GetOpenGLVersion();

	static void EnableTextures(bool enabled);
	static void UnbindTextures();

	static void SetClearColor(Vector3 color);

	static std::vector<float> GetFloatVector(std::vector<Vertex> vertices);


};

