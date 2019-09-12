#pragma once
#include <SDL.h>
#include <iostream>
#include <math.h>
#include <string>
#include "include\GL\glew.h"
//#define GLEW_STATIC
#include "RenderUtil.h"
#include "Helpers.h"
#include "Vector2.h"
#include "Vector3.h"
#include "ResourceLoader.h"
#include "Texture.h"
#include "Main.h"
#include "InputManager.h"
#include "Time.h"
#include "BaseGame.h"
#include "Transform.h"

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 768;
static const int FRAMES_PER_SECOND = 60;

template<class T>
inline void SafeDelete(T &pObjectToDelete)
{
	if (pObjectToDelete != 0)
	{
		delete(pObjectToDelete);
		pObjectToDelete = 0;
	}
}

static std::vector<float> GetFloatVector(std::vector<Vertex> vertices)
{
	vector<float> verts;

	for (int i = 0; i < vertices.size(); i++)
	{
		verts.push_back(vertices.at(i).position.x);
		verts.push_back(vertices.at(i).position.y);
		verts.push_back(vertices.at(i).position.z);

		//tex
		verts.push_back(vertices.at(i).texCoord.x);
		verts.push_back(vertices.at(i).texCoord.y);

		//n
		verts.push_back(vertices.at(i).normal.x);
		verts.push_back(vertices.at(i).normal.y);
		verts.push_back(vertices.at(i).normal.z);

		//tangents
		verts.push_back(vertices.at(i).tangent.x);
		verts.push_back(vertices.at(i).tangent.y);
		verts.push_back(vertices.at(i).tangent.z);
	}

	return verts;
}