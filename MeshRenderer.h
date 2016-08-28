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
	void Draw(const GameContext gameContext, Transform* transform, Shader* shader);
	void Initialize(const GameContext gameContext, Transform* transform);
	void Update(const GameContext gameContext, Transform* transform);
private:
	Mesh* mesh;
	Material* material;
	Shader* shader;
};

