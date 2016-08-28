#include "PhongShader.h"
#include "Transform.h"

Vector3 PhongShader::AmbientLight;
DirectionalLight PhongShader::LightDirectional;
std::vector<PointLight> PhongShader::PointLights;

PhongShader::PhongShader() : Shader()
{
	AddVertexShader(ResourceLoader::LoadShader("resources/shaders/phongVertex.vs"));
	AddFragmentShader(ResourceLoader::LoadShader("resources/shaders/phongFragment.fs"));
	CompileShader();

	//core transforms
	AddUniform("transform");
	AddUniform("transformProjected");
	AddUniform("baseColor");
	AddUniform("ambientLight");

	//directionalLight
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");

	//specular
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");

	AddUniform("useTexture");
	AddUniform("useSpecularTexture");

	diffuseTextureUnit = AddUniform("sampler");
	//specTextureUnit = AddUniform("SpecularMapSampler");

	//point lights
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		AddUniform("pointLights[" + to_string(i) + "].base.color");
		AddUniform("pointLights[" + to_string(i) + "].base.intensity");
		AddUniform("pointLights[" + to_string(i) + "].attenuation.constant");
		AddUniform("pointLights[" + to_string(i) + "].attenuation.linear");
		AddUniform("pointLights[" + to_string(i) + "].attenuation.exponent");
		AddUniform("pointLights[" + to_string(i) + "].position");
		AddUniform("pointLights[" + to_string(i) + "].range");
	}
}


PhongShader::~PhongShader()
{
}

void PhongShader::UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix)
{
	glActiveTexture(GL_TEXTURE0);
	if (material->UseTexture)
		material->GetTexture()->Bind(diffuseTextureUnit);

	glActiveTexture(GL_TEXTURE1);
	if (material->UseSpecularMap)
		material->GetSpecularTexture()->Bind(specTextureUnit);

	SetUniformMatrix("transformProjected", projectionMatrix);
	SetUniformMatrix("transform", worldMatrix);
	SetUniformVector("baseColor", material->Color);
	SetUniformBool("useTexture", material->UseTexture);
	SetUniformBool("useSpecularTexture", material->UseSpecularMap);

	//specular
	SetUniformFloat("specularIntensity", material->SpecularIntensity);
	SetUniformFloat("specularPower", material->SpecularPower);

	SetUniformVector("eyePos", Transform::camera->GetPosition());

	SetUniformVector("ambientLight", AmbientLight);
	SetUniform("directionalLight", LightDirectional);

	for (int i = 0; i < PointLights.size(); i++)
		SetUniform("pointLights[" + to_string(i) + "]", PointLights.at(i));
}

void PhongShader::SetUniform(string uniformName, BaseLight baseLight)
{
	SetUniformVector(uniformName + ".color", baseLight.color);
	SetUniformFloat(uniformName + ".intensity", baseLight.intensity);
	//glUniform1i(uniforms.at(uniformName), value);
}

void PhongShader::SetUniform(string uniformName, DirectionalLight directionalLight)
{
	SetUniform(uniformName + ".base", directionalLight.base);
	SetUniformVector(uniformName + ".direction", directionalLight.direction);
	//glUniform1i(uniforms.at(uniformName), value);
}

void PhongShader::SetUniform(string uniformName, PointLight pointLight)
{
	SetUniform(uniformName + ".base", pointLight.base);
	SetUniformFloat(uniformName + ".attenuation.constant", pointLight.attenuation.constant);
	SetUniformFloat(uniformName + ".attenuation.linear", pointLight.attenuation.linear);
	SetUniformFloat(uniformName + ".attenuation.exponent", pointLight.attenuation.exponent);
	SetUniformFloat(uniformName + ".range", pointLight.range);
	SetUniformVector(uniformName + ".position", pointLight.position);
}

void PhongShader::SetPointLights(std::vector<PointLight> pointLights)
{
	if (pointLights.size() > MAX_POINT_LIGHTS)
	{
		LOGERROR("Maximum number of point lights exceeded. Maximum allowed point light count:" + MAX_POINT_LIGHTS);
	}
	else
	{
		PhongShader::PointLights = pointLights;
	}
}
