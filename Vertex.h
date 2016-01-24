#pragma once
#include "Vector3.h"

class Vertex
{
public:
	Vertex();
	Vertex(Vector3 position);
	Vertex(Vector3 position, Vector3 texCoord);
	Vertex(Vector3 position, Vector3 texCoord, Vector3 normal);
	Vertex(float x, float y, float z);

	Vector3 GetPosition();
	void SetPosition(Vector3 vec);
	
	virtual ~Vertex();
	static const int SIZE = 8;
	Vector3 position;
	Vector3 texCoord;
	Vector3 normal;
	int index;
private:

};

