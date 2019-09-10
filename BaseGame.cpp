#include "BaseGame.h"
#include "GameObject.h"
#include "BasicShader.h"

BaseGame::BaseGame() 
{

}

BaseGame::~BaseGame()
{
	delete m_Root; //All root objects deleted here.
}

GameObject * BaseGame::GetRoot()
{
	if (m_Root == nullptr)
		m_Root = new GameObject();
	return m_Root;
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

void BaseGame::SetInputManager(std::shared_ptr<InputManager> inputManager)
{
	this->m_InputManager = inputManager;
}

void BaseGame::SetMainCamera(Camera* mainCam)
{
	this->m_MainCamera = mainCam;
}

void BaseGame::AddToGame(std::shared_ptr<GameObject> gameObject)
{
	GetRoot()->AddChild(gameObject);
}

