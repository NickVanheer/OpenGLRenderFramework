#pragma once
#include "Shader.h"
class BasicShader :
	public Shader
{
public:
	BasicShader();
	virtual ~BasicShader();
	void UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix);
};

