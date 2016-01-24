#include "Core.h"
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
	}

}


Shader::~Shader()
{
	delete material;
}

void Shader::AddVertexShader(string text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::AddFragmentShader(string text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::AddGeometryShader(string text)
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
}

void Shader::AddUniform(string uniform)
{
	int uniformLocation = glGetUniformLocation(gProgramID, uniform.c_str());
	
	if (uniformLocation == 0xFFFFFFFF)
		LOGERROR("Could not find uniform variable: " + uniform);

	std::pair<string, int> newUniform(uniform, uniformLocation);
	uniforms.insert(newUniform);

}

void Shader::Bind()
{
	glUseProgram(gProgramID);
}

void Shader::SetUniformInt(string uniformName, int value)
{
	//TODO: check if key exists
	glUniform1i(uniforms.at(uniformName), value);
}

void Shader::SetUniformFloat(string uniformName, float value)
{
	//make sure program is in use (Bind())
	//TODO: check if key exists
	int index = uniforms.at(uniformName);
	glUniform1f(index, value);

}


void Shader::SetUniformVector(string uniformName, Vector3 value)
{
	//TODO: check if key exists
	glUniform3f(uniforms.at(uniformName), value.x, value.y, value.z);
}

float * test()
{
	float ma[16] = { 1,0,0,0,
					 0,1,0,0,
					 0,0,1,0,
					 0,0,0,1 };
	return ma;
}

void Shader::SetUniformMatrix(string uniformName, Matrix4 value)
{
	//third paramater->transpose
	float ma[16] = {	1,0,0,1,
						0,1,0,1,
						0,0,1,0,
						0,0,0,1 };

	//glUniformMatrix4fv(uniforms.at(uniformName), 1, true, ma);

	glUniformMatrix4fv(uniforms.at(uniformName), 1, true, value.CalculateSingleArray());
}

void Shader::SetUniformBool(string uniformName, bool value)
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

void Shader::UpdateUniforms(Matrix4 worldMatrix, Matrix4 projectionMatrix)
{
}



void Shader::TestRemove()
{
	//Success flag
	bool success = true;
	


	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
	"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
	printf("Unable to compile vertex shader %d!\n", vertexShader);
	printShaderLog(vertexShader);
	success = false;
	}

	//Attach vertex shader to program
	glAttachShader(gProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Get fragment source
	const GLchar* fragmentShaderSource[] =
	{
	"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.0, 1.0, 1.0 ); }"
	};

	//Set fragment source
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

	//Compile fragment source
	glCompileShader(fragmentShader);

	//Check fragment shader for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
	{
	printf("Unable to compile fragment shader %d!\n", fragmentShader);
	printShaderLog(fragmentShader);
	success = false;
	}

	//Attach fragment shader to program
	glAttachShader(gProgramID, fragmentShader);


	//Link program
	glLinkProgram(gProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
	printf("Error linking program %d!\n", gProgramID);
	printProgramLog(gProgramID);
	success = false;
	}

	//Initialize clear color
	glClearColor(1.f, 0.f, 0.f, 1.f);
	

	
}

void Shader::addProgram(std::string text, int type)
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

void Shader::printProgramLog(GLuint shader)
{
}
