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

	//FLOOR
	meshFloor = ResourceLoader::LoadModel("resources/models/bigplane.obj");

	materialFloor = new Material("FloorMaterial");
	materialFloor->Color = Vector3(0.8, 0.8, 0.8);
	materialFloor->SpecularPower = 0.3;
	materialFloor->SpecularIntensity = 1.2;
	materialFloor->SetTexture(ResourceLoader::LoadTexture("resources/textures/Wall.png"));
	materialFloor->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/Wall_Spec.png"));
	materialFloor->SetNormalMap(ResourceLoader::LoadTexture("resources/textures/Wall_Normal.png"));

	MeshRenderer* meshRendererFloor = new MeshRenderer(meshFloor, materialFloor);
	
	//
	gOFloor = new GameObject();
	gOFloor->AddComponent(meshRendererFloor);
	gOFloor->GetTransform()->SetPosition(0, -1, 2);
	gOFloor->GetTransform()->SetRotation(-0, 0, 0);
								   
	AddToGame(gOFloor);

	//BOX
	meshBox = ResourceLoader::LoadModel("resources/models/cube.obj");

	//box material
	materialBox = new Material("BoxMaterial");
	materialBox->Color = Vector3(1.0, 1.0, 1.0);
	materialBox->SpecularPower = 3;
	materialBox->SpecularIntensity = 2;
	materialBox->SetTexture(ResourceLoader::LoadTexture("resources/textures/TrainFloor.png"));
	materialBox->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Spec.png"));
	materialBox->SetNormalMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Normal.png"));

	MeshRenderer* meshRendererBox = new MeshRenderer(meshBox, materialBox);

	//
	gOBox = new GameObject();
	gOBox->AddComponent(meshRendererBox);
	gOBox->GetTransform()->SetPosition(0, 0, 0);
	//gO->GetTransform()->Scale(0, RandomFloat(1, 3) , 0);
	AddToGame(gOBox);

	//zoom out
	mainCamera->Move(mainCamera->GetForward(), -2);
}

void Game::Input(GameContext gameContext)
{
	float movAmount = gameContext.deltaTime;
	float rotAmount = gameContext.deltaTime;

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
		mainCamera->MoveForward(movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_S))
		mainCamera->MoveForward(-movAmount);

	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
		mainCamera->MoveLeft(movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_D))
		mainCamera->MoveRight(movAmount);

	if (inputManager->IsKeyDown(SDL_SCANCODE_LEFT))
		mainCamera->RotateY(-rotAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
		mainCamera->RotateY(rotAmount);

	if (inputManager->IsKeyDown(SDL_SCANCODE_UP))
		mainCamera->MoveUp(movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_DOWN))
		mainCamera->MoveUp(-movAmount);
}

void Game::Update(GameContext gameContext)
{
	BaseGame::Update(gameContext);
	float y = gOFloor->GetTransform()->GetRotation().y;
	gOFloor->GetTransform()->SetRotation(0, y + gameContext.deltaTime * 5, 0);
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
	//Root GameObjects and Components destroyed in BaseGame's destructor.
}