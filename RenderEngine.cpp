#include "RenderEngine.h"
#include "GameObject.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"

RenderEngine::RenderEngine()
{
	InitGraphics();
	
	//TODO get from CoreEngine
	float width = WINDOW_WIDTH;
	float height = WINDOW_HEIGHT;
	mainCamera = new Camera((float)TO_RADIANS(70.0f), width / height, 0.01f, 1000.0f);
	ambientLight = Vector3(0.2f, 0.2f, 0.2f);

	Vector3 dLightDirection = Vector3(0.3f,1,0);
	directionalLight = DirectionalLight(BaseLight(Vector3(1, 1, 1), 0.9f), dLightDirection);
	pointLight = PointLight(BaseLight(Vector3(0, 1, 0), 0.9f), Attenuation(0, 0, 1), Vector3(0, 0, 0), 100);
	
	//shader init

	forwardAmbient = new ForwardAmbient(); 
	forwardAmbient->SetRenderEngine(this);


	forwardDirectional = new ForwardDirectional();
	forwardDirectional->SetRenderEngine(this);

	forwardPoint = new ForwardPoint(); 
	forwardPoint->SetRenderEngine(this);



}

void RenderEngine::Initialize()
{
	//shader used to be here, now constructor only called after window is initialized
}

RenderEngine::~RenderEngine()
{
}

Vector3 RenderEngine::GetAmbientLight()
{
	return ambientLight;
}

DirectionalLight RenderEngine::GetDirectionalLight()
{
	return directionalLight;
}

PointLight RenderEngine::GetPointLight()
{
	return pointLight;
}

void RenderEngine::Input(float delta)
{

}


void RenderEngine::Render(GameObject* object, GameContext gameContext)
{
	ClearScreen();
	const GameContext c = GameContext();

	//OutputDebugString("gheloo");
	object->Render(c, forwardAmbient);

	//enable correct blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE); //existing color times one, new color times one -> so add
	glDepthMask(false); //disables writing to depth buffer [pixel check to draw or not draw]
	glDepthFunc(GL_EQUAL); //only adds to pixel when exact same depth value -> only do lighting calculations for pixels that make it into the final image

	object->Render(c, forwardPoint);
	
	//reset
	glDepthFunc(GL_LESS); //default, only add pixels when less
	glDepthMask(true);
	glDisable(GL_BLEND);

}

void RenderEngine::clearScreen()
{

}


void RenderEngine::ClearScreen()
{
	//todo stencil buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::InitGraphics()
{
	//return;
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_FRAMEBUFFER_SRGB);
}

void RenderEngine::SetMainCamera(Camera* cam)
{
	mainCamera = cam;
}

Camera* RenderEngine::GetMainCamera()
{
	return mainCamera;
}

//TODO::fix
char * RenderEngine::GetOpenGLVersion()
{
	if (SDL_GL_GetCurrentContext() == NULL)
	{
		//todo trigger assert
		int i = 0;
	}

	auto glver = glGetString(GL_VERSION);

	return (char*)glver;
}

void RenderEngine::EnableTextures(bool enabled)
{
	enabled ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	enabled ? glEnable(GL_TEXTURE_3D) : glDisable(GL_TEXTURE_3D);
}

void RenderEngine::UnbindTextures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderEngine::SetClearColor(Vector3 color)
{
	glClearColor(color.x, color.y, color.z, 1);
}

void RenderEngine::DrawGrid(int halfGridSize)
{
/*
	for (int i = -halfGridSize; i <= halfGridSize; i++)
	{
		glVertex3f((float)i, 0, (float)-halfGridSize);
		glVertex3f((float)i, 0, (float)halfGridSize);

		glVertex3f((float)-halfGridSize, 0, (float)i);
		glVertex3f((float)halfGridSize, 0, (float)i);
	}

*/


}