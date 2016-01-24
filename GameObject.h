#pragma once
#include "Core.h"
#include "Component.h"
#include <vector>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//children
	void AddChild(GameObject* obj);
	void RemoveChild(GameObject* obj);

	//components
	void AddComponent(Component* pComp);
	void RemoveComponent(Component* pComp);

protected:
	virtual void Initialize(const GameContext gameContext);
	virtual void Draw(const GameContext gameContext);
	virtual void Update(const GameContext gameContext);

private:
	std::vector<GameObject*> Children;
	std::vector<Component*> Components;

	GameObject(const GameObject &obj);
	GameObject& operator=(const GameObject& obj);

	bool initialized;
};

