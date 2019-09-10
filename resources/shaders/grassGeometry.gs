#version 420
 
layout(triangles) in;
layout (triangle_strip, max_vertices=120) out;
 
in vec2 VTexUV[3];
in vec3 Vnormal[3];
 
out VertexData {
    vec2 texCoord;
    vec3 normal;
	vec3 color;
	vec3 worldPos;
} VertexOut;
 
uniform float m_Time;
uniform mat3 transform;
uniform mat4 transformProjected;
uniform vec3 eyePos;

bool IsWind = true;
bool drawOriginalGeometry = true;
bool IsDense = true;
float m_WindVelocity = 8;

int maxHeight = 8;
float peakHeight = 2;
float maxWidth = 6;
float clipDistance = 300;

struct VertexInfo
{
	vec3 pos;
	vec3 normal;
	vec2 texCoord;
	vec3 color;
};

//samplers
uniform sampler2D samHeightmap;
uniform sampler2D samNoise; //for randomness like the direction

void CreateVertex(vec3 pos, vec3 normal, vec2 texCoord, vec3 vertcolor)
{
    gl_Position = transformProjected * vec4(pos,1);
	VertexOut.normal = normalize(transform * normal);
    VertexOut.texCoord = texCoord;
	VertexOut.color = vertcolor;

	
    EmitVertex();
}

// Create a vertex with the given matrix and three vertexes
void createTriangle(vec3 A, vec3 B, vec3 C) {
  CreateVertex(A, vec3(0,0,0), vec2(0,0), vec3(0,0,0));
  CreateVertex(B, vec3(0,0,0), vec2(0,0), vec3(0,0,0));
  CreateVertex(C, vec3(0,0,0), vec2(0,0), vec3(0,0,0));
}

void createTriangle(VertexInfo A, VertexInfo B, VertexInfo C) {
  CreateVertex(A.pos, A.normal, A.texCoord, A.color);
  CreateVertex(B.pos, B.normal, B.texCoord, B.color);
  CreateVertex(C.pos, C.normal, C.texCoord, C.color);
}

void CreateGrass(float height, float direction, vec3 pos0, vec3 pos1, vec3 pos2, vec3 normal, vec3 normal2, vec3 normal3)
{
	//NEW and simplified
	//distance check
	vec4 posWorld = transformProjected * vec4(pos0,1);
	float dist = distance(posWorld, vec4(eyePos,1));
	 
	if(dist > clipDistance)
		return;

	//Calculate basepoints to start at
	vec3 basePoint  = ( pos0 + pos1 + pos2 ) / 3; 
	vec3 normalbasepoint = ( normal + normal2 + normal3 ) / 3; 
	
  //direction (skip)
  vec2 dir = vec2(20,20);
  float xAngle = dir.x * 0.015f * maxWidth; //offset from the center at a given direction
  float yAngle = dir.y * 0.015f * maxWidth;
  float grassHeight = height * maxHeight;
  
  float xOffset = maxWidth * 0.1f;
  float yOffset = maxWidth * 0.1f;
  
  //wind
  float windSTR = m_WindVelocity * height * sin(m_Time * 1 * height) * 0.1;
  
  float midCurve = 0.6f;
  float yPos = 0;
  vec3 A = basePoint + vec3(xOffset, yPos, yOffset);
  vec3 B = basePoint + vec3(-xOffset, yPos, -yOffset);
  vec3 C = basePoint + vec3(xOffset * windSTR, yPos + grassHeight * peakHeight, yOffset * windSTR);
  vec3 D = basePoint + vec3(-xOffset * midCurve, yPos + grassHeight, -yOffset * midCurve);
  //vec3 E = basePoint + vec3(windSTR, grassHeight + (grassHeight * peakHeight), windSTR);
 
  vec3 normA = vec3(0,0,0);
  vec3 bottomColor = vec3(30,20,24);
  vec3 midColor = vec3(79,102,56);
  vec3 topColor = vec3(165,188,88);
  
  bottomColor /= 255; //turn the RGB into the right 0-1 value
  midColor /= 255; //turn the RGB into the right 0-1 value
  topColor /= 255; //turn the RGB into the right 0-1 value
  
  VertexInfo vertA = VertexInfo(A, normA, vec2(0.0f,0.0f), bottomColor);
  VertexInfo vertB = VertexInfo(B, normA, vec2(0.0f,0.0f), bottomColor);
  VertexInfo vertC = VertexInfo(C, normA, vec2(0.0f,0.0f), topColor);
  VertexInfo vertD = VertexInfo(D, normA, vec2(0.0f,0.0f), topColor);
  //VertexInfo vertE = VertexInfo(E, normA, vec2(0.0f,0.0f), topColor);

  createTriangle(vertA, vertB, vertC);
  createTriangle(vertB, vertD, vertC);
  //createTriangle(vertC, vertD, vertE);
  EndPrimitive();
}


void main()
{
	if(drawOriginalGeometry)
	{
		//Base mesh
		for(int i = 0; i < gl_in.length(); i++)
		{
			float samplePoint =  texture2D(samHeightmap, VTexUV[i]).r;
			vec4 pos = gl_in[i].gl_Position; 
			gl_Position = transformProjected * pos;
			VertexOut.normal = normalize(transform * Vnormal[i]);
			VertexOut.texCoord = VTexUV[i];
			VertexOut.color = vec3(0.3,0.3,0.3);

			EmitVertex();
		}
		  
		EndPrimitive();
	}
	
	//return;
	if(IsDense)
	{
		vec3 m0 = (vec3(gl_in[0].gl_Position) + vec3(gl_in[1].gl_Position)) * 0.5;
		vec3 m1 = (vec3(gl_in[1].gl_Position) + vec3(gl_in[2].gl_Position)) * 0.5;
		vec3 m2 = (vec3(gl_in[2].gl_Position) + vec3(gl_in[0].gl_Position)) * 0.5;
		
		float samplePoint =  texture2D(samHeightmap, VTexUV[0]).r;
		float samplePoint2 =  texture2D(samHeightmap, VTexUV[1]).r;
		float samplePoint3 =  texture2D(samHeightmap, VTexUV[2]).r;
		
		float directionSamplePoint = texture2D(samHeightmap, VTexUV[0]).r;
		float directionSamplePoint2 = texture2D(samHeightmap, VTexUV[1]).r;
		float directionSamplePoint3 = texture2D(samHeightmap, VTexUV[2]).r;
		
		CreateGrass(samplePoint, directionSamplePoint, m1, gl_in[1].gl_Position.xyz, m0, Vnormal[0].xyz, Vnormal[1].xyz, Vnormal[2].xyz);
		CreateGrass(samplePoint2, directionSamplePoint2, gl_in[0].gl_Position.xyz, m0, m2, Vnormal[0].xyz, Vnormal[1].xyz, Vnormal[2].xyz);
		CreateGrass(samplePoint3, directionSamplePoint3, m2, m1, gl_in[2].gl_Position.xyz, Vnormal[0].xyz, Vnormal[1].xyz, Vnormal[2].xyz);
	}
	else
	{	
		float samplePoint =  texture2D(samHeightmap, VTexUV[0]).r;
		float directionSamplePoint = texture2D(samHeightmap, VTexUV[0]).r;
		CreateGrass(samplePoint, directionSamplePoint, gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz, gl_in[1].gl_Position.xyz, Vnormal[0].xyz, Vnormal[1].xyz, Vnormal[2].xyz);
	}
	
	
}
