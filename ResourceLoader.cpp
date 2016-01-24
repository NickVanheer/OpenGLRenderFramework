#include "Core.h"
#include <vector>
#include "ResourceLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION   
#include "stb_image.h"
#include "Texture.h"
#include "Mesh.h"

ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}

Texture * ResourceLoader::LoadTexture(string filename)
{
	Texture * tex = new Texture(0);

	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb);

	tex->SetData(image, (unsigned int)w, (unsigned int)h);
	return tex;
	/*
	if (image == nullptr)
		LOGERROR("Failed to load texture");


	return image;
	*/
}

string ResourceLoader::LoadShader(string filename)
{
	ifstream file(filename);
	string text;

	if (!file)
		cout << "Can't open file";
	else
	{
		std::string sLine;
		std::cout << "\n============== \n Loading SHADER " << filename << " \n ==============" << endl;

		while (!file.eof())
		{
			getline(file, sLine);
			text += sLine + "\n";
		}

		file.close();
	}

	return text;
}

Mesh * ResourceLoader::LoadModel(string filename)
{
	std::ifstream file(filename);
	Mesh* newMesh = new Mesh();

	//all of them as parsed
	std::vector<Vertex> Vertexes;
	std::vector<Vector3> texc;
	std::vector<unsigned int> indices;

	int vCount = 0;
	int iCount = 0;

	int normal_index = 0;

	if (!file)
		std::cout << "Can't open file";
	else
	{
		std::string sLine;
		std::cout << "\n============== \n Loading MODEL " << filename << " \n ==============" << endl;

		while (!file.eof())
		{
			getline(file, sLine);

			if (sLine[0] == 'v' && sLine[1] == ' ')
			{
				vector<string> parts = SPLIT(sLine, ' ');

				double x = stod(parts[2]);
				double y = stod(parts[3]);
				double z = stod(parts[4]);

				Vertexes.push_back(Vertex(x, y, z));
			}

			if (sLine[0] == 'v' && sLine[1] == 't')
			{
				vector<string> parts = SPLIT(sLine, ' ');

				double xCoord = stod(parts[1]);
				double yCoord = stod(parts[2]);
				double zCoord = stod(parts[3]);

				float yC = RangeConverter(yCoord, 0, 1, -1, 1);
				float xC = RangeConverter(xCoord, 0, 1, -1, 1);

				texc.push_back(Vector3(1 - yCoord, xCoord, zCoord));
				//double check this

			}

			if (sLine[0] == 'v' && sLine[1] == 'n')
			{
				vector<string> parts = SPLIT(sLine, ' ');

				double x = stod(parts[1]);
				double y = stod(parts[2]);
				double z = stod(parts[3]);

				//Normals calculated outside of this
			}

			//v-t-n
			if (sLine[0] == 'f')
			{
				vector<string> parts = SPLIT(sLine, ' ');
				string a = parts[1];
				string b = parts[2];
				string c = parts[3];

				vector<string> partsFaceOne = SPLIT(a, '/');
				vector<string> partsFaceTwo = SPLIT(b, '/');
				vector<string> partsFaceThree = SPLIT(c, '/');

				tridata td;

				//v
				td.v[0] = stoi(partsFaceOne[0]);
				td.v[1] = stoi(partsFaceTwo[0]);
				td.v[2] = stoi(partsFaceThree[0]);

				//t
				td.t[0] = stoi(partsFaceOne[1]);
				td.t[1] = stoi(partsFaceTwo[1]);
				td.t[2] = stoi(partsFaceThree[1]);

				//n
				td.n[0] = stoi(partsFaceOne[2]);
				td.n[1] = stoi(partsFaceTwo[2]);
				td.n[2] = stoi(partsFaceThree[2]);

				indices.push_back(td.v[0] - 1);
				indices.push_back(td.v[1] - 1);
				indices.push_back(td.v[2] - 1);


				for (int i = 0; i < 3; i++)
				{
					//current pos
					Vector3 position = Vector3(Vertexes.at(td.v[i] - 1).position.x, Vertexes.at(td.v[i] - 1).position.y, Vertexes.at(td.v[i] - 1).position.z);
					int texCoordIndex = td.t[i] - 1;
					Vector3 texCoord = texc.at(texCoordIndex);

					for (int j = 0; j < Vertexes.size(); j++)
					{
						if (Vertexes.at(j).position == position)
						{
							Vertexes.at(j).texCoord = Vector3(texCoord.x, texCoord.y, 0);
						}
					}
				}
			}
		}

		file.close();
	}

	//TODO http://assimp.sourceforge.net/lib_html/install.html maybe
	newMesh->AddVertices(Vertexes, indices, true);

	return newMesh;
}