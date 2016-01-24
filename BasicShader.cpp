#include "Core.h"
#include "BasicShader.h"



BasicShader::BasicShader() : Shader()
{
	AddVertexShader(ResourceLoader::LoadShader("resources/shaders/basicVertex.vs"));
	AddFragmentShader(ResourceLoader::LoadShader("resources/shaders/basicFragment.fs"));
	CompileShader();

	AddUniform("transform");
	AddUniform("color");
}


BasicShader::~BasicShader()
{
}

void BasicShader::UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix)
{
	if (material->UseTexture)
		material->GetTexture()->Bind();

	SetUniformMatrix("transform", projectionMatrix);
	SetUniformVector("color", material->Color);
}
