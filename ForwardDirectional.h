#pragma once
#include "Shader.h"
#include "RenderUtil.h"

class ForwardDirectional : public Shader
{
public:
	ForwardDirectional();
	virtual ~ForwardDirectional();

	void UpdateUniforms(Transform* transform);
	void SetUniform(string uniformName, DirectionalLight directionalLight);
	void SetUniform(string uniformName, BaseLight baseLight);
	virtual Shader* GetInstance();

	int specTextureUnit;
	int diffuseTextureUnit;
	int normalTextureUnit;
};

