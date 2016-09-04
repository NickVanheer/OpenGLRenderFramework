#pragma once
#include "Helpers.h" //GameContext //TODO cleanup
#include "Camera.h"
class GameObject;
class InputManager;
class Shader;


class BaseGame
{
public:
	BaseGame();
	virtual ~BaseGame();
	GameObject* GetRoot();
	virtual void Initialize();
	virtual void Input(GameContext gameContext);
	//virtual void Render(GameContext gameContext);
	virtual void Update(GameContext gameContext);
	void SetInputManager(InputManager* inputManager);
	void SetMainCamera(Camera* mainCam);

protected:
	GameObject* root;
	InputManager* inputManager;
	Camera* mainCamera;
	//Shader* shader;

};

