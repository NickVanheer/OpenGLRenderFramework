// Author:
// Title: Vertex
#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec2 VTexUV;
out vec3 Vnormal;

void main()
{
	VTexUV = texCoords;
	Vnormal = normal;
	gl_Position = vec4(position, 1.0);
}