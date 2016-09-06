#include "Core.h"
#include "Texture.h"



Texture::Texture(int id) : id(id)
{
}


Texture::~Texture()
{
	if(this->data != nullptr)
		delete[] this->data;
}

void Texture::Bind(int slot)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, slot);
}

void Texture::SetData(unsigned char * data, unsigned int width, unsigned int height)
{
	this->data = data;
	this->width = width;
	this->height = height;
}

void Texture::SendTextureToOpenGL()
{
	//Bind(0);
}


