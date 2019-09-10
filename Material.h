#pragma once
#include "Core.h"
#include "Texture.h"
class Material
{
public:
	Material();
	Material(string materialName);
	Material(Texture* texture, Vector3 color);
	Material(Texture* texture, Vector3 color, float specularIntensity, float specularExponent);
	virtual ~Material();
	Vector3 Color;

	string Name;
	void SetNormalMap(Texture* texture);
	void SetSpecularMap(Texture* texture);
	void SetTexture(Texture* texture);
	void SetHeightMap(Texture* texture);
	void SetDirectionTexture(Texture* texture);
	Texture* GetTexture();
	Texture* GetSpecularTexture();
	Texture* GetHeightMap();
	Texture* GetDirectionTexture();
	Texture* GetNormalMapTexture();

	float SpecularIntensity; //intensity
	float SpecularPower; //spread of specular

	bool UseTexture;
	bool UseSpecularMap;
	bool UseNormalMap;
	bool useHeightMap;
	bool useDirectionMap;
private:
	Texture* Textuur;
	Texture* SpecularMapTexture;
	Texture* NormalMapTexture;
	Texture* HeightMapTexture;
	Texture* DirectionTexture;

};

