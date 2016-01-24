
#pragma once
class Texture
{
public:
	Texture(int id);
	virtual ~Texture();
	void Bind();
	void SetData(unsigned char* data, unsigned int width, unsigned int height);
	void SendTextureToOpenGL();
	int GetID() { return id; }
private:
	int id;
	unsigned char *data;
	unsigned int width, height;
};

