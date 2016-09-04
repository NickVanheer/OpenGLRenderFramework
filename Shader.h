#include <string>
#include <unordered_map>
#include "Vector3.h"
#include "Matrix4.h"
#include "Material.h"
#include "RenderEngine.h"
#pragma once

class RenderEngine;

using namespace std;
class Shader
{
public:
	Shader();
	virtual ~Shader();
	void AddVertexShader(string text);
	void AddFragmentShader(string text);
	void AddGeometryShader(string text);
	void CompileShader();
	int AddUniform(string uniform);
	void Bind();

	void SetUniformInt(string uniformName, int value);
	void SetUniformFloat(string uniformName, float value);
	void SetUniformVector(string uniformName, Vector3 value);
	void SetUniformMatrix(string uniformName, Matrix4 value);
	void SetUniformBool(string uniformName, bool value);
	void SetMaterial(Material* m);
	void SetAttributeLocation(string attribName, int location);


	//
	RenderEngine* GetRenderEngine();
	void SetRenderEngine(RenderEngine* renderEngine);

	virtual Shader* GetInstance() = 0;
	Material* GetMaterial();

	virtual void UpdateUniforms(Transform* transform);

private:
	int gProgramID;
	
	void addProgram(std::string text, int type);
	void printShaderLog(GLuint shader);
	void printProgramLog(GLuint shader);
	std::unordered_map<string, int> uniforms;
protected: 
	Material* material;
	Shader* instance;
	RenderEngine* renderEngine;



};

