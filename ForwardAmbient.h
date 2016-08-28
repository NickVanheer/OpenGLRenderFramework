#pragma once
#include "Shader.h"
class ForwardAmbient :
	public Shader
{
public:
	ForwardAmbient();
	virtual ~ForwardAmbient();
	void UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix);
	static ForwardAmbient* GetInstance() { return instance; }
private:
	static ForwardAmbient* instance;
};

