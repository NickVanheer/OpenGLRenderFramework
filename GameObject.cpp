#include "GameObject.h"



GameObject::GameObject()
{
	transform = new	Transform();
}


GameObject::~GameObject()
{
	return;

	//todo fix cleanup error

	//Component Cleanup
	for (Component* pComp : Components)
	{
		SafeDelete(pComp);
	}

	//Object Cleanup
	for (GameObject* pChild : Children)
	{
		SafeDelete(pChild);
	}
}

void GameObject::AddChild(GameObject * obj)
{
	Children.push_back(obj);
}

void GameObject::RemoveChild(GameObject * obj)
{
}

void GameObject::AddComponent(Component * pComp)
{
	//TODO: Complete and check for duplicates
	Components.push_back(pComp);
}

void GameObject::RemoveComponent(Component * pComp)
{
}

void GameObject::SetTransform(Transform* t)
{
	transform = t;
}

Transform* GameObject::GetTransform()
{
	return transform;
}

void GameObject::Initialize(const GameContext gameContext)
{
	if (initialized)
		return;

	//User-Object Initialization
	//Initialize(gameContext);


	//Root-Component Initialization
	for (Component* pComp : Components)
	{
		pComp->Initialize(gameContext, transform);
	}

	//Root-Object Initialization
	for (GameObject* pChild : Children)
	{
		pChild->Initialize(gameContext);
	}

	initialized = true;
}

void GameObject::Render(const GameContext gameContext, Shader* shader)
{
	//inherit draw in child class
	//Draw(gameContext);

	//Component draw
	for (Component* pComp : Components)
	{
		pComp->Render(gameContext, transform, shader);
	}

	//children objects draw
	for (GameObject* pChild : Children)
	{
		pChild->Render(gameContext, shader);
	}
}

void GameObject::Update(const GameContext gameContext)
{
	//inherit Update in child class
	//Update(gameContext);

	//Component Update
	for (Component* pComp : Components)
	{
		pComp->Update(gameContext, transform);
	}

	//children objects update
	for (GameObject* pChild : Children)
	{
		pChild->Update(gameContext);
	}
}
