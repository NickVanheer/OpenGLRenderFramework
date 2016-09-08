#include "Mesh.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>  



Mesh::Mesh() 
{
}


Mesh::~Mesh()
{
}

void Mesh::AddVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	AddVertices(vertices, indices, false);
}

//todo hook up shader http://lazyfoo.net/tutorials/SDL/51_SDL_and_modern_opengl/ 
void Mesh::AddVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool calcNormals)
{
	if (calcNormals)
	{
		CalculateNormals(vertices, indices);
	}

	size = indices.size();



	//data
	// VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * Vertex::SIZE * sizeof(float), GetFloatVector(vertices).data(), GL_STATIC_DRAW);

	//structure
	glGenBuffers(1, &gVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVAO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}
float thing = 0.0f;
void Mesh::Draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float), 0); //vertex
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float), (void*)12); //texture
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float), (void*)20); //normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * sizeof(float), (void*)32); //tangent

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVAO);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void Mesh::CalculateNormals(std::vector<Vertex> & vertices, std::vector<unsigned int> indices)
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices.at(i);
		int i1 = indices.at(i + 1);
		int i2 = indices.at(i + 2);

		Vector3 v1 = vertices.at(i1).GetPosition() - vertices.at(i0).GetPosition();
		Vector3 v2 = vertices.at(i2).GetPosition() - vertices.at(i0).GetPosition();

		Vector3 normal = v1.cross(v2).normalized();

		vertices.at(i0).normal = vertices.at(i0).normal + normal;
		vertices.at(i1).normal = vertices.at(i1).normal + normal;
		vertices.at(i2).normal = vertices.at(i2).normal + normal;
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices.at(i).normal = vertices.at(i).normal.normalized();
	}

}



