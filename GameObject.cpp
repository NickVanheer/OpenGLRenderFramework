#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
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
}

void GameObject::RemoveChild(GameObject * obj)
{
}

void GameObject::AddComponent(Component * pComp)
{
}

void GameObject::RemoveComponent(Component * pComp)
{
}

void GameObject::Initialize(const GameContext gameContext)
{
	if (initialized)
		return;

	//User-Object Initialization
	Initialize(gameContext);


	//Root-Component Initialization
	for (Component* pComp : Components)
	{
		pComp->Initialize(gameContext);
	}

	//Root-Object Initialization
	for (GameObject* pChild : Children)
	{
		pChild->Initialize(gameContext);
	}

	initialized = true;
}

void GameObject::Draw(const GameContext gameContext)
{
	//inherit draw in child class
	Draw(gameContext);

	//Component draw
	for (Component* pComp : Components)
	{
		pComp->Draw(gameContext);
	}

	//children objects draw
	for (GameObject* pChild : Children)
	{
		pChild->Draw(gameContext);
	}
}

void GameObject::Update(const GameContext gameContext)
{
	//inherit Update in child class
	Update(gameContext);

	//Component Update
	for (Component* pComp : Components)
	{
		pComp->Update(gameContext);
	}

	//children objects update
	for (GameObject* pChild : Children)
	{
		pChild->Update(gameContext);
	}
}
