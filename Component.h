#pragma once
#include "Helpers.h"

class Component
{
public:
	Component();
	virtual ~Component();
	bool IsEnabled;

	virtual void Initialize(const GameContext gameContext) = 0;
	virtual void Update(const GameContext gameContext) = 0;
	virtual void Draw(const GameContext gameContext) = 0;

};

