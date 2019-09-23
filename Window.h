#pragma once
#include "pch.h"

class InputManager;
class Window
{
public:
	Window();
	~Window();

	void CreateWindow(int width, int height, const char* title);
	void Render();
	void Close();
	void DrawText(std::string text);
	bool IsCloseRequested();
	const int GetWidth() const;
	const int GetHeight() const;
	const Vector2 GetCenter() const;

	//
	void BindAsRenderTarget();

	bool SetInputManager(std::shared_ptr<InputManager> inputManager);

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//OpenGL context
	SDL_GLContext gContext;

private:
	bool isCloseRequested = false;
	std::shared_ptr<InputManager> inputManager;
	int width;
	int height;

}; 

