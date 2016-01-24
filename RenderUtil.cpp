#include "Core.h"
#include "RenderUtil.h"




RenderUtil::RenderUtil()
{
}


RenderUtil::~RenderUtil()
{
}

void RenderUtil::ClearScreen()
{
	
	//todo stencil buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::InitGraphics()
{
	//return;
	glClearColor(0.01f, 0.01f, 0.01f, 1.f);
	
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

//TODO::fix
char * RenderUtil::GetOpenGLVersion()
{
	if (SDL_GL_GetCurrentContext() == NULL)
	{
		//trigger assert
		//LOGERROR("gg");
		int i = 0;
	}

	auto glver = glGetString(GL_VERSION);
	//TCHAR* chars = glver;

	return (char*)glver;
}

void RenderUtil::EnableTextures(bool enabled)
{
	enabled ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	enabled ? glEnable(GL_TEXTURE_3D) : glDisable(GL_TEXTURE_3D);
}

void RenderUtil::UnbindTextures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderUtil::SetClearColor(Vector3 color)
{
	glClearColor(color.x, color.y, color.z, 1);
}

std::vector<float> RenderUtil::GetFloatVector(vector<Vertex> vertices)
{
	vector<float> verts;

	for (int i = 0; i < vertices.size(); i++)
	{
		verts.push_back(vertices.at(i).position.x);
		verts.push_back(vertices.at(i).position.y);
		verts.push_back(vertices.at(i).position.z);

		//tex
		verts.push_back(vertices.at(i).texCoord.x);
		verts.push_back(vertices.at(i).texCoord.y);

		//n
		verts.push_back(vertices.at(i).normal.x);
		verts.push_back(vertices.at(i).normal.y);
		verts.push_back(vertices.at(i).normal.z);

	}

	return verts;

}
