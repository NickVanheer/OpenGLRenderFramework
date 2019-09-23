#include "pch.h"

static std::vector<float> GetFloatVector(std::vector<Vertex> vertices)
{
	std::vector<float> verts;

	for (int i = 0; i < vertices.size(); i++)
	{
		verts.push_back(vertices.at(i).position.x);
		verts.push_back(vertices.at(i).position.y);
		verts.push_back(vertices.at(i).position.z);

		//tex
		verts.push_back(vertices.at(i).texCoord.x);
		verts.push_back(vertices.at(i).texCoord.y);

		//n
		verts.push_back(vertices.at(i).normal.x);
		verts.push_back(vertices.at(i).normal.y);
		verts.push_back(vertices.at(i).normal.z);

		//tangents
		verts.push_back(vertices.at(i).tangent.x);
		verts.push_back(vertices.at(i).tangent.y);
		verts.push_back(vertices.at(i).tangent.z);
	}

	return verts;
}
