#include "ForwardAmbient.h"


ForwardAmbient* ForwardAmbient::instance = nullptr;

ForwardAmbient::ForwardAmbient() : Shader()
{
	AddVertexShader(ResourceLoader::LoadShader("resources/shaders/forward-ambient.vs"));
	AddFragmentShader(ResourceLoader::LoadShader("resources/shaders/forward-ambient.fs"));
	CompileShader();

	//if earlier version of OpenGL (not 3.3)
	SetAttributeLocation("position", 0);
	SetAttributeLocation("texCoord", 1);

	AddUniform("MVP");
	AddUniform("ambientIntensity");
}


ForwardAmbient::~ForwardAmbient()
{
}

void ForwardAmbient::UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix)
{
	if (material->UseTexture)
		material->GetTexture()->Bind(0);

	SetUniformMatrix("MVP", projectionMatrix);
	SetUniformVector("ambientIntensity", material->Color); //Get value from render engine
}
