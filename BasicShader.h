#pragma once
#include "Shader.h"
class BasicShader :
	public Shader
{
public:
	BasicShader();
	virtual ~BasicShader();
	void UpdateUniforms(Transform* transform);
};

