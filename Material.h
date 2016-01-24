#pragma once
#include "Core.h"
#include "Texture.h"
class Material
{
public:
	Material();
	Material(Texture* texture, Vector3 color);
	Material(Texture* texture, Vector3 color, float specularIntensity, float specularExponent);
	virtual ~Material();
	Vector3 Color;

	void SetTexture(Texture* texture);
	Texture* GetTexture();
	float SpecularIntensity; //intensity
	float SpecularPower; //spread of specular

	bool UseTexture;
private:
	Texture* Textuur;

};

