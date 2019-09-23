#include "pch.h"
#include "GameObject.h"

GameObject::GameObject() : isInitialized(false), transform(Transform())
{
}

void GameObject::AddChild(shared_ptr<GameObject> obj)
{
	Children.push_back(obj);
}

void GameObject::AddComponent(shared_ptr<Component> pComp)
{
	//TODO: Complete and check for duplicates
	Components.push_back(pComp);
}

void GameObject::SetTransform(Transform& t)
{
	transform = t;
}

Transform& GameObject::GetTransform() 
{
	return transform;
}

void GameObject::Initialize(const GameContext gameContext)
{
	if (isInitialized)
		return;

	//User-Object Initialization
	//Initialize(gameContext);

	//Root-Component Initialization
	for (shared_ptr<Component> pComp : Components)
	{
		pComp->Initialize(gameContext, transform);
	}

	//Root-Object Initialization
	for (shared_ptr<GameObject> pChild : Children)
	{
		pChild->Initialize(gameContext);
	}

	isInitialized = true;
}

void GameObject::Render(const GameContext gameContext, Shader* shader)
{
	//Component draw
	for (shared_ptr<Component> pComp : Components)
	{
		pComp->Render(gameContext, transform, shader);
	}

	//children objects draw
	for (shared_ptr<GameObject> pChild : Children)
	{
		pChild->Render(gameContext, shader);
	}
}

void GameObject::Update(const GameContext gameContext)
{
	//Component Update
	for (shared_ptr<Component> pComp : Components)
	{
		pComp->Update(gameContext, transform);
	}

	//children objects update
	for (shared_ptr<GameObject> pChild : Children)
	{
		pChild->Update(gameContext);
	}
}
