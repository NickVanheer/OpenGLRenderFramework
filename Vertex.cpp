#include "Vertex.h"




Vertex::Vertex()
{
}

Vertex::Vertex(Vector3 position)
{
	this->position = position;
	this->texCoord = Vector3(0, 0, 0);
	this->normal = Vector3(0, 0, 0);
	this->tangent = Vector3(0, 0, 0);
}

Vertex::Vertex(Vector3 position, Vector3 texCoord)
{
	Vertex(position, texCoord, Vector3(0, 0, 0), Vector3(0, 0, 0));
}

Vertex::Vertex(Vector3 position, Vector3 texCoord, Vector3 normal)
{
	this->position = position;
	this->texCoord = texCoord;
	this->normal = normal;
	this->tangent = Vector3(0, 0, 0);
}

Vertex::Vertex(Vector3 position, Vector3 texCoord, Vector3 normal, Vector3 tangent)
{
	this->position = position;
	this->texCoord = texCoord;
	this->normal = normal;
	this->tangent = tangent;
}


Vertex::Vertex(float x, float y, float z)
{
	this->position = Vector3(x, y, z);
}

Vector3 Vertex::GetPosition()
{
	return position;
}

void Vertex::SetPosition(Vector3 vec)
{
	position = vec;
}

Vertex::~Vertex()
{
}
