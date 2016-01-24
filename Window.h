#pragma once
#include "Core.h"
#include <tchar.h>

class InputManager;
class Window
{
public:
	Window();
	~Window();

	void CreateWindow(int width, int height, TCHAR* title);
	void Render();
	void Close();
	bool IsCloseRequested();
	int GetWidth();
	int GetHeight();

	bool LoadImage(SDL_Surface *& image, TCHAR* path);
	bool SetInputManager(InputManager *& inputManager);

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld = NULL;

	//OpenGL context
	SDL_GLContext gContext;

private:
	bool isCloseRequested = false;
	InputManager* inputManager;

};

