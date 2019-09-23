#pragma once
#include "pch.h"

#include <unordered_map>
#include "Material.h"
#include "RenderEngine.h"

class RenderEngine;

using namespace std;
class Shader
{
public:
	Shader();
	virtual ~Shader();
	void AddVertexShader(const string& text);
	void AddFragmentShader(const string& text);
	void AddGeometryShader(const string& text);
	void CompileShader();
	int AddUniform(const string& uniform);
	void Bind();
	void Unbind();

	void SetUniformInt(const string& uniformName, int value);
	void SetUniformFloat(const string& uniformName, float value);
	void SetUniformVector(const string& uniformName, Vector3 value);
	void SetUniformMatrix(const string& uniformName, Matrix4 value);
	void SetUniformBool(const string& uniformName, bool value);
	void SetMaterial(Material* m);
	void SetAttributeLocation(const string& attribName, int location);

	//
	RenderEngine& GetRenderEngine() const;
	void SetRenderEngine(RenderEngine* renderEngine);

	virtual Shader* GetInstance() = 0;
	Material* GetMaterial();

	virtual void UpdateUniforms(Transform& transform, GameContext gameContext);
	virtual void PostDrawUpdateUniforms(Transform& transform, GameContext gameContext);

private:
	void addProgram(const string& text, int type);
	void printShaderLog(GLuint shader);
	void printProgramLog(GLuint shader);
	std::unordered_map<string, int> uniforms;
protected: 
	Material* material;
	Shader* instance;
	int gProgramID;
	RenderEngine* renderEngine;



};

