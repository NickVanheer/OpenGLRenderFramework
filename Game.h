#pragma once
#include "Transform.h"
class Mesh;
class Shader;
class Camera;
class InputManager;
class Texture;
class Material;


class Game
{
public:
	Game();
	virtual ~Game();
	void Start();
	void Stop();
	void Input();
	void Update();
	void Render();
	void Cleanup();
	void SetInputManager(InputManager* inputManager);
private:
	Mesh* mesh;
	Shader* shader;
	Transform transform;
	Camera* camera;
	InputManager* inputManager;
	Texture* texture;

	Material* material;


	//floor
	Mesh* meshFloor;
	Shader* shaderFloor;
	Transform transformFloor;
	Material* materialFloor;
};

