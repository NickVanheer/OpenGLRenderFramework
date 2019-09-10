// Author:
// Title: Fragment

#version 330

in VertexData {
    vec2 texCoord;
    vec3 normal;
	vec3 color;
	vec3 worldPos;
} VertexIn;

in vec3 vertColor; 
in vec2 texUV;
out vec4 fragColor;

struct BaseLight
{
	vec3 color;
	float intensity;
};

uniform vec3 ambientLight;
uniform vec3 baseColor;
uniform bool useTexture;
uniform sampler2D samDiffuse;

void main()
{   
	//vec4 totalLight = vec4(ambientLight, 1);
	vec4 color = vec4(VertexIn.color, 1);
	fragColor = color;
}