#pragma once
#include "Helpers.h" //GameContext //TODO cleanup
#include "Camera.h"
#include <memory>

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
	void SetInputManager(std::shared_ptr<InputManager> inputManager);
	void SetMainCamera(Camera* mainCam);

	void AddToGame(std::shared_ptr<GameObject> gO);



protected:
	GameObject* m_Root;
	std::shared_ptr<InputManager> m_InputManager;
	Camera* m_MainCamera;
	//Shader* shader;

};

