#include "ForwardAmbient.h"


Shader* ForwardAmbient::GetInstance()
{
	if (instance == nullptr)
		instance = new ForwardAmbient();
	return instance;
}

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

void ForwardAmbient::UpdateUniforms(Transform* transform)
{
	if (material->UseTexture)
		material->GetTexture()->Bind(0);


	RenderEngine* r = GetRenderEngine();
	Camera* c = r->GetMainCamera();


	Matrix4 worldMatrix = transform->GetTransformation();
	Matrix4 projectedMatrix = c->GetViewProjection().Multiply(worldMatrix);

	SetUniformMatrix("MVP", projectedMatrix);
	SetUniformVector("ambientIntensity", GetRenderEngine()->GetAmbientLight()); //Get value from render engine
}
