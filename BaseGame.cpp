#include "BaseGame.h"
#include "GameObject.h"
#include "BasicShader.h"

BaseGame::BaseGame()
{

}


BaseGame::~BaseGame()
{
}

GameObject * BaseGame::GetRoot()
{
	if (root == nullptr)
		root = new GameObject();
	return root;
}

void BaseGame::Initialize()
{
	shader = new BasicShader();
}

void BaseGame::Input(GameContext gameContext)
{
	//root->Input(gameContext);
}

void BaseGame::Render(GameContext gameContext)
{
	GetRoot()->Draw(gameContext, shader); //fix to not load shader every frame
}

void BaseGame::Update(GameContext gameContext)
{
	GetRoot()->Update(gameContext);
}
