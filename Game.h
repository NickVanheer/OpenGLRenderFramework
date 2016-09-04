#pragma once
#include "Core.h"

class Mesh;
class Material;
class GameObject;

class Game : public BaseGame
{
public:
	Game();
	virtual ~Game();
	void Initialize();
	void Stop();
	void Input(GameContext gameContext);
	virtual void Update(GameContext gameContext);
	void Cleanup();

private:
	//floor
	Mesh* meshFloor;
	Material* materialFloor;
	GameObject* gOFloor;

	//box
	Mesh* meshBox;
	Material* materialBox;
	GameObject* gOBox;
};

