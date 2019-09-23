/*************************************

		OBSOLETE AND NOT USED

**************************************/

#pragma once
#include "include\GL\glew.h"
//#define GLEW_STATIC
#include "RenderUtil.h"
#include "Helpers.h"
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
