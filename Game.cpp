#include "Core.h" //Always at the top

#include "Game.h"
#include "Mesh.h"
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
- Component/GameObject system (done)
- General code cleanup and framework improvements
- Improving rendering materials: cubemap, normal map
- Shadows
- Geometry shader
- Improved texture IDs and smoothing group-based normals

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
	materialBox->Color = Vector3(0.0, 0.0, 0.0);
	materialBox->SpecularPower = 4;
	materialBox->SpecularIntensity = 4;
	materialBox->SetTexture(ResourceLoader::LoadTexture("resources/textures/bluefield.jpg"));
	//materialBox->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Spec.png"));

	//floor
	meshFloor = ResourceLoader::LoadModel("resources/models/bigplane.obj");

	materialFloor = new Material();
	materialFloor->Color = Vector3(0.8, 0.8, 0.8);
	materialFloor->SpecularPower = 4;
	materialFloor->SpecularIntensity = 2;
	materialFloor->SetTexture(ResourceLoader::LoadTexture("resources/textures/Wall.png"));
	materialFloor->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Spec.png"));

	//RenderUtil::EnableTextures(true);

	MeshRenderer* meshRendererFloor = new MeshRenderer(meshFloor, materialFloor);
	MeshRenderer* meshRendererBox = new MeshRenderer(meshBox, materialBox);
	
	//
	gOFloor = new GameObject();
	gOFloor->AddComponent(meshRendererFloor);
	gOFloor->GetTransform()->SetPosition(0, -2, 3);

	gOBox = new GameObject();
	gOBox->AddComponent(meshRendererBox);
	gOBox->GetTransform()->SetPosition(0, 0, 3);
	
	//
												   
	//GetRoot()->AddChild(gOBox);
	GetRoot()->AddChild(gOFloor);
}

void Game::Stop()
{

}

void Game::Input(GameContext gameContext)
{

	float movAmount = gameContext.deltaTime * 10;
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

	//TODO: Sort of broken
	if (inputManager->IsKeyDown(SDL_SCANCODE_UP))
		mainCamera->Move(mainCamera->GetUp(), movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_DOWN))
		mainCamera->Move(mainCamera->GetUp(), -movAmount);
}

float temp = 0.0f;
GameContext okay;
void Game::Update(GameContext gameContext)
{
	temp += gameContext.deltaTime;
	
	//gOBox->GetTransform()->SetRotation(sin(temp) * 90, sin(temp) * 180, 0);

	BaseGame::Update(okay);
	//GetRoot()->Update(okay);
}


/*
void Game::Render()
{
	//BaseGame::Render(okay);
	//GetRoot()->Draw(okay);
	return;

	//Torus
	shader->Bind(); //use shader program
	shader->SetMaterial(material); //set material
	shader->UpdateUniforms(transform->GetTransformation(), transform->GetProjectedTransformation()); //update shader variables and its material variables

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);
	mesh->Draw(); //program is unbound in the above draw method


	//Floor
	shaderFloor->SetMaterial(materialFloor); //set material
	shaderFloor->UpdateUniforms(transformFloor->GetTransformation(), transformFloor->GetProjectedTransformation()); //update shader variables and its material variables

	meshFloor->Draw();

}
*/

void Game::Cleanup()
{
	delete gOFloor;
	delete gOBox;
}

