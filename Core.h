#pragma once
#include <SDL.h>
//include other headers like mouse etc?
#define GLEW_STATIC
#include "glew.h"
#include "RenderUtil.h"
#include "glut.h"  // in glut-3.7.6-bin
#include "Helpers.h"
#include <string>
#include "Vector2.h"
#include "Vector3.h"
#include "ResourceLoader.h"
#include <math.h>
#include "Texture.h"
#include "Main.h"
#include "InputManager.h"
#include "Time.h"
#include "BaseGame.h"
#include "Transform.h"

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
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

	}

	return verts;
}