#include "Core.h" //Always at the top

#include "Game.h"
#include "Mesh.h"
#include "Helpers.h"
#include "Shader.h"
#include "Camera.h"
#include "BasicShader.h"
#include "PhongShader.h"
#include "ForwardAmbient.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "GameObject.h"

/*
Features:	
- SDL for window handling and input
- Core classes for common 3D objects
- Texture and OBJ model loader (wip)
- Shader support and basic camera/lighting
- forward rendering support
- Directional light, point light, specular light and specular map support
- Some example OBJs and textures included.


General TODOs:
- Wrap major classes in core header (wip)
- Separate rendering code from game code (done)
- Destructor cleanup and fixes
- Naming conventions
- Component/GameObject system (done)
- General code cleanup and framework improvements
- Improving rendering materials: normal map (done)
- Shadows
- Geometry shader
- Improved texture IDs and smoothing group-based normals (done)
- Fix references

www.nickvanheer.com 
nickvanheer at live.be
*/

Game::Game() : BaseGame()
{
	
}


Game::~Game()
{
	Cleanup();
}


void Game::Initialize()
{
	BaseGame::Initialize();

	//box model TODO: flip in code flag
	meshBox = ResourceLoader::LoadModel("resources/models/cube.obj");

	//box material
	materialBox = new Material();
	materialBox->Color = Vector3(1.0, 1.0, 1.0);
	materialBox->SpecularPower = 3;
	materialBox->SpecularIntensity = 2;
	materialBox->SetTexture(ResourceLoader::LoadTexture("resources/textures/TrainFloor.png"));
	materialBox->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Spec.png"));
	materialBox->SetNormalMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Normal.png"));

	//floor
	meshFloor = ResourceLoader::LoadModel("resources/models/bigplane.obj");

	materialFloor = new Material();
	materialFloor->Color = Vector3(0.8, 0.8, 0.8);
	materialFloor->SpecularPower = 2;
	materialFloor->SpecularIntensity = 2;
	materialFloor->SetTexture(ResourceLoader::LoadTexture("resources/textures/Wall.png"));
	materialFloor->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/Wall_Spec.png"));
	//materialFloor->SetNormalMap(ResourceLoader::LoadTexture("resources/textures/Wall_Normal.jpg"));

	MeshRenderer* meshRendererFloor = new MeshRenderer(meshFloor, materialFloor);
	
	//
	gOFloor = new GameObject();
	gOFloor->AddComponent(meshRendererFloor);
	gOFloor->GetTransform()->SetPosition(0, -1, 2);
	gOFloor->GetTransform()->SetRotation(-90, 0, 0);
								   
	GetRoot()->AddChild(gOFloor);
	generateBoxes();

	//zoom out
	mainCamera->Move(mainCamera->GetForward(), -2);
}

void Game::Stop()
{

}

void Game::Input(GameContext gameContext)
{

	float movAmount = gameContext.deltaTime * 2;
	float rotAmount = gameContext.deltaTime;

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
		mainCamera->Move(mainCamera->GetForward(), movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_S))
		mainCamera->Move(mainCamera->GetForward(), -movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
		mainCamera->Move(mainCamera->GetLeft(), movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_D))
		mainCamera->Move(mainCamera->GetRight(), movAmount);

	if (inputManager->IsKeyDown(SDL_SCANCODE_LEFT))
		mainCamera->RotateY(-rotAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
		mainCamera->RotateY(rotAmount);

	if (inputManager->IsKeyDown(SDL_SCANCODE_UP))
		mainCamera->Move(mainCamera->GetUp(), movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_DOWN))
		mainCamera->Move(mainCamera->GetUp(), -movAmount);
}

float temp = 0.0f;
GameContext okay;
void Game::Update(GameContext gameContext)
{
	BaseGame::Update(okay);
}

void Game::generateBoxes()
{
	int count = 1;
	MeshRenderer* meshRendererBox = new MeshRenderer(meshBox, materialBox);

	//
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; j++)
		{
			GameObject* gO = new GameObject();
			gO->AddComponent(meshRendererBox);
			gO->GetTransform()->SetPosition(i * 4, 0, j * 4);
			//gO->GetTransform()->Scale(0, RandomFloat(1, 3) , 0);
			GetRoot()->AddChild(gO);
		}

	}

}

void Game::Cleanup()
{
	delete gOFloor;
}

