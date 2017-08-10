#include "MeshRenderer.h" 
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "PhongShader.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material)
{
	this->mesh = mesh;
	this->material = material;
}


MeshRenderer::~MeshRenderer()
{
	delete mesh;
}

void MeshRenderer::Render(const GameContext gameContext, Transform* transform, Shader* shader)
{
	//TODO check if shader is null
	shader->Bind(); //use shader program
	shader->SetMaterial(material); //set material 
	shader->UpdateUniforms(transform);
//shader->UpdateUniforms(transform->GetTransformation(), transform->GetProjectedTransformation()); //update shader variables and its material variables
	mesh->Draw();
}

void MeshRenderer::Initialize(const GameContext gameContext, Transform* transform)
{
}

void MeshRenderer::Update(const GameContext gameContext, Transform* transform)
{
}
