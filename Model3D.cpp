#include "Model3D.h"
#include <iostream>

#include <fstream>
#include <sstream>
#include <stdio.h>  
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "Mesh.h"
#include <unordered_map>
#include "Helpers.h"
using namespace std; //remove and use std::[]


#pragma region helpers
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
#pragma endregion


Model3D::Model3D()
{
}


Model3D::~Model3D()
{
}

void Model3D::Initialize()
{

}

Vector3 calculateNormal(Vector3 coord1, Vector3 coord2, Vector3 coord3)
{
	/* calculate Vector1 and Vector2 */
	float va[3], vb[3], vr[3], val;
	va[0] = coord1.x - coord2.x;
	va[1] = coord1.y - coord2.y;
	va[2] = coord1.z - coord2.z;

	vb[0] = coord1.x - coord3.x;
	vb[1] = coord1.y - coord3.y;
	vb[2] = coord1.z - coord3.z;

	/* cross product */
	vr[0] = va[1] * vb[2] - vb[1] * va[2];
	vr[1] = vb[0] * va[2] - va[0] * vb[2];
	vr[2] = va[0] * vb[1] - vb[0] * va[1];

	/* normalization factor */
	val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

	float norm[3];
	norm[0] = vr[0] / val;
	norm[1] = vr[1] / val;
	norm[2] = vr[2] / val;


	return Vector3(norm[0], norm[1], norm[2]);
}

Mesh* Model3D::LoadModel(TCHAR* filename)
{
	std::vector<tridata> triangles;
	std::ifstream file(filename);
	Mesh* newMesh = new Mesh();

	std::vector<float> vertices;
	std::vector<float> textures;
	std::vector<float> norms; 
	std::vector<unsigned int> indices;

	std::vector<Vertex> Vertexes;

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
				vector<string> parts = split(sLine, ' ');

				double x = stod(parts[2]);
				double y = stod(parts[3]);
				double z = stod(parts[4]);
				//cout << x << " / " << y << " / " << z << endl;

				Vertexes.push_back(Vertex(x, y, z));
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
				
			}

			if (sLine[0] == 'v' && sLine[1] == 't')
			{
				vector<string> parts = split(sLine, ' ');

				double xCoord = stod(parts[1]);
				double yCoord = stod(parts[2]);
				double zCoord = stod(parts[3]);
				//cout << x << " / " << y << " / " << z << endl;

				float yC = RangeConverter(yCoord, 0, 1, -1, 1);
				float xC = RangeConverter(xCoord, 0, 1, -1, 1);

				texc.push_back(Vector3(1 - yCoord, xCoord, zCoord));

				//flip X AND Y!! IF MODEL BLANK FLIP AGAIN TODO CHECK SETTING IN MAX
				textures.push_back(yC);
				textures.push_back(xC);
		
				textures.push_back(0);
			}

			if (sLine[0] == 'v' && sLine[1] == 'n')
			{
				vector<string> parts = split(sLine, ' ');

				double x = stod(parts[1]);
				double y = stod(parts[2]);
				double z = stod(parts[3]);

				normals.push_back(Vector3(x, y, z));
				
				norms.push_back(x);
				norms.push_back(y);
				norms.push_back(z); 

			}

			//v-t-n
			if (sLine[0] == 'f')
			{
				vector<string> parts = split(sLine, ' ');
				string a = parts[1];
				string b = parts[2];
				string c = parts[3];

				vector<string> partsFaceOne = split(a, '/');
				vector<string> partsFaceTwo = split(b, '/');
				vector<string> partsFaceThree = split(c, '/');

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

				//get 3 normals
				Vector3 NormalA = normals[td.n[0] - 1];
				Vector3 NormalB = normals[td.n[1] - 1];
				Vector3 NormalC = normals[td.n[2] - 1];
				
				//Calculate final normal
				Vector3 finalNormal = calculateNormal(NormalA, NormalB, NormalC); 

				//push the final calculated normal
				norms.push_back(finalNormal.x);
				norms.push_back(finalNormal.y);
				norms.push_back(finalNormal.z);

				triangles.push_back(td);

			}
		}

		file.close();
	}

	vector<float> okay;
	vector<float> indokay;

	int um = Vertexes.size();

	for (int i = 0; i < Vertexes.size(); i++)
	{
		okay.push_back(Vertexes.at(i).position.x);
		okay.push_back(Vertexes.at(i).position.y);
		okay.push_back(Vertexes.at(i).position.z);
		
		//tex
		okay.push_back(Vertexes.at(i).texCoord.x);
		okay.push_back(Vertexes.at(i).texCoord.y);
		//vertices.push_back(Vertexes.at(i).texCoord.x);
		//vertices.push_back(Vertexes.at(i).texCoord.y);

		indokay.push_back(Vertexes.at(i).index);
	}
	
	//TODO http://assimp.sourceforge.net/lib_html/install.html
	newMesh->AddVertices(okay, indices);

	return newMesh;
}

/*

FIX
vertices.clear
next_vertex = 0;

for each face
for each vertex in face
key = fn(position_index,normal_index,texcoord_index)
if vertices.find(key)
new_index = vertex(key).index
else
create vertex from position/normal/texcorrd
store new vertex in vertices with key and next_vertex
new_index = next_vertex
increment next_index
end
save new_index in index buffer
loop

*/