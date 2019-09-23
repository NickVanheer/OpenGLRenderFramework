#pragma once
#include "BaseGame.h"

class Mesh;
class Material;
class GameObject;
class BaseGame;

class Game : public BaseGame
{
public:
	Game();
	virtual ~Game();
	void Initialize();
	void Input(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext) override;
	void Cleanup();

private:
	//box
	Mesh* meshBox;
	Material* materialBox;
	GameObject* gOBox;
};

