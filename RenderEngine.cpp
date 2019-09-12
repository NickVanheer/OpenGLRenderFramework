#include "RenderEngine.h"
#include "GameObject.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "PhongShader.h"
#include "GrassShader.h"
#include "Window.h"

bool RenderEngine::isWireFrame = false;
RenderEngine::RenderEngine() 
{
	InitGraphics();
	
	//TODO get from CoreEngine
	float width = WINDOW_WIDTH;
	float height = WINDOW_HEIGHT;
	mainCamera = new Camera((float)TO_RADIANS(70.0f), width / height, 0.01f, 1000.0f);
	ambientLight = Vector3(0.4f, 0.4f, 0.4f);

	Vector3 baseColor = Vector3(1, 1, 1);
	float lightIntensity = 0.1f;
	Vector3 dLightDirection = Vector3(-0.3f,-0.3,-0.3f);
	directionalLight = DirectionalLight(BaseLight(baseColor, lightIntensity), dLightDirection);
	pointLight = PointLight(BaseLight(Vector3(0, 1, 0), 0.9f), Attenuation(0, 0, 1), Vector3(0, 0, -2), 100);
	
	//shader init
	forwardAmbient = new ForwardAmbient(); 
	forwardAmbient->SetRenderEngine(this);

	forwardDirectional = new ForwardDirectional();
	forwardDirectional->SetRenderEngine(this);

	forwardPoint = new ForwardPoint(); 
	forwardPoint->SetRenderEngine(this);

	//PhongShader
	phongShader = new PhongShader();
	phongShader->SetRenderEngine(this);
	PhongShader::AmbientLight = Vector3(0.1f, 0.1f, 0.1f);
	PhongShader::LightDirectional = DirectionalLight(BaseLight(baseColor, lightIntensity), dLightDirection);

	//GrassShader
	GrassShader::AmbientLight = Vector3(0.1f, 0.1f, 0.1f);
	GrassShader::LightDirectional = DirectionalLight(BaseLight(baseColor, lightIntensity), dLightDirection);
	
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

 DirectionalLight& RenderEngine::GetDirectionalLight()
{
	return directionalLight;
}

 PointLight& RenderEngine::GetPointLight()
{
	return pointLight;
}

void RenderEngine::Input(float delta)
{

}

void RenderEngine::ToggleWireframe()
{
	isWireFrame = !isWireFrame;
}

void RenderEngine::Render(GameObject* object, GameContext gameContext)
{
	mainWindow->BindAsRenderTarget();
	ClearScreen();

	if (isWireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	object->Render(gameContext, phongShader);
	return;

	//Forward rendering
	glDisable(GL_BLEND);
	object->Render(gameContext, forwardAmbient);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE); //existing color times one, new color times one -> so add
	glDepthMask(false); //disables writing to depth buffer [pixel check to draw or not draw]
	glDepthFunc(GL_EQUAL); //only adds to pixel when exact same depth value -> only do lighting calculations for pixels that make it into the final image

	//do multiple light passes here
	object->Render(gameContext, forwardDirectional);
	object->Render(gameContext, forwardPoint);
	
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
	glClearColor(0.7f, 0.7f, 0.7f, 1.f);

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

void RenderEngine::SetMainWindow(std::shared_ptr<Window> window)
{
	this->mainWindow = window;
}

Camera& RenderEngine::GetMainCamera() const
{
	return *mainCamera;
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

