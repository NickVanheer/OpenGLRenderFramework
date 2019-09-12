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
	glUseProgram(gProgramID);

	//if earlier version of OpenGL (not 3.3)
	SetAttributeLocation("position", 0);
	SetAttributeLocation("texCoord", 1);

	diffuseTextureUnit = AddUniform("sampler");
	SetUniformInt("sampler", 0);

	AddUniform("MVP");
	AddUniform("ambientIntensity");
}


ForwardAmbient::~ForwardAmbient()
{
}

void ForwardAmbient::UpdateUniforms(Transform* transform)
{
	glUseProgram(gProgramID);

	glActiveTexture(GL_TEXTURE0);
	if (material->UseTexture)
		material->GetTexture()->Bind(diffuseTextureUnit);

	RenderEngine& r = GetRenderEngine();
	const Camera& c = r.GetMainCamera();

	Matrix4 worldMatrix = transform->GetTransformation();
	Matrix4 projectedMatrix = c.GetViewProjection().Multiply(worldMatrix);

	SetUniformMatrix("MVP", projectedMatrix);
	SetUniformVector("ambientIntensity", r.GetAmbientLight()); //Get value from render engine
}
