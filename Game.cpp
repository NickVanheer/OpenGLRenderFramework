#include "Core.h" //Always at the top

#include "Game.h"
#include "Mesh.h"
#include "Helpers.h"
#include "Shader.h"
#include "Camera.h"
#include "BasicShader.h"
#include "GrassShader.h"
#include "PhongShader.h"
#include "ForwardAmbient.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include <memory>

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

Mesh* getGrid(float size, int rows, int columns)
{
	Mesh* mesh = new Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	int index = 0;
	for (int i = 0; i < columns; ++i)
	{
		for (int j = 0; j < rows; j++)
		{
			int s = i * size;
			int t = j * size;
			vertices.push_back(Vertex(s, 0, t, (float)j / (float)rows, (float)i / (float)columns));
			vertices.push_back(Vertex(s + size, 0, t + size, (float)j / (float)columns, (float)i / (float)columns));
			vertices.push_back(Vertex(s + size, 0, t, (float)j / (float)columns, (float)i / (float)columns));

			vertices.push_back(Vertex(s, 0, t, (float)j / (float)rows, (float)i / (float)columns));
			vertices.push_back(Vertex(s, 0, t + size, (float)j / (float)rows, (float)i / (float)columns));
			vertices.push_back(Vertex(s + size, 0, t + size, (float)j / (float)rows, (float)i / (float)columns));

			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + 2);

			indices.push_back(index + 3);
			indices.push_back(index + 4);
			indices.push_back(index + 5);

			index += 6;
		}
	
	}

	mesh->AddVertices(vertices, indices);
	return mesh;
}

void Game::Initialize()
{
	BaseGame::Initialize();

	//Box
	meshBox = ResourceLoader::LoadModel("resources/models/teapotflip.obj");

	//box material
	materialBox = new Material("BoxMaterial");
	materialBox->Color = Vector3(1.0, 1.0, 1.0);
	materialBox->SpecularPower = 3;
	materialBox->SpecularIntensity = 1;
	materialBox->SetTexture(ResourceLoader::LoadTexture("resources/textures/TrainFloor.png"));
	//materialBox->SetSpecularMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Spec.png")); //!
	//materialBox->SetNormalMap(ResourceLoader::LoadTexture("resources/textures/TrainFloor_Normal.png"));

	shared_ptr<MeshRenderer> meshRendererBox = make_shared<MeshRenderer>(meshBox, materialBox);
	shared_ptr<GameObject> gameObjectBox = make_shared<GameObject>();

	//Box GameObject
	//gameObjectBox = new GameObject();
	gameObjectBox->AddComponent(meshRendererBox);
	gameObjectBox->GetTransform().SetPosition(0, 15, 0);
	gameObjectBox->GetTransform().Scale(5, 5 , 5);
	AddToGame(gameObjectBox);
	
	//zoom out
	m_MainCamera->SetPosition(Vector3(0, 0, 0));
	m_MainCamera->Move(m_MainCamera->GetForward(), -20);
	m_MainCamera->MoveUp(6);
}


void Game::Input(const GameContext& gameContext)
{
	float movAmount = gameContext.deltaTime * 70;
	float rotAmount = gameContext.deltaTime;
	
	if (m_InputManager->IsKeyDown(SDL_SCANCODE_W))
		m_MainCamera->MoveForward(movAmount);
	if (m_InputManager->IsKeyDown(SDL_SCANCODE_S))
		m_MainCamera->MoveForward(-movAmount);

	if (m_InputManager->IsKeyDown(SDL_SCANCODE_A))
		m_MainCamera->MoveLeft(movAmount);
	if (m_InputManager->IsKeyDown(SDL_SCANCODE_D))
		m_MainCamera->MoveRight(movAmount);

	if (m_InputManager->IsKeyDown(SDL_SCANCODE_LEFT))
		m_MainCamera->RotateY(-rotAmount);
	if (m_InputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
		m_MainCamera->RotateY(rotAmount);

	if (m_InputManager->IsKeyDown(SDL_SCANCODE_UP))
		m_MainCamera->MoveUp(movAmount);
	if (m_InputManager->IsKeyDown(SDL_SCANCODE_DOWN))
		m_MainCamera->MoveUp(-movAmount);
}

void Game::Update(const GameContext& gameContext)
{
	BaseGame::Update(gameContext);
}

void Game::Cleanup()
{
	//Root GameObjects and Components destroyed in BaseGame's destructor.
}