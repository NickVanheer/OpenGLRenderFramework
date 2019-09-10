#pragma once
#include "Component.h"
class Mesh;
class Material;
class Shader;

class MeshRenderer :
	public Component
{
public:
	MeshRenderer(Mesh* mesh, Material* material);
	virtual ~MeshRenderer();
	void Render(const GameContext gameContext, Transform& transform, Shader* shader) override;
	void Initialize(const GameContext gameContext, Transform& transform) override;
	void Update(const GameContext gameContext, Transform& transform) override;
	void SetCustomShader(Shader* shader);
private:
	Mesh* mesh;
	Material* material;

	bool isCustomShader;
	Shader* customShader;
};

