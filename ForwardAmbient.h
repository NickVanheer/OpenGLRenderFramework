#pragma once
#include "Shader.h"
class ForwardAmbient :
	public Shader
{
public:
	ForwardAmbient();
	virtual ~ForwardAmbient();
	void UpdateUniforms(Transform* transform);
	virtual Shader* GetInstance();

};

