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

void BasicShader::UpdateUniforms(Transform* transform)
{
		material->GetTexture()->Bind(0);

		RenderEngine* r = GetRenderEngine();
 		Camera* c = r->GetMainCamera();

		Matrix4 worldMatrix = transform->GetTransformation();
		Matrix4 projectedMatrix = c->GetViewProjection().Multiply(worldMatrix);

	SetUniformMatrix("transform", projectedMatrix);
	SetUniformVector("color", material->Color);
}
