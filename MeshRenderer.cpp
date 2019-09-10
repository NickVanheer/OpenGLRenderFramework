#include "MeshRenderer.h" 
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "PhongShader.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : isCustomShader(false), customShader(nullptr)
{
	this->mesh = mesh;
	this->material = material;
}

MeshRenderer::~MeshRenderer()
{
	delete mesh;
}

void MeshRenderer::SetCustomShader(Shader * shader)
{
	customShader = shader;
	isCustomShader = true;
}

void MeshRenderer::Render(const GameContext gameContext, Transform& transform, Shader* shader)
{
	Shader* toUse;
	if (isCustomShader)
		toUse = customShader;
	else
		toUse = shader;
		
	if (toUse == nullptr)
	{
		//TODO
	}

	toUse->Bind(); //use shader program
	toUse->SetMaterial(material); //set material 
	toUse->UpdateUniforms(transform, gameContext);
//shader->UpdateUniforms(transform->GetTransformation(), transform->GetProjectedTransformation()); //update shader variables and its material variables
	mesh->Draw();
	toUse->PostDrawUpdateUniforms(transform, gameContext);
	toUse->Unbind();
}

void MeshRenderer::Initialize(const GameContext gameContext, Transform& transform)
{
}

void MeshRenderer::Update(const GameContext gameContext, Transform& transform)
{
}
