#pragma once
#include "Helpers.h" //GameContext //TODO cleanup
class GameObject;
class Shader;

class BaseGame
{
public:
	BaseGame();
	~BaseGame();
	GameObject* GetRoot();

protected:
	virtual void Initialize();
	virtual void Input(GameContext gameContext);
	virtual void Render(GameContext gameContext);
	virtual void Update(GameContext gameContext);
private:
	GameObject* root;
	Shader* shader;

};

