#include "RenderEngine.h"
#include "GameObject.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"

RenderEngine::RenderEngine()
{
	
}

void RenderEngine::Initialize()
{
	shader = new BasicShader();
	fwAmbientShader = new ForwardAmbient();
}

RenderEngine::~RenderEngine()
{
}

Vector3 RenderEngine::GetAmbientLight()
{
	return NULL;
}

void RenderEngine::Input(float delta)
{

}

void RenderEngine::Render(GameObject* object)
{
	const GameContext c = GameContext();
	object->Draw(c, fwAmbientShader);
}

void RenderEngine::clearScreen()
{

}
