#include "Component.h"



Component::Component() : IsEnabled(true)
{
}


Component::~Component()
{
}

void Component::Initialize(const GameContext gameContext, Transform* transform)
{
}

void Component::Update(const GameContext gameContext, Transform* transform)
{
}

void Component::Draw(const GameContext gameContext, Transform* transform, Shader* shader)
{
}

void Component::SetTransform(Transform t)
{
	transform = t;
}
