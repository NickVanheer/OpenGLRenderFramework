#include "pch.h"
#include "Component.h"

Component::Component() : IsEnabled(true)
{
}

Component::~Component()
{
}

void Component::SetTransform(const Transform& t)
{
	transform = t;
}
