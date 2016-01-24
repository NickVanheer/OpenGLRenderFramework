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


	void SetSpecularMap(Texture* texture);
	void SetTexture(Texture* texture);
	Texture* GetTexture();
	Texture* GetSpecularTexture();
	float SpecularIntensity; //intensity
	float SpecularPower; //spread of specular

	bool UseTexture;
	bool UseSpecularMap;
private:
	Texture* Textuur;
	Texture* SpecularMapTexture;

};

