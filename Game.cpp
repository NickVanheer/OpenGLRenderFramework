#include "Core.h" //Always at the top

#include "Game.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "BasicShader.h"
#include "PhongShader.h"
#include "Material.h"

/*
General TODOs:
- Wrap major classes in core header
- Component/GameObject system
- General code cleanup and framework improvements
- Improving rendering materials: cubemap, normal map, Skybox
- Shadows
- Geometry shader
- Improved texture IDs and smoothing group-based normals
- Transition to PBR

www.nickvanheer.com 
nickvanheer @ live.be
*/

Game::Game()
{
	mesh = new Mesh();
	shader = new PhongShader();

	camera = new Camera();
	camera->Move(Vector3(0, 1, 0), 1);
	transform = Transform();
	
	//TODO: Get window reference height/width
	transform.SetProjection(Main::WIDTH, Main::HEIGHT, 60, 1000, 0.1);
	transform.SetCamera(camera);

	Vector3 baseColor = Vector3(1, 1, 1);
	Vector3 lightDirection = Vector3(1, 1, 0);
	float lightIntensity = 2.3;

	//lighting setup
	//TODO: Make getters and setters instead of statics
	PhongShader::AmbientLight = Vector3(0.1f, 0.1f, 0.1f);
	PhongShader::LightDirectional = DirectionalLight(BaseLight(baseColor, lightIntensity), lightDirection);

	//model TODO: flip in code flag
	mesh = ResourceLoader::LoadModel("resources/models/torusflipped.obj");
	
	//material
	material = new Material();
	material->Color = Vector3(0.2, 0.2, 0.8);
	material->SpecularPower = 30;
	material->SpecularIntensity = 5;
	material->SetTexture(ResourceLoader::LoadTexture("resources/textures/tiles.png"));
	RenderUtil::EnableTextures(true);
}


Game::~Game()
{
	Cleanup();
}


void Game::Start()
{
	Update();
}

void Game::Stop()
{

}

void Game::Input()
{
	float movAmount = Time::getDelta() * 10;
	float rotAmount = Time::getDelta() * 400;

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
		camera->Move(camera->GetForward(), movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_S))
		camera->Move(camera->GetForward(), -movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
		camera->Move(camera->GetLeft(), movAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_D))
		camera->Move(camera->GetRight(), movAmount);


	if (inputManager->IsKeyDown(SDL_SCANCODE_LEFT))
		camera->RotateY(-rotAmount);
	if (inputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
		camera->RotateY(rotAmount);
	
}

float temp = 0.0f;
void Game::Update()
{
	temp += (float)Time::getDelta();
	transform.SetTranslation(0, 1, 2);
	transform.SetRotation(sin(temp) * 180, 0, 0);
	transform.SetScale(0.5, 0.5, 0.5);
}

void Game::Render()
{
	shader->Bind(); //use shader program
	shader->SetMaterial(material); //set material
	shader->UpdateUniforms(transform.GetTransformation(), transform.GetProjectedTransformation()); //update shader variables and its material variables
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);
	mesh->Draw(); //program is unbound in the above draw method
}

void Game::Cleanup()
{
	delete mesh;
	delete shader; //deletes texture and material
	delete camera;
	delete inputManager;
}

void Game::SetInputManager(InputManager * inputManager)
{
	this->inputManager = inputManager;
}