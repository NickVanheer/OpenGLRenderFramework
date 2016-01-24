#pragma once
#include "Core.h"
#include <string>
using namespace std;
class Texture;
class Mesh;

class ResourceLoader
{
public:
	ResourceLoader();
	virtual ~ResourceLoader();


	static Texture * LoadTexture(string filename);
	static string LoadShader(string filename);
	static Mesh * LoadModel(string filename);
};

