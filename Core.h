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


template<class T>
inline void SafeDelete(T &pObjectToDelete)
{
	if (pObjectToDelete != 0)
	{
		delete(pObjectToDelete);
		pObjectToDelete = 0;
	}
}