#pragma once
#include "Helpers.h"
#include "Transform.h"
class Shader;
class Component
{
public:
	Component();
	virtual ~Component();
	bool IsEnabled;
	Transform transform;

	virtual void Initialize(const GameContext gameContext, Transform* transform);
	virtual void Update(const GameContext gameContext, Transform* transform);
	virtual void Render(const GameContext gameContext, Transform* transform, Shader* shader);

	void SetTransform(Transform t);

};

