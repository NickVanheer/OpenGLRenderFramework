#pragma once
#include "Shader.h"
#include "RenderUtil.h"

class ForwardPoint : public Shader
{
public:
	ForwardPoint();
	virtual ~ForwardPoint();

	void UpdateUniforms(Transform* transform);
	void SetUniform(string uniformName, DirectionalLight directionalLight);
	void SetUniform(string uniformName, BaseLight baseLight);
	void SetUniform(string uniformName, PointLight pointLight);
	virtual Shader* GetInstance();
};