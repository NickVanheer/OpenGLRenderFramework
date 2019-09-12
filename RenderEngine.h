#pragma once

#include "Vector3.h"

#include <tchar.h>

#include <vector>
#include "Vertex.h"
#include "Camera.h"
#include "RenderUtil.h"
#include <memory>

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
	Camera& GetMainCamera() const;

	Vector3 GetAmbientLight();
	DirectionalLight& GetDirectionalLight();
	PointLight& GetPointLight();

	void SetMainWindow(std::shared_ptr<Window> window);

	//
	static void ClearScreen();

	static void InitGraphics();
	static void ToggleWireframe();
	static char* GetOpenGLVersion();

	static void EnableTextures(bool enabled);
	static void UnbindTextures();

	static void SetClearColor(Vector3 color);

private:
	void clearScreen();

	//
	Vector3 ambientLight;
	DirectionalLight directionalLight;
	PointLight pointLight;
	Camera* mainCamera;

	Shader* phongShader;
	Shader* forwardAmbient;
	Shader* forwardDirectional;
	Shader* forwardPoint;

	std::shared_ptr<Window> mainWindow;

	static bool isWireFrame;
};

