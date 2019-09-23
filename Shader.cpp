#include "pch.h"
#include "Shader.h"

Shader::Shader()
{
	//Success flag
	bool success = true;

	//Generate program
	gProgramID = glCreateProgram();

	if (gProgramID == 0)
	{
		//shader creation failed couldn't find decent value for shader
		cout << "Error creating shader and assigning shader ID." << endl;
	}
}

Shader::~Shader()
{
	delete material;
}

void Shader::AddVertexShader(const string& text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::AddFragmentShader(const string& text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::AddGeometryShader(const string& text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}


void Shader::CompileShader()
{
	//compile is already taken care of in addProgram
	glLinkProgram(gProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", gProgramID);
		printProgramLog(gProgramID);
		//success = false;
	}

	
	glValidateProgram(gProgramID);
	printf("Compiled!\n");
}

int Shader::AddUniform(const string& uniform)
{
	int uniformLocation = glGetUniformLocation(gProgramID, uniform.c_str());
	
	if (uniformLocation == 0xFFFFFFFF)
		LOGERROR("Could not find uniform variable: " + uniform);

	std::pair<string, int> newUniform(uniform, uniformLocation);
	uniforms.insert(newUniform);

	return uniformLocation;
}

void Shader::Bind()
{
	glUseProgram(gProgramID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniformInt(const string& uniformName, int value)
{
	//TODO: check if key exists
	glUniform1i(uniforms.at(uniformName), value);
}

void Shader::SetUniformFloat(const string& uniformName, float value)
{
	//make sure program is in use (Bind())
	//TODO: check if key exists
	int index = uniforms.at(uniformName);
	glUniform1f(index, value);

}

void Shader::SetAttributeLocation(const string& attribName, int location)
{
	glBindAttribLocation(gProgramID, location, attribName.c_str());
}


void Shader::SetUniformVector(const string& uniformName, Vector3 value)
{
	//TODO: check if key exists
	glUniform3f(uniforms.at(uniformName), value.x, value.y, value.z);
}

void Shader::SetUniformMatrix(const string& uniformName, Matrix4 value)
{
	//third paramater->transpose
	float ma[16] = {	1,0,0,1,
						0,1,0,1,
						0,0,1,0,
						0,0,0,1 };

	//glUniformMatrix4fv(uniforms.at(uniformName), 1, true, ma);

	std::unordered_map<std::string, int>::const_iterator has = uniforms.find(uniformName); //TODO: remove because overhead?

	if (has == uniforms.end())
	{
		//uniform not found
		cout << uniformName << " not found" << endl;
	}
	else
	{
		glUniformMatrix4fv(uniforms.at(uniformName), 1, true, value.CalculateSingleArray());
	}

}

void Shader::SetUniformBool(const string& uniformName, bool value)
{
	glUniform1i(uniforms.at(uniformName), value);
}

void Shader::SetMaterial(Material* m)
{
	this->material = m;
}

Material* Shader::GetMaterial()
{
	return material;
}

void Shader::UpdateUniforms(Transform& transform, GameContext gameContext)
{
}

void Shader::PostDrawUpdateUniforms(Transform& transform, GameContext gameContext)
{
	//assert(false);
}


void Shader::addProgram(const std::string& text, int type)
{
	int shader = glCreateShader(type); //actually a gluint

	if (shader == 0)
	{
		//error
	}

	//Set source
	const char *cstring = text.c_str();
	glShaderSource(shader, 1, &cstring, NULL);
	glCompileShader(shader);

	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile fragment shader %d!\n", shader);
		printShaderLog(shader);
		//success = false;
	}


	/*
	//GLint status = 0;
	//glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == 0)
	{
		//glGetShaderInfoLog(shader, )
	}
	*/

	glAttachShader(gProgramID, shader);
}

void Shader::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

RenderEngine& Shader::GetRenderEngine() const
{
	return *renderEngine;
}
void Shader::SetRenderEngine(RenderEngine* renderEngine)
{
	this->renderEngine = renderEngine; 
}

void Shader::printProgramLog(GLuint shader)
{
}
