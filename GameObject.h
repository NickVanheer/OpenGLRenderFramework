#pragma once
#include "Core.h"
#include "Component.h"
#include <vector>
#include "Transform.h"
#include <memory>

class Shader;
class GameObject
{
public:
	GameObject();

	//children
	void AddChild(shared_ptr<GameObject> obj);

	//components
	void AddComponent(shared_ptr<Component> pComp);
	void RemoveComponent(shared_ptr<Component> pComp);
	void SetTransform(Transform& t);
	Transform& GetTransform();

	virtual void Initialize(const GameContext gameContext);
	virtual void Render(const GameContext gameContext, Shader* shader);
	virtual void Update(const GameContext gameContext);
	
private:
	std::vector<shared_ptr<GameObject>> Children;
	std::vector<shared_ptr<Component>> Components;

	GameObject(const GameObject& obj);

	bool isInitialized;

	Transform transform;
};

