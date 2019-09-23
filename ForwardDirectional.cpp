#include "pch.h"
#include "ForwardDirectional.h"

ForwardDirectional::ForwardDirectional() : Shader()
{
	AddVertexShader(ResourceLoader::LoadShader("resources/shaders/forward-directional.vs"));
	AddFragmentShader(ResourceLoader::LoadShader("resources/shaders/forward-directional.fs"));

	//if earlier version of OpenGL (not 3.3)
	SetAttributeLocation("position", 0);
	SetAttributeLocation("texCoord", 1);
	SetAttributeLocation("normal", 2);

	CompileShader();
	glUseProgram(gProgramID);

	AddUniform("model");
	AddUniform("MVP");
	
	//base
	diffuseTextureUnit = AddUniform("DiffuseMapSampler");
	SetUniformInt("DiffuseMapSampler", 0);
	AddUniform("useTexture");
	AddUniform("baseColor");

	//specular
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("useSpecularTexture");
	specTextureUnit = AddUniform("SpecularMapSampler");
	SetUniformInt("SpecularMapSampler", 1);

	//normal
	normalTextureUnit = AddUniform("NormalMapSampler");
	SetUniformInt("NormalMapSampler", 2);

	AddUniform("useNormalTexture");

	//directional
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");
}

Shader* ForwardDirectional::GetInstance()
{
	if (instance == nullptr)
		instance = new ForwardDirectional();
	return instance;
}

ForwardDirectional::~ForwardDirectional()
{
}

void ForwardDirectional::SetUniform(string uniformName, BaseLight baseLight)
{
	SetUniformVector(uniformName + ".color", baseLight.color);
	SetUniformFloat(uniformName + ".intensity", baseLight.intensity);
	//glUniform1i(uniforms.at(uniformName), value);
}

void ForwardDirectional::SetUniform(string uniformName, DirectionalLight directionalLight)
{
	SetUniform(uniformName + ".base", directionalLight.base);
	SetUniformVector(uniformName + ".direction", directionalLight.direction);
	//glUniform1i(uniforms.at(uniformName), value);
}

void ForwardDirectional::UpdateUniforms(Transform* transform)
{
	glUseProgram(gProgramID);

	glActiveTexture(GL_TEXTURE0);
	if (material->UseTexture)
		material->GetTexture()->Bind(diffuseTextureUnit);
	
	glActiveTexture(GL_TEXTURE1);
	if (material->UseSpecularMap)
		material->GetSpecularTexture()->Bind(specTextureUnit);

	glActiveTexture(GL_TEXTURE2);
	if (material->UseNormalMap)
		material->GetNormalMapTexture()->Bind(normalTextureUnit);


	RenderEngine& r = GetRenderEngine();
	const Camera& c = r.GetMainCamera();

	Matrix4 worldMatrix = transform->GetTransformation();
	Matrix4 projectedMatrix = c.GetViewProjection().Multiply(worldMatrix);

	SetUniformMatrix("model", worldMatrix);
	SetUniformMatrix("MVP", projectedMatrix);

	//base
	SetUniformVector("baseColor", material->Color);
	SetUniformBool("useTexture", material->UseTexture);

	//specular
	SetUniformFloat("specularIntensity", material->SpecularIntensity);
	SetUniformFloat("specularPower", material->SpecularPower);
	SetUniformBool("useSpecularTexture", material->UseSpecularMap);

	//normal
	SetUniformBool("useNormalTexture", material->UseNormalMap);

	SetUniformVector("eyePos", c.GetPosition());
	SetUniform("directionalLight", r.GetDirectionalLight());
}

