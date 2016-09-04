#include "ForwardPoint.h"

ForwardPoint::ForwardPoint() : Shader()
{
	AddVertexShader(ResourceLoader::LoadShader("resources/shaders/forward-point.vs"));
	AddFragmentShader(ResourceLoader::LoadShader("resources/shaders/forward-point.fs"));


	//if earlier version of OpenGL (not 3.3)
	SetAttributeLocation("position", 0);
	SetAttributeLocation("texCoord", 1);
	SetAttributeLocation("normal", 2);

	CompileShader();

	AddUniform("model");
	AddUniform("MVP");

	//specular
	//AddUniform("specularIntensity");
	//AddUniform("specularPower");
	//AddUniform("eyePos");

	AddUniform("pointLight.base.color");
	AddUniform("pointLight.base.intensity");
	AddUniform("pointLight.attenuation.constant");
	AddUniform("pointLight.attenuation.linear");
	AddUniform("pointLight.attenuation.exponent");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");
}

Shader* ForwardPoint::GetInstance()
{
	if (instance == nullptr)
		instance = new ForwardPoint();
	return instance;
}

ForwardPoint::~ForwardPoint()
{
}

void ForwardPoint::SetUniform(string uniformName, BaseLight baseLight)
{
	SetUniformVector(uniformName + ".color", baseLight.color);
	SetUniformFloat(uniformName + ".intensity", baseLight.intensity);
	//glUniform1i(uniforms.at(uniformName), value);
}

void ForwardPoint::SetUniform(string uniformName, DirectionalLight directionalLight)
{
	SetUniform(uniformName + ".base", directionalLight.base);
	SetUniformVector(uniformName + ".direction", directionalLight.direction);
	//glUniform1i(uniforms.at(uniformName), value);
}

void ForwardPoint::SetUniform(string uniformName, PointLight pointLight)
{
	SetUniform(uniformName + ".base", pointLight.base);
	SetUniformFloat(uniformName + ".attenuation.constant", pointLight.attenuation.constant);
	SetUniformFloat(uniformName + ".attenuation.linear", pointLight.attenuation.linear);
	SetUniformFloat(uniformName + ".attenuation.exponent", pointLight.attenuation.exponent);
	SetUniformFloat(uniformName + ".range", pointLight.range);
	SetUniformVector(uniformName + ".position", pointLight.position);
}


void ForwardPoint::UpdateUniforms(Transform* transform)
{
	if (material->UseTexture)
		material->GetTexture()->Bind(0);


	RenderEngine* r = GetRenderEngine();
	Camera* c = r->GetMainCamera();


	Matrix4 worldMatrix = transform->GetTransformation();
	Matrix4 projectedMatrix = c->GetViewProjection().Multiply(worldMatrix);

	SetUniformMatrix("model", worldMatrix);
	SetUniformMatrix("MVP", projectedMatrix);

	//specular
	//SetUniformFloat("specularIntensity", material->SpecularIntensity);
	//SetUniformFloat("specularPower", material->SpecularPower);
	//SetUniformBool("useSpecularTexture", material->UseSpecularMap);
	//SetUniformVector("eyePos", c->GetPosition());
	
	//point
	SetUniform("pointLight", r->GetPointLight());
}

