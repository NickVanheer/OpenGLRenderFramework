#include "PhongShader.h"
#include "Transform.h"

Vector3 PhongShader::AmbientLight;
DirectionalLight PhongShader::LightDirectional;

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
}


PhongShader::~PhongShader()
{
}

void PhongShader::UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix)
{
	if (material->UseTexture)
		material->GetTexture()->Bind();

	SetUniformMatrix("transformProjected", projectionMatrix);
	SetUniformMatrix("transform", worldMatrix);
	SetUniformVector("baseColor", material->Color);
	SetUniformBool("useTexture", material->UseTexture);

	//specular
	SetUniformFloat("specularIntensity", material->SpecularIntensity);
	SetUniformFloat("specularPower", material->SpecularPower);

	SetUniformVector("eyePos", Transform::CameraInstance->GetPosition());

	SetUniformVector("ambientLight", AmbientLight);
	SetUniform("directionalLight", LightDirectional);
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