#include <string>
#include <unordered_map>
#include "Vector3.h"
#include "Matrix4.h"
#include "Material.h"
#pragma once


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
	void AddUniform(string uniform);
	void Bind();

	void SetUniformInt(string uniformName, int value);
	void SetUniformFloat(string uniformName, float value);
	void SetUniformVector(string uniformName, Vector3 value);
	void SetUniformMatrix(string uniformName, Matrix4 value);
	void SetUniformBool(string uniformName, bool value);
	void SetMaterial(Material* m);
	Material* GetMaterial();

	virtual void UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix);

	void TestRemove();
private:
	int gProgramID;
	void addProgram(std::string text, int type);
	void printShaderLog(GLuint shader);
	void printProgramLog(GLuint shader);
	std::unordered_map<string, int> uniforms;
protected: 
	Material* material;


};

