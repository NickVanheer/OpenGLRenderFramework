#pragma once
#include "Core.h"

class Mesh;
class Shader;
class Camera;
class InputManager;
class Texture;
class Material;
class GameObject;

class Game : public BaseGame
{
public:
	Game();
	virtual ~Game();
	void Initialize();
	void Stop();
	void Input();
	void Update();
	/*void Render();*/ //done in renderengine
	void Cleanup();
	void SetInputManager(InputManager* inputManager);
private:
	Mesh* mesh;
	Shader* shader;
	Transform* transform;
	Camera* camera;
	InputManager* inputManager;
	Texture* texture;

	Material* material;


	//floor
	Mesh* meshFloor;
	Shader* shaderFloor;
	Transform* transformFloor;
	Material* materialFloor;


	GameObject* gOBox;

};

