#pragma once
#include "Shader.h"
#include "RenderUtil.h"
class PhongShader :
	public Shader
{
public:
	PhongShader();
	virtual ~PhongShader();
	void UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix);
	static Vector3 AmbientLight;
	static DirectionalLight LightDirectional;
	void SetUniform(string uniformName, BaseLight baseLight);
	void SetUniform(string uniformName, DirectionalLight directionalLight);
};

