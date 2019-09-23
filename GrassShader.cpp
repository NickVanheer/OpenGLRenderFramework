#include "pch.h"
#include "GrassShader.h"

Vector3 GrassShader::AmbientLight;
DirectionalLight GrassShader::LightDirectional;
std::vector<PointLight> GrassShader::PointLights;

GrassShader::GrassShader() : Shader()  
{
	AddVertexShader(ResourceLoader::LoadShader("resources/shaders/grassVertex.vs"));
	AddGeometryShader(ResourceLoader::LoadShader("resources/shaders/grassGeometry.gs"));
	AddFragmentShader(ResourceLoader::LoadShader("resources/shaders/grassFragment.fs"));
	CompileShader();

	m_Time = 0.0f;

	glUseProgram(gProgramID);

	//core transforms
	AddUniform("transform");
	AddUniform("VP");
	AddUniform("transformProjected");
	AddUniform("m_Time");

	//0
	heightmapTextureUnit = AddUniform("samHeightmap");
	SetUniformInt("samHeightmap", 0);

	//1
	diffuseTextureUnit = AddUniform("samDiffuse");
	SetUniformInt("samDiffuse", 1);
	
	AddUniform("useTexture");
	AddUniform("eyePos");
	/*
	AddUniform("baseColor");
	AddUniform("ambientLight");

	//directionalLight
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");

	//specular
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	

	//diffuse spec and normal samplers
	
	SetUniformInt("DiffuseMapSampler", 0);
	AddUniform("useTexture");

	specTextureUnit = AddUniform("SpecularMapSampler");
	SetUniformInt("SpecularMapSampler", 1);
	AddUniform("useSpecularTexture");

	normalTextureUnit = AddUniform("NormalMapSampler");
	SetUniformInt("NormalMapSampler", 2);
	AddUniform("useNormalTexture");

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
	}*/
}

Shader* GrassShader::GetInstance()
{
	return instance;
}
GrassShader::~GrassShader()
{
}

void GrassShader::UpdateUniforms(Transform* transform, GameContext gameContext)
{
	//cout << gameContext.deltaTime << endl;
	m_Time += gameContext.deltaTime;
	glUseProgram(gProgramID);
	
	glActiveTexture(GL_TEXTURE0);
	if (material->useHeightMap)
		material->GetHeightMap()->Bind(heightmapTextureUnit);
	
	glActiveTexture(GL_TEXTURE1);
	if (material->UseTexture)
		material->GetTexture()->Bind(diffuseTextureUnit);

	SetUniformBool("useTexture", material->UseTexture);

	/*
	glActiveTexture(GL_TEXTURE2);
	if (material->UseNormalMap)
		material->GetNormalMapTexture()->Bind(normalTextureUnit);
	*/

	RenderEngine* r = gameContext.renderEngine;
	const Camera& c = r->GetMainCamera();

	Matrix4 worldMatrix = transform->GetTransformation();
	Matrix4 projectedMatrix = c.GetViewProjection().Multiply(worldMatrix);

	SetUniformMatrix("transformProjected", projectedMatrix);
	SetUniformFloat("m_Time", m_Time);
	SetUniformVector("eyePos", c.GetPosition());

	SetUniformMatrix("transform", worldMatrix);

	/*
	//base
	SetUniformVector("baseColor", material->Color);

	//specular
	SetUniformFloat("specularIntensity", material->SpecularIntensity);
	SetUniformFloat("specularPower", material->SpecularPower);
	SetUniformBool("useSpecularTexture", material->UseSpecularMap);

	//normal
	SetUniformBool("useNormalTexture", material->UseNormalMap);

	SetUniformVector("eyePos", c->GetPosition());

	SetUniformVector("ambientLight", AmbientLight);
	SetUniform("directionalLight", LightDirectional);
		*/
}

void GrassShader::PostDrawUpdateUniforms(Transform* transform, GameContext gameContext)
{
	glActiveTexture(GL_TEXTURE0);
	if (material->useHeightMap)
		material->GetHeightMap()->Bind(0);

	glActiveTexture(GL_TEXTURE1);
	if (material->UseTexture)
		material->GetTexture()->Bind(0);

	glUseProgram(0);
}


void GrassShader::SetUniform(string uniformName, BaseLight baseLight)
{
	SetUniformVector(uniformName + ".color", baseLight.color);
	SetUniformFloat(uniformName + ".intensity", baseLight.intensity);
	//glUniform1i(uniforms.at(uniformName), value);
}

void GrassShader::SetUniform(string uniformName, DirectionalLight directionalLight)
{
	SetUniform(uniformName + ".base", directionalLight.base);
	SetUniformVector(uniformName + ".direction", directionalLight.direction);
	//glUniform1i(uniforms.at(uniformName), value);
}

void GrassShader::SetUniform(string uniformName, PointLight pointLight)
{
	SetUniform(uniformName + ".base", pointLight.base);
	SetUniformFloat(uniformName + ".attenuation.constant", pointLight.attenuation.constant);
	SetUniformFloat(uniformName + ".attenuation.linear", pointLight.attenuation.linear);
	SetUniformFloat(uniformName + ".attenuation.exponent", pointLight.attenuation.exponent);
	SetUniformFloat(uniformName + ".range", pointLight.range);
	SetUniformVector(uniformName + ".position", pointLight.position);
}

void GrassShader::SetPointLights(std::vector<PointLight> pointLights)
{
	if (pointLights.size() > MAX_POINT_LIGHTS)
	{
		LOGERROR("Maximum number of point lights exceeded. Maximum allowed point light count:" + MAX_POINT_LIGHTS);
	}
	else
	{
		GrassShader::PointLights = pointLights;
	}
}