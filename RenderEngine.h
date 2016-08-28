#pragma once
#include "Vector3.h"
class GameObject;
class BasicShader;
class ForwardAmbient;
class RenderEngine
{
public:
	RenderEngine();
	virtual ~RenderEngine();
	Vector3 GetAmbientLight();
	void Input(float delta);
	void Render(GameObject* object);
	BasicShader* shader;
	ForwardAmbient* fwAmbientShader;
	void Initialize();
private:
	void clearScreen();
	
};

