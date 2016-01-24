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
	void SetUniform(string uniformName, PointLight pointLight);

	static const int MAX_POINT_LIGHTS = 4;
	static std::vector<PointLight> PointLights;
	static void SetPointLights(std::vector<PointLight> pointLights);

	int diffuseTextureUnit;
	int specTextureUnit;
};

