#pragma once
#include <vector>
#include "Core.h"
#include "Vertex.h"


class Mesh
{
public:
	Mesh();
	virtual ~Mesh();
	void AddVertices(std::vector<Vertex> vertices, const std::vector<unsigned int>& indices);
	void AddVertices(std::vector<Vertex> vertices, const std::vector<unsigned int>& indices, bool calcNormals);
	void Draw();
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO;
	GLuint gVAO;
	GLuint texcoordBuffer;
	GLuint normalBuffer;

	void CalculateNormals(std::vector<Vertex> & vertices, std::vector<unsigned int> indices);
	int size;
};

