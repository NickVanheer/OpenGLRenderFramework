#pragma once

#include "Vector3.h"

#include <tchar.h>

#include <vector>
#include "Vertex.h"
#include "Camera.h"
#include "RenderUtil.h"


class GameObject;
class Shader;
class Camera;
class Window;


class RenderEngine
{
public:
	RenderEngine();
	virtual ~RenderEngine();

	void Input(float delta);
	void Render(GameObject* object, GameContext gameContext);
	Shader* shader;
	void Initialize();

	//
	void SetMainCamera(Camera* cam);
	Camera* GetMainCamera() const;
	Vector3 GetAmbientLight();
	DirectionalLight GetDirectionalLight();
	PointLight GetPointLight();

	void SetMainWindow(Window* cam);


	//
	static void ClearScreen();

	static void InitGraphics();

	static char* GetOpenGLVersion();

	static void EnableTextures(bool enabled);
	static void UnbindTextures();

	static void SetClearColor(Vector3 color);
	static void DrawGrid(int halfGridSize);

	

private:
	void clearScreen();

	//
	Vector3 ambientLight;
	DirectionalLight directionalLight;
	PointLight pointLight;
	Camera* mainCamera;

	Shader* forwardAmbient;
	Shader* forwardDirectional;
	Shader* forwardPoint;

	Window* mainWindow;
	
};

