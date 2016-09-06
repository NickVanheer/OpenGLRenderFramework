#include "Material.h"



Material::Material()
{
	this->Textuur = nullptr;
	this->Color = Vector3(1,1,1);
	this->SpecularPower = 32;
	this->SpecularIntensity = 2;

	if (Textuur == nullptr)
		UseTexture = false;
	else
		UseTexture = true;

	UseSpecularMap = false;
	UseNormalMap = false;
}

Material::Material(Texture* texture, Vector3 color)
{
	this->Textuur = texture;
	this->Color = color;
	this->SpecularPower = 32;
	this->SpecularIntensity = 2;

	if (Textuur == nullptr)
		UseTexture = false;
	else
		UseTexture = true;

	UseSpecularMap = false;
	UseNormalMap = false;
}

Material::Material(Texture * texture, Vector3 color, float specularIntensity, float specularPower) : Color(color), Textuur(texture), SpecularIntensity(specularIntensity), SpecularPower(specularPower)
{
	if (Textuur == nullptr)
		UseTexture = false;
	else
		UseTexture = true;

	UseSpecularMap = false;
	UseNormalMap = false;
}

Material::~Material()
{
	delete Textuur;
}
void Material::SetNormalMap(Texture * texture)
{
	this->NormalMapTexture = texture;
	if (NormalMapTexture == nullptr)
		UseNormalMap = false;
	else
		UseNormalMap = true;
}
void Material::SetSpecularMap(Texture * texture)
{
	this->SpecularMapTexture = texture;
	if (SpecularMapTexture == nullptr)
		UseSpecularMap = false;
	else
		UseSpecularMap = true;
}

void Material::SetTexture(Texture * texture)
{
	this->Textuur = texture;
	if (Textuur == nullptr)
		UseTexture = false;
	else
		UseTexture = true;
}

Texture * Material::GetTexture()
{
	return Textuur;
}

Texture * Material::GetSpecularTexture()
{
	return SpecularMapTexture;
}

Texture * Material::GetNormalMapTexture()
{
	return NormalMapTexture;
}
