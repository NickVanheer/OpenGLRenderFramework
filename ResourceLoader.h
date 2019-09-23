#pragma once

using namespace std;
class Texture;
class Mesh;

class ResourceLoader
{
public:
	ResourceLoader();
	virtual ~ResourceLoader();

	static Texture * LoadTexture(const string& filename);
	static string LoadShader(const string& filename);
	static Mesh * LoadModel(const string& filename); 

	static Mesh * LoadLegacy(const string& filename);
	static Mesh * LoadAssimp(const string& filename);
};

