#include "BaseGame.h"
#include "GameObject.h"
#include "BasicShader.h"

BaseGame::BaseGame()
{

}


BaseGame::~BaseGame()
{
	delete root;
	delete inputManager;
	delete mainCamera;
}

GameObject * BaseGame::GetRoot()
{
	if (root == nullptr)
		root = new GameObject();
	return root;
}

void BaseGame::Initialize()
{
}

void BaseGame::Input(GameContext gameContext)
{
	//root->Input(gameContext);
}



void BaseGame::Update(GameContext gameContext)
{
	GetRoot()->Update(gameContext);
}

void BaseGame::SetInputManager(InputManager * inputManager)
{
	this->inputManager = inputManager;
}

void BaseGame::SetMainCamera(Camera* mainCam)
{
	this->mainCamera = mainCam;
}

